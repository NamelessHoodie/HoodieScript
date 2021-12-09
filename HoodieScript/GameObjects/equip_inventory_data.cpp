#pragma once

#include "pch.h"
#include "equip_inventory_data.h"
#include "databaseaddress.h"
#include "memory_util.h"

namespace hoodie_script {

EquipInventoryData::EquipInventoryData(uintptr_t address)
{
	this->address = address;
}

void EquipInventoryData::discardInventoryItems(int32_t inventoryItemId, int32_t quantity)
{
	void (*DiscardItems)(...);
	*(uintptr_t*)&DiscardItems = 0x140a28eb0;
	DiscardItems(address + 0x10, inventoryItemId);
}

void EquipInventoryData::addItem(ItemParamIdPrefix paramIdPrefix, int32_t paramId, uint32_t quantity, int32_t durability)
{
	int32_t data[2] = {};
	*(int32_t*)data = durability;
	void (*AddItem)(...);
	*(uintptr_t*)&AddItem = 0x14058aa20;
	AddItem(address, paramIdPrefix, paramId, quantity, data);
}

InventoryItem* EquipInventoryData::getInventoryItemById(int32_t inventoryItemId)
{
	uintptr_t (*GetInventoryItem)(...);
	*(uintptr_t*)&GetInventoryItem = 0x14058cb30;
	return reinterpret_cast<InventoryItem*>(GetInventoryItem(address, inventoryItemId));
}

int32_t EquipInventoryData::getInventoryItemCount()
{
	return *accessMultilevelPointer<int32_t>(address + 0x88) + 1;
}

bool FOLWisHiddenItem(const uint32_t itemId)
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

std::vector<InventoryItemLua> EquipInventoryData::GetInventoryItems()
{
	std::vector<InventoryItemLua> lst;
	for (int32_t i = 0; i < getInventoryItemCount(); i++) {
		auto* item = getInventoryItemById(i);
		if (item == nullptr) continue;
		int32_t itemId = item->giveId;

		ItemParamIdPrefix itemType;

		if (itemId >= (int32_t)ItemParamIdPrefix::Goods)
		{
			itemId -= (int32_t)ItemParamIdPrefix::Goods;
			itemType = ItemParamIdPrefix::Goods;
		}
		else if (itemId >= (int32_t)ItemParamIdPrefix::Accessory)
		{
			itemId -= (int32_t)ItemParamIdPrefix::Accessory;
			itemType = ItemParamIdPrefix::Accessory;
		}
		else if (itemId >= (int32_t)ItemParamIdPrefix::Protector)
		{
			itemId -= (int32_t)ItemParamIdPrefix::Protector;
			itemType = ItemParamIdPrefix::Protector;
		}
		else
		{
			itemType = ItemParamIdPrefix::Weapon;
		}
		lst.push_back(InventoryItemLua(i, item->uniqueId, itemId, item->quantity, item->unknown1, itemType));
	}
	//std::cout << "Constructing\n";
	//InventoryItem* structPtr = getInventoryItemById(invId);
	//std::cout << std::hex << structPtr << "\n";
	//InventoryItem structVar = InventoryItem(structPtr->uniqueId ,structPtr->giveId, structPtr->quantity, structPtr->unknown1);
	//std::cout << "Sending\n";
	return lst;
}

}