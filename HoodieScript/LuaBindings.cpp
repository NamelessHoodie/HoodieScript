#include "pch.h"
#include "LuaBindings.h"

namespace hoodie_script
{
	void LuaBindings::initializeEnums(sol::state_view luaSol)
	{
		luaSol["VK"] = luaSol.create_table_with(
			"NONE", VK::NONE,
			"LBUTTON", VK::LBUTTON,
			"RBUTTON", VK::RBUTTON,
			"CANCEL", VK::CANCEL,
			"MBUTTON", VK::MBUTTON,
			"XBUTTON1M", VK::XBUTTON1M,
			"XBUTTON2M", VK::XBUTTON2M,
			"BACK", VK::BACK,
			"TAB", VK::TAB,
			"CLEAR", VK::CLEAR,
			"RETURN", VK::RETURN,
			"SHIFT", VK::SHIFT,
			"CONTROL", VK::CONTROL,
			"MENU", VK::MENU,
			"PAUSE", VK::PAUSE,
			"CAPITAL", VK::CAPITAL,
			"KANA", VK::KANA,
			"HANGUL", VK::HANGUL,
			"JUNJA", VK::JUNJA,
			"FINAL", VK::FINAL,
			"HANJA", VK::HANJA,
			"KANJI", VK::KANJI,
			"ESCAPE", VK::ESCAPE,
			"CONVERT", VK::CONVERT,
			"NONCONVERT", VK::NONCONVERT,
			"ACCEPT", VK::ACCEPT,
			"MODECHANGE", VK::MODECHANGE,
			"SPACE", VK::SPACE,
			"PRIOR", VK::PRIOR,
			"NEXT", VK::NEXT,
			"END", VK::END,
			"HOME", VK::HOME,
			"LEFT", VK::LEFT,
			"UP", VK::UP,
			"RIGHT", VK::RIGHT,
			"DOWN", VK::DOWN,
			"SELECT", VK::SELECT,
			"PRINT", VK::PRINT,
			"EXECUTE", VK::EXECUTE,
			"SNAPSHOT", VK::SNAPSHOT,
			"INSERT", VK::INSERT,
			"DEL", VK::DEL,
			"HELP", VK::HELP,
			"KEY_0", VK::KEY_0,
			"KEY_1", VK::KEY_1,
			"KEY_2", VK::KEY_2,
			"KEY_3", VK::KEY_3,
			"KEY_4", VK::KEY_4,
			"KEY_5", VK::KEY_5,
			"KEY_6", VK::KEY_6,
			"KEY_7", VK::KEY_7,
			"KEY_8", VK::KEY_8,
			"KEY_9", VK::KEY_9,
			"KEY_A", VK::KEY_A,
			"KEY_B", VK::KEY_B,
			"KEY_C", VK::KEY_C,
			"KEY_D", VK::KEY_D,
			"KEY_E", VK::KEY_E,
			"KEY_F", VK::KEY_F,
			"KEY_G", VK::KEY_G,
			"KEY_H", VK::KEY_H,
			"KEY_I", VK::KEY_I,
			"KEY_J", VK::KEY_J,
			"KEY_K", VK::KEY_K,
			"KEY_L", VK::KEY_L,
			"KEY_M", VK::KEY_M,
			"KEY_N", VK::KEY_N,
			"KEY_O", VK::KEY_O,
			"KEY_P", VK::KEY_P,
			"KEY_Q", VK::KEY_Q,
			"KEY_R", VK::KEY_R,
			"KEY_S", VK::KEY_S,
			"KEY_T", VK::KEY_T,
			"KEY_U", VK::KEY_U,
			"KEY_V", VK::KEY_V,
			"KEY_W", VK::KEY_W,
			"KEY_X", VK::KEY_X,
			"KEY_Y", VK::KEY_Y,
			"KEY_Z", VK::KEY_Z,
			"LWIN", VK::LWIN,
			"RWIN", VK::RWIN,
			"APPS", VK::APPS,
			"SLEEP", VK::SLEEP,
			"NUMPAD0", VK::NUMPAD0,
			"NUMPAD1", VK::NUMPAD1,
			"NUMPAD2", VK::NUMPAD2,
			"NUMPAD3", VK::NUMPAD3,
			"NUMPAD4", VK::NUMPAD4,
			"NUMPAD5", VK::NUMPAD5,
			"NUMPAD6", VK::NUMPAD6,
			"NUMPAD7", VK::NUMPAD7,
			"NUMPAD8", VK::NUMPAD8,
			"NUMPAD9", VK::NUMPAD9,
			"MULTIPLY", VK::MULTIPLY,
			"ADD", VK::ADD,
			"SEPARATOR", VK::SEPARATOR,
			"SUBTRACT", VK::SUBTRACT,
			"DECIMAL", VK::DECIMAL,
			"DIVIDE", VK::DIVIDE,
			"F1", VK::F1,
			"F2", VK::F2,
			"F3", VK::F3,
			"F4", VK::F4,
			"F5", VK::F5,
			"F6", VK::F6,
			"F7", VK::F7,
			"F8", VK::F8,
			"F9", VK::F9,
			"F10", VK::F10,
			"F11", VK::F11,
			"F12", VK::F12,
			"F13", VK::F13,
			"F14", VK::F14,
			"F15", VK::F15,
			"F16", VK::F16,
			"F17", VK::F17,
			"F18", VK::F18,
			"F19", VK::F19,
			"F20", VK::F20,
			"F21", VK::F21,
			"F22", VK::F22,
			"F23", VK::F23,
			"F24", VK::F24,
			"NUMLOCK", VK::NUMLOCK,
			"SCROLL", VK::SCROLL,
			"LSHIFT", VK::LSHIFT,
			"RSHIFT", VK::RSHIFT,
			"LCONTROL", VK::LCONTROL,
			"RCONTROL", VK::RCONTROL,
			"LMENU", VK::LMENU,
			"RMENU", VK::RMENU,
			"BROWSER_BACK", VK::BROWSER_BACK,
			"BROWSER_FORWARD", VK::BROWSER_FORWARD,
			"BROWSER_REFRESH", VK::BROWSER_REFRESH,
			"BROWSER_STOP", VK::BROWSER_STOP,
			"BROWSER_SEARCH", VK::BROWSER_SEARCH,
			"BROWSER_FAVORITES", VK::BROWSER_FAVORITES,
			"BROWSER_HOME", VK::BROWSER_HOME,
			"VOLUME_MUTE", VK::VOLUME_MUTE,
			"VOLUME_DOWN", VK::VOLUME_DOWN,
			"VOLUME_UP", VK::VOLUME_UP,
			"MEDIA_NEXT_TRACK", VK::MEDIA_NEXT_TRACK,
			"MEDIA_PREV_TRACK", VK::MEDIA_PREV_TRACK,
			"MEDIA_STOP", VK::MEDIA_STOP,
			"MEDIA_PLAY_PAUSE", VK::MEDIA_PLAY_PAUSE,
			"LAUNCH_MAIL", VK::LAUNCH_MAIL,
			"LAUNCH_MEDIA_SELECT", VK::LAUNCH_MEDIA_SELECT,
			"LAUNCH_APP1", VK::LAUNCH_APP1,
			"LAUNCH_APP2", VK::LAUNCH_APP2,
			"OEM_1", VK::OEM_1,
			"OEM_PLUS", VK::OEM_PLUS,
			"OEM_COMMA", VK::OEM_COMMA,
			"OEM_MINUS", VK::OEM_MINUS,
			"OEM_PERIOD", VK::OEM_PERIOD,
			"OEM_2", VK::OEM_2,
			"OEM_3", VK::OEM_3,
			"OEM_4", VK::OEM_4,
			"OEM_5", VK::OEM_5,
			"OEM_6", VK::OEM_6,
			"OEM_7", VK::OEM_7,
			"OEM_8", VK::OEM_8,
			"OEM_102", VK::OEM_102,
			"PROCESSKEY", VK::PROCESSKEY,
			"PACKET", VK::PACKET,
			"ATTN", VK::ATTN,
			"CRSEL", VK::CRSEL,
			"EXSEL", VK::EXSEL,
			"EREOF", VK::EREOF,
			"PLAY", VK::PLAY,
			"ZOOM", VK::ZOOM,
			"NONAME", VK::NONAME,
			"PA1", VK::PA1,
			"OEM_CLEAR", VK::OEM_CLEAR
		);
	}
	void LuaBindings::initializeStaticFunctions(sol::state_view luaSol)
	{
		luaSol.set_function("SubscribeToEventOnHkbAnimation", OnHkbAnimation::SubscribeToEventOnHkbAnimation);
		luaSol.set_function("SubscribeToEventOnSpEffect", OnSpeffectActive::SubscribeToEventOnSpEffect);
		luaSol.set_function("SubscribeToEventOnRenderingFrame", OnRenderingFrame::SubscribeToEventOnRenderingFrame);
		luaSol.set_function("SubscribeToEventOnParamLoaded", OnParamLoaded::SubscribeToEventOnParamLoaded);
		luaSol.set_function("SubscribeToEventOnGameFrame", OnGameFrame::SubscribeToEventOnGameFrame);
		luaSol.set_function("RegisterHotkey", OnHotKey::RegisterHotkey);
		luaSol.set_function("UnregisterHotkey", OnHotKey::UnregisterHotkey);
		luaSol.set_function("EntityHasSpeffect", EntityHasSpEffectSafe);
		luaSol.set_function("print", Luaprint);
		luaSol.set_function("WasKeyPressed", HotKeyManager::WasKeyPressed);
		luaSol.set_function("WasKeyReleased", HotKeyManager::WasKeyReleased);

		sol_ImGui::Init(luaSol);
	}
	void LuaBindings::initializeClasses(sol::state_view luaSol)
	{
		sol::usertype<PlayerIns> player_type = luaSol.new_usertype<PlayerIns>("PlayerIns", sol::constructors<PlayerIns(uintptr_t)>());
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
		player_type["hasSpEffect"] = &PlayerIns::hasSpEffect;
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
		//Temporary Members, remember to fix this bad meme
		player_type["ActiveRightHandWeaponNetworked"] = sol::property(&PlayerIns::getRightHandWeaponActive, &PlayerIns::setRightHandWeaponActiveNetworked);
		player_type["setRightHandWeaponNetworked"] = &PlayerIns::setRightHandWeaponNetworked;
		player_type["WeaponSheatState"] = sol::property(&PlayerIns::getWeaponSheathState, &PlayerIns::setWeaponSheathState);
		player_type["RemoveWeaponFromInventory"] = &PlayerIns::removeWeaponFromInventory;
		player_type["ReplaceWeaponNetworked"] = &PlayerIns::ReplaceWeapon;

		sol::usertype<WorldChrMan> world_chr_man = luaSol.new_usertype<WorldChrMan>("WorldChrMan");
		world_chr_man["getCurrentMapEnemies"] = WorldChrMan::getCurrentMapEnemies;
		world_chr_man["reloadCharacterFiles"] = WorldChrMan::reloadCharacterFiles;
		world_chr_man["findEntityTest"] = WorldChrMan::findEntityTest;
		world_chr_man["getInsByHandle"] = WorldChrMan::getInsByHandle;
		world_chr_man["getCamVector"] = WorldChrMan::getCamVector;
		world_chr_man["getInstance"] = WorldChrMan::getInstance;
		world_chr_man["hasInstance"] = WorldChrMan::hasInstance;
	}
	void LuaBindings::Luaprint(sol::variadic_args va, std::string) {
		std::string r = "";
		for (auto v : va) {
			if (v.is<bool>())
			{
				bool value = v;
				r += value ? "True" : "False";
			}
			else
			{
				std::string value = v;
				r += value;
			}
		}
		std::cout << r << std::endl;
	}
	bool LuaBindings::EntityHasSpEffectSafe(unsigned int entityId, int spEffect)
	{
		auto worldChrManPointer = (uintptr_t*)DataBaseAddress::WorldChrMan;
		if (*worldChrManPointer != NULL)
		{
			return call(has_speffect_hook::_instance->get_original(), entityId, spEffect);
		}
		return false;
	}
}