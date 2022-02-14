#pragma once
#include "pch.h"
#include "LuaBindings.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "LuaEvents/OnSpeffectActive.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnRenderingFrame.h"
#include "LuaEvents/OnSessionSend.h"
#include "LuaEvents/OnSessionReceive.h"
#include "LuaEvents/OnPositionUpdate.h"
#include "HotKeyManager.h"
#include "LuaObjects/LuaMemory.h"
#include "GameObjects/sprj_chr_data_module.h"
#include <GameObjects/SprjMsgRepositoryImp.h>
#include "GameDebugClasses/world_chr_man.h"
#include <GameDebugClasses/GameFlags.h>
#include "LuaEvents/OnHotkey.h"
#include "LuaEvents/OnHksAct.h"
#include "LuaEvents/OnHksEnv.h"
#include "script_runtime.h"
#include <LuaObjects/LuaArgs.h>

namespace hoodie_script
{
	void LuaBindings::initializeEnums(sol::state_view luaSol)
	{
		luaSol["ItemType"] = luaSol.create_table_with(
			"Weapon", ItemParamIdPrefix::Weapon,
			"Protector", ItemParamIdPrefix::Protector,
			"Accessory", ItemParamIdPrefix::Accessory,
			"Goods", ItemParamIdPrefix::Goods
		);

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

		luaSol["Handle"] = luaSol.create_table_with(
			"MainChr", ChrIns::Handle::MainChr,
			"None", ChrIns::Handle::None
		);
	}
	void LuaBindings::initializeStaticFunctions(sol::state_view luaSol)
	{

		//Lua Events Registration
		luaSol["GameEvents"] = luaSol.create_table_with(
			"SubscribeToEventOnHkbAnimation", OnHkbAnimation::SubscribeToEventOnHkbAnimation,
			"SubscribeToEventOnSpEffect", OnSpeffectActive::SubscribeToEventOnSpEffect,
			"SubscribeToEventOnRenderingFrame", OnRenderingFrame::SubscribeToEventOnRenderingFrame,
			"SubscribeToEventOnParamLoaded", OnParamLoaded::SubscribeToEventOnParamLoaded,
			"SubscribeToEventOnGameFrame", OnGameFrame::SubscribeToEventOnGameFrame,
			"SubscribeToEventOnHksAct", OnHksAct::SubscribeToEventOnHksAct,
			"SubscribeToEventOnHksEnv", OnHksEnv::SubscribeToEventOnHksEnv,
			"SubscribeToEventOnPositionUpdate", OnPositionUpdate::SubscribeToEventOnPositionUpdate,
			"SubscribeToEventOnSessionSend", OnSessionSend::SubscribeToEventOnSessionSend,
			"SubscribeToEventOnSessionReceive", OnSessionReceive::SubscribeToEventOnSessionReceive);

		//Functions
		luaSol.set_function("RegisterHotkey", OnHotKey::RegisterHotkey);
		luaSol.set_function("UnregisterHotkey", OnHotKey::UnregisterHotkey);
		luaSol.set_function("EntityHasSpeffect", EntityHasSpEffectSafe);
		luaSol.set_function("print", Luaprint);
		luaSol.set_function("WasKeyPressed", HotKeyManager::WasKeyPressed);
		luaSol.set_function("WasKeyReleased", HotKeyManager::WasKeyReleased);
		luaSol.set_function("TryLockGameInputs", TryLockGameInputs);
		luaSol.set_function("TryUnlockGameInputs", TryUnlockGameInputs);

		sol_ImGui::Init(luaSol);
	}
	void LuaBindings::initializeClasses(sol::state_view luaSol)
	{
		sol::usertype<PlayerIns> sol_playerins = luaSol.new_usertype<PlayerIns>("PlayerIns", sol::constructors<PlayerIns(uintptr_t)>());
		//PlayerIns : Chr_Ins Members
		sol_playerins["isValid"] = &PlayerIns::isValid;
		sol_playerins["getEntityId"] = &PlayerIns::getEntityId;
		sol_playerins["getHandle"] = &PlayerIns::getHandle;
		sol_playerins["getChrType"] = &PlayerIns::getChrType;
		sol_playerins["setChrType"] = &PlayerIns::setChrType;
		sol_playerins["getTeam"] = &PlayerIns::getTeam;
		sol_playerins["setTeam"] = &PlayerIns::setTeam;
		sol_playerins["getForwardId"] = &PlayerIns::getForwardId;
		sol_playerins["getCharacterString"] = &PlayerIns::getCharacterString;
		sol_playerins["getCharacterId"] = &PlayerIns::getCharacterId;
		sol_playerins["getAnimationString"] = &PlayerIns::getAnimationString;
		sol_playerins["getAnimationTime"] = &PlayerIns::getAnimationTime;
		sol_playerins["getMaxAnimationTime"] = &PlayerIns::getMaxAnimationTime;
		sol_playerins["getTurnRate"] = &PlayerIns::getTurnRate;
		sol_playerins["setPosition"] = &PlayerIns::setPosition;
		sol_playerins["getPosition"] = &PlayerIns::getPosition;
		sol_playerins["setPosition"] = &PlayerIns::setPosition;
		sol_playerins["getAngle"] = &PlayerIns::getAngle;
		sol_playerins["getCrossbowAngle"] = &PlayerIns::getCrossbowAngle;
		sol_playerins["setAngle"] = &PlayerIns::setAngle;
		sol_playerins["getSprjChrDataModule"] = &PlayerIns::getSprjChrDataModule;
		sol_playerins["getSprjChrDamageModule"] = &PlayerIns::getSprjChrDamageModule;
		sol_playerins["isDead"] = &PlayerIns::isDead;
		sol_playerins["setIsDead"] = &PlayerIns::setIsDead;
		sol_playerins["getLockOnTarget"] = &PlayerIns::getLockOnTarget;
		sol_playerins["setLockOnTarget"] = &PlayerIns::setLockOnTarget;
		sol_playerins["getLockOnTargetChrHandle"] = &PlayerIns::getLockOnTargetChrHandle;
		sol_playerins["setLockOnTargetChrHandle"] = &PlayerIns::setLockOnTargetChrHandle;
		sol_playerins["isNoGravity"] = &PlayerIns::isNoGravity;
		sol_playerins["setNoGravity"] = &PlayerIns::setNoGravity;
		sol_playerins["isDodging"] = &PlayerIns::isDodging;
		sol_playerins["getHkbCharacter"] = &PlayerIns::getHkbCharacter;
		sol_playerins["hasHkbCharacter"] = &PlayerIns::hasHkbCharacter;
		sol_playerins["playAnimation"] = &PlayerIns::playAnimation;
		sol_playerins["playAnimationString"] = &PlayerIns::playAnimationString;
		sol_playerins["getHkbIdFromString"] = &PlayerIns::getHkbIdFromString;
		sol_playerins["getHkbStringFromId"] = &PlayerIns::getHkbStringFromId;
		sol_playerins["getWeightIndex"] = &PlayerIns::getWeightIndex;
		sol_playerins["hasSpEffect"] = &PlayerIns::hasSpEffect;
		sol_playerins["setWeightIndex"] = &PlayerIns::setWeightIndex;
		sol_playerins["setDebugAnimSpeed"] = &PlayerIns::setDebugAnimSpeed;
		sol_playerins["getDummyPolyPositions"] = &PlayerIns::getDummyPolyPositions;
		sol_playerins["getAddress"] = &PlayerIns::getAddress;
		sol_playerins["isPlayerOffsetNumber"] = &PlayerIns::isPlayerOffsetNumber;
		sol_playerins["isChrIns"] = &PlayerIns::isChrIns;
		sol_playerins["isPlayableCharacter"] = &PlayerIns::isPlayableCharacter;
		sol_playerins["isNPC"] = &PlayerIns::isNPC;
		sol_playerins["toPlayerIns"] = &PlayerIns::toPlayerIns;
		//PlayerIns Members
		sol_playerins["getPlayerGameData"] = &PlayerIns::getPlayerGameData;
		sol_playerins["hasPlayerGameData"] = &PlayerIns::hasPlayerGameData;
		sol_playerins["getEquipGameData"] = &PlayerIns::getEquipGameData;
		sol_playerins["hasEquipGameData"] = &PlayerIns::hasEquipGameData;
		sol_playerins["getEquipInventoryData"] = &PlayerIns::getEquipInventoryData;
		sol_playerins["hasEquipInventoryData"] = &PlayerIns::hasEquipInventoryData;
		sol_playerins["getNetworkPointer"] = &PlayerIns::getNetworkPointer;
		sol_playerins["isNoGoodsConsume"] = &PlayerIns::isNoGoodsConsume;
		sol_playerins["setNoGoodsConsume"] = &PlayerIns::setNoGoodsConsume;
		sol_playerins["getPlayerCtrl"] = &PlayerIns::getPlayerCtrl;
		sol_playerins["getNetworkHandle"] = &PlayerIns::getNetworkHandle;
		sol_playerins["isValid"] = &PlayerIns::isValid;
		sol_playerins["getMainChr"] = PlayerIns::getMainChr;
		sol_playerins["isMainChr"] = &PlayerIns::isMainChr;
		sol_playerins["isMainChrLoaded"] = PlayerIns::isMainChrLoaded;

		sol::usertype<WorldChrMan> sol_worldchrman = luaSol.new_usertype<WorldChrMan>("WorldChrMan");
		sol_worldchrman["getCurrentMapEnemies"] = WorldChrMan::getCurrentMapEnemies;
		sol_worldchrman["reloadCharacterFiles"] = WorldChrMan::reloadCharacterFiles;
		sol_worldchrman["findEntityTest"] = WorldChrMan::findEntityTest;
		sol_worldchrman["getInsByHandle"] = WorldChrMan::getInsByHandle;
		sol_worldchrman["getCamVector"] = WorldChrMan::getCamVector;
		sol_worldchrman["getMainChr"] = WorldChrMan::getMainChr;
		sol_worldchrman["isMainChrLoaded"] = WorldChrMan::isMainChrLoaded;
		sol_worldchrman["getPlayerByOffsetNumber"] = WorldChrMan::getPlayerByOffsetNumber;
		sol_worldchrman["isLoaded"] = WorldChrMan::isLoaded;
		sol_worldchrman["getAddress"] = WorldChrMan::getAddress;

		sol::usertype<ChrIns> sol_chrins = luaSol.new_usertype<ChrIns>("ChrIns", sol::constructors<ChrIns(uintptr_t)>());
		sol_chrins["isValid"] = &ChrIns::isValid;
		sol_chrins["getEntityId"] = &ChrIns::getEntityId;
		sol_chrins["getHandle"] = &ChrIns::getHandle;
		sol_chrins["getChrType"] = &ChrIns::getChrType;
		sol_chrins["setChrType"] = &ChrIns::setChrType;
		sol_chrins["getTeam"] = &ChrIns::getTeam;
		sol_chrins["setTeam"] = &ChrIns::setTeam;
		sol_chrins["getForwardId"] = &ChrIns::getForwardId;
		sol_chrins["getCharacterString"] = &ChrIns::getCharacterString;
		sol_chrins["getCharacterId"] = &ChrIns::getCharacterId;
		sol_chrins["getAnimationString"] = &ChrIns::getAnimationString;
		sol_chrins["getAnimationTime"] = &ChrIns::getAnimationTime;
		sol_chrins["getMaxAnimationTime"] = &ChrIns::getMaxAnimationTime;
		sol_chrins["getTurnRate"] = &ChrIns::getTurnRate;
		sol_chrins["setPosition"] = &ChrIns::setPosition;
		sol_chrins["getPosition"] = &ChrIns::getPosition;
		sol_chrins["setPosition"] = &ChrIns::setPosition;
		sol_chrins["getAngle"] = &ChrIns::getAngle;
		sol_chrins["getCrossbowAngle"] = &ChrIns::getCrossbowAngle;
		sol_chrins["setAngle"] = &ChrIns::setAngle;
		sol_chrins["getSprjChrDataModule"] = &ChrIns::getSprjChrDataModule;
		sol_chrins["getSprjChrDamageModule"] = &ChrIns::getSprjChrDamageModule;
		sol_chrins["isDead"] = &ChrIns::isDead;
		sol_chrins["setIsDead"] = &ChrIns::setIsDead;
		sol_chrins["setLockOnTarget"] = &ChrIns::setLockOnTarget;
		sol_chrins["setLockOnTargetChrHandle"] = &ChrIns::setLockOnTargetChrHandle;
		sol_chrins["isNoGravity"] = &ChrIns::isNoGravity;
		sol_chrins["setNoGravity"] = &ChrIns::setNoGravity;
		sol_chrins["isDodging"] = &ChrIns::isDodging;
		sol_chrins["getHkbCharacter"] = &ChrIns::getHkbCharacter;
		sol_chrins["hasHkbCharacter"] = &ChrIns::hasHkbCharacter;
		sol_chrins["playAnimation"] = &ChrIns::playAnimation;
		sol_chrins["playAnimationString"] = &ChrIns::playAnimationString;
		sol_chrins["getHkbIdFromString"] = &ChrIns::getHkbIdFromString;
		sol_chrins["getHkbStringFromId"] = &ChrIns::getHkbStringFromId;
		sol_chrins["getWeightIndex"] = &ChrIns::getWeightIndex;
		sol_chrins["hasSpEffect"] = &ChrIns::hasSpEffect;
		sol_chrins["setWeightIndex"] = &ChrIns::setWeightIndex;
		sol_chrins["setDebugAnimSpeed"] = &ChrIns::setDebugAnimSpeed;
		sol_chrins["getDummyPolyPositions"] = &ChrIns::getDummyPolyPositions;
		sol_chrins["getAddress"] = &ChrIns::getAddress;
		sol_chrins["isPlayerOffsetNumber"] = &ChrIns::isPlayerOffsetNumber;
		sol_chrins["isChrIns"] = &ChrIns::isChrIns;
		sol_chrins["isPlayableCharacter"] = &ChrIns::isPlayableCharacter;
		sol_chrins["isNPC"] = &ChrIns::isNPC;
		sol_chrins["toPlayerIns"] = &ChrIns::toPlayerIns;

		sol::usertype<SprjChrDataModule> sol_sprjchrdatamodule = luaSol.new_usertype<SprjChrDataModule>("SprjChrDataModule", sol::constructors<SprjChrDataModule(uintptr_t)>());
		sol_sprjchrdatamodule["getHealth"] = &SprjChrDataModule::getHealth;
		sol_sprjchrdatamodule["setHealth"] = &SprjChrDataModule::setHealth;
		sol_sprjchrdatamodule["getStamina"] = &SprjChrDataModule::getStamina;
		sol_sprjchrdatamodule["setStamina"] = &SprjChrDataModule::setStamina;
		sol_sprjchrdatamodule["getFP"] = &SprjChrDataModule::getFP;
		sol_sprjchrdatamodule["setFP"] = &SprjChrDataModule::setFP;
		sol_sprjchrdatamodule["getMaxHealth"] = &SprjChrDataModule::getMaxHealth;
		sol_sprjchrdatamodule["setMaxHealth"] = &SprjChrDataModule::setMaxHealth;
		sol_sprjchrdatamodule["getMaxStamina"] = &SprjChrDataModule::getMaxStamina;
		sol_sprjchrdatamodule["setMaxStamina"] = &SprjChrDataModule::setMaxStamina;
		sol_sprjchrdatamodule["getMaxFP"] = &SprjChrDataModule::getMaxFP;
		sol_sprjchrdatamodule["setMaxFP"] = &SprjChrDataModule::setMaxFP;
		sol_sprjchrdatamodule["getBaseMaxHealth"] = &SprjChrDataModule::getBaseMaxHealth;
		sol_sprjchrdatamodule["setBaseMaxHealth"] = &SprjChrDataModule::setBaseMaxHealth;
		sol_sprjchrdatamodule["getBaseMaxStamina"] = &SprjChrDataModule::getBaseMaxStamina;
		sol_sprjchrdatamodule["setBaseMaxStamina"] = &SprjChrDataModule::setBaseMaxStamina;
		sol_sprjchrdatamodule["getBaseMaxFP"] = &SprjChrDataModule::getBaseMaxFP;
		sol_sprjchrdatamodule["setBaseMaxFP"] = &SprjChrDataModule::setBaseMaxFP;
		sol_sprjchrdatamodule["isNoDamage"] = &SprjChrDataModule::isNoDamage;
		sol_sprjchrdatamodule["setNoDamage"] = &SprjChrDataModule::setNoDamage;
		sol_sprjchrdatamodule["isNoDead"] = &SprjChrDataModule::isNoDead;
		sol_sprjchrdatamodule["setNoDead"] = &SprjChrDataModule::setNoDead;
		sol_sprjchrdatamodule["isNoStaminaConsumption"] = &SprjChrDataModule::isNoStaminaConsumption;
		sol_sprjchrdatamodule["setNoStaminaConsumption"] = &SprjChrDataModule::setNoStaminaConsumption;
		sol_sprjchrdatamodule["isNoFPConsumption"] = &SprjChrDataModule::isNoFPConsumption;
		sol_sprjchrdatamodule["setNoFPConsumption"] = &SprjChrDataModule::setNoFPConsumption;
		sol_sprjchrdatamodule["getAddress"] = &SprjChrDataModule::getAddress;

		sol::usertype<EquipInventoryData> sol_equipinventorydata = luaSol.new_usertype<EquipInventoryData>("EquipInventoryData", sol::constructors<EquipInventoryData(uintptr_t)>());
		sol_equipinventorydata["discardInventoryItems"] = &EquipInventoryData::discardInventoryItems;
		sol_equipinventorydata["addItem"] = &EquipInventoryData::addItem;
		sol_equipinventorydata["getInventoryItemById"] = &EquipInventoryData::getInventoryItemById;
		sol_equipinventorydata["getInventoryItemCount"] = &EquipInventoryData::getInventoryItemCount;
		sol_equipinventorydata["GetInventoryItems"] = &EquipInventoryData::GetInventoryItems;
		sol_equipinventorydata["getItemParamIdPrefixFromGiveId"] = EquipInventoryData::getItemParamIdPrefixFromGiveId;
		sol_equipinventorydata["isHiddenItem"] = &EquipInventoryData::isHiddenItem;

		sol::usertype<PlayerGameData> sol_playergamedata = luaSol.new_usertype<PlayerGameData>("PlayerGameData", sol::constructors<PlayerGameData(uintptr_t)>());
		sol_playergamedata["getPlayerNo"] = &PlayerGameData::getPlayerNo;
		sol_playergamedata["getVoice"] = &PlayerGameData::getVoice;
		sol_playergamedata["setVoice"] = &PlayerGameData::setVoice;
		sol_playergamedata["getClass"] = &PlayerGameData::getClass;
		sol_playergamedata["setClass"] = &PlayerGameData::setClass;
		sol_playergamedata["getGender"] = &PlayerGameData::getGender;
		sol_playergamedata["setGender"] = &PlayerGameData::setGender;
		sol_playergamedata["getAge"] = &PlayerGameData::getAge;
		sol_playergamedata["setAge"] = &PlayerGameData::setAge;
		sol_playergamedata["getFaceData"] = &PlayerGameData::getFaceData;
		sol_playergamedata["setFaceData"] = &PlayerGameData::setFaceData;
		sol_playergamedata["getBodyProportions"] = &PlayerGameData::getBodyProportions;
		sol_playergamedata["setBodyPreportions"] = &PlayerGameData::setBodyPreportions;
		sol_playergamedata["getAttributes"] = &PlayerGameData::getAttributes;
		sol_playergamedata["setAttributes"] = &PlayerGameData::setAttributes;
		sol_playergamedata["getName"] = &PlayerGameData::getName;
		sol_playergamedata["setName"] = &PlayerGameData::setName;
		sol_playergamedata["getCovenant"] = &PlayerGameData::getCovenant;
		sol_playergamedata["setCovenant"] = &PlayerGameData::setCovenant;
		sol_playergamedata["getInvadeType"] = &PlayerGameData::getInvadeType;
		sol_playergamedata["setInvadeType"] = &PlayerGameData::setInvadeType;
		sol_playergamedata["getSpell"] = &PlayerGameData::getSpell;
		sol_playergamedata["setSpell"] = &PlayerGameData::setSpell;
		sol_playergamedata["getGesture"] = &PlayerGameData::getGesture;
		sol_playergamedata["setGesture"] = &PlayerGameData::setGesture;
		sol_playergamedata["getEquipGameData"] = &PlayerGameData::getEquipGameData;
		sol_playergamedata["getWeaponSheathData"] = &PlayerGameData::getWeaponSheathData;
		sol_playergamedata["getActiveLeftHandSlot"] = &PlayerGameData::getActiveLeftHandSlot;
		sol_playergamedata["setActiveLeftHandSlot"] = &PlayerGameData::setActiveLeftHandSlot;
		sol_playergamedata["getActiveRightHandSlot"] = &PlayerGameData::getActiveRightHandSlot;
		sol_playergamedata["setActiveRightHandSlot"] = &PlayerGameData::setActiveRightHandSlot;
		sol_playergamedata["getWeaponSheathState"] = &PlayerGameData::getWeaponSheathState;
		sol_playergamedata["setWeaponSheathState"] = &PlayerGameData::setWeaponSheathState;
		sol_playergamedata["getAmmo"] = &PlayerGameData::getAmmo;
		sol_playergamedata["setAmmo"] = &PlayerGameData::setAmmo;
		sol_playergamedata["getLeftHandWeapon"] = &PlayerGameData::getLeftHandWeapon;
		sol_playergamedata["setLeftHandWeapon"] = &PlayerGameData::setLeftHandWeapon;
		sol_playergamedata["getLeftHandWeaponActive"] = &PlayerGameData::getLeftHandWeaponActive;
		sol_playergamedata["setLeftHandWeaponActive"] = &PlayerGameData::setLeftHandWeaponActive;
		sol_playergamedata["getRightHandWeapon"] = &PlayerGameData::getRightHandWeapon;
		sol_playergamedata["setRightHandWeapon"] = &PlayerGameData::setRightHandWeapon;
		sol_playergamedata["getRightHandWeaponActive"] = &PlayerGameData::getRightHandWeaponActive;
		sol_playergamedata["setRightHandWeaponActive"] = &PlayerGameData::setRightHandWeaponActive;
		sol_playergamedata["getHead"] = &PlayerGameData::getHead;
		sol_playergamedata["setHead"] = &PlayerGameData::setHead;
		sol_playergamedata["getChest"] = &PlayerGameData::getChest;
		sol_playergamedata["setChest"] = &PlayerGameData::setChest;
		sol_playergamedata["getHands"] = &PlayerGameData::getHands;
		sol_playergamedata["setHands"] = &PlayerGameData::setHands;
		sol_playergamedata["getLegs"] = &PlayerGameData::getLegs;
		sol_playergamedata["setLegs"] = &PlayerGameData::setLegs;
		sol_playergamedata["getRing"] = &PlayerGameData::getRing;
		sol_playergamedata["setRing"] = &PlayerGameData::setRing;
		sol_playergamedata["getAddress"] = &PlayerGameData::getAddress;

		sol::usertype<InventoryItem> sol_InventoryItem = luaSol.new_usertype<InventoryItem>("InventoryItem");
		sol_InventoryItem["inventoryIndex"] = &InventoryItem::inventoryIndex;
		sol_InventoryItem["uniqueId"] = &InventoryItem::uniqueId;
		sol_InventoryItem["itemId"] = &InventoryItem::itemId;
		sol_InventoryItem["quantity"] = &InventoryItem::quantity;
		sol_InventoryItem["unknown1"] = &InventoryItem::unknown1;
		sol_InventoryItem["itemType"] = &InventoryItem::itemType;
		sol_InventoryItem["GetGaitemInstance"] = &InventoryItem::GetGaitemInstance;

		sol::usertype<LuaMemory> sol_luamemory = luaSol.new_usertype<LuaMemory>("Memory");
		sol_luamemory["MultiLevelPointer"] = LuaMemory::MultiLevelPointer;
		sol_luamemory["DereferencePointer"] = LuaMemory::DereferencePointer;
		sol_luamemory["Allocate"] = LuaMemory::Allocate;
		sol_luamemory["AllocateBytes"] = LuaMemory::AllocateBytes;
		sol_luamemory["AllocateNear"] = LuaMemory::AllocateNear;
		sol_luamemory["AllocateBytesNear"] = LuaMemory::AllocateBytesNear;
		sol_luamemory["Deallocate"] = LuaMemory::Deallocate;
		sol_luamemory["IsPtrValid"] = LuaMemory::IsPtrValid;
		sol_luamemory["ReadInt8"] = LuaMemory::ReadInt8;
		sol_luamemory["ReadInt16"] = LuaMemory::ReadInt16;
		sol_luamemory["ReadInt32"] = LuaMemory::ReadInt32;
		sol_luamemory["ReadInt64"] = LuaMemory::ReadInt64;
		sol_luamemory["ReadUint8"] = LuaMemory::ReadUint8;
		sol_luamemory["ReadUint16"] = LuaMemory::ReadUint16;
		sol_luamemory["ReadUint32"] = LuaMemory::ReadUint32;
		sol_luamemory["ReadUint64"] = LuaMemory::ReadUint64;
		sol_luamemory["ReadFloat"] = LuaMemory::ReadFloat;
		sol_luamemory["ReadDouble"] = LuaMemory::ReadDouble;
		sol_luamemory["ReadString"] = LuaMemory::ReadString;
		sol_luamemory["ReadBytes"] = LuaMemory::ReadBytes;
		sol_luamemory["WriteInt8"] = LuaMemory::WriteInt8;
		sol_luamemory["WriteInt16"] = LuaMemory::WriteInt16;
		sol_luamemory["WriteInt32"] = LuaMemory::WriteInt32;
		sol_luamemory["WriteInt64"] = LuaMemory::WriteInt64;
		sol_luamemory["WriteUint8"] = LuaMemory::WriteUint8;
		sol_luamemory["WriteUint16"] = LuaMemory::WriteUint16;
		sol_luamemory["WriteUint32"] = LuaMemory::WriteUint32;
		sol_luamemory["WriteUint64"] = LuaMemory::WriteUint64;
		sol_luamemory["WriteFloat"] = LuaMemory::WriteFloat;
		sol_luamemory["WriteDouble"] = LuaMemory::WriteDouble;
		sol_luamemory["WriteString"] = LuaMemory::WriteString;
		sol_luamemory["WriteBytes"] = LuaMemory::WriteBytes;

		sol::usertype<SprjMsgRepositoryImp> sol_sprjmsgrepositoryimp = luaSol.new_usertype<SprjMsgRepositoryImp>("FMGRepository");
		sol_sprjmsgrepositoryimp["getTalkMsg"] = SprjMsgRepositoryImp::getTalkMsg;
		sol_sprjmsgrepositoryimp["getBloodMsg"] = SprjMsgRepositoryImp::getBloodMsg;
		sol_sprjmsgrepositoryimp["getMovieSubtitle"] = SprjMsgRepositoryImp::getMovieSubtitle;
		sol_sprjmsgrepositoryimp["getGoodsName"] = SprjMsgRepositoryImp::getGoodsName;
		sol_sprjmsgrepositoryimp["getGoodsInfo"] = SprjMsgRepositoryImp::getGoodsInfo;
		sol_sprjmsgrepositoryimp["getGoodsCaption"] = SprjMsgRepositoryImp::getGoodsCaption;
		sol_sprjmsgrepositoryimp["getWeaponName"] = SprjMsgRepositoryImp::getWeaponName;
		sol_sprjmsgrepositoryimp["getWeaponInfo"] = SprjMsgRepositoryImp::getWeaponInfo;
		sol_sprjmsgrepositoryimp["getWeaponCaption"] = SprjMsgRepositoryImp::getWeaponCaption;
		sol_sprjmsgrepositoryimp["getProtectorName"] = SprjMsgRepositoryImp::getProtectorName;
		sol_sprjmsgrepositoryimp["getProtectorInfo"] = SprjMsgRepositoryImp::getProtectorInfo;
		sol_sprjmsgrepositoryimp["getProtectorCaption"] = SprjMsgRepositoryImp::getProtectorCaption;
		sol_sprjmsgrepositoryimp["getAccessoryName"] = SprjMsgRepositoryImp::getAccessoryName;
		sol_sprjmsgrepositoryimp["getAccessoryInfo"] = SprjMsgRepositoryImp::getAccessoryInfo;
		sol_sprjmsgrepositoryimp["getAccessoryCaption"] = SprjMsgRepositoryImp::getAccessoryCaption;
		sol_sprjmsgrepositoryimp["getGemName"] = SprjMsgRepositoryImp::getGemName;
		sol_sprjmsgrepositoryimp["getGemInfo"] = SprjMsgRepositoryImp::getGemInfo;
		sol_sprjmsgrepositoryimp["getGemCaption"] = SprjMsgRepositoryImp::getGemCaption;
		sol_sprjmsgrepositoryimp["getMagicName"] = SprjMsgRepositoryImp::getMagicName;
		sol_sprjmsgrepositoryimp["getMagicCaption"] = SprjMsgRepositoryImp::getMagicCaption;
		sol_sprjmsgrepositoryimp["getActionEventInfo"] = SprjMsgRepositoryImp::getActionEventInfo;
		sol_sprjmsgrepositoryimp["getInGameMenu"] = SprjMsgRepositoryImp::getInGameMenu;
		sol_sprjmsgrepositoryimp["getLineHelp"] = SprjMsgRepositoryImp::getLineHelp;
		sol_sprjmsgrepositoryimp["getKeyGuide"] = SprjMsgRepositoryImp::getKeyGuide;
		sol_sprjmsgrepositoryimp["getContentsHelp"] = SprjMsgRepositoryImp::getContentsHelp;
		sol_sprjmsgrepositoryimp["getDialog"] = SprjMsgRepositoryImp::getDialog;
		sol_sprjmsgrepositoryimp["getMenuOther"] = SprjMsgRepositoryImp::getMenuOther;
		sol_sprjmsgrepositoryimp["getMenuCommon"] = SprjMsgRepositoryImp::getMenuCommon;
		sol_sprjmsgrepositoryimp["getTestError"] = SprjMsgRepositoryImp::getTestError;
		sol_sprjmsgrepositoryimp["getTagError"] = SprjMsgRepositoryImp::getTagError;
		sol_sprjmsgrepositoryimp["getSysMsg"] = SprjMsgRepositoryImp::getSysMsg;
		sol_sprjmsgrepositoryimp["getNpcName"] = SprjMsgRepositoryImp::getNpcName;
		sol_sprjmsgrepositoryimp["getPlaceName"] = SprjMsgRepositoryImp::getPlaceName;
		sol_sprjmsgrepositoryimp["getMenuText"] = SprjMsgRepositoryImp::getMenuText;
		sol_sprjmsgrepositoryimp["getInventoryItemName"] = SprjMsgRepositoryImp::getInventoryItemName;
		sol_sprjmsgrepositoryimp["getInventoryItemInfo"] = SprjMsgRepositoryImp::getInventoryItemInfo;
		sol_sprjmsgrepositoryimp["getInventoryItemCaption"] = SprjMsgRepositoryImp::getInventoryItemCaption;
		sol_sprjmsgrepositoryimp["IsLoaded"] = SprjMsgRepositoryImp::IsLoaded;

		sol::usertype<GameFlags> sol_gameflags = luaSol.new_usertype<GameFlags>("GameFlags");
		sol_gameflags["SetFlagState"] = GameFlags::SetFlagState;
		sol_gameflags["GetFlagState"] = GameFlags::GetFlagState;

		sol::usertype<SprjGaitemIns> sol_sprjgaitemins = luaSol.new_usertype<SprjGaitemIns>("Gaitem", sol::constructors<SprjGaitemIns(uintptr_t)>());
		sol_sprjgaitemins["getDurability"] = &SprjGaitemIns::getDurability;
		sol_sprjgaitemins["setDurability"] = &SprjGaitemIns::setDurability;
		sol_sprjgaitemins["isSprjGaiItemIns"] = &SprjGaitemIns::isSprjGaiItemIns;
		sol_sprjgaitemins["getId"] = &SprjGaitemIns::getId;
		sol_sprjgaitemins["isValid"] = &SprjGaitemIns::isValid;
		sol_sprjgaitemins["getVtablePtr"] = &SprjGaitemIns::getVtablePtr;
		sol_sprjgaitemins["getAddress"] = &SprjGaitemIns::getAddress;

		sol::usertype<LuaArgs> sol_luaargs = luaSol.new_usertype<LuaArgs>("HksArgs", sol::constructors<LuaArgs(uintptr_t)>());
		sol_luaargs["GetString0"] = &LuaArgs::GetString0;
		sol_luaargs["GetString1"] = &LuaArgs::GetString1;
		sol_luaargs["HasUint64"] = &LuaArgs::HasUint64;
		sol_luaargs["GetUint64"] = &LuaArgs::GetUint64;
	}
	void LuaBindings::Luaprint(sol::variadic_args va) {
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
	bool LuaBindings::TryLockGameInputs()
	{
		uint32_t menuState = (uint32_t)call(0x14075ec70, 8);
		if (!script_runtime::isGameInputLocked && menuState == 0)
		{
			script_runtime::isGameInputLocked = true;
			call(0x140762880, 8, 7);
		}
		return script_runtime::isGameInputLocked;
	}
	bool LuaBindings::TryUnlockGameInputs()
	{
		if (script_runtime::isGameInputLocked)
		{
			script_runtime::isGameInputLocked = false;
			call(0x140762880, 8, 0);
			return true;
		}
		return false;
	}
}