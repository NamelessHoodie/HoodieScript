#include "pch.h"
#include "PlayerUtilities.h"
#include <Amir/player_network_session.h>
#include "GameDebugClasses/game_data_man.h"
#include "GameDebugClasses/world_chr_man.h"
#include <script_runtime.h>

namespace hoodie_script
{

	void PlayerUtilities::clearInventory() {
		EquipGameData equipGameData = PlayerIns::getMainChr().
			getPlayerGameData().
			getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		auto inventoryItems = equipInventoryData.GetInventoryItems();
		for (auto i = inventoryItems.begin(); i != inventoryItems.end(); i++) {
			auto inventoryItem = *i;
			if (inventoryItem.itemType != ItemParamIdPrefix::Goods)
				equipInventoryData.discardInventoryItems(inventoryItem.inventoryIndex,
					inventoryItem.quantity);
			else equipGameData.modifyInventoryItemQuantity(inventoryItem.inventoryIndex,
				-(int32_t)inventoryItem.quantity);
		}
	}

	void PlayerUtilities::setSheathStateNetworked(uint16_t newSheatState)
	{
		if (!PlayerIns::isMainChrLoaded())
			return;

		auto playableCharacter = PlayerIns::getMainChr();
		if (!playableCharacter.hasHkbCharacter())
			return;

		playableCharacter.setWeaponSheathState(newSheatState);
		uint16_t sheathData[2] = { newSheatState, PlayerIns::getMainChr().getForwardId() };
		PlayerNetworkSession session(PlayerNetworkSession::getInstance());
		session.sessionPacketSend(13, (char*)sheathData, 4);
	}

	int32_t PlayerUtilities::GetInventorySlotDurability(InventorySlot slot)
	{
		EquipGameData equipGameData = PlayerIns::getMainChr().
												 getPlayerGameData().
												 getEquipGameData();

		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		auto index = equipGameData.getInventoryItemIdBySlot(slot);
		auto inventoryItemInternal = equipInventoryData.getInventoryItemById(index);
		InventoryItem inventoryItem = InventoryItem(inventoryItemInternal, index);
		std::cout << std::dec << "InventoryItem : Index = " << inventoryItem.inventoryIndex << ", " << "UID = " << std::hex << inventoryItem.uniqueId << ", " << "ItemId = " << std::dec << inventoryItem.itemId << ", " << "ItemType = " << std::hex << (int32_t)inventoryItem.itemType << ", " << "Quantity = " << std::dec << inventoryItem.quantity << ", " << std::hex << "Unk1 = " << inventoryItem.unknown1 << std::endl;
		auto gaitemIns = inventoryItem.GetGaitemInstance();
		if (gaitemIns.isValid())
		{
			return gaitemIns.getDurability();
		}
		return 0;
	}

	void PlayerUtilities::RemoveItemFromInventoryByItemId(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId)
	{
		EquipGameData equipGameData = PlayerIns::getMainChr().
			getPlayerGameData().
			getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
		if (indexOfItem.has_value())
		{
			auto a = equipInventoryData.getInventoryItemById(indexOfItem.value());
			equipInventoryData.discardInventoryItems(indexOfItem.value(), 1);
		}
	}

	void PlayerUtilities::ReplaceWeaponRightActiveNetworked(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement)
	{
		if (!PlayerIns::isMainChrLoaded())
			return;

		PlayerIns mainPlayer = PlayerIns::getMainChr();
		auto rightWeaponActiveIndex = mainPlayer.GetActiveWeaponSlotRightHand();

		ReplaceWeaponRightHandBySlotIndexNetworked(rightWeaponActiveIndex, equipParamWeaponTarget, equipParamWeaponReplacement);
	}

	void PlayerUtilities::ReplaceWeaponLeftActiveNetworked(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement)
	{
		if (!PlayerIns::isMainChrLoaded())
			return;

		PlayerIns mainPlayer = PlayerIns::getMainChr();
		auto leftWeaponActiveIndex = mainPlayer.GetActiveWeaponSlotLeftHand();

		ReplaceWeaponLeftHandBySlotIndexNetworked(leftWeaponActiveIndex, equipParamWeaponTarget, equipParamWeaponReplacement);
	}

	void  PlayerUtilities::ReplaceWeaponLeftHandBySlotIndexNetworked(uint32_t weaponSlot, int32_t equipParamWeaponTarget, const int32_t equipParamWeaponReplacement)
	{
		int array[]{ 0,2,4 };
		ReplaceWeaponByInventorySlotNetworked((InventorySlot)array[weaponSlot], ItemParamIdPrefix::Weapon, equipParamWeaponTarget, equipParamWeaponReplacement, -1);
	}

	void  PlayerUtilities::ReplaceWeaponRightHandBySlotIndexNetworked(uint32_t weaponSlot, int32_t equipParamWeaponTarget, const int32_t equipParamWeaponReplacement)
	{
		int array[]{ 1,3,5 };
		ReplaceWeaponByInventorySlotNetworked((InventorySlot)array[weaponSlot], ItemParamIdPrefix::Weapon, equipParamWeaponTarget, equipParamWeaponReplacement, -1);
	}

	void PlayerUtilities::ReplaceWeaponByInventorySlotNetworked(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemIdTarget, int32_t paramItemIdReplacement, int32_t durability)
	{
		if (!PlayerIns::isMainChrLoaded() || !PlayerIns::getMainChr().hasPlayerGameData())
			return;


		if (durability == -1)
			durability = GetInventorySlotDurability(inventorySlot);
		else
			durability = getItemMaxDurability(paramIdPrefix, paramItemIdReplacement);

		PlayerGameData playerGameData = GameDataMan::getInstance().getPlayerGameData();
		auto sheatState = playerGameData.getWeaponSheathState();
		RemoveItemFromInventoryByInventorySlot(inventorySlot, paramIdPrefix);
		giveItemAndEquipInInventorySlot(inventorySlot, paramIdPrefix, paramItemIdReplacement, durability);
		setSheathStateNetworked(sheatState);
	}

	void PlayerUtilities::ReloadC0000()
	{
		if (PlayerIns::isMainChrLoaded())
			return;
		if (!accessMultilevelPointer<uintptr_t>(PlayerIns::getMainChr().getAddress() + 0x1F90, 0x58, 0x8, 0x1F90, 0x28, 0x10, 0x28, 0xB8))
			return;
		WorldChrMan::reloadCharacterFiles(L"c0000");
	}

	int32_t PlayerUtilities::getItemMaxDurability(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId)
	{
		uint16_t durabilityStage;
		if (paramIdPrefix == ItemParamIdPrefix::Weapon)
		{
			if (hoodie_script::script_runtime::paramPatcher->GetParamEntry(L"EquipParamWeapon", paramItemId, 0xBE, &durabilityStage))
			{
				return (int16_t)(durabilityStage);
			}
			else
			{
				return NULL;
			}
		}
		else if (paramIdPrefix == ItemParamIdPrefix::Protector)
		{
			if (script_runtime::paramPatcher->GetParamEntry(L"EquipParamProtector", paramItemId, 0xAC, &durabilityStage))
			{
				std::cout << durabilityStage << std::endl;
				return (int16_t)(durabilityStage);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}

	void PlayerUtilities::RemoveItemFromInventoryByInventorySlot(InventorySlot slot, ItemParamIdPrefix paramIdPrefix)
	{
		EquipGameData equipGameData = PlayerIns::getMainChr().
			getPlayerGameData().
			getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		auto index = equipGameData.getInventoryItemIdBySlot(slot);
		giveItemAndEquipInInventorySlot(slot, paramIdPrefix, 110000, -1);
		equipInventoryData.discardInventoryItems(index, 1);
	}

	void PlayerUtilities::unequipAllEquipment()
	{
		GameDataMan gameDataMan = GameDataMan::getInstance();
		PlayerGameData playerGameData = gameDataMan.getPlayerGameData();
		EquipGameData equipGameData = playerGameData.getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i <= 21; ++i) {
			switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				giveItemAndEquipInInventorySlot((InventorySlot)i, ItemParamIdPrefix::Weapon, 110000, -1);
				break;
			case 12:
				giveItemAndEquipInInventorySlot((InventorySlot)i, ItemParamIdPrefix::Protector, 900000, -1);
				break;
			case 13:
				giveItemAndEquipInInventorySlot((InventorySlot)i, ItemParamIdPrefix::Protector, 901000, -1);
				break;
			case 14:
				giveItemAndEquipInInventorySlot((InventorySlot)i, ItemParamIdPrefix::Protector, 902000, -1);
				break;
			case 15:
				giveItemAndEquipInInventorySlot((InventorySlot)i, ItemParamIdPrefix::Protector, 903000, -1);
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			{
				equipGameData.equipInventoryItem((InventorySlot)i, -1);
				break;
			}
			default:
				break;
			}
		}

		for (int32_t i = 0; i <= 0xE; ++i) {
			equipGameData.equipGoodsInventoryItem((GoodsSlot)i, -1);
		}

		for (int32_t i = 1; i <= 14; ++i) {
			playerGameData.setSpell(i, -1);
		}
	}

	std::optional<int32_t> PlayerUtilities::findInventoryIdByGiveId(int32_t giveId)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().
			getPlayerGameData().
			getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem;

		for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
			auto* item = equipInventoryData.getInventoryItemById(i);

			if (item != nullptr && item->giveId == giveId) {
				indexOfItem = i;
				break;
			}
		}

		return indexOfItem;
	}

	void PlayerUtilities::giveItemAndEquipInInventorySlot(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemId, int32_t durability)
	{
		EquipGameData equipGameData = PlayerIns::getMainChr().
			getPlayerGameData().
			getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);

		if (!indexOfItem.has_value()) {
			equipInventoryData.addItem(paramIdPrefix, paramItemId, 1, durability);
			indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
			equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
			PlayerNetworkSession::queueEquipmentPacket();
		}
		else
		{
			equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
			PlayerNetworkSession::queueEquipmentPacket();
		}
	}

	void PlayerUtilities::giveGoodsAndEquipInGoodSlot(GoodsSlot goodsSlot, int32_t paramItemId, int32_t quantity)
	{
		if (!PlayerIns::isMainChrLoaded())
			return;

		EquipGameData equipGameData = PlayerIns::getMainChr().
												 getPlayerGameData().
												 getEquipGameData();

		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);

		if (!indexOfItem.has_value()) {
			equipInventoryData.addItem(ItemParamIdPrefix::Goods, paramItemId, quantity, 0);
			indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
		}

		if (indexOfItem.has_value()) {
			equipGameData.equipGoodsInventoryItem(goodsSlot, indexOfItem.value());
		}
	}
}