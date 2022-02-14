/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
#include "equip_game_data.h"

namespace hoodie_script {

	struct Attributes
	{
		int32_t vigor;
		int32_t attunement;
		int32_t endurance;
		int32_t strength;
		int32_t dexterity;
		int32_t intelligence;
		int32_t faith;
		int32_t luck;
		int32_t unknown1;
		int32_t humanity;
		int32_t vitality;
		int32_t soulLevel;

		bool operator==(const Attributes& other) const
		{
			return vigor == other.vigor
				&& attunement == other.attunement
				&& endurance == other.endurance
				&& strength == other.dexterity
				&& dexterity == other.dexterity
				&& intelligence == other.intelligence
				&& faith == other.faith
				&& luck == other.luck
				&& vitality == other.vitality
				&& soulLevel == other.soulLevel;
		}
	};

	struct BodyProportions
	{
		float head;
		float upperBody;
		float lowerBody;
		float rightHand;
		float rightLeg;
		float leftHand;
		float leftLeg;
	};

	class PlayerGameData
	{
	public:
		enum class Covenant : uint8_t {
			None = 0,
			BladeOfTheDarkmoon = 1,
			WarriorsOfSunlight = 2,
			MoundMakers = 3,
			SpearsOfTheChurch = 4,
			FingersOfRosaria = 5,
			WatchdogsOfFarron = 6,
			AldrichFaithfuls = 7,
			WayOfBlue = 8,
			BlueSentinels = 9
		};

		enum class InvadeType : int32_t {
			Host = 0,
			SummonWhite = 1,
			SummonRed = 2,
			InvadeRed = 3,
			SummonPurpleWhite = 4,
			SpearsOfTheChurch = 6,
			CovenantBladeOfTheDarkmoon = 7,
			UnusedGuardianOfRosaria = 8,
			CovenantWatchdogsOfFarron = 9,
			CovenantAldrichFaithfuls = 10,
			UnusedAvatar = 11,
			ArenaBrawl = 12,
			UnusedUmbasaWhite = 13,
			SummonSunlightWhite = 14,
			SummonSunlightDark = 15,
			SummonPurpleDark = 16,
			InvadeSunlightDark = 17,
			InvadePurpleDark = 18,
			UnusedForceJoinSession = 19,
			UnusedRedHunter = 20,
			BlueSentinels = 21
		};

		enum class Voice : uint8_t {
			Young = 0,
			Mature = 1,
			Aged = 2,
			None = 174
		};

		enum class Class : uint8_t {
			Knight = 0,
			Mercenary = 1,
			Warrior = 2,
			Herald = 3,
			Thief = 4,
			Assassin = 5,
			Sorcerer = 6,
			Pyromancer = 7,
			Cleric = 8,
			Deprived = 9
		};

		enum class Gender : uint8_t {
			Female = 0,
			Male = 1
		};

		enum class Age : uint8_t {
			Young = 0,
			Mature = 1,
			Aged = 2,
			Gael = 3
		};

		PlayerGameData(uintptr_t address);

		/**
		* Gets this players numeber, which is used to identify unique players in online sessions.
		*
		* @return The player number.
		*/
		int32_t getPlayerNo() const;

		/**
		* Gets the voice type of his player.
		*
		* @return The player's voice type.
		*/
		Voice getVoice() const;

		/**
		* Sets the voice type of his player.
		*
		* @param voice The voice type to give to the player.
		*/
		void setVoice(const Voice& voice);

		/**
		* Gets the starting class of this player.
		*
		* @return The starting class of this player.
		*/
		Class getClass() const;

		/**
		* Sets the starting class of this player.
		*
		* @param chrClass The starting class to set for this player.
		*/
		void setClass(const Class& chrClass);

		/**
		* Gets the gender of this player.
		*
		* @return This player's gender.
		*/
		Gender getGender() const;

		/**
		* Sets the gender of this player.
		*
		* @param gender The gender to set for this player.
		*/
		void setGender(const Gender& gender);

		/**
		* Gets the age type of this player.
		*
		* @return The age type of this player.
		*/
		Age getAge() const;

		/**
		* Sets the age type of this player.
		*
		* @param age The age type to set for this player.
		*/
		void setAge(const Age& age);

		/**
		* Gets the face data of this player.
		*
		* @return The face data of this player.
		*/
		std::array<uint8_t, 256> getFaceData() const;

		/**
		* Sets the face data of this player.
		*
		* @param faceData The face data to set for this player.
		*/
		void setFaceData(const std::array<uint8_t, 256>& faceData);

		/**
		* Gets the body proportions of this player.
		*
		* @return The body preportions of this player.
		*/
		BodyProportions getBodyProportions() const;

		void setBodyPreportions(const BodyProportions& bodyPreportions);

		/**
		* Gets the attributes(also known as stats) of this player.
		*
		* @return The attributes of this player.
		*/
		Attributes getAttributes() const;

		/**
		* Sets the attributes(also known as stats) of this player.
		*
		* If you wish to edit the attributes and still have them add up, you'll need to add up the attributes up and use a formula to determine the soul level.
			  Do not add the values of humanity and unknown1 as those are both unused. Here is the formula:
		*
		* SoulLevel = AttributesTotal - 89
		*
		* @param attributes The attributes to set for this player.
		*/
		void setAttributes(const Attributes& attributes);

		/**
		* Gets the name of this player.
		*
		* @return This player's name.
		*/
		std::wstring getName() const;

		/**
		* Sets the name of this player.
		*
		* @param name The name to set for this player.
		*/
		void setName(const std::wstring& name);

		/**
		* Gets the current covenant of this player.
		*
		* @return The current covenant of this player.
		*/
		Covenant getCovenant();

		/**
		* Sets the current covenant of this player.
		*
		* If you to modify this you'll also need to patch the code writing to this value. It's constantly being updated to match the equippd covenant item.
		*
		* @param covenant The covenant to set for this player.
		*/
		void setCovenant(Covenant covenant);

		/**
		* Gets the invasion type of this player.
		*
		* The invasion type simply identifies a catagory which describes how & why a player entered a session, what they are there to do, and how they
		* interact with others and objects within the session.
		*
		* @return The invasion type of this player.
		*/
		InvadeType getInvadeType() const;

		/**
		* Sets the invasion type of this player.
		*
		* The invasion type simply identifies a catagory which describes how & why a player entered a session, what they are there to do, and how they
		* interact with others and objects within the session.
		*
		* @param invadeType The invasion type to set for this player.
		*/
		void setInvadeType(const InvadeType& invadeType);

		/**
		* Gets the spell in the specified spell slot of this PlayerIns in the game's memory.
		*
		* @param slotNumber The spell slot to get the ring from, must be a integer ranging 1-14.
		* @return magicParamId of the spell in this slot.
		*/
		int32_t getSpell(const uint32_t& slotNumber) const;

		/**
		* Sets the spell in the specified attunment slot of this PlayerIns in the game's memory.
		*
		* Setting this value may not result in expected behaivor, to learn more read this header's documentation
		* at the top of the file.
		*
		* @param slotNumber The attunement slot to put the spell in, must be an integer ranging 1-14.
		* @param magicId magicParamId of the spell to put in this slot.
		*/
		void setSpell(const uint32_t& slotNumber, const int32_t& magicId);

		uint8_t getGesture(const uint32_t& slotNumber) const;

		void setGesture(const uint32_t& slotNumber, const uint8_t& gestureId);

		/**
		* Gets the virtual address of this player's EquipGameData.
		*
		* @return The virtual address of this player's EquipGameData.
		*/
		EquipGameData getEquipGameData();

		/**
		* Gets the weapon sheath data of this player.
		*
		* This is a combination of the weapon sheath state and selected weapon slots compressed down into 2 bytes for a network packet.
		*
		* @return The weapon sheath data of this player.
		*/
		uint16_t getWeaponSheathData() const;

		/**
		* Gets the selected left hand weapon slot number of this player.
		*
		* The slot numbers range 0-2.
		*
		* @return The selected left hand slot number.
		*/
		int32_t getActiveLeftHandSlot() const;

		/**
		* Sets the selected left hand weapon slot number of this player.
		*
		* The slot numbers range 0-2.
		*
		* @param slot The slot to set as currently selected.
		*/
		void setActiveLeftHandSlot(const int32_t& slot);

		/**
		* Gets the selected right hand weapon slot number of this player.
		*
		* The slot numbers range 0-2.
		*
		* @return The selected right hand slot number.
		*/
		int32_t getActiveRightHandSlot() const;

		/**
		* Sets the selected right hand weapon slot number of this player.
		*
		* The slot numbers range 0-2.
		*
		* @param slot The slot to set as currently selected.
		*/
		void setActiveRightHandSlot(const int32_t& slot);

		/**
		* Gets the weapon sheath state of this player.
		*
		* The weapon sheath state simply identifies the way the player is holding their weapon, or they way have their right and left hand weapons sheathed.
		*
		* @return The weapon sheath state of this player.
		*/
		int32_t getWeaponSheathState() const;

		/**
		* Sets the weapon sheath state of this player.
		*
		* The weapon sheath state simply identifies the way the player is holding their weapon, or they way have their right and left hand weapons sheathed.
		*
		* @param state The weapon sheath state to set for this player.
		*/
		void setWeaponSheathState(const int32_t& state);

		int32_t getAmmo(uint32_t slotNumber);

		void setAmmo(uint32_t slotNumber, int32_t equipParamAccessoryId);

		int32_t getLeftHandWeapon(uint32_t slotNumber);

		void setLeftHandWeapon(uint32_t slotNumber, int32_t equipParamWeaponId);

		int32_t getLeftHandWeaponActive();

		void setLeftHandWeaponActive(int32_t equipParamWeaponId);

		int32_t getRightHandWeapon(uint32_t slotNumber);

		void setRightHandWeapon(uint32_t slotNumber, int32_t equipParamWeaponId);

		int32_t getRightHandWeaponActive();

		void setRightHandWeaponActive(int32_t equipParamWeaponId);

		int32_t getHead();

		void setHead(int32_t equipParamProtectorId);

		int32_t getChest();

		void setChest(int32_t equipParamProtectorId);

		int32_t getHands();

		void setHands(int32_t equipParamProtectorId);

		int32_t getLegs();

		void setLegs(int32_t equipParamProtectorId);

		int32_t getRing(uint32_t slotNumber);

		void setRing(uint32_t slotNumber, int32_t equipParamAccessoryId);

		uintptr_t getAddress() const;
	private:
		uintptr_t address;
	};

}
