#pragma once
#include "GameObjects/sprj_gaitem_ins.h"
namespace hoodie_script
{
	struct InventoryItemInternal
	{
		uint32_t uniqueId;
		int32_t giveId;
		uint32_t quantity;
		int32_t unknown1;
	};

	enum class ItemParamIdPrefix : int32_t
	{
		Weapon = 0,
		Protector = 0x10000000,
		Accessory = 0x20000000,
		Goods = 0x40000000,
	};

	class InventoryItem
	{
	public:
		InventoryItem(int32_t inventoryIndex, uint32_t uniqueid, int32_t itemId, uint32_t quantity, int32_t unknown1, ItemParamIdPrefix itemType);
		InventoryItem(InventoryItemInternal* itemStructPtr, size_t gameInventoryIndex);
		int32_t inventoryIndex;
		uint32_t uniqueId;
		int32_t itemId;
		uint32_t quantity;
		int32_t unknown1;
		ItemParamIdPrefix itemType;
		SprjGaitemIns GetGaitemInstance();
	private:
	};
}