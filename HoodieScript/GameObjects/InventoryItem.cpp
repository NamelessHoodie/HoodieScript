#include "pch.h"
#include "InventoryItem.h"
#include "GameObjects/equip_inventory_data.h"
#include "GameObjects/sprj_gaitem_Imp.h"

namespace hoodie_script
{
	InventoryItem::InventoryItem(int32_t inventoryIndexArg, uint32_t uniqueidArg, int32_t itemIdArg, uint32_t quantityArg, uint32_t unknown1Arg, ItemParamIdPrefix itemTypeArg)
	{
		this->inventoryIndex = inventoryIndexArg;
		this->uniqueId = uniqueidArg;
		this->itemId = itemIdArg;
		this->quantity = quantityArg;
		this->unknown1 = unknown1Arg;
		this->itemType = itemTypeArg;
	}

	InventoryItem::InventoryItem(InventoryItemInternal* itemStructPtr, size_t gameInventoryIndex)
	{
		int32_t giveId = itemStructPtr->giveId;
		ItemParamIdPrefix varItemType = EquipInventoryData::getItemParamIdPrefixFromGiveId(giveId);
		int32_t notFullyQualifiedItemId = giveId - (int32_t)varItemType;

		this->inventoryIndex = gameInventoryIndex;
		this->uniqueId = itemStructPtr->uniqueId;
		this->itemId = notFullyQualifiedItemId;
		this->quantity = itemStructPtr->quantity;
		this->unknown1 = itemStructPtr->unknown1;
		this->itemType = varItemType;
	}

	SprjGaitemIns InventoryItem::GetGaitemInstance()
	{
		//logging::write_line(std::format("HasGaitemImp = {0}, ItemType = {1}", SprjGaitemImp::hasInstance(), (int32_t)itemType));
		if (SprjGaitemImp::hasInstance() && (itemType == ItemParamIdPrefix::Weapon || itemType == ItemParamIdPrefix::Protector))
		{
			auto a = SprjGaitemImp::getInstance().getItemByUniqueId(this->uniqueId);
			if (a.has_value())
			{
				return SprjGaitemIns(*a);
			}
		}
		return SprjGaitemIns(0);

	}
}