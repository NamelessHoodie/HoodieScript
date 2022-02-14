#include "pch.h"
#include "chr_ins.h"
#include "GameDebugClasses/world_chr_man.h"
#include "GameDebugClasses/Bullet_Spawn.h"
#include "Hooks/hkb_animation_hook.h"
#include "memory_util.h"
#include "Amir/ds3runtime.h"

namespace hoodie_script {

	ChrIns::ChrIns(uintptr_t address)
	{
		this->address = address;
	}

	bool ChrIns::isValid() const
	{
		const uintptr_t* bodyNodeFunction = accessMultilevelPointer<uintptr_t>(address, 0x400);
		return bodyNodeFunction && (*bodyNodeFunction == 0x14087D320 || *bodyNodeFunction == 0x1408AF650);
	}

	uint32_t ChrIns::getEntityId()
	{
		return *(uint32_t*)(address + 0x1A1C);
	}

	ChrIns::Handle ChrIns::getHandle() const
	{
		return static_cast<Handle>(*accessMultilevelPointer<uint32_t>(address + 8));
	}

	ChrIns::ChrType ChrIns::getChrType() const
	{
		return static_cast<ChrType>(*accessMultilevelPointer<uint32_t>(address + 0x70));
	}

	void ChrIns::setChrType(const ChrType& chrType)
	{
		*accessMultilevelPointer<uint32_t>(address + 0x70) = static_cast<uint32_t>(chrType);
	}

	ChrIns::Team ChrIns::getTeam() const
	{
		return static_cast<Team>(*accessMultilevelPointer<uint32_t>(address + 0x74));
	}

	void ChrIns::setTeam(const Team& team)
	{
		*accessMultilevelPointer<uint32_t>(address + 0x74) = static_cast<uint32_t>(team);
	}

	unsigned short ChrIns::getForwardId() const
	{
		return *accessMultilevelPointer<unsigned short>(address + 0x78);
	}

	std::wstring ChrIns::getCharacterString() const
	{
		return std::wstring(accessMultilevelPointer<wchar_t>(address + 0x1F90, 0x18, 0x130));
	}

	std::wstring ChrIns::getCharacterId() const
	{
		auto ptr = accessMultilevelPointer<wchar_t>(address + 0x1F90, 0x18, 0x48);
		return ptr != nullptr ? std::wstring(ptr) : L"";
	}

	std::wstring ChrIns::getAnimationString() const
	{
		return std::wstring(accessMultilevelPointer<wchar_t>(address + 0x1F90, 0x28, 0x898));
	}

	float ChrIns::getAnimationTime() const
	{
		return *accessMultilevelPointer<float>(address + 0x1F90, 0x10, 0x24);
	}

	float ChrIns::getMaxAnimationTime() const
	{
		return *accessMultilevelPointer<float>(address + 0x1F90, 0x10, 0x2C);
	}

	float ChrIns::getTurnRate() const
	{
		return *accessMultilevelPointer<float>(address + 0x1F90, 0x0, 0x1A0);
	}

	std::vector<float> ChrIns::getPosition() const
	{
		//float* positionArray = accessMultilevelPointer<float>(address + 0x1f90, 0xa8, 0x40, 0x70);
		float* positionArray = accessMultilevelPointer<float>(address + 0x18, 0x28, 0x80);
		std::vector<float> position(positionArray, positionArray + 3);
		return position;
	}

	void ChrIns::setPosition(const std::vector<float>& position)
	{
		//memcpy(accessMultilevelPointer<float>(address + 0x1f90, 0xa8, 0x40, 0x70), &position[0], 12);
		memcpy(accessMultilevelPointer<float>(address + 0x18, 0x28, 0x80), &position[0], 12);
	}

	float ChrIns::getAngle() const
	{
		return *accessMultilevelPointer<float>(address + 0x18, 0x28, 0x74);
	}

	float ChrIns::getCrossbowAngle() const
	{
		return *accessMultilevelPointer<float>(address + 0x18, 0x28, 0x70);
	}

	void ChrIns::setAngle(const float& angle)
	{
		*accessMultilevelPointer<float>(address + 0x18, 0x28, 0x74) = angle;
	}

	uintptr_t ChrIns::getSprjChrDataModule()
	{
		return *accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x18);
	}

	uintptr_t ChrIns::getSprjChrDamageModule()
	{
		return *accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x98);
	}

	int32_t ChrIns::isDead() const
	{
		return *accessMultilevelPointer<int32_t>(address + 0x50, 0x48, 0x11C);
	}

	void ChrIns::setIsDead(const int32_t& isDead)
	{
		*accessMultilevelPointer<int32_t>(address + 0x50, 0x48, 0x11C) = isDead;
	}

	ChrIns ChrIns::getLockOnTarget()
	{
		return WorldChrMan::getInsByHandle(getLockOnTargetChrHandle());
	}

	void ChrIns::setLockOnTarget(ChrIns& characterInstance)
	{
		setLockOnTargetChrHandle(characterInstance.getHandle());
	}

	ChrIns::Handle ChrIns::getLockOnTargetChrHandle() const
	{
		return *accessMultilevelPointer<Handle>(address + 0x50, 0x110, 0x330, 0x27DC);
	}

	void ChrIns::setLockOnTargetChrHandle(const ChrIns::Handle chrHandle)
	{
		*accessMultilevelPointer<Handle>(address + 0x50, 0x110, 0x330, 0x27DC) = chrHandle;
	}

	bool ChrIns::isNoGravity() const
	{
		return (*accessMultilevelPointer<uint8_t>(address + 0x1A08) & static_cast<uint8_t>(pow(2, 6))) == pow(2, 6);
	}

	void ChrIns::setNoGravity(const bool& value)
	{
		uint8_t* newByte = accessMultilevelPointer<uint8_t>(address + 0x1A08);
		if (value) *newByte = *newByte | static_cast<uint8_t>(pow(2, 6));
		else *newByte = (*newByte & ~static_cast<uint8_t>(pow(2, 6)));
	}

	bool ChrIns::isDodging() const
	{
		return (*accessMultilevelPointer<uint8_t>(address + 0x1F90, 0, 0x58) & static_cast<uint8_t>(pow(2, 1))) == pow(2, 1);
	}

	uintptr_t ChrIns::getHkbCharacter()
	{
		return *accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x28, 0x10, 0x28, 0xB8);
	}

	bool ChrIns::hasHkbCharacter() const
	{
		return accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x28, 0x10, 0x28, 0xB8);
	}

	void ChrIns::playAnimation(const int32_t& animationStringId)
	{
		auto hook = hoodie_script::hkb_animation_hook::_instance;
		int32_t input[6] = { animationStringId, 0, 0 };
		uintptr_t animationHandle = getHkbCharacter();
		void(*playAnimationInternal)(uintptr_t, int32_t*);
		*reinterpret_cast<uintptr_t*>(&playAnimationInternal) = hook != nullptr ? hook->get_original() : 0x140D84870;
		playAnimationInternal(animationHandle, input);
	}

	void ChrIns::playAnimationString(const std::wstring& animationString)
	{
		uintptr_t* animationHandle = accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x28, 0x10, 0x28); //AnibndResCap
		void(*playAnimationStringInternal)(...);
		*reinterpret_cast<uintptr_t*>(&playAnimationStringInternal) = 0x140D84450;
		playAnimationStringInternal(animationHandle, animationString.c_str());
	}

	int32_t ChrIns::getHkbIdFromString(const std::wstring& animationString) const
	{
		char arr[32] = {};
		int32_t(*function)(...);
		*reinterpret_cast<uintptr_t*>(&function) = 0x141049BD0;
		return function(*accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x28, 0x10, 0x28, 0xA0), ds3runtime_global->utf8_encode(animationString).c_str());
	}

	void ChrIns::SpawnBullet(int32_t bulletId, std::vector<float> spawnPosition, std::vector<float> direction)
	{
		auto entryBullet = bullet_spawn_request();
		entryBullet.set_bullet_param_id((bullet_type)bulletId);
		entryBullet.set_owner((int32_t)getHandle());
		entryBullet.set_direction(direction);
		//entryBullet.set_homing_flag(-1);
		entryBullet.set_coordinates(spawnPosition);
		bullet_facade::spawn(&entryBullet);
	}

	std::wstring ChrIns::getHkbStringFromId(const int32_t& id) const
	{
		char* (*function)(...);
		*reinterpret_cast<uintptr_t*>(&function) = 0x141049bf0;
		return ds3runtime_global->utf8_decode(std::string(function(*accessMultilevelPointer<uintptr_t>(address + 0x1F90, 0x28, 0x10, 0x28, 0xA0), id)));
	}

	int32_t ChrIns::getWeightIndex() const
	{
		return *accessMultilevelPointer<int32_t>(address + 0x50, 0x2B4);
	}

	bool ChrIns::hasSpEffect(const int32_t& spEffectId)
	{
		const uintptr_t effectBase = *accessMultilevelPointer<uintptr_t>(address + 0x11c8);
		uintptr_t effectPtr = *accessMultilevelPointer<uintptr_t>(effectBase + 8);
		if (reinterpret_cast<uintptr_t*>(effectPtr) == nullptr) return false;
		uint8_t effectcount = 0;

		for (effectPtr = *accessMultilevelPointer<uintptr_t>(effectPtr + 0x78); accessMultilevelPointer<uintptr_t*>(effectPtr) != nullptr; effectPtr = *accessMultilevelPointer<uintptr_t>(effectPtr + 0x78)) {
			if (*accessMultilevelPointer<int32_t>(effectPtr + 0x60) == spEffectId) return true;
		}
		return false;
	}

	void ChrIns::setWeightIndex(const int32_t& weightIndex)
	{
		*accessMultilevelPointer<int32_t>(address + 0x50, 0x2B4) = weightIndex;
	}

	void ChrIns::setDebugAnimSpeed(const float& speedModifier)
	{
		*accessMultilevelPointer<float>(address + 0x1F90, 0x28, 0xA58) = speedModifier;
	}

	std::vector<std::array<float, 4>> ChrIns::getDummyPolyPositions(const int32_t& dummyPolyId, const uint32_t& polyCount) const
	{
		std::vector<float> resultBuffer(16 * static_cast<size_t>(polyCount));
		std::vector<int32_t> inputBuffer(4);
		inputBuffer[0] = dummyPolyId;
		void(*getBodyNodePositionInternal)(...);
		*reinterpret_cast<uintptr_t*>(&getBodyNodePositionInternal) = *accessMultilevelPointer<uintptr_t>(address, 0x400);
		getBodyNodePositionInternal(address, &resultBuffer[0], &inputBuffer[0], polyCount);
		std::vector<std::array<float, 4>> returnVector(polyCount);

		for (uint32_t i = 0; i < polyCount; i++) {
			std::array<float, 4> position;
			position[0] = resultBuffer[3 + static_cast<size_t>(i) * 12];
			position[1] = resultBuffer[7 + static_cast<size_t>(i) * 12];
			position[2] = resultBuffer[11 + static_cast<size_t>(i) * 12];
			returnVector[i] = position;
		}

		return returnVector;
	}

	uintptr_t ChrIns::getAddress() const
	{
		return address;
	}

	bool ChrIns::isPlayerOffsetNumber(OffsetNumber offsetNumber)
	{
		const uintptr_t chrAddress = WorldChrMan::getPlayerByOffsetNumber(offsetNumber).getAddress();
		if (chrAddress == NULL)
			return false;

		if (chrAddress == address)
			return true;

		return false;
	}

	bool ChrIns::isChrIns()
	{
		const uintptr_t* bodyNodeFunction = accessMultilevelPointer<uintptr_t>(address, 0x400);
		return bodyNodeFunction && (*bodyNodeFunction == 0x14087D320 || *bodyNodeFunction == 0x1408AF650);
	}

	bool ChrIns::isPlayableCharacter()
	{
		bool isPlayer = false;
		for (uint32_t i = 0; i < 5; i++) 
			if (isPlayerOffsetNumber(static_cast<OffsetNumber>(i)))
				isPlayer = true;
		return isChrIns() && isPlayer && accessMultilevelPointer<uint32_t>(address + 0x1FA0, 0xFC);
	}

	bool ChrIns::isNPC()
	{
		if (isPlayableCharacter() || !toPlayerIns().hasPlayerGameData())
			return false;

		return true;
	}

	ChrIns ChrIns::toChrIns()
	{
		return ChrIns(getAddress());
	}

	PlayerIns ChrIns::toPlayerIns()
	{
		return PlayerIns(getAddress());
	}
}
