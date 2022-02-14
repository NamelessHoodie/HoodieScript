/*
	* DS3RuntimeScripting
	* Contributers: Amir
	* Further notes on how to use this class:
*/

#pragma once

#include "GameObjects/player_ins.h"

namespace hoodie_script {

class WorldChrMan
{
public:
	static std::vector<uintptr_t> getCurrentMapEnemies();
	static bool reloadCharacterFiles(std::wstring characterId);
	static void findEntityTest(int32_t id);
	static ChrIns getInsByHandle(ChrIns::Handle handle);

	/**
	* Gets the camera euler angle.
	* 
	* @return The camera euler angle.
	*/
	static std::array<float, 3> getCamVector();
	static PlayerIns getMainChr();
	static bool isMainChrLoaded();
	static bool isLoaded();
	static uintptr_t getAddress();
private:
};

}