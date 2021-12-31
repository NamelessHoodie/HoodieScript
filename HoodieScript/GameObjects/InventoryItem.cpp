#include "pch.h"
#include "InventoryItem.h"

namespace hoodie_script
{
	InventoryItem::InventoryItem(int32_t inventoryIndexArg, uint32_t uniqueidArg, int32_t itemIdArg, uint32_t quantityArg, int32_t unknown1Arg, ItemParamIdPrefix itemTypeArg)
	{
		this->inventoryIndex = inventoryIndexArg;
		this->uniqueId = uniqueidArg;
		//logging::write_line(std::to_string(uniqueidArg));
		this->itemId = itemIdArg;
		this->quantity = quantityArg;
		this->unknown1 = unknown1Arg;
		this->itemType = itemTypeArg;
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