#include "pch.h"
#include "script_runtime.h"

using namespace sol;

namespace hoodie_script {

	lua_State* script_runtime::_luaState = nullptr;
	ParamPatcher* script_runtime::paramPatcher = nullptr;
	goods_use_hook* script_runtime::goodsUseHook = nullptr;
	hkb_animation_hook* script_runtime::hkbAnimationHook = nullptr;
	game_frame_hook* script_runtime::gameFrameHook = nullptr;
	session_send_hook* script_runtime::sessionsendhook = nullptr;
	has_speffect_hook* script_runtime::hasspeffecthook = nullptr;
	jumptable_hook* script_runtime::jumptable_hook = nullptr;
	hksEnvGetter_hook* script_runtime::hksget_hook = nullptr;
	hksActSetter_hook* script_runtime::hksActSet_hook = nullptr;

	void script_runtime::InitializeFunctionLuaBindings()
	{
		state_view lua(_luaState);
		LuaBindings::initializeClasses(lua);
		LuaBindings::initializeEnums(lua);
		LuaBindings::initializeStaticFunctions(lua);
	}



	void script_runtime::initialize()
	{
		//Generate Instances of Hooks
		goodsUseHook = new hoodie_script::goods_use_hook();
		hkbAnimationHook = new hoodie_script::hkb_animation_hook();
		gameFrameHook = new hoodie_script::game_frame_hook();
		//sessionsendhook = new hoodie_script::session_send_hook();
		hasspeffecthook = new hoodie_script::has_speffect_hook();
		jumptable_hook = new hoodie_script::jumptable_hook();
		hksget_hook = new hoodie_script::hksEnvGetter_hook();
		hksActSet_hook = new hoodie_script::hksActSetter_hook();

		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		_luaState = L;
		InitializeFunctionLuaBindings();
		script_runtime::paramPatcher = new ParamPatcher();
		OnParamLoaded::DoOnParamLoaded(_luaState);
	}

	void script_runtime::initializeHooks()
	{
		//Install hooks
		goodsUseHook->install();
		hkbAnimationHook->install();
		//sessionsendhook->install();
		hasspeffecthook->install();
		jumptable_hook->install();
		hksget_hook->install();
		hksActSet_hook->install();

		//Important that this is hook installed last
		gameFrameHook->install();
	}

	void script_runtime::refreshHooks()
	{
		//Avoid refreshing game frame hook for now, seems to cause crashes.
		//gameFrameHook->tryRefresh();

		goodsUseHook->tryRefresh();
		hkbAnimationHook->tryRefresh();
		//sessionsendhook->tryRefresh();
		hasspeffecthook->tryRefresh();
		jumptable_hook->tryRefresh();
		hksget_hook->tryRefresh();
		hksActSet_hook->tryRefresh();
	}

	void script_runtime::deinitializeHooks()
	{
		//Important that this is installed and uninstalled first
		gameFrameHook->uninstall();

		goodsUseHook->uninstall();
		hkbAnimationHook->uninstall();
		//sessionsendhook->uninstall();
		hasspeffecthook->uninstall();
		jumptable_hook->uninstall();
		hksget_hook->uninstall();
		hksActSet_hook->uninstall();
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
		auto mainChrPtr = PlayerIns::getMainChrAddress();
		auto mainChr = PlayerIns(mainChrPtr);
		if (mainChr.getHkbCharacter() == hbkCharacter)
		{
			return OnHkbAnimation::DoOnHkbAnimation(_luaState, mainChrPtr, animationId);
		}
		else
		{
			return animationId;
		}
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
		ImGui_ImplDX11_NewFrame();
		HotKeyManager::Update();
		OnHotKey::DoOnHotkey(_luaState);
		OnRenderingFrame::DoOnRenderingFrame(_luaState);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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