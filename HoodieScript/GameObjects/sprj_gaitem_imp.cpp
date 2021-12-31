#pragma once
#include "pch.h"
#include "sprj_gaitem_imp.h"
#include "databaseaddress.h"
#include "memory_util.h"

namespace hoodie_script {

SprjGaitemImp::SprjGaitemImp(uintptr_t address)
{
	this->address = address;
}

std::optional<SprjGaitemIns> SprjGaitemImp::getItemByUniqueId(uint32_t uniqueId)
{
	std::optional<SprjGaitemIns> item;
	uintptr_t itemOffset = (uniqueId % 0x10000ull) * 8ull + 0x40ull;
	uintptr_t* itemPtrPtr = (uintptr_t*)(address + itemOffset);
	if (itemPtrPtr) {
		uintptr_t itemPtr = *itemPtrPtr;
		auto itemCheck = SprjGaitemIns(itemPtr);
		if (itemCheck.isValid()) 
		{ 
			item = itemCheck;
		}
	}

	return item;
}

SprjGaitemImp SprjGaitemImp::getInstance()
{
	return SprjGaitemImp(*accessMultilevelPointer<uintptr_t>(DataBaseAddress::SprjGaitem));
}

bool SprjGaitemImp::hasInstance()
{
	return accessMultilevelPointer<uintptr_t>(DataBaseAddress::SprjGaitem) != nullptr;
}

}