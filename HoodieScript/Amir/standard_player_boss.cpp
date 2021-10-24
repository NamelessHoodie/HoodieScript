#pragma once

#include "pch.h"
#include "standard_player_boss.h"

namespace hoodie_script {

std::optional<uintptr_t> StandardPlayerBoss::getChrAddress()
{
	if (PlayerIns::isMainChrLoaded() && PlayerIns(PlayerIns::getMainChrAddress()).hasHkbCharacter()) return PlayerIns::getMainChrAddress();
	return {};
}

void StandardPlayerBoss::savePlayerData()
{
	PlayerIns chr(getChrAddress().value());
	PlayerGameData playerGameData(chr.getPlayerGameData());
	savedBodyProportions = playerGameData.getBodyProportions();
	savedAttributes = playerGameData.getAttributes();
	savedGender = playerGameData.getGender();
	savedClass = playerGameData.getClass();
	savedAge = playerGameData.getAge();
	savedVoice = playerGameData.getVoice();
}

void StandardPlayerBoss::restorePlayerData()
{
	PlayerIns chr(getChrAddress().value());
	PlayerGameData playerGameData(chr.getPlayerGameData());
	playerGameData.setBodyPreportions(savedBodyProportions);
	playerGameData.setAttributes(savedAttributes);
	playerGameData.setGender(savedGender);
	playerGameData.setClass(savedClass);
	playerGameData.setAge(savedAge);
	playerGameData.setVoice(savedVoice);
}

void StandardPlayerBoss::giveGoodsAndSwap(GoodsSlot goodsSlot,
	int32_t paramItemId, int32_t quantity)
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());
	std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
	
	if (!indexOfItem.has_value()) {
		equipInventoryData.addItem(ItemParamIdPrefix::Goods, paramItemId, quantity, 0);
		indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
	}

	if (indexOfItem.has_value()) {
		equipGameData.equipGoodsInventoryItem(goodsSlot, indexOfItem.value());
	}
}

void StandardPlayerBoss::giveItemAndSwap(InventorySlot inventorySlot,
	ItemParamIdPrefix paramIdPrefix,
	int32_t paramItemId,
	int32_t durability)
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());
	std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);

	if (!indexOfItem.has_value()) {
		const int32_t durability = 20; // always gibs at durability -1 //getItemMaxDurability(paramIdPrefix, paramItemId - paramItemId % 100);
		equipInventoryData.addItem(paramIdPrefix, paramItemId, 1, durability);
		indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
	}

	if (indexOfItem.has_value()) {
		equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
		PlayerNetworkSession::queueEquipmentPacket();
	}
}

void StandardPlayerBoss::DoMeme(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemId, int32_t durability, bool networked)
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());
	std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
	if (indexOfItem.has_value())
	{
		equipInventoryData.discardInventoryItems(indexOfItem.value(), 1);
		logging::write_line("Discarded : ", std::to_string(indexOfItem.value()), " EPW = ", std::to_string(paramItemId));
	}
}

void StandardPlayerBoss::SwapItem(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemId, int32_t durability, bool networked)
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());
	std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);

	if (!indexOfItem.has_value()) {
		const int32_t durability = 20; // always gibs at durability -1 //getItemMaxDurability(paramIdPrefix, paramItemId - paramItemId % 100);
		equipInventoryData.addItem(paramIdPrefix, paramItemId, 1, durability);
		indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
		equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
		if (networked)
		{
			PlayerNetworkSession::queueEquipmentPacket();
		}
		//equipInventoryData.discardInventoryItems(indexOfItem.value(), 1);
	}
	else
	{
		equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
		if (networked)
		{
			PlayerNetworkSession::queueEquipmentPacket();
		}
	}
}

std::optional<int32_t> StandardPlayerBoss::findInventoryIdByGiveId(int32_t giveId)
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());
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

void StandardPlayerBoss::saveEquipment()
{
	GameDataMan gameDataMan(GameDataMan::getInstance());
	PlayerGameData playerGameData(gameDataMan.getPlayerGameData());
	EquipGameData equipGameData(playerGameData.getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());

	for (int32_t i = 0; i <= 21; i++) {
		if (i == 10 || i == 11 || i == 16) continue;
		const int32_t inventoryItemId = equipGameData.getInventoryItemIdBySlot((InventorySlot)i);
		std::optional<InventoryItem> item;

		if (inventoryItemId != -1) {
			auto* itemPtr = equipInventoryData.getInventoryItemById(inventoryItemId);;
			if (itemPtr != nullptr) item = *itemPtr;
		}

		savedEquipment[(InventorySlot)i] = item;
	}

	for (int32_t i = 0; i <= 0xE; ++i) {
		int32_t inventoryItemId = -1;
		if (i < 10) inventoryItemId = equipGameData.getInventoryItemIdByQuickSlot((GoodsSlot)i);
		else inventoryItemId = equipGameData.getInventoryItemIdByToolbeltSlot((GoodsSlot)i);

		std::optional<InventoryItem> item;

		if (inventoryItemId != -1) {
			auto* itemPtr = equipInventoryData.getInventoryItemById(inventoryItemId);;
			if (itemPtr != nullptr) item = *itemPtr;
		}

		savedGoods[(GoodsSlot)i] = item;
	}

	for (int32_t i = 1; i <= 14; ++i) {
		savedSpells[i] = playerGameData.getSpell(i);
	}
}

void StandardPlayerBoss::unequipAllEquipment()
{
	GameDataMan gameDataMan(GameDataMan::getInstance());
	PlayerGameData playerGameData(gameDataMan.getPlayerGameData());
	EquipGameData equipGameData(playerGameData.getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());

	for (int32_t i = 0; i <= 21; ++i) {
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Weapon, 110000, -1);
			break;
		case 12:
			giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 900000, -1);
			break;
		case 13:
			giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 901000, -1);
			break;
		case 14:
			giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 902000, -1);
			break;
		case 15:
			giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 903000, -1);
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

void StandardPlayerBoss::reequipSavedEquipment()
{
	for (auto entry : savedEquipment) {
		if (!entry.second.has_value()) continue;
		const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(entry.second->giveId);
		uint32_t paramItemId = entry.second->giveId;
		if (prefix != 0) paramItemId = paramItemId % prefix;

		giveItemAndSwap(entry.first, 
			(ItemParamIdPrefix)prefix,
			paramItemId,
			0);
	}

	for (auto entry : savedGoods) {
		if (!entry.second.has_value()) continue;
		const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(entry.second->giveId);
		uint32_t paramItemId = entry.second->giveId;
		if (prefix != 0) paramItemId = paramItemId % prefix;

		giveGoodsAndSwap(entry.first,
			paramItemId, entry.second->quantity);
	}

	for (auto&& entry : savedSpells) {
		GameDataMan gameDataMan(GameDataMan::getInstance());
		PlayerGameData playerGameData(gameDataMan.getPlayerGameData());
		playerGameData.setSpell(entry.first, entry.second);
	}
}

void StandardPlayerBoss::saveAndDiscardItems()
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());

	for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
		auto* item = equipInventoryData.getInventoryItemById(i);
		if (item == nullptr || isHiddenItem(item->giveId)) continue;
		savedItems.push_back(*item);
		if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
		else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
	}
}

void StandardPlayerBoss::loadAndGiveSavedItems()
{
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());

	for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
		auto* item = equipInventoryData.getInventoryItemById(i);
		if (item == nullptr || isHiddenItem(item->giveId)) continue;
		if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
		else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
	}

	for (auto item : savedItems) {
		const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(item.giveId);
		uint32_t paramItemId = item.giveId;
		if (prefix != 0) paramItemId = paramItemId % prefix;
		const int32_t durability = 1;//Always 1 fix this if you need it  //getItemMaxDurability((ItemParamIdPrefix)prefix, paramItemId - paramItemId % 100);
		if ((ItemParamIdPrefix)prefix != ItemParamIdPrefix::Goods) equipInventoryData.addItem((ItemParamIdPrefix)prefix, paramItemId, item.quantity, durability);
		else {
			std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);

			if (!indexOfItem.has_value()) {
				equipInventoryData.addItem(ItemParamIdPrefix::Goods, paramItemId, item.quantity, 0);
				indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
			}
			else {
				equipGameData.modifyInventoryItemQuantity(indexOfItem.value(), (int32_t)item.quantity);
			}
		}
	}
}

ItemParamIdPrefix StandardPlayerBoss::getItemParamIdPrefixFromGiveId(int32_t giveId)
{
	if ((giveId & (uint32_t)ItemParamIdPrefix::Protector) == (uint32_t)ItemParamIdPrefix::Protector) {
		return ItemParamIdPrefix::Protector;
	}
	else if ((giveId & (uint32_t)ItemParamIdPrefix::Accessory) == (uint32_t)ItemParamIdPrefix::Accessory) {
		return ItemParamIdPrefix::Accessory;
	}
	else if ((giveId & (uint32_t)ItemParamIdPrefix::Goods) == (uint32_t)ItemParamIdPrefix::Goods) {
		return ItemParamIdPrefix::Goods;
	}
	else {
		return ItemParamIdPrefix::Weapon;
	}
}


bool StandardPlayerBoss::isHiddenItem(const uint32_t itemId)
{
	static std::vector<uint32_t> hiddenItems = {
		0xFFFFFF,
		(uint32_t)ItemParamIdPrefix::Weapon + 110000u,
		(uint32_t)ItemParamIdPrefix::Protector + 900000u,
		(uint32_t)ItemParamIdPrefix::Protector + 901000u,
		(uint32_t)ItemParamIdPrefix::Protector + 902000u,
		(uint32_t)ItemParamIdPrefix::Protector + 903000u,
	};

	for (uint32_t hiddenItemId : hiddenItems) {
		if (hiddenItemId == itemId) return true;
	}

	return false;
}

//uintptr_t* StandardPlayerBoss::GetRowAddressInParam(int RowID, uintptr_t paramPtr) { this is not good, make sure to fix it if you use it.
//	int num = 0;
//	byte* param = (byte*)paramPtr;
//	byte* DataOffset = param + (byte)0x40;
//	if (*(unsigned int*)DataOffset == RowID) {
//		return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
//	}
//	while (true) {
//		num += 1;
//		DataOffset += (byte)0x18;
//		if (*(unsigned int*)DataOffset == 0) {
//			std::cout << "Row ID: " << std::dec << RowID << " Was Not Found" << std::endl;
//			return nullptr;
//		}
//		else if (*(unsigned int*)DataOffset == RowID) {
//			return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
//		}
//	}
//}

//int32_t StandardPlayerBoss::getItemMaxDurability(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId)
//{
//
//	//uintptr_t* EquiParamWeapon = accessMultilevelPointer<uintptr_t>(0x144782838, 0x70, 0x68, 0x68, 0x0);
//
//
//	auto* paramPatcher = (ParamPatcher*)ds3runtime_global->accessScript("param_patcher");
//
//	if (paramIdPrefix == ItemParamIdPrefix::Weapon 
//		&& paramPatcher->doesIdExistInParam(L"EquipParamWeapon", paramItemId)) {
//		ParamHandler weapon("", L"EquipParamWeapon", paramItemId);
//		return weapon.read<uint16_t>(0xBE);
//	}
//	else if (paramIdPrefix == ItemParamIdPrefix::Protector
//		&& paramPatcher->doesIdExistInParam(L"EquipParamProtector", paramItemId)) {
//		ParamHandler protector("", L"EquipParamProtector", paramItemId);
//		return protector.read<uint16_t>(0xAC);
//	}
//	else {
//		return 0;
//	}
//}

void StandardPlayerBoss::tryReloadPlayerChr()
{
	std::optional<WorldChrMan> worldChrMan;
	if (WorldChrMan::hasInstance()) worldChrMan = WorldChrMan::getInstance();
	if (!worldChrMan.has_value() || !PlayerIns::isMainChrLoaded() || !accessMultilevelPointer<uintptr_t>(PlayerIns::getMainChrAddress() + 0x1F90, 0x58, 0x8, 0x1F90, 0x28, 0x10, 0x28, 0xB8)) return;
	worldChrMan->reloadCharacterFiles(L"c0000");
}

void StandardPlayerBoss::setSheathState(int32_t slot)
{
	if (!GameDataMan::hasInstance()
		|| GameDataMan(GameDataMan::getInstance()).getPlayerGameData() == 0) return;
	PlayerGameData playerGameData = GameDataMan(GameDataMan::getInstance()).getPlayerGameData();
	playerGameData.setWeaponSheathState(slot);
	uint16_t sheathData[2] = {};
	sheathData[0] = playerGameData.getWeaponSheathData();
	sheathData[1] = PlayerIns(getChrAddress().value()).getForwardId();
	PlayerNetworkSession session(PlayerNetworkSession::getInstance());
	session.sessionPacketSend(13, (char*)sheathData, 4);
}

void StandardPlayerBoss::clearInventory() {
	EquipGameData equipGameData(PlayerGameData(GameDataMan(GameDataMan::getInstance()).getPlayerGameData()).getEquipGameData());
	EquipInventoryData equipInventoryData(equipGameData.getEquipInventoryData());

	for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
		auto* item = equipInventoryData.getInventoryItemById(i);
		if (item == nullptr || isHiddenItem(item->giveId)) continue;
		if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
		else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
	}
}
}