#pragma once
//Thank you church guard for the addresses, impplementation from NamelessHoodie[2].
#include "GameObjects/equip_inventory_data.h"
namespace hoodie_script
{

	class SprjMsgRepositoryImp
	{
	public:
		struct ItemIdStruct
		{
			const char padding[15] = {0};
			int32_t itemId;
			ItemIdStruct(int32_t itemId)
			{
				this->itemId = itemId;
			}
		};
		static const std::wstring getTalkMsg(long long fmgId);
		static const std::wstring getBloodMsg(long long fmgId);
		static const std::wstring getMovieSubtitle(long long fmgId);
		static const std::wstring getGoodsName(long long fmgId);
		static const std::wstring getGoodsInfo(long long fmgId);
		static const std::wstring getGoodsCaption(long long fmgId);
		static const std::wstring getWeaponName(long long fmgId);
		static const std::wstring getWeaponInfo(long long fmgId);
		static const std::wstring getWeaponCaption(long long fmgId);
		static const std::wstring getProtectorName(long long fmgId);
		static const std::wstring getProtectorInfo(long long fmgId);
		static const std::wstring getProtectorCaption(long long fmgId);
		static const std::wstring getAccessoryName(long long fmgId);
		static const std::wstring getAccessoryInfo(long long fmgId);
		static const std::wstring getAccessoryCaption(long long fmgId);
		static const std::wstring getGemName(long long fmgId);
		static const std::wstring getGemInfo(long long fmgId);
		static const std::wstring getGemCaption(long long fmgId);
		static const std::wstring getMagicName(long long fmgId);
		static const std::wstring getMagicCaption(long long fmgId);
		static const std::wstring getActionEventInfo(long long fmgId);
		static const std::wstring getInGameMenu(long long fmgId);
		static const std::wstring getLineHelp(long long fmgId);
		static const std::wstring getKeyGuide(long long fmgId);
		static const std::wstring getContentsHelp(long long fmgId);
		static const std::wstring getDialog(long long fmgId);
		static const std::wstring getMenuOther(long long fmgId);
		static const std::wstring getMenuCommon(long long fmgId);
		static const std::wstring getTestError(long long fmgId);
		static const std::wstring getTagError(long long fmgId);
		static const std::wstring getSysMsg(long long fmgId);
		static const std::wstring getNpcName(long long fmgId);
		static const std::wstring getPlaceName(long long fmgId);
		static const std::wstring getMenuText(long long fmgId);
		static const std::wstring getInventoryItemName(ItemParamIdPrefix itemType, long long fmgId);
		static const std::wstring getInventoryItemInfo(ItemParamIdPrefix itemType, long long fmgId);
		static const std::wstring getInventoryItemCaption(ItemParamIdPrefix itemType, long long fmgId);
		static bool IsLoaded();
	private:
		std::wstring multiTryGetFmgString(long long fmgId, const wchar_t* defaultVal, uintptr_t offsets...);
		static const wchar_t* tryGetFmgString(uintptr_t offset, long long fmgId);
		static uintptr_t GetInstanceAddress();
	};

}