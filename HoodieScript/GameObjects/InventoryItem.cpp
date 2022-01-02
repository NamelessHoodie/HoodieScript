#include "pch.h"
#include "InventoryItem.h"

namespace hoodie_script
{
	InventoryItem::InventoryItem(int32_t inventoryIndexArg, uint32_t uniqueidArg, int32_t itemIdArg, uint32_t quantityArg, int32_t unknown1Arg, ItemParamIdPrefix itemTypeArg)
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
		int32_t notFullyQualifiedItemId = itemStructPtr->giveId;
		ItemParamIdPrefix varItemType;

		if (notFullyQualifiedItemId >= (int32_t)ItemParamIdPrefix::Goods)
		{
			notFullyQualifiedItemId -= (int32_t)ItemParamIdPrefix::Goods;
			varItemType = ItemParamIdPrefix::Goods;
		}
		else if (itemId >= (int32_t)ItemParamIdPrefix::Accessory)
		{
			notFullyQualifiedItemId -= (int32_t)ItemParamIdPrefix::Accessory;
			varItemType = ItemParamIdPrefix::Accessory;
		}
		else if (itemId >= (int32_t)ItemParamIdPrefix::Protector)
		{
			notFullyQualifiedItemId -= (int32_t)ItemParamIdPrefix::Protector;
			varItemType = ItemParamIdPrefix::Protector;
		}
		else
		{
			varItemType = ItemParamIdPrefix::Weapon;
		}
		this->inventoryIndex = gameInventoryIndex;
		this->uniqueId = itemStructPtr->uniqueId;
		this->itemId = notFullyQualifiedItemId;
		this->quantity = itemStructPtr->quantity;
		this->unknown1 = itemStructPtr->unknown1;
		this->itemType = varItemType;
	}

	SprjGaitemIns InventoryItem::GetGaitemInstance()
	{
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