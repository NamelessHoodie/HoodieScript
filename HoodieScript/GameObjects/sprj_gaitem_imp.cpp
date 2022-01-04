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
	//std::cout << "UID - " << uniqueId << std::endl;
	uintptr_t itemOffset = (uniqueId % 0x10000u) * 8u + 0x40u;
	//std::cout << "RelativeInsOffset - " << itemOffset << std::endl;
	uintptr_t* itemPtrPtr = (uintptr_t*)(address + itemOffset);
	//std::cout << "PtrToPtrToIns - " << itemPtrPtr << std::endl;
	if (itemPtrPtr) {
		//std::cout << "PtrToIns - " << *itemPtrPtr << std::endl;
		uintptr_t itemPtr = *itemPtrPtr;
		std::optional<SprjGaitemIns> item = SprjGaitemIns(itemPtr);
		//std::cout << "PtrToInsObj - " << item->getAddress() << std::endl;
		if (item->isValid())
			return item;
	}
	return std::optional<SprjGaitemIns>();
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