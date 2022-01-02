#include "pch.h"
#include "player_ins.h"
#include "Amir/standard_player_boss.h"
#include "memory_util.h"
#include "databaseaddress.h"
#include "GameDebugClasses/world_chr_man.h"

namespace hoodie_script {

	PlayerIns::PlayerIns(uintptr_t address) : ChrIns::ChrIns(address)
	{
	}

	PlayerGameData PlayerIns::getPlayerGameData()
	{
		return PlayerGameData(*accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FA0));
	}

	bool PlayerIns::hasPlayerGameData()
	{
		return accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FA0) != nullptr;
	}

	uintptr_t* PlayerIns::getNetworkPointer()
	{
		return accessMultilevelPointer<uintptr_t>(getAddress() + 0x1FD0, 8);
	}

	int32_t PlayerIns::getLeftHandWeapon(const uint32_t& slotNumber) const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x32C + (slotNumber) * 8);
	}

	int32_t PlayerIns::getLeftHandWeaponActive() const
	{
		auto leftHandActiveWeaponSlot = GetActiveWeaponSlotLeftHand();
		return getLeftHandWeapon(leftHandActiveWeaponSlot);
	}

	void PlayerIns::setLeftHandWeapon(const uint32_t& slotNumber, const int32_t& equipParamWeaponId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x32C + (slotNumber) * 8) = equipParamWeaponId;
	}

	void PlayerIns::setLeftHandWeaponActive(const int32_t& equipParamWeaponId)
	{
		auto leftHandActiveWeaponSlot = GetActiveWeaponSlotLeftHand();
		setLeftHandWeapon(leftHandActiveWeaponSlot, equipParamWeaponId);
	}

	uint32_t PlayerIns::GetActiveWeaponSlotRightHand() const
	{
		return *accessMultilevelPointer<uint32_t>(getAddress() + 0x1FA0, 0x2C0);
	}

	uint32_t PlayerIns::GetActiveWeaponSlotLeftHand() const
	{
		return *accessMultilevelPointer<uint32_t>(getAddress() + 0x1FA0, 0x2BC);
	}

	int32_t PlayerIns::getRightHandWeapon(const uint32_t& slotNumber) const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x330 + (slotNumber) * 8);
	}

	int32_t PlayerIns::getRightHandWeaponActive() const
	{
		auto rightHandActiveWeaponSlot = GetActiveWeaponSlotRightHand();
		return getRightHandWeapon(rightHandActiveWeaponSlot);
	}

	void PlayerIns::setRightHandWeapon(const uint32_t& slotNumber, const int32_t& equipParamWeaponId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x330 + (slotNumber) * 8) = equipParamWeaponId;
	}

	void PlayerIns::setRightHandWeaponActive(const int32_t& equipParamWeaponId)
	{
		auto rightHandSlot = GetActiveWeaponSlotRightHand();
		setRightHandWeapon(rightHandSlot, equipParamWeaponId);
	}

	void PlayerIns::setWeaponSheathState(int32_t sheatState)
	{
		getPlayerGameData().setWeaponSheathState(sheatState);
	}

	int32_t PlayerIns::getWeaponSheathState()
	{
		return getPlayerGameData().getWeaponSheathState();
	}


	void PlayerIns::setRightHandWeaponActiveNetworked(const int32_t& equipParamWeaponId)
	{
		auto rightHandSlot = GetActiveWeaponSlotRightHand();
		setRightHandWeaponNetworked(equipParamWeaponId, rightHandSlot);
	}

	void PlayerIns::setRightHandWeaponNetworked(const int32_t& equipParamWeaponId, int index)
	{
		int array[]{ 1,3,5 };
		StandardPlayerBoss hello = StandardPlayerBoss();
		hello.giveItemAndSwap((InventorySlot)array[index], ItemParamIdPrefix::Weapon, equipParamWeaponId, -1);
	}

	bool PlayerIns::removeWeaponFromInventory(const int32_t& equipParamWeaponId)
	{
		StandardPlayerBoss hello = StandardPlayerBoss();
		hello.RemoveItemFromInventory(ItemParamIdPrefix::Weapon, equipParamWeaponId);
		return true;
	}

	void PlayerIns::ReplaceWeapon(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement, int index)
	{
		int array[]{ 1,3,5 };
		StandardPlayerBoss hello = StandardPlayerBoss();
		hello.ReplaceItem((InventorySlot)array[index], ItemParamIdPrefix::Weapon, equipParamWeaponTarget, equipParamWeaponReplacement, -1);
	}

	void PlayerIns::ReplaceWeaponActiveRight(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement)
	{
		auto rightHandSlot = *accessMultilevelPointer<int32_t>(0x144740178, 0x10, 0x2C0);
		int array[]{ 1,3,5 };
		StandardPlayerBoss hello = StandardPlayerBoss();
		hello.ReplaceItem((InventorySlot)array[rightHandSlot], ItemParamIdPrefix::Weapon, equipParamWeaponTarget, equipParamWeaponReplacement, -1);
	}

	int32_t PlayerIns::getHead() const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x35C);
	}

	void PlayerIns::setHead(const int32_t& equipParamProtectorId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x35C) = equipParamProtectorId;
	}

	int32_t PlayerIns::getChest() const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x360);
	}

	void PlayerIns::setChest(const int32_t& equipParamProtectorId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x360) = equipParamProtectorId;
	}

	int32_t PlayerIns::getHands() const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x364);
	}

	void PlayerIns::setHands(const int32_t& equipParamProtectorId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x364) = equipParamProtectorId;
	}

	int32_t PlayerIns::getLegs() const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x368);
	}

	void PlayerIns::setLegs(const int32_t& equipParamProtectorId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x368) = equipParamProtectorId;
	}

	int32_t PlayerIns::getRing(const uint32_t& slotNumber) const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x370 + (slotNumber - 1) * 4);
	}

	void PlayerIns::setRing(const uint32_t& slotNumber, const int32_t& equipParamAccessoryId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x370 + (slotNumber - 1) * 4) = equipParamAccessoryId;
	}

	int32_t PlayerIns::getAmmo(const uint32_t& slotNumber) const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x344 + (slotNumber - 1) * 4);
	}

	void PlayerIns::setAmmo(const uint32_t& slotNumber, const int32_t& equipParamAccessoryId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x344 + (slotNumber - 1) * 4) = equipParamAccessoryId;
	}

	int32_t PlayerIns::getCovenant() const
	{
		return *accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x380);
	}

	void PlayerIns::setCovenant(const int32_t& equipParamAccessoryId)
	{
		*accessMultilevelPointer<int32_t>(getAddress() + 0x1FA0, 0x380) = equipParamAccessoryId;
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

	uintptr_t PlayerIns::getAddressByOffsetNumber(const OffsetNumber& offsetNumber)
	{
		return *accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan, 0x40, static_cast<uint32_t>(offsetNumber) * 0x38);
	}

	bool PlayerIns::isChrWithOffsetNumber(const OffsetNumber& offsetNumber)
	{
		const uintptr_t* chrAddress = accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan, 0x40, static_cast<uint32_t>(offsetNumber) * 0x38);
		return chrAddress != nullptr && isPlayer(*chrAddress);
	}

	bool PlayerIns::isPlayer(const uintptr_t& address)
	{
		bool isPlayer = false;
		for (int i = 0; i < 5; i++) if (getAddressByOffsetNumber(static_cast<OffsetNumber>(i)) == address) isPlayer = true;
		return isChrIns(address) && isPlayer && accessMultilevelPointer<uint32_t>(address + 0x1FA0, 0xFC);
	}

	bool PlayerIns::isValid() const
	{
		bool isPlayer = false;
		if (getAddress() == 0)
			return false;
		for (int i = 0; i < 5; i++) if (getAddressByOffsetNumber(static_cast<OffsetNumber>(i)) == getAddress()) isPlayer = true;
		return isPlayer && accessMultilevelPointer<uint32_t>(getAddress() + 0x1FA0, 0xFC);
	}

	PlayerIns PlayerIns::getMainChr()
	{
		return WorldChrMan::getMainChr();
	}

	bool PlayerIns::isMainChr(const uintptr_t& address)
	{
		return isChrIns(address) && address == reinterpret_cast<uintptr_t>(accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan, 0x80, 0));
	}

	bool PlayerIns::isMainChrLoaded()
	{
		return WorldChrMan::isMainChrLoaded();
	}

};
