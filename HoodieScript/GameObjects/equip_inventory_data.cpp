#include "pch.h"
#include "databaseaddress.h"
#include "memory_util.h"
#include "equip_inventory_data.h"

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

InventoryItemInternal* EquipInventoryData::getInventoryItemById(int32_t inventoryItemId)
{
	uintptr_t (*GetInventoryItem)(...);
	*(uintptr_t*)&GetInventoryItem = 0x14058cb30;
	return reinterpret_cast<InventoryItemInternal*>(GetInventoryItem(address, inventoryItemId));
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

ItemParamIdPrefix EquipInventoryData::getItemParamIdPrefixFromGiveId(int32_t giveId)
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

bool EquipInventoryData::isHiddenItem(const uint32_t itemId)
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

std::vector<InventoryItem> EquipInventoryData::GetInventoryItems()
{
	std::vector<InventoryItem> lst;
	for (int32_t i = 0; i < getInventoryItemCount(); i++) {
		auto* item = getInventoryItemById(i);
		if (item == nullptr) continue;
		lst.push_back(InventoryItem(item, i));
	}
	//std::cout << "Constructing\n";
	//InventoryItem* structPtr = getInventoryItemById(invId);
	//std::cout << std::hex << structPtr << "\n";
	//InventoryItem structVar = InventoryItem(structPtr->uniqueId ,structPtr->giveId, structPtr->quantity, structPtr->unknown1);
	//std::cout << "Sending\n";
	return lst;
}

}