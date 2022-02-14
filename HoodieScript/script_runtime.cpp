#include "pch.h"
#include "script_runtime.h"
#include "LuaObjects/middleclass.c"
#include "script_repository.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "LuaEvents/OnSpeffectActive.h"
#include "LuaEvents/OnRenderingFrame.h"
#include "LuaEvents/OnHotkey.h"
#include "LuaEvents/OnHksAct.h"
#include "LuaEvents/OnPositionUpdate.h"
#include "LuaEvents/OnSessionReceive.h"
#include "LuaEvents/OnSessionSend.h"
#include "GameDebugClasses/world_chr_man.h"
#include "GameObjects/sprj_chr_data_module.h"
#include "LuaBindings.h"
#include <random>
#include "HotKeyManager.h"
#include "GameExtensions/GameExtensionsManager.h"
#include <filesystem>
#include "LuaEvents/LuaStateThreadLock.h"

using namespace sol;

namespace hoodie_script {

	lua_State* script_runtime::_luaState = nullptr;
	ParamPatcher* script_runtime::paramPatcher = nullptr;
	goods_use_hook* script_runtime::goodsUseHook = nullptr;
	hkb_animation_hook* script_runtime::hkbAnimationHook = nullptr;
	game_frame_hook* script_runtime::gameFrameHook = nullptr;
	has_speffect_hook* script_runtime::hasspeffecthook = nullptr;
	OnTaeEvent_hook* script_runtime::onTaeEvent_hook_instance = nullptr;
	hksEnvGetter_hook* script_runtime::hksget_hook = nullptr;
	hksActSetter_hook* script_runtime::hksActSet_hook = nullptr;
	menu_isopen_getter_hook* script_runtime::menu_isopen_getter_hook = nullptr;
	session_send_hook* script_runtime::_session_send_hook_instancePtr = nullptr;
	session_receive_hook* script_runtime::_session_receive_hook_instancePtr = nullptr;
	PositionUpdate_Hook* script_runtime::position_Update_Hook = nullptr;

	bool script_runtime::isGameInputLocked = false;

	void script_runtime::InitializeFunctionLuaBindings()
	{
		state_view lua(_luaState);

		LuaBindings::initializeClasses(lua);
		LuaBindings::initializeEnums(lua);
		LuaBindings::initializeStaticFunctions(lua);
	}

	void script_runtime::InitializeLuaEmbeddedFiles()
	{
		state_view lua(_luaState);

		lua.require_script("classes", _acmiddleclass);
	}

	void script_runtime::initialize()
	{
		//Generate Instances of Hooks
		goodsUseHook = new hoodie_script::goods_use_hook();
		hkbAnimationHook = new hoodie_script::hkb_animation_hook();
		gameFrameHook = new hoodie_script::game_frame_hook();
		hasspeffecthook = new hoodie_script::has_speffect_hook();
		onTaeEvent_hook_instance = new hoodie_script::OnTaeEvent_hook();
		hksget_hook = new hoodie_script::hksEnvGetter_hook();
		hksActSet_hook = new hoodie_script::hksActSetter_hook();
		menu_isopen_getter_hook = new hoodie_script::menu_isopen_getter_hook();
		_session_receive_hook_instancePtr = new session_receive_hook();
		_session_send_hook_instancePtr = new session_send_hook();
		position_Update_Hook = new hoodie_script::PositionUpdate_Hook();

		//LuaStateThreadLock::Lock();
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		_luaState = L;
		InitializeLuaEmbeddedFiles();
		InitializeFunctionLuaBindings();
		LuaSetPath(L);
		GameExtensionManager::registerEmbeddedExtensions();
		//LuaStateThreadLock::Unlock();

		script_runtime::paramPatcher = new ParamPatcher();
		OnParamLoaded::DoOnParamLoaded(_luaState);
	}

	void script_runtime::LuaSetPath(lua_State* L)
	{
		state_view a(L);

		//Read path values
		std::string pathValue = a["package"]["path"];
		std::string cpathValue = a["package"]["cpath"];

		//Declare new paths
		std::string lua_pathStrHoodieScriptsFolder = ";" + script_repository::get_scripts_path() + "/?.lua";
		std::string lua_cpathStrHoodieScriptsFolder = ";" + script_repository::get_scripts_path() + "/?.dll";

		//Assign new paths
		a["package"]["path"] = pathValue + lua_pathStrHoodieScriptsFolder + lua_cpathStrHoodieScriptsFolder;
	}

	void script_runtime::initializeHooks()
	{
		//Install hooks
		goodsUseHook->install();
		hkbAnimationHook->install();
		hasspeffecthook->install();
		onTaeEvent_hook_instance->install();
		hksget_hook->install();
		hksActSet_hook->install();
		menu_isopen_getter_hook->install();
		_session_send_hook_instancePtr->install();
		_session_receive_hook_instancePtr->install();
		position_Update_Hook->install();

		//Important that this hook is installed last, 
		//in order to avoid hook refresh conflicts during initialization.
		gameFrameHook->install();
	}

	void script_runtime::refreshHooks()
	{
		//Avoid refreshing game frame hook for now, seems to cause crashes.
		//gameFrameHook->tryRefresh();

		goodsUseHook->tryRefresh();
		hkbAnimationHook->tryRefresh();
		hasspeffecthook->tryRefresh();
		onTaeEvent_hook_instance->tryRefresh();
		hksget_hook->tryRefresh();
		hksActSet_hook->tryRefresh();
		menu_isopen_getter_hook->tryRefresh();
		_session_send_hook_instancePtr->tryRefresh();
		_session_receive_hook_instancePtr->tryRefresh();
		position_Update_Hook->tryRefresh();

	}

	void script_runtime::deinitializeHooks()
	{
		//LuaStateThreadLock::Lock();

		//Important that this is installed and uninstalled first, 
		//in order to avoid hook refresh conflicts during uinitialization.
		gameFrameHook->uninstall();

		goodsUseHook->uninstall();
		hkbAnimationHook->uninstall();
		hasspeffecthook->uninstall();
		onTaeEvent_hook_instance->uninstall();
		hksget_hook->uninstall();
		hksActSet_hook->uninstall();
		menu_isopen_getter_hook->uninstall();
		_session_send_hook_instancePtr->uninstall();
		_session_receive_hook_instancePtr->uninstall();
		position_Update_Hook->uninstall();

		//LuaStateThreadLock::Unlock();
	}

	void script_runtime::handle_error(lua_State* luaState)
	{
		logging::write_line("Got error: %s", lua_tostring(_luaState, -1));
		lua_pop(_luaState, 1);
	}

	// TODO: cache the loadfile output so we don't do duplicate work
	// TODO: make every lua file have its own state
	bool script_runtime::initialize_file(std::filesystem::path file)
	{
		auto filePath = file.string().c_str();
		if (luaL_loadfile(_luaState, filePath) != LUA_OK) {
			logging::write_line("Could not load LUA file %s", file.string().c_str());
			handle_error(_luaState);
			return false;
		}

		lua_newtable(_luaState);
		lua_newtable(_luaState);
		lua_getglobal(_luaState, "_G");
		lua_setfield(_luaState, -2, "__index");
		lua_setmetatable(_luaState, -2);
		lua_setfield(_luaState, LUA_REGISTRYINDEX, filePath);
		lua_getfield(_luaState, LUA_REGISTRYINDEX, filePath);
		lua_setupvalue(_luaState, 1, 1);



		if (lua_pcall(_luaState, 0, LUA_MULTRET, 0)) {
			logging::write_line("Could not init LUA file %s", file.string().c_str());
			handle_error(_luaState);
			return false;
		}
		return true;
	}

	void script_runtime::on_goods_use(int goodsId) {
		//for (auto file : script_repository::get_files()) {
		//	lua_getglobal(_luaState, "on_goods_use");
		//	lua_pushinteger(_luaState, goodsId);
		//	if (lua_pcall(_luaState, 1, 0, 0) != LUA_OK) {
		//		logging::write_line("Could not invoke LUA %s - on_goods_use", file.string().c_str());
		//		handle_error(_luaState);
		//	}
		//}
	}

	int script_runtime::on_hkb_animation(uintptr_t hbkCharacter, int animationId)
	{
		auto mainChr = PlayerIns::getMainChr();
		if (mainChr.getHkbCharacter() == hbkCharacter)
		{
			return OnHkbAnimation::DoOnHkbAnimation(_luaState, mainChr.getAddress(), animationId);
		}
		else
		{
			return animationId;
		}
	}

	void script_runtime::on_position_update(uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2)
	{
		OnPositionUpdate::DoOnPositionUpdate(_luaState, CsHkCharacterProxy, SprjChrPhysicsModulePtr, unk0, unk1, unk2);
	}

	uint32_t script_runtime::on_network_session_send(uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength)
	{
		return OnSessionSend::DoOnSessionSend(_luaState, networkSession, networkHandle, id, buffer, maxLength);
	}

	uint32_t script_runtime::on_network_session_receive(uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength, uint32_t receiveLength)
	{
		return OnSessionReceive::DoOnSessionReceive(_luaState, networkSession, networkHandle, id, buffer, maxLength, receiveLength);
	}

	double uniform()
	{
		return (double)rand() / RAND_MAX;
	}

	class Solution {
	public:
		Solution(float radius, float x_center, float y_center)
			: _radius(radius), _x(x_center), _y(y_center), _gen(_rd()),
			_radius_distribution(0, ((float)radius)* radius),
			_angle_distribution(0, 2 * M_PI) {}

		std::vector<float> randPoint() {
			float radius = std::sqrt(_radius_distribution(_gen));
			float angle = _angle_distribution(_gen);    return { _x + radius * cos(angle), _y + radius * sin(angle) };
		} private:
			float _radius;
			float _x;
			float _y;
			std::random_device _rd;
			std::mt19937 _gen;
			std::uniform_real_distribution<> _radius_distribution;
			std::uniform_real_distribution<> _angle_distribution;
	};

	void script_runtime::OnRenderFrame()
	{
		HotKeyManager::Update();
		OnHotKey::DoOnHotkey(_luaState);
		OnRenderingFrame::DoOnRenderingFrame(_luaState);
	}

	void script_runtime::on_game_frame()
	{
		static uint64_t uniqueFrameClock = 0;
		//if (uniqueFrameClock % 2 == 0)
		//{



		//	auto plr = PlayerIns(PlayerIns::getMainChrAddress());
		//	logging::write_line(std::to_string(plr.getAddress()));
		//	//entryBullet->set_owner((int32_t)chr.getHandle());
		//	float radius = 50;
		//	auto a = plr.getPosition();
		//	for (size_t i = 0; i < 10; i++)
		//	{
		//		auto entryBullet = new bullet_spawn_request();
		//		entryBullet->set_bullet_param_id((bullet_type)12457000);
		//		entryBullet->set_owner((int32_t)plr.getHandle());
		//		auto b = Solution(radius, a[0], a[2]).randPoint();
		//		entryBullet->set_direction({0,0,0});
		//		a[0] = b[0];
		//		a[2] = b[1];
		//		a[1] += 50;
		//		entryBullet->set_coordinates(a);
		//		bullet_facade::spawn(entryBullet);
		//	}
		//}
		//auto plr = PlayerIns(PlayerIns::getMainChrAddress());
		//auto memes = plr.getDummyPolyPositions(12, 99);
		//for (auto i = memes.begin(); i != memes.end(); i++)
		//{
		//	auto meme = *i;
		//	plr.SpawnBullet(150, {meme[0], meme[1], meme[2], meme[3]});
		//}
		//plr.
		uniqueFrameClock++;
		if (uniqueFrameClock % 2 == 0) {
			OnGameFrame::DoOnGameFrame(_luaState);
			OnSpeffectActive::DoOnSpEffect(_luaState);
		}
		refreshHooks();
	}

	void script_runtime::on_speffect(unsigned int handle, int speffect)
	{
	}
}