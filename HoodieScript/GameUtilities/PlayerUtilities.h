#pragma once
#include "GameObjects/InventoryItem.h"
#include "GameObjects/equip_game_data.h"

namespace hoodie_script
{
	class PlayerUtilities
	{
	public:
		static void clearInventory();
		static void unequipAllEquipment();
		static void setSheathStateNetworked(uint16_t newSheatState);
		static void ReplaceWeaponRightActiveNetworked(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement);
		static void ReplaceWeaponRightHandBySlotIndexNetworked(uint32_t weaponSlot, int32_t equipParamWeaponTarget, const int32_t equipParamWeaponReplacement);
		static void ReplaceWeaponLeftActiveNetworked(const int32_t& equipParamWeaponTarget, const int32_t equipParamWeaponReplacement);
		static void ReplaceWeaponLeftHandBySlotIndexNetworked(uint32_t weaponSlot, int32_t equipParamWeaponTarget, const int32_t equipParamWeaponReplacement);
		static void ReloadC0000();
		static void giveItemAndEquipInInventorySlot(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemId, int32_t durability);
		static void giveGoodsAndEquipInGoodSlot(GoodsSlot goodsSlot, int32_t paramItemId, int32_t quantity);
	private:
		static void RemoveItemFromInventoryByItemId(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId);
		static int32_t GetInventorySlotDurability(InventorySlot slot);
		static void ReplaceWeaponByInventorySlotNetworked(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemIdTarget, int32_t paramItemIdReplacement, int32_t durability);
		static void RemoveItemFromInventoryByInventorySlot(InventorySlot slot, ItemParamIdPrefix paramIdPrefix);
		static std::optional<int32_t> findInventoryIdByGiveId(int32_t giveId);
		static int32_t getItemMaxDurability(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId);
	};
}