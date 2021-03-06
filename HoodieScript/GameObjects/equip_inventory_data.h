/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#include <GameObjects/InventoryItem.h>

namespace hoodie_script {

class EquipInventoryData
{
public:
	EquipInventoryData(uintptr_t address);
	void discardInventoryItems(int32_t inventoryItemId, int32_t quantity);
	void addItem(ItemParamIdPrefix paramIdPrefix, int32_t paramId, uint32_t quantity, int32_t durability);
	InventoryItemInternal* getInventoryItemById(int32_t inventoryItemId);
	int32_t getInventoryItemCount();
	std::vector<InventoryItem> GetInventoryItems();
	static ItemParamIdPrefix getItemParamIdPrefixFromGiveId(int32_t giveId);
	bool isHiddenItem(const uint32_t itemId);
private:
	uintptr_t address;
};

}