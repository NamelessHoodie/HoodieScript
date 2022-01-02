/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
#include "GameObjects/equip_game_data.h"
#include "GameObjects/player_game_data.h"
//#include <ds3runtime/scripts/param_patcher.h>
#include "GameDebugClasses/game_data_man.h"
#include <databaseaddress.h>
#include <GameDebugClasses/world_chr_man.h>
#include <GameDebugClasses/game_option_man.h>
//#include "ds3runtime/scripts/animation_id_handler.h"
#include <Amir/player_network_session.h>
#include <Hooks/hkb_animation_hook.h>
#include "GameObjects/player_ins.h"
#include "script_runtime.h"

namespace hoodie_script {

class StandardPlayerBoss
{
public:
	StandardPlayerBoss()
	{
	}
	
	virtual std::optional<uintptr_t> getChrAddress();

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

	void setSheathState(int32_t slot);
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