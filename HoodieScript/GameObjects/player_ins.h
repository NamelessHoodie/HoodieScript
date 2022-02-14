/*
	* DS3RuntimeScripting
	* Contributers: Amir
	* Further notes on how to use this class:
	*
	* -EquipData Setters- Online limitations.
	* Setting equipment values is only local and in online session will be reverted as
	* the PlayerIns's game regularly sends their actual equip data.
	*
	* Changing your own PlayerIns's equipdata will not be reverted but not change
	* on other's games unless you send a network packet with the updated data.
	*
	* The game normally sends the equip data of your inventory items rather than
	* the data on these pointers. However your game aside from durablity, UI and
	* other inventory specific things, your game renders and uses the data from the
	* item identified in this pointer.
	*
	* Use this api's network utilites in your scripts to ensure intended behaivor and utilize possible work arounds.
*/

#pragma once
#include "chr_ins.h"
#include "GameObjects/player_game_data.h"

namespace hoodie_script {

	class PlayerIns : public ChrIns
	{
	public:
		PlayerIns(uintptr_t address);

		/**
		* Gets an instance of this Player's PlayerGameData object.
		*
		* @return Virtual address of this Player's PlayerGameData object.
		*/
		PlayerGameData getPlayerGameData();


		/**
		* checks if this player or npc has a PlayerGameData object.
		*
		* @return true if the PlayerGameData is present, false if it isn't.
		*/
		bool hasPlayerGameData();

		EquipGameData getEquipGameData();

		bool hasEquipGameData();

		EquipInventoryData getEquipInventoryData();

		bool hasEquipInventoryData();

		/**
		* Gets the virtual address of this Player's NetworkPointer object.
		*
		* @return Virtual address of this Player's NetworkPointer object.
		*/
		uintptr_t* getNetworkPointer();

		/**
		* Checks if the "No Goods Consume" debug flag is set for this Player. This flag prevents consumption of inventory goods which may allow them to be used
		  infintely.
		*
		* @return True if the "No Goods Consume" debug flag is set for this Player.
		*/
		bool isNoGoodsConsume() const;

		/**
		* Sets the "No Goods Consume" debug flag on or off for this Player. This flag prevents consumption of inventory goods which may allow them to be used
		  infintely.
		*
		* @param value The state to set for the flag.
		*/
		void setNoGoodsConsume(const bool& value);

		/**
		* Gets the virtual address of this Player's PlayerCtrl object.
		*
		* @return Virtual address of this Player's PlayerCtrl object.
		*/
		uintptr_t getPlayerCtrl();


		/**
		* Gets a pointer to this player's network handle on the game's peer-to-peer network.
		*
		* @return Pointer to this player's network handle on the game's peer-to-peer network.
		*/
		uintptr_t* getNetworkHandle();

		/**
		* Check if this refers to a valid PlayerIns object.
		*
		* Peformes several multi-level pointer checks.
		*
		* @return True if PlayerIns is valid.
		*/
		bool isValid();

		/**
		* Get an instance of the main chr(The player charater the game takes the perspective of and allows you to control).
		*
		* @return Virtual address of the main chr.
		*/
		static PlayerIns getMainChr();

		/**
		* Check if this PlayerIns matches the PlayerIns of the main character.
		*
		* @return True if this PlayerIns is the PlayerIns of the main chr.
		*/
		bool isMainChr();

		/**
		* Check if the main chr is loaded(The player charater the game takes the perspective of and allows you to control).
		*
		* @return True if the main chr is loaded
		*/
		static bool isMainChrLoaded();
	};

}
