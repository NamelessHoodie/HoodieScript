#include "pch.h"
#include "pch.h"
#include "script_runtime.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "GameObjects/player_ins.h"
#include "GameObjects/chr_ins.h"

using namespace sol;

namespace hoodie_script {

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

		state_view lua(_luaState);

		// make usertype metatable
		sol::usertype<PlayerIns> player_type = lua.new_usertype<PlayerIns>("PlayerIns", sol::constructors<PlayerIns(uintptr_t)>());
		//PlayerIns : Chr_Ins Members
		player_type["isValid"] = &PlayerIns::isValid;
		player_type["getHandle"] = &PlayerIns::getHandle;
		player_type["ChrType"] = sol::property(&PlayerIns::getChrType, &PlayerIns::setChrType);
		player_type["Team"] = sol::property(&PlayerIns::getTeam, &PlayerIns::setTeam);
		player_type["getForwardId"] = &PlayerIns::getForwardId;
		player_type["getCharacterString"] = &PlayerIns::getCharacterString;
		player_type["getAnimationString"] = &PlayerIns::getAnimationString;
		player_type["getAnimationTime"] = &PlayerIns::getAnimationTime;
		player_type["getMaxAnimationTime"] = &PlayerIns::getMaxAnimationTime;
		player_type["getTurnRate"] = &PlayerIns::getTurnRate;
		player_type["Position"] = sol::property(&PlayerIns::getPosition, &PlayerIns::setPosition);
		player_type["Angle"] = sol::property(&PlayerIns::getAngle, &PlayerIns::setAngle);
		player_type["getCrossbowAngle"] = &PlayerIns::getCrossbowAngle;
		player_type["getSprjChrDataModule"] = &PlayerIns::getSprjChrDataModule;
		player_type["getSprjChrDamageModule"] = &PlayerIns::getSprjChrDamageModule;
		player_type["isDead"] = sol::property(&PlayerIns::isDead, &PlayerIns::setIsDead);
		player_type["isNoGravity"] = sol::property(&PlayerIns::isNoGravity, &PlayerIns::setNoGravity);
		player_type["isDodging"] = &PlayerIns::isDodging;
		player_type["getHkbCharacter"] = &PlayerIns::getHkbCharacter;
		player_type["hasHkbCharacter"] = &PlayerIns::hasHkbCharacter;
		player_type["playAnimation"] = &PlayerIns::playAnimation;
		player_type["playAnimationString"] = &PlayerIns::playAnimationString;
		player_type["getHkbIdFromString"] = &PlayerIns::getHkbIdFromString;
		player_type["getHkbStringFromId"] = &PlayerIns::getHkbStringFromId;
		player_type["WeightIndex"] = sol::property(&PlayerIns::getWeightIndex, &PlayerIns::setWeightIndex);
		player_type["WeightIndex"] = sol::property(&PlayerIns::getWeightIndex, &PlayerIns::setWeightIndex);
		player_type["getHkbIdFromString"] = &PlayerIns::getHkbIdFromString;
		player_type["setDebugAnimSpeed"] = &PlayerIns::setDebugAnimSpeed;
		player_type["getDummyPolyPositions"] = &PlayerIns::getDummyPolyPositions;
		player_type["getAddress"] = &PlayerIns::getAddress;
		player_type["isChrIns"] = &PlayerIns::isChrIns;
		//PlayerIns Members
		player_type["getPlayerGameData"] = &PlayerIns::getPlayerGameData;
		player_type["getNetworkPointer"] = &PlayerIns::getNetworkPointer;
		player_type["ActiveLeftHandWeapon"] = sol::property(&PlayerIns::getLeftHandWeaponActive, &PlayerIns::setLeftHandWeaponActive);
		player_type["ActiveRightHandWeapon"] = sol::property(&PlayerIns::getRightHandWeaponActive, &PlayerIns::setRightHandWeaponActive);
		player_type["getLeftHandWeapon"] = &PlayerIns::getLeftHandWeapon;
		player_type["setLeftHandWeapon"] = &PlayerIns::setLeftHandWeapon;
		player_type["getRightHandWeapon"] = &PlayerIns::getRightHandWeapon;
		player_type["setRightHandWeapon"] = &PlayerIns::setRightHandWeapon;
		player_type["getNetworkPointer"] = &PlayerIns::getNetworkPointer;
		player_type["HeadArmor"] = sol::property(&PlayerIns::getHead, &PlayerIns::setHead);
		player_type["ChestArmor"] = sol::property(&PlayerIns::getChest, &PlayerIns::setChest);
		player_type["HandsArmor"] = sol::property(&PlayerIns::getHands, &PlayerIns::setHands);
		player_type["Legs"] = sol::property(&PlayerIns::getLegs, &PlayerIns::setLegs);
		player_type["getNetworkPointer"] = &PlayerIns::getNetworkPointer;
		player_type["getRing"] = &PlayerIns::getRing;
		player_type["setRing"] = &PlayerIns::setRing;
		player_type["getAmmo"] = &PlayerIns::getAmmo;
		player_type["setAmmo"] = &PlayerIns::setAmmo;
		player_type["ActiveCovenant"] = sol::property(&PlayerIns::getCovenant, &PlayerIns::setCovenant);
		player_type["isNoGoodsConsume"] = sol::property(&PlayerIns::isNoGoodsConsume, &PlayerIns::setNoGoodsConsume);
		player_type["getPlayerCtrl"] = &PlayerIns::getPlayerCtrl;
		player_type["getNetworkHandle"] = &PlayerIns::getNetworkHandle;
		player_type["getAddressByOffsetNumber"] = &PlayerIns::getAddressByOffsetNumber;
		player_type["isChrWithOffsetNumber"] = &PlayerIns::isChrWithOffsetNumber;
		player_type["isPlayer"] = &PlayerIns::isPlayer;
		player_type["isValid"] = &PlayerIns::isValid;
		player_type["getMainChrAddress"] = &PlayerIns::getMainChrAddress;
		player_type["isMainChr"] = &PlayerIns::isMainChr;
		player_type["isMainChrLoaded"] = &PlayerIns::isMainChrLoaded;

		sol::usertype<MyClass> ex = lua.new_usertype<MyClass>("MyClass", sol::constructors<MyClass(float)>());
		ex["Value"] = &MyClass::value;
		ex["GetValue"] = &MyClass::GetValue;


		// typical member function that returns a variable
		//player_type["shoot"] = &player::shoot;

		// gets or set the value using member variable syntax

		// read and write variable
		//player_type["speed"] = &player::speed;
		// can only read from, not write to
		// .set(foo, bar) is the same as [foo] = bar;
		//player_type.set("bullets", sol::readonly(&player::bullets));
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
		auto mainChr = PlayerIns(PlayerIns::getMainChrAddress());
		if (mainChr.getHkbCharacter() == hbkCharacter)
		{
			return OnHkbAnimation::DoOnHkbAnimation(_luaState, mainChr, animationId);
		}
		else
		{
			return animationId;
		}
	}

	void script_runtime::on_game_frame()
	{
		OnGameFrame::DoOnGameFrame(_luaState);
	}
}