#pragma once

#include "pch.h"
#include "standard_player_boss.h"

namespace hoodie_script {

	std::optional<uintptr_t> StandardPlayerBoss::getChrAddress()
	{
		if (PlayerIns::isMainChrLoaded() && PlayerIns(PlayerIns::getMainChrAddress()).hasHkbCharacter()) return PlayerIns::getMainChrAddress();
		return {};
	}

	void StandardPlayerBoss::savePlayerData()
	{
		PlayerIns chr(getChrAddress().value());
		PlayerGameData playerGameData = chr.getPlayerGameData();
		savedBodyProportions = playerGameData.getBodyProportions();
		savedAttributes = playerGameData.getAttributes();
		savedGender = playerGameData.getGender();
		savedClass = playerGameData.getClass();
		savedAge = playerGameData.getAge();
		savedVoice = playerGameData.getVoice();
	}

	void StandardPlayerBoss::restorePlayerData()
	{
		PlayerIns chr(getChrAddress().value());
		PlayerGameData playerGameData = chr.getPlayerGameData();
		playerGameData.setBodyPreportions(savedBodyProportions);
		playerGameData.setAttributes(savedAttributes);
		playerGameData.setGender(savedGender);
		playerGameData.setClass(savedClass);
		playerGameData.setAge(savedAge);
		playerGameData.setVoice(savedVoice);
	}

	void StandardPlayerBoss::giveGoodsAndSwap(GoodsSlot goodsSlot,
		int32_t paramItemId, int32_t quantity)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);

		if (!indexOfItem.has_value()) {
			equipInventoryData.addItem(ItemParamIdPrefix::Goods, paramItemId, quantity, 0);
			indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
		}

		if (indexOfItem.has_value()) {
			equipGameData.equipGoodsInventoryItem(goodsSlot, indexOfItem.value());
		}
	}

	void StandardPlayerBoss::giveItemAndSwap(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemId, int32_t durability)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);

		if (!indexOfItem.has_value()) {
			equipInventoryData.addItem(paramIdPrefix, paramItemId, 1, durability);
			indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
			equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
			PlayerNetworkSession::queueEquipmentPacket();
		}
		else
		{
			equipGameData.equipInventoryItem(inventorySlot, indexOfItem.value());
			PlayerNetworkSession::queueEquipmentPacket();
		}
	}

	void StandardPlayerBoss::RemoveItemFromInventory(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)paramIdPrefix + paramItemId);
		if (indexOfItem.has_value())
		{
			auto a = equipInventoryData.getInventoryItemById(indexOfItem.value());
			equipInventoryData.discardInventoryItems(indexOfItem.value(), 1);
		}
	}

	int32_t StandardPlayerBoss::GetInventorySlotDurability(InventorySlot slot, ItemParamIdPrefix paramIdPrefix)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().
												   getPlayerGameData().
												   getEquipGameData();
		EquipInventoryData equipInventoryData = GameDataMan::getInstance().
															 getPlayerGameData().
			                                                 getEquipGameData().
			                                                 getEquipInventoryData();
		auto index = equipGameData.getInventoryItemIdBySlot(slot);
		auto inventoryItemInternal = equipInventoryData.getInventoryItemById(index);
		InventoryItem inventoryItem = InventoryItem(inventoryItemInternal, index);
		auto gaitemIns = inventoryItem.GetGaitemInstance();
		if (gaitemIns.isValid())
		{
			return gaitemIns.getDurability();
		}
		return 0;
	}

	void StandardPlayerBoss::RemoveItemFromInventory(InventorySlot slot, ItemParamIdPrefix paramIdPrefix)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		auto index = equipGameData.getInventoryItemIdBySlot(slot);
		giveItemAndSwap(slot, paramIdPrefix, 110000, -1);
		equipInventoryData.discardInventoryItems(index, 1);
	}

	void StandardPlayerBoss::ReplaceItem(InventorySlot inventorySlot, ItemParamIdPrefix paramIdPrefix, int32_t paramItemIdTarget, int32_t paramItemIdReplacement, int32_t durability)
	{
		if (!GameDataMan::hasInstance() || 
			 GameDataMan::getInstance().
			 getPlayerGameData().
			 getAddress() == 0) 
			return;
		
		if (durability == -1)
			durability = GetInventorySlotDurability(inventorySlot, paramIdPrefix);
		else
			durability = getItemMaxDurability(paramIdPrefix, paramItemIdReplacement);

		PlayerGameData playerGameData = GameDataMan::getInstance().getPlayerGameData();
		auto sheatState = playerGameData.getWeaponSheathState();
		RemoveItemFromInventory(inventorySlot, paramIdPrefix);
		giveItemAndSwap(inventorySlot, paramIdPrefix, paramItemIdReplacement, durability);
		setSheathState(sheatState);
	}

	std::optional<int32_t> StandardPlayerBoss::findInventoryIdByGiveId(int32_t giveId)
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();
		std::optional<int32_t> indexOfItem;

		for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
			auto* item = equipInventoryData.getInventoryItemById(i);

			if (item != nullptr && item->giveId == giveId) {
				indexOfItem = i;
				break;
			}
		}

		return indexOfItem;
	}

	void StandardPlayerBoss::saveEquipment()
	{
		GameDataMan gameDataMan = GameDataMan::getInstance();
		PlayerGameData playerGameData = gameDataMan.getPlayerGameData();
		EquipGameData equipGameData = playerGameData.getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i <= 21; i++) {
			if (i == 10 || i == 11 || i == 16) continue;
			const int32_t inventoryItemId = equipGameData.getInventoryItemIdBySlot((InventorySlot)i);
			std::optional<InventoryItemInternal> item;

			if (inventoryItemId != -1) {
				auto* itemPtr = equipInventoryData.getInventoryItemById(inventoryItemId);;
				if (itemPtr != nullptr) item = *itemPtr;
			}

			savedEquipment[(InventorySlot)i] = item;
		}

		for (int32_t i = 0; i <= 0xE; ++i) {
			int32_t inventoryItemId = -1;
			if (i < 10) inventoryItemId = equipGameData.getInventoryItemIdByQuickSlot((GoodsSlot)i);
			else inventoryItemId = equipGameData.getInventoryItemIdByToolbeltSlot((GoodsSlot)i);

			std::optional<InventoryItemInternal> item;

			if (inventoryItemId != -1) {
				auto* itemPtr = equipInventoryData.getInventoryItemById(inventoryItemId);;
				if (itemPtr != nullptr) item = *itemPtr;
			}

			savedGoods[(GoodsSlot)i] = item;
		}

		for (int32_t i = 1; i <= 14; ++i) {
			savedSpells[i] = playerGameData.getSpell(i);
		}
	}

	void StandardPlayerBoss::unequipAllEquipment()
	{
		GameDataMan gameDataMan = GameDataMan::getInstance();
		PlayerGameData playerGameData = gameDataMan.getPlayerGameData();
		EquipGameData equipGameData = playerGameData.getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i <= 21; ++i) {
			switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Weapon, 110000, -1);
				break;
			case 12:
				giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 900000, -1);
				break;
			case 13:
				giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 901000, -1);
				break;
			case 14:
				giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 902000, -1);
				break;
			case 15:
				giveItemAndSwap((InventorySlot)i, ItemParamIdPrefix::Protector, 903000, -1);
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			{
				equipGameData.equipInventoryItem((InventorySlot)i, -1);
				break;
			}
			default:
				break;
			}
		}

		for (int32_t i = 0; i <= 0xE; ++i) {
			equipGameData.equipGoodsInventoryItem((GoodsSlot)i, -1);
		}

		for (int32_t i = 1; i <= 14; ++i) {
			playerGameData.setSpell(i, -1);
		}
	}

	void StandardPlayerBoss::reequipSavedEquipment()
	{
		for (auto entry : savedEquipment) {
			if (!entry.second.has_value()) continue;
			const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(entry.second->giveId);
			uint32_t paramItemId = entry.second->giveId;
			if (prefix != 0) paramItemId = paramItemId % prefix;

			giveItemAndSwap(entry.first,
				(ItemParamIdPrefix)prefix,
				paramItemId,
				0);
		}

		for (auto entry : savedGoods) {
			if (!entry.second.has_value()) continue;
			const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(entry.second->giveId);
			uint32_t paramItemId = entry.second->giveId;
			if (prefix != 0) paramItemId = paramItemId % prefix;

			giveGoodsAndSwap(entry.first,
				paramItemId, entry.second->quantity);
		}

		for (auto&& entry : savedSpells) {
			GameDataMan gameDataMan = GameDataMan::getInstance();
			PlayerGameData playerGameData = gameDataMan.getPlayerGameData();
			playerGameData.setSpell(entry.first, entry.second);
		}
	}

	void StandardPlayerBoss::saveAndDiscardItems()
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
			auto* item = equipInventoryData.getInventoryItemById(i);
			if (item == nullptr || isHiddenItem(item->giveId)) continue;
			savedItems.push_back(*item);
			if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
			else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
		}
	}

	void StandardPlayerBoss::loadAndGiveSavedItems()
	{
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
			auto* item = equipInventoryData.getInventoryItemById(i);
			if (item == nullptr || isHiddenItem(item->giveId)) continue;
			if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
			else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
		}

		for (auto item : savedItems) {
			const uint32_t prefix = (uint32_t)getItemParamIdPrefixFromGiveId(item.giveId);
			uint32_t paramItemId = item.giveId;
			if (prefix != 0) paramItemId = paramItemId % prefix;
			const int32_t durability = getItemMaxDurability((ItemParamIdPrefix)prefix, paramItemId - paramItemId % 100);
			if ((ItemParamIdPrefix)prefix != ItemParamIdPrefix::Goods) equipInventoryData.addItem((ItemParamIdPrefix)prefix, paramItemId, item.quantity, durability);
			else {
				std::optional<int32_t> indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);

				if (!indexOfItem.has_value()) {
					equipInventoryData.addItem(ItemParamIdPrefix::Goods, paramItemId, item.quantity, 0);
					indexOfItem = findInventoryIdByGiveId((uint32_t)ItemParamIdPrefix::Goods + paramItemId);
				}
				else {
					equipGameData.modifyInventoryItemQuantity(indexOfItem.value(), (int32_t)item.quantity);
				}
			}
		}
	}

	ItemParamIdPrefix StandardPlayerBoss::getItemParamIdPrefixFromGiveId(int32_t giveId)
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


	bool StandardPlayerBoss::isHiddenItem(const uint32_t itemId)
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


	//std::map<std::string, uintptr_t> my_map = {
	//				{"ActionButtonParam", 0xAD8},
	//				{"AiSoundParam", 0xD60},
	//				{"AtkParam_Npc", 0x268},
	//				{"AtkParam_Pc", 0x2B0},
	//				{"AttackElementCorrectParam", 0x1660},
	//				{"BehaviorParam", 0x3D0},
	//				{"BehaviorParam_PC", 0x418},
	//				{"BonfireWarpParam", 0xF10},
	//				{"BudgetParam", 0xEC8},
	//				{"Bullet", 0x388},
	//				{"BulletCreateLimitParam", 0x1780},
	//				{"CalcCorrectGraph", 0x8E0},
	//				{"Ceremony", 0x1078},
	//				{"CharaInitParam", 0x658},
	//				{"CharMakeMenuListItemParam", 0x1150},
	//				{"CharMakeMenuTopParam", 0x1108},
	//				{"ClearCountCorrectParam", 0x17C8},
	//				{"CoolTimeParam", 0x1A98},
	//				{"CultSettingParam", 0x1468},
	//				{"DecalParam", 0xA90},
	//				{"DirectionCameraParam", 0x1390},
	//				{"EquipMtrlSetParam", 0x6A0},
	//				{"EquipParamAccessory", 0x100},
	//				{"EquipParamGoods", 0x148},
	//				{"EquipParamProtector", 0xB8},
	//				{"EquipParamWeapon", 0x70},
	//				{"FaceGenParam", 0x6E8},
	//				{"FaceParam", 0x730},
	//				{"FaceRangeParam", 0x778},
	//				{"FootSfxParam", 0x16F0},
	//				{"GameAreaParam", 0x850},
	//				{"GameProgressParam", 0x1810},
	//				{"GemCategoryParam", 0xC40},
	//				{"GemDropDopingParam", 0xC88},
	//				{"GemDropModifyParam", 0xCD0},
	//				{"GemeffectParam", 0xBF8},
	//				{"GemGenParam", 0xBB0},
	//				{"HitEffectSeParam", 0x1270},
	//				{"HitEffectSfxConceptParam", 0x11E0},
	//				{"HitEffectSfxParam", 0x1228},
	//				{"HPEstusFlaskRecoveryParam", 0x14F8},
	//				{"ItemLotParam", 0x5C8},
	//				{"KnockBackParam", 0xA00},
	//				{"KnowledgeLoadScreenItemParam", 0x18E8},
	//				{"LoadBalancerDrawDistScaleParam", 0x1A50},
	//				{"LoadBalancerParam", 0x1858},
	//				{"LockCamParam", 0x928},
	//				{"Magic", 0x460},
	//				{"MapMimicryEstablishmentParam", 0x15D0},
	//				{"MenuOffscrRendParam", 0x1930},
	//				{"MenuPropertyLayoutParam", 0xFA0},
	//				{"MenuPropertySpecParam", 0xF58},
	//				{"MenuValueTableParam", 0xFE8},
	//				{"ModelSfxParam", 0xD18},
	//				{"MoveParam", 0x610},
	//				{"MPEstusFlaskRecoveryParam", 0x1540},
	//				{"MultiHPEstusFlaskBonusParam", 0x1978},
	//				{"MultiMPEstusFlaskBonusParam", 0x19C0},
	//				{"MultiPlayCorrectionParam", 0x1588},
	//				{"NetWorkAreaParam", 0xDF0},
	//				{"NetworkMsgParam", 0xE80},
	//				{"NetworkParam", 0xE38},
	//				{"NewMenuColorTableParam", 0x1198},
	//				{"NpcAiActionParam", 0x1738},
	//				{"NpcParam", 0x220},
	//				{"NpcThinkParam", 0x2F8},
	//				{"ObjActParam", 0x970},
	//				{"ObjectMaterialSfxParam", 0x18A0},
	//				{"ObjectParam", 0x340},
	//				{"PhantomParam", 0x10C0},
	//				{"PlayRegionParam", 0xDA8},
	//				{"ProtectorGenParam", 0xB68},
	//				{"RagdollParam", 0x7C0},
	//				{"ReinforceParamProtector", 0x1D8},
	//				{"ReinforceParamWeapon", 0x190},
	//				{"RoleParam", 0x13D8},
	//				{"SeMaterialConvertParam", 0x1348},
	//				{"ShopLineupParam", 0x808},
	//				{"SkeletonParam", 0x898},
	//				{"SpEffectParam", 0x4A8},
	//				{"SpEffectVfxParam", 0x4F0},
	//				{"SwordArtsParam", 0x14B0},
	//				{"TalkParam", 0x538},
	//				{"ThrowDirectionSfxParam", 0x16A8},
	//				{"ToughnessParam", 0x1300},
	//				{"UpperArmParam", 0x1618},
	//				{"WeaponGenParam", 0xB20},
	//				{"WepAbsorpPosParam", 0x12B8},
	//				{"WetAspectParam", 0x1420},
	//				{"Wind", 0xA48},
	//};
	//
	//uintptr_t StandardPlayerBoss::GetParamPtr(ParamBaseOffset Offset)
	//{
	//	var ParamPtr = IntPtr.Add(Memory.BaseAddress, 0x4782838);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, (int)Offset);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, 0x68);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, 0x68);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//
	//	return accessMultilevelPointer<uintptr_t>((uintptr_t)((byte)DataBaseAddress::BASEExecutable + (byte)0x4782838), Offset, 0x68, 0x68);
	//}
	//
	//uintptr_t* StandardPlayerBoss::GetRowAddressInParam(int RowID, uintptr_t paramPtr) { //this is not good, make sure to fix it if you use it.
	//	int num = 0;
	//	byte* param = (byte*)paramPtr;
	//	byte* DataOffset = param + (byte)0x40;
	//	if (*(unsigned int*)DataOffset == RowID) {
	//		return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
	//	}
	//	while (true) {
	//		num += 1;
	//		DataOffset += (byte)0x18;
	//		if (*(unsigned int*)DataOffset == 0) {
	//			std::cout << "Row ID: " << std::dec << RowID << " Was Not Found" << std::endl;
	//			return nullptr;
	//		}
	//		else if (*(unsigned int*)DataOffset == RowID) {
	//			return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
	//		}
	//	}
	//}

	int32_t StandardPlayerBoss::getItemMaxDurability(ItemParamIdPrefix paramIdPrefix, int32_t paramItemId)
	{
		uint16_t durabilityStage;
		if (paramIdPrefix == ItemParamIdPrefix::Weapon)
		{
			if (hoodie_script::script_runtime::paramPatcher->GetParamEntry(L"EquipParamWeapon", paramItemId, 0xBE, &durabilityStage))
			{
				return (int16_t)(durabilityStage);
			}
			else
			{
				return NULL;
			}
		}
		else if (paramIdPrefix == ItemParamIdPrefix::Protector)
		{
			if (script_runtime::paramPatcher->GetParamEntry(L"EquipParamProtector", paramItemId, 0xAC, &durabilityStage))
			{
				std::cout << durabilityStage << std::endl;
				return (int16_t)(durabilityStage);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	void StandardPlayerBoss::tryReloadPlayerChr()
	{
		if (!WorldChrMan::hasInstance() || !PlayerIns::isMainChrLoaded() || !accessMultilevelPointer<uintptr_t>(PlayerIns::getMainChrAddress() + 0x1F90, 0x58, 0x8, 0x1F90, 0x28, 0x10, 0x28, 0xB8)) return;
		WorldChrMan::reloadCharacterFiles(L"c0000");
	}

	void StandardPlayerBoss::setSheathState(int32_t slot)
	{
		if (!GameDataMan::hasInstance()
			|| GameDataMan::getInstance().getPlayerGameData().getAddress() == 0) return;
		PlayerGameData playerGameData = GameDataMan::getInstance().getPlayerGameData();
		playerGameData.setWeaponSheathState(slot);
		uint16_t sheathData[2] = {};
		sheathData[0] = playerGameData.getWeaponSheathData();
		sheathData[1] = PlayerIns(getChrAddress().value()).getForwardId();
		PlayerNetworkSession session(PlayerNetworkSession::getInstance());
		session.sessionPacketSend(13, (char*)sheathData, 4);
	}

	void StandardPlayerBoss::clearInventory() {
		EquipGameData equipGameData = GameDataMan::getInstance().getPlayerGameData().getEquipGameData();
		EquipInventoryData equipInventoryData = equipGameData.getEquipInventoryData();

		for (int32_t i = 0; i < equipInventoryData.getInventoryItemCount(); i++) {
			auto* item = equipInventoryData.getInventoryItemById(i);
			if (item == nullptr || isHiddenItem(item->giveId)) continue;
			if (getItemParamIdPrefixFromGiveId(item->giveId) != ItemParamIdPrefix::Goods) equipInventoryData.discardInventoryItems(i, item->quantity);
			else equipGameData.modifyInventoryItemQuantity(i, -(int32_t)item->quantity);
		}
	}
}