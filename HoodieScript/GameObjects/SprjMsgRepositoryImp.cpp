//Thank you church guard for the addresses, impplementation from NamelessHoodie[2].
#include "pch.h"
#include "SprjMsgRepositoryImp.h"
namespace hoodie_script
{

SprjMsgRepositoryImp::SprjMsgRepositoryImp(uintptr_t address)
{
	this->address = address;
}

const std::wstring SprjMsgRepositoryImp::getTalkMsg(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d420, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getBloodMsg(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c780, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMovieSubtitle(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cfc0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGoodsName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cab0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGoodsInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e221d0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGoodsCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e22180, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getWeaponName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d5d0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getWeaponInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e33090, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getWeaponCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e33040, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getProtectorName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d280, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getProtectorInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e2c850, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getProtectorCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e2c800, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getAccessoryName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c610, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getAccessoryInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e16990, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getAccessoryCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e16940, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGemName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21db0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGemInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21d60, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getGemCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21d10, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMagicName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0ce30, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMagicCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e25620, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getActionEventInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c690, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getInGameMenu(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cb30, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getLineHelp(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cd60, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getKeyGuide(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cc70, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getContentsHelp(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c830, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getDialog(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c860, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMenuOther(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cf00, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMenuCommon(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0ceb0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getTestError(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d020, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getTagError(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cff0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getSysMsg(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d150, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getNpcName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d050, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getPlaceName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d0d0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMenuText(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0cf50, address, fmgId));
}

const std::wstring SprjMsgRepositoryImp::getInventoryItemName(ItemParamIdPrefix itemType, long long fmgId)
{
	if (itemType == ItemParamIdPrefix::Goods)
		return getGoodsName(fmgId);
	else if (itemType == ItemParamIdPrefix::Accessory)
		return getAccessoryName(fmgId);
	else if (itemType == ItemParamIdPrefix::Protector)
		return getProtectorName(fmgId);
	else
		return getWeaponName(fmgId);
}
const std::wstring SprjMsgRepositoryImp::getInventoryItemInfo(ItemParamIdPrefix itemType, long long fmgId)
{
	if (itemType == ItemParamIdPrefix::Goods)
		return getGoodsInfo(fmgId);
	else if (itemType == ItemParamIdPrefix::Accessory)
		return getAccessoryInfo(fmgId);
	else if (itemType == ItemParamIdPrefix::Protector)
		return getProtectorInfo(fmgId);
	else
		return getWeaponInfo(fmgId);
}
const std::wstring SprjMsgRepositoryImp::getInventoryItemCaption(ItemParamIdPrefix itemType, long long fmgId)
{
	if (itemType == ItemParamIdPrefix::Goods)
		return getGoodsCaption(fmgId);
	else if (itemType == ItemParamIdPrefix::Accessory)
		return getAccessoryCaption(fmgId);
	else if (itemType == ItemParamIdPrefix::Protector)
		return getProtectorCaption(fmgId);
	else
		return getWeaponCaption(fmgId);
}

bool SprjMsgRepositoryImp::GameHasInstance()
{
	return *(uintptr_t**)0x1447819d0 != nullptr;
}

SprjMsgRepositoryImp SprjMsgRepositoryImp::GameGetInstance()
{
	return SprjMsgRepositoryImp(*(uintptr_t*)0x1447819d0);
}

}
