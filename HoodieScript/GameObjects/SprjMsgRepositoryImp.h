#pragma once
//Thank you church guard for the addresses, impplementation from NamelessHoodie[2].
#include "GameObjects/equip_inventory_data.h"
namespace hoodie_script
{

	class SprjMsgRepositoryImp
	{
	public:
		SprjMsgRepositoryImp(uintptr_t address);
		const std::wstring getTalkMsg(long long fmgId);
		const std::wstring getBloodMsg(long long fmgId);
		const std::wstring getMovieSubtitle(long long fmgId);
		const std::wstring getGoodsName(long long fmgId);
		const std::wstring getGoodsInfo(long long fmgId);
		const std::wstring getGoodsCaption(long long fmgId);
		const std::wstring getWeaponName(long long fmgId);
		const std::wstring getWeaponInfo(long long fmgId);
		const std::wstring getWeaponCaption(long long fmgId);
		const std::wstring getProtectorName(long long fmgId);
		const std::wstring getProtectorInfo(long long fmgId);
		const std::wstring getProtectorCaption(long long fmgId);
		const std::wstring getAccessoryName(long long fmgId);
		const std::wstring getAccessoryInfo(long long fmgId);
		const std::wstring getAccessoryCaption(long long fmgId);
		const std::wstring getGemName(long long fmgId);
		const std::wstring getGemInfo(long long fmgId);
		const std::wstring getGemCaption(long long fmgId);
		const std::wstring getMagicName(long long fmgId);
		const std::wstring getMagicCaption(long long fmgId);
		const std::wstring getActionEventInfo(long long fmgId);
		const std::wstring getInGameMenu(long long fmgId);
		const std::wstring getLineHelp(long long fmgId);
		const std::wstring getKeyGuide(long long fmgId);
		const std::wstring getContentsHelp(long long fmgId);
		const std::wstring getDialog(long long fmgId);
		const std::wstring getMenuOther(long long fmgId);
		const std::wstring getMenuCommon(long long fmgId);
		const std::wstring getTestError(long long fmgId);
		const std::wstring getTagError(long long fmgId);
		const std::wstring getSysMsg(long long fmgId);
		const std::wstring getNpcName(long long fmgId);
		const std::wstring getPlaceName(long long fmgId);
		const std::wstring getMenuText(long long fmgId);
		const std::wstring getInventoryItemName(ItemParamIdPrefix itemType, long long fmgId);
		const std::wstring getInventoryItemInfo(ItemParamIdPrefix itemType, long long fmgId);
		const std::wstring getInventoryItemCaption(ItemParamIdPrefix itemType, long long fmgId);
		static bool GameHasInstance();
		static SprjMsgRepositoryImp GameGetInstance();
	private:
		uintptr_t address;
	};

}