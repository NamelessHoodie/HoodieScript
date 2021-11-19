/*
	* DS3RuntimeScripting
	* Contributers: Amir
	* Further notes on how to use this class:
*/

#pragma once

#include "memory_util.h"
#include "GameObjects/chr_ins.h"

namespace hoodie_script {

class WorldChrMan
{
public:
	static std::vector<uintptr_t> getCurrentMapEnemies();

	static bool reloadCharacterFiles(std::wstring characterId);

	static void findEntityTest(int32_t id);

	static uintptr_t getInsByHandle(int32_t handle);

	/**
	* Gets the camera euler angle.
	* 
	* @return The camera euler angle.
	*/
	static std::array<float, 3> getCamVector();

	static uintptr_t getInstance();

	static bool hasInstance();
};

}