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
	return std::wstring((const wchar_t*)call(0x140e221d0, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?GoodsInfo?", 0x6e, 0x14, 0xd9, 0x101);
}
const std::wstring SprjMsgRepositoryImp::getGoodsCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e22180, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?GoodsCaption?", 100, 0x18, 0xdd, 0x105);
}
const std::wstring SprjMsgRepositoryImp::getWeaponName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d5d0, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getWeaponInfo(long long fmgId)
{
	auto itemStruct = ItemIdStruct(fmgId);
	return std::wstring((const wchar_t*)call(0x140e33090, &itemStruct));
	//return multiTryGetFmgString(fmgId, L"?WeaponInfo?", 0x72, 0x15, 0xda, 0x102);
}
const std::wstring SprjMsgRepositoryImp::getWeaponCaption(long long fmgId)
{
	auto itemStruct = ItemIdStruct(fmgId);
	return std::wstring((const wchar_t*)call(0x140e33040, &itemStruct));
	//return multiTryGetFmgString(fmgId, L"?WeaponCaption?", 0x6a, 0x19, 0xde, 0x106);
	//return std::wstring((const wchar_t*)call(0x140e33040, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getProtectorName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0d280, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getProtectorInfo(long long fmgId)
{
	auto itemStruct = ItemIdStruct(fmgId);
	return std::wstring((const wchar_t*)call(0x140e2c850, &itemStruct));
	//return multiTryGetFmgString(fmgId, L"?ProtectorInfo?", 0x74, 0x16, 0xdb, 0x103);
}
const std::wstring SprjMsgRepositoryImp::getProtectorCaption(long long fmgId)
{
	auto itemStruct = ItemIdStruct(fmgId);
	return std::wstring((const wchar_t*)call(0x140e2c800, &itemStruct));
	//return multiTryGetFmgString(fmgId, L"?ProtectorCaption?", 0x6c, 0x1a, 0xdf, 0x107);
}
const std::wstring SprjMsgRepositoryImp::getAccessoryName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0c610, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getAccessoryInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e16990, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?AccessoryInfo?", 0x70, 0x17, 0xdc, 0x104);
}
const std::wstring SprjMsgRepositoryImp::getAccessoryCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e16940, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?AccessoryCaption?", 0x6d, 0x1b, 0xe0, 0x108);
}
const std::wstring SprjMsgRepositoryImp::getGemName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21db0, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?GemName?", 0x1f);
}
const std::wstring SprjMsgRepositoryImp::getGemInfo(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21d60, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?GemInfo?", 0x20);
}
const std::wstring SprjMsgRepositoryImp::getGemCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e21d10, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?GemCaption?", 0x21);
}
const std::wstring SprjMsgRepositoryImp::getMagicName(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e0ce30, address, fmgId));
}
const std::wstring SprjMsgRepositoryImp::getMagicCaption(long long fmgId)
{
	return std::wstring((const wchar_t*)call(0x140e25620, &fmgId));
	//return multiTryGetFmgString(fmgId, L"?MagicCaption?", 0x69, 0x1d, 0xe2, 0x10a);
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

std::wstring SprjMsgRepositoryImp::multiTryGetFmgString(long long fmgId, const wchar_t* defaultVal, uintptr_t offsets ...)
{
	va_list args;
	va_start(args, offsets);

	while (offsets != NULL)
	{
		auto offset = va_arg(args, uintptr_t);
		const wchar_t* tryGetVal = tryGetFmgString(offset, fmgId);

		if (tryGetVal != nullptr)
			return std::wstring(tryGetVal);

		offsets++;
	}

	va_end(args);
	return std::wstring(defaultVal);
}

const wchar_t* SprjMsgRepositoryImp::tryGetFmgString(uintptr_t offset, long long fmgId)
{
	uintptr_t unkOffset = 0;
	const wchar_t* attempt = (const wchar_t*)call(0x1423458a0, address, unkOffset, offset, fmgId);
	return attempt;
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
