/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
//#include <ds3runtime/scripts/param_patcher.h>

//#include "ds3runtime/scripts/animation_id_handler.h"
#include "GameObjects/player_game_data.h"

namespace hoodie_script {

class StandardPlayerBoss
{
public:
	StandardPlayerBoss()
	{
	}
	
	void replacePlayerAnibndFile(std::filesystem::path path);

	void restoreVannilaPlayerAnibndFile();

	void giveItemAndSwap(InventorySlot inventorySlot,
		ItemParamIdPrefix paramIdPrefix,
		int32_t paramItemId,
		int32_t durability);

	void ReplaceItem(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemIdTarget, int32_t paramItemIdReplacement, int32_t durability);

	void RemoveItemFromInventory(InventorySlot slot, ItemParamIdPrefix paramIdPrefix);

	void RemoveItemFromInventory(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId);

	int32_t GetInventorySlotDurability(InventorySlot slot, ItemParamIdPrefix paramIdPrefix);

	void giveGoodsAndSwap(GoodsSlot inventorySlot,
		int32_t paramItemId, int32_t quantity);

	void tryReloadPlayerChr();

	bool isAnimationPresent(int32_t animationId);

	void setSheathStateNetworked(int32_t newSheatState);
private:
	//static uintptr_t* GetRowAddressInParam(int RowID, uintptr_t paramPtr);
	std::vector<InventoryItemInternal> savedItems;
	std::unordered_map<InventorySlot, std::optional<InventoryItemInternal>> savedEquipment;
	std::unordered_map<GoodsSlot, std::optional<InventoryItemInternal>> savedGoods;
	std::unordered_map<int32_t, int32_t> savedSpells;
	std::wstring savedName;
	Attributes savedAttributes;
	PlayerGameData::Gender savedGender;
	PlayerGameData::Class savedClass;
	PlayerGameData::Age savedAge;
	PlayerGameData::Voice savedVoice;
	BodyProportions savedBodyProportions;

	std::optional<int32_t> findInventoryIdByGiveId(int32_t giveId);

	void savePlayerData();

	void saveEquipment();

	void saveAndDiscardItems();

	ItemParamIdPrefix getItemParamIdPrefixFromGiveId(int32_t giveId);

	bool isHiddenItem(const uint32_t itemId);

	int32_t getItemMaxDurability(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId);
protected:
	void restorePlayerData();

	void unequipAllEquipment();

	void reequipSavedEquipment();

	void loadAndGiveSavedItems();

	void clearInventory();
};

}