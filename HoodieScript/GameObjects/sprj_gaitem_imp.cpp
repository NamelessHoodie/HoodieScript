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
	uintptr_t itemOffset = (uniqueId % 0x10000u) * 8u + 0x40u;
	uintptr_t* itemPtrPtr = (uintptr_t*)(address + itemOffset);
	uintptr_t itemPtr = 0;
	std::optional<SprjGaitemIns> item = std::optional<SprjGaitemIns>();
	if (itemPtrPtr) {
		itemPtr = *itemPtrPtr;
		item = SprjGaitemIns(itemPtr);
		if (item->isValid())
			return item;
	}

	std::stringstream sstream;
	sstream << std::hex;
	sstream << "UID - " << uniqueId << std::endl;
	sstream << "RelativeInsOffset - " << itemOffset << std::endl;
	sstream << "PtrToPtrToIns - " << itemPtrPtr << std::endl;
	sstream << "PtrToIns - " << itemPtr << std::endl;
	sstream << "PtrToInsObj - " << item->getAddress() << std::endl;
	logging::write_line(sstream.str());
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