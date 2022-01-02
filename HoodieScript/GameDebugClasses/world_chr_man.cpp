#include "pch.h"
#include "world_chr_man.h"
#include "memory_util.h"
#include "databaseaddress.h"

namespace hoodie_script {

	std::vector<uintptr_t> WorldChrMan::getCurrentMapEnemies()
	{
		std::vector<uintptr_t> enemies;
		if (isLoaded())
		{
			auto aPa = accessMultilevelPointer<unsigned int>(getAddress() + 0x1d0, 0x0);
			if (aPa != nullptr)
			{
				auto aP = *aPa;
				for (size_t i = 0; i < aP; i++)
				{
					auto a = accessMultilevelPointer<uintptr_t*>(getAddress() + 0x1d0, 0x8);
					if (a != nullptr)
					{
						uintptr_t* mapCharacterEntry = (uintptr_t*)((byte*)*a + (0x38 * i));
						if (mapCharacterEntry != nullptr)
						{
							auto chrInsPointer = *mapCharacterEntry;
							if (chrInsPointer != NULL)
							{
								enemies.push_back(*mapCharacterEntry);
							}
						}
					}
				}
			}
		}
		return enemies;
	}

	bool WorldChrMan::reloadCharacterFiles(std::wstring characterId)
	{
		if (isLoaded())
		{
			*accessMultilevelPointer<bool>(0x144768F7F) = true;
			void(*ReloadChrFunction)(...);
			*(uintptr_t*)&ReloadChrFunction = 0x1408D1E10;
			ReloadChrFunction(getAddress(), characterId.c_str());
			return true;
		}
		return false;
	}

	void WorldChrMan::findEntityTest(int32_t id)
	{
		if (isLoaded())
		{
			int32_t buffer[2] = {};
			void(*FindEntityTest)(...);
			*(uintptr_t*)&FindEntityTest = 0x140436870;
			FindEntityTest(buffer, id);
		}
	}

	uintptr_t WorldChrMan::getInsByHandle(int32_t handle)
	{
		if (isLoaded())
		{
			uintptr_t(*GetInsByHandle)(int32_t handle);
			*(uintptr_t*)&GetInsByHandle = 0x140601fc0;
			return GetInsByHandle(handle);
		}
		return NULL;
	}

	std::array<float, 3> WorldChrMan::getCamVector()
	{

		std::array<float, 3> quaternion;
		if (isLoaded())
		{
			memcpy(&quaternion[0], accessMultilevelPointer<float>(getAddress() + 0x31A0, 0x30), sizeof(float) * 3);
		}
		return quaternion;
	}

	PlayerIns WorldChrMan::getMainChr()
	{
		return PlayerIns(*accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan, 0x80));
	}

	bool WorldChrMan::isMainChrLoaded()
	{
		if (WorldChrMan::isLoaded())
			return accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan, 0x80);
		return false;
	}

	uintptr_t WorldChrMan::getAddress()
	{
		return *accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan);
	}

	bool WorldChrMan::isLoaded()
	{
		return accessMultilevelPointer<uintptr_t>(DataBaseAddress::WorldChrMan) != nullptr;
	}

};