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

	/**
	* Get the instance of PlayerIns by the offset.
	*
	* 0 is the main character you control in the game, 1-5 are the PlayerIns'
	* that may appear in your game via online session.
	*
	* @param offsetNumber The PlayerIns number to get the address of
	* @return The base address of the specified PlayerIns if they exist in memory, otherwise this returns 0.
	*/
	static PlayerIns getPlayerByOffsetNumber(ChrIns::OffsetNumber offsetNumber);
	static bool isLoaded();
	static uintptr_t getAddress();
private:
};

}