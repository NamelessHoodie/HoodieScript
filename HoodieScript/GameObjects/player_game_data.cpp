#include "pch.h"
#include "player_game_data.h"
#include "databaseaddress.h"
#include "memory_util.h"

namespace hoodie_script {

PlayerGameData::PlayerGameData(uintptr_t address)
{
	this->address = address;
}

int32_t PlayerGameData::getPlayerNo() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x10);
}

PlayerGameData::Voice PlayerGameData::getVoice() const
{
	return static_cast<Voice>(*accessMultilevelPointer<uint8_t>(address + 0xAB));
}

void PlayerGameData::setVoice(const Voice& voice)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAB) = static_cast<uint8_t>(voice);
}

PlayerGameData::Class PlayerGameData::getClass() const
{
	return static_cast<Class>(*accessMultilevelPointer<uint8_t>(address + 0xAE));
}

void PlayerGameData::setClass(const Class& chrClass)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAE) = static_cast<uint8_t>(chrClass);
}

PlayerGameData::Gender PlayerGameData::getGender() const
{
	return (Gender)*accessMultilevelPointer<uint8_t>(address + 0xAA);
}

void PlayerGameData::setGender(const Gender& gender)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAA) = static_cast<uint8_t>(gender);
}

PlayerGameData::Age PlayerGameData::getAge() const
{
	return static_cast<Age>(*accessMultilevelPointer<uint8_t>(address + 0x6B8));
}

void PlayerGameData::setAge(const Age& age)
{
	*accessMultilevelPointer<uint8_t>(address + 0x6B8) = static_cast<uint8_t>(age);
}

std::array<uint8_t, 256> PlayerGameData::getFaceData() const
{
	auto faceDataPointer = accessMultilevelPointer<uint8_t>(address + 0x6B0);
	std::array<uint8_t, 256> faceDataArray = {};
	std::copy_n(faceDataPointer, faceDataArray.size(), faceDataArray.begin());
	return faceDataArray;
}

void PlayerGameData::setFaceData(const std::array<uint8_t, 256>& faceData)
{
	auto faceDataPointer = accessMultilevelPointer<uint8_t>(address + 0x6B0);
	memcpy(faceDataPointer, &faceData[0], 256);
}

BodyProportions PlayerGameData::getBodyProportions() const
{
	return *reinterpret_cast<BodyProportions*>(accessMultilevelPointer<uintptr_t>(address + 0x3B0));
}

void PlayerGameData::setBodyPreportions(const BodyProportions& bodyPreportions)
{
	*reinterpret_cast<BodyProportions*>(accessMultilevelPointer<uintptr_t>(address + 0x3B0)) = bodyPreportions;
}

Attributes PlayerGameData::getAttributes() const
{
	return *reinterpret_cast<Attributes*>(accessMultilevelPointer<uintptr_t>(address + 0x44));
}

void PlayerGameData::setAttributes(const Attributes& attributes)
{
	*reinterpret_cast<Attributes*>(accessMultilevelPointer<uintptr_t>(address + 0x44)) = attributes;
}

std::wstring PlayerGameData::getName() const
{
	return std::wstring(accessMultilevelPointer<wchar_t>(address + 0x88));
}

void PlayerGameData::setName(const std::wstring& name)
{
	wchar_t* namePointer = accessMultilevelPointer<wchar_t>(address + 0x88);
	memset(namePointer, 0, 16);
	memcpy(namePointer, name.c_str(), name.length() * 2);
}

PlayerGameData::Covenant PlayerGameData::getCovenant()
{
	return static_cast<Covenant>(*accessMultilevelPointer<uint32_t>(address + 0xF7));
	//return static_cast<Covenant>(*accessMultilevelPointer<int32_t>(address + 0x380));
}

void PlayerGameData::setCovenant(Covenant covenant)
{
	*accessMultilevelPointer<uint32_t>(address + 0xF7) = static_cast<uint32_t>(covenant);
	//*accessMultilevelPointer<int32_t>(address + 0x380) = equipParamAccessoryId;
}

PlayerGameData::InvadeType PlayerGameData::getInvadeType() const
{
	return static_cast<InvadeType>(*accessMultilevelPointer<uint32_t>(address + 0xFC));
}

void PlayerGameData::setInvadeType(const PlayerGameData::InvadeType& invadeType)
{
	*accessMultilevelPointer<uint32_t>(address + 0xFC) = (uint32_t)invadeType;
}

int32_t PlayerGameData::getSpell(const uint32_t& slotNumber) const
{
	return *accessMultilevelPointer<int32_t>(address + 0x470, 0x18 + (slotNumber - 1) * 8);
}

void PlayerGameData::setSpell(const uint32_t& slotNumber, const int32_t& spellId)
{
	*accessMultilevelPointer<int32_t>(address + 0x470, 0x18 + (slotNumber - 1) * 8) = spellId;
}

uint8_t PlayerGameData::getGesture(const uint32_t& slotNumber) const
{
	return *accessMultilevelPointer<uint8_t>(address + 0x528, 0x10 + (slotNumber - 1) * 4);
}

void PlayerGameData::setGesture(const uint32_t& slotNumber, const uint8_t& gestureId)
{
	*accessMultilevelPointer<uint8_t>(address + 0x528, 0x10 + (slotNumber - 1) * 4) = gestureId;
}

EquipGameData PlayerGameData::getEquipGameData()
{
	return EquipGameData(address + 0x228);
}

uint16_t PlayerGameData::getWeaponSheathData() const
{
	uint16_t(*function)(uintptr_t);
	*reinterpret_cast<uintptr_t*>(&function) = 0x1409EBA70;
	return function(address + 0x2B8);
}

int32_t PlayerGameData::getActiveLeftHandSlot() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2BC);
}

void PlayerGameData::setActiveLeftHandSlot(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2BC) = slot;
}

int32_t PlayerGameData::getActiveRightHandSlot() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2C0);
}

void PlayerGameData::setActiveRightHandSlot(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2C0) = slot;
}

int32_t PlayerGameData::getWeaponSheathState() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2B8);
}

void PlayerGameData::setWeaponSheathState(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2B8) = slot;
}

//

int32_t PlayerGameData::getAmmo(uint32_t slotNumber)
{
	return *accessMultilevelPointer<int32_t>(address + 0x344 + (slotNumber - 1) * 4);
}

void PlayerGameData::setAmmo(uint32_t slotNumber, int32_t equipParamAccessoryId)
{
	*accessMultilevelPointer<int32_t>(address + 0x344 + (slotNumber - 1) * 4) = equipParamAccessoryId;
}

int32_t PlayerGameData::getLeftHandWeapon(uint32_t slotNumber)
{
	return *accessMultilevelPointer<int32_t>(address + 0x32C + (slotNumber) * 8);
}

void PlayerGameData::setLeftHandWeapon(uint32_t slotNumber, int32_t equipParamWeaponId)
{
	*accessMultilevelPointer<int32_t>(address + 0x32C + (slotNumber) * 8) = equipParamWeaponId;
}

int32_t PlayerGameData::getLeftHandWeaponActive()
{
	auto leftHandActiveWeaponSlot = getActiveLeftHandSlot();
	return getLeftHandWeapon(leftHandActiveWeaponSlot);
}

void PlayerGameData::setLeftHandWeaponActive(int32_t equipParamWeaponId)
{
	auto leftHandActiveWeaponSlot = getActiveLeftHandSlot();
	setLeftHandWeapon(leftHandActiveWeaponSlot, equipParamWeaponId);
}

int32_t PlayerGameData::getRightHandWeapon(uint32_t slotNumber)
{
	return *accessMultilevelPointer<int32_t>(address + 0x330 + (slotNumber) * 8);
}

void PlayerGameData::setRightHandWeapon(uint32_t slotNumber, int32_t equipParamWeaponId)
{
	*accessMultilevelPointer<int32_t>(address + 0x330 + (slotNumber) * 8) = equipParamWeaponId;
}

int32_t PlayerGameData::getRightHandWeaponActive()
{
	auto rightHandActiveWeaponSlot = getActiveRightHandSlot();
	return getRightHandWeapon(rightHandActiveWeaponSlot);
}

void PlayerGameData::setRightHandWeaponActive(int32_t equipParamWeaponId)
{
	auto rightHandSlot = getActiveRightHandSlot();
	setRightHandWeapon(rightHandSlot, equipParamWeaponId);
}

int32_t PlayerGameData::getHead()
{
	return *accessMultilevelPointer<int32_t>(address + 0x35C);
}

void PlayerGameData::setHead(int32_t equipParamProtectorId)
{
	*accessMultilevelPointer<int32_t>(address + 0x35C) = equipParamProtectorId;
}

int32_t PlayerGameData::getChest()
{
	return *accessMultilevelPointer<int32_t>(address + 0x360);
}

void PlayerGameData::setChest(int32_t equipParamProtectorId)
{
	*accessMultilevelPointer<int32_t>(address + 0x360) = equipParamProtectorId;
}

int32_t PlayerGameData::getHands()
{
	return *accessMultilevelPointer<int32_t>(address + 0x364);
}

void PlayerGameData::setHands(int32_t equipParamProtectorId)
{
	*accessMultilevelPointer<int32_t>(address + 0x364) = equipParamProtectorId;
}

int32_t PlayerGameData::getLegs()
{
	return *accessMultilevelPointer<int32_t>(address + 0x368);
}

void PlayerGameData::setLegs(int32_t equipParamProtectorId)
{
	*accessMultilevelPointer<int32_t>(address + 0x368) = equipParamProtectorId;
}

int32_t PlayerGameData::getRing(uint32_t slotNumber)
{
	return *accessMultilevelPointer<int32_t>(address + 0x370 + (slotNumber - 1) * 4);
}

void PlayerGameData::setRing(uint32_t slotNumber, int32_t equipParamAccessoryId)
{
	*accessMultilevelPointer<int32_t>(address + 0x370 + (slotNumber - 1) * 4) = equipParamAccessoryId;
}

uintptr_t PlayerGameData::getAddress() const
{
	return address;
}

}
