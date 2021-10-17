#include "pch.h"
#include "script_runtime.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "GameObjects/player_ins.h"
#include "GameObjects/chr_ins.h"

namespace hoodie_script {

	class MyClass
	{
	public:
		float value;
		MyClass(float valueFun);
		float GetValue();
	private:

	};

	MyClass::MyClass(float valueFun)
	{
		value = valueFun;
	}

	float MyClass::GetValue()
	{
		return value;
	}

	lua_State* script_runtime::_luaState = nullptr;

	void script_runtime::InitializeFunctionLuaBindings()
	{
		lua_getglobal(_luaState, "_G");

		//Define print()
		static const struct luaL_Reg printlib[] = { {"print", Luaprint}, {NULL, NULL} };
		luaL_setfuncs(_luaState, printlib, 0);

		//Define SubscribeToEventOnParamLoaded
		lua_register(_luaState, "SubscribeToEventOnParamLoaded", OnParamLoaded::SubscribeToEventOnParamLoaded);

		//Define SubscribeToEventOnGameFrame
		lua_register(_luaState, "SubscribeToEventOnGameFrame", OnGameFrame::SubscribeToEventOnGameFrame);

		//Define SubscribeToEventOnAnimationId
		lua_register(_luaState, "SubscribeToEventOnHkbAnimation", OnHkbAnimation::SubscribeToEventOnHkbAnimation);

		lua_pop(_luaState, 1);

		luabridge::getGlobalNamespace(_luaState)
			.beginClass<MyClass>("MyClass")
			.addData<float>("value", &MyClass::value)
			.addFunction("method", &MyClass::GetValue)
			.endClass();

		luabridge::getGlobalNamespace(_luaState)
			.beginClass <ChrIns>("ChrIns")
			.addFunction("isValid", &ChrIns::isValid)
			.addFunction("getHandle", &ChrIns::getHandle)
			.addFunction("getChrType", &ChrIns::getChrType)
			.addFunction("setChrType", &ChrIns::setChrType)
			.addFunction("getTeam", &ChrIns::getTeam)
			.addFunction("setTeam", &ChrIns::setTeam)
			.addFunction("getForwardId", &ChrIns::getForwardId)
			.addFunction("getCharacterString", &ChrIns::getCharacterString)
			.addFunction("getAnimationString", &ChrIns::getAnimationString)
			.addFunction("getAnimationTime", &ChrIns::getAnimationTime)
			.addFunction("getMaxAnimationTime", &ChrIns::getMaxAnimationTime)
			.addFunction("getTurnRate", &ChrIns::getTurnRate)
			.addFunction("getPosition", &ChrIns::getPosition)
			.addFunction("setPosition", &ChrIns::setPosition)
			.addFunction("getAngle", &ChrIns::getAngle)
			.addFunction("getCrossbowAngle", &ChrIns::getCrossbowAngle)
			.addFunction("setAngle", &ChrIns::setAngle)
			.addFunction("getSprjChrDataModule", &ChrIns::getSprjChrDataModule)
			.addFunction("getSprjChrDamageModule", &ChrIns::getSprjChrDamageModule)
			.addFunction("isDead", &ChrIns::isDead)
			.addFunction("setIsDead", &ChrIns::setIsDead)
			.addFunction("isNoGravity", &ChrIns::isNoGravity)
			.addFunction("setNoGravity", &ChrIns::setNoGravity)
			.addFunction("isDodging", &ChrIns::isDodging)
			.addFunction("getHkbCharacter", &ChrIns::getHkbCharacter)
			.addFunction("hasHkbCharacter", &ChrIns::hasHkbCharacter)
			.addFunction("playAnimation", &ChrIns::playAnimation)
			.addFunction("playAnimationString", &ChrIns::playAnimationString)
			.addFunction("getHkbIdFromString", &ChrIns::getHkbIdFromString)
			.addFunction("getHkbStringFromId", &ChrIns::getHkbStringFromId)
			.addFunction("getWeightIndex", &ChrIns::getWeightIndex)
			.addFunction("setWeightIndex", &ChrIns::setWeightIndex)
			.addFunction("setDebugAnimSpeed", &ChrIns::setDebugAnimSpeed)
			.addFunction("getDummyPolyPositions", &ChrIns::getDummyPolyPositions)
			.addFunction("getAddress", &ChrIns::getAddress)
			.addStaticFunction("isChrIns", &ChrIns::isChrIns)
			.endClass()
			.deriveClass<PlayerIns, ChrIns>("PlayerIns")
			.addFunction("getPlayerGameData", &PlayerIns::getPlayerGameData)
			.addFunction("getNetworkPointer", &PlayerIns::getNetworkPointer)
			.addFunction("getLeftHandWeapon", &PlayerIns::getLeftHandWeapon)
			.addFunction("setLeftHandWeapon", &PlayerIns::setLeftHandWeapon)
			.addFunction("getRightHandWeapon", &PlayerIns::getRightHandWeapon)
			.addFunction("setRightHandWeapon", &PlayerIns::setRightHandWeapon)
			.addFunction("getHead", &PlayerIns::getHead)
			.addFunction("setHead", &PlayerIns::setHead)
			.addFunction("getChest", &PlayerIns::getChest)
			.addFunction("setChest", &PlayerIns::setChest)
			.addFunction("getHands", &PlayerIns::getHands)
			.addFunction("setHands", &PlayerIns::setHands)
			.addFunction("getLegs", &PlayerIns::getLegs)
			.addFunction("setLegs", &PlayerIns::setLegs)
			.addFunction("getRing", &PlayerIns::getRing)
			.addFunction("setRing", &PlayerIns::setRing)
			.addFunction("getAmmo", &PlayerIns::getAmmo)
			.addFunction("setAmmo", &PlayerIns::setAmmo)
			.addFunction("getCovenant", &PlayerIns::getCovenant)
			.addFunction("setCovenant", &PlayerIns::setCovenant)
			.addFunction("isNoGoodsConsume", &PlayerIns::isNoGoodsConsume)
			.addFunction("setNoGoodsConsume", &PlayerIns::setNoGoodsConsume)
			.addFunction("getPlayerCtrl", &PlayerIns::getPlayerCtrl)
			.addFunction("getNetworkHandle", &PlayerIns::getNetworkHandle)
			.addFunction("isValid", &PlayerIns::isValid)
			.addStaticFunction("getAddressByOffsetNumber", &PlayerIns::getAddressByOffsetNumber)
			.addStaticFunction("isChrWithOffsetNumber", &PlayerIns::isChrWithOffsetNumber)
			.addStaticFunction("isPlayer", &PlayerIns::isPlayer)
			.addStaticFunction("getMainChrAddress", &PlayerIns::getMainChrAddress)
			.addStaticFunction("isMainChr", &PlayerIns::isMainChr)
			.addStaticFunction("isMainChrLoaded", &PlayerIns::isMainChrLoaded)
			.endClass();

	}

	int script_runtime::Luaprint(lua_State* L) {
		int nargs = lua_gettop(L);

		for (int i = 1; i <= nargs; i++) {
			if (lua_isstring(L, i)) {
				std::cout << lua_tostring(L, i);
			}
			else {
				/* Do something with non-strings if you like */
			}

			if (i == nargs)
			{
				std::cout << std::endl;
			}
		}

		return 0;
	}


	void script_runtime::initialize()
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		_luaState = L;

		InitializeFunctionLuaBindings();
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
		if (luaL_loadfile(_luaState, filePath) != LUA_OK ) {
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
		//MyClass myObject(200); // single instance

		//// lookup script function in global table
		//luabridge::LuaRef processFunc = luabridge::LuaRef::getGlobal(_luaState, "process");

		//if (processFunc.isFunction()) {
		//	processFunc(&myObject);
		//}

		PlayerIns a(hbkCharacter);
		return OnHkbAnimation::DoOnHkbAnimation(_luaState, a ,animationId);
	}

	void script_runtime::on_game_frame()
	{
		OnGameFrame::DoOnGameFrame(_luaState);
	}
}