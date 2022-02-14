#include "pch.h"
#include "player_ins.h"
#include "memory_util.h"
#include "databaseaddress.h"
#include "GameDebugClasses/world_chr_man.h"

namespace hoodie_script {

	PlayerIns::PlayerIns(uintptr_t address) : ChrIns::ChrIns(address)
	{
	}

	uintptr_t* PlayerIns::getNetworkPointer()
	{
		return accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FD0, 8);
	}

	PlayerGameData PlayerIns::getPlayerGameData()
	{
		return PlayerGameData(*accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FA0));
	}

	bool PlayerIns::hasPlayerGameData()
	{
		return accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FA0) != nullptr;
	}

	EquipGameData PlayerIns::getEquipGameData()
	{
		return getPlayerGameData().getEquipGameData();
	}

	bool PlayerIns::hasEquipGameData()
	{
		return hasPlayerGameData();
	}

	EquipInventoryData PlayerIns::getEquipInventoryData()
	{
		return getEquipGameData().getEquipInventoryData();
	}

	bool PlayerIns::hasEquipInventoryData()
	{
		return hasPlayerGameData();
	}

	bool PlayerIns::isNoGoodsConsume() const
	{
		bool value = (*accessMultilevelPointer<uint8_t>(getAddress() + 0x1EEA) & static_cast<uint8_t>(pow(2, 3))) == pow(2, 3);
		return value;
	}

	void PlayerIns::setNoGoodsConsume(const bool& value)
	{
		uint8_t* newByte = accessMultilevelPointer<uint8_t>(getAddress() + 0x1EEA);
		if (value) *newByte = *newByte | static_cast<uint8_t>(pow(2, 3));
		else *newByte = (*newByte & ~static_cast<uint8_t>(pow(2, 3)));
	}

	uintptr_t PlayerIns::getPlayerCtrl()
	{
		return *accessMultilevelPointer<uintptr_t>(getAddress() + 0x50);
	}

	uintptr_t* PlayerIns::getNetworkHandle()
	{
		return accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FD0, 0x8);
	}

	bool PlayerIns::isValid()
	{
		if (getAddress() == 0)
			return false;
		return hasPlayerGameData();
	}

	PlayerIns PlayerIns::getMainChr()
	{
		return WorldChrMan::getMainChr();
	}

	bool PlayerIns::isMainChr()
	{
		return isChrIns() && getAddress() == WorldChrMan::getMainChr().getAddress();
	}

	bool PlayerIns::isMainChrLoaded()
	{
		return WorldChrMan::isMainChrLoaded();
	}

};
