#include "pch.h"
#include "sprj_gaitem_ins.h"
#include "memory_util.h"

namespace hoodie_script {

SprjGaitemIns::SprjGaitemIns(uintptr_t addressArg)
{
	this->address = addressArg;
}

int32_t SprjGaitemIns::getId()
{
	return *(int32_t*)(getAddress() + 0xC);
}

bool SprjGaitemIns::isValid()
{
	if (address == NULL)
		return false;

	//auto a = *(uintptr_t**)address;
	return true;
}

uint32_t SprjGaitemIns::getDurability()
{
	//std::cout << std::hex << "Help Me Please - " << (getAddress() + 0x10) << std::endl;
	//return *(uint32_t*)(getAddress() + 0x10);
	//return 0;
	return (uint32_t)call(0x140a27610, getAddress());
}

void SprjGaitemIns::setDurability(uint32_t newDurability)
{
	//*(uint32_t*)(getAddress() + 0x10) = newDurability;
	call(0x140a27770, getAddress(), newDurability);
}

bool SprjGaitemIns::isSprjGaiItemIns()
{
	auto vtablePtr = (uintptr_t*)getAddress();
	return vtablePtr && (*vtablePtr == 0x14289A8C8 || *vtablePtr == 0x14289A7D8);
}

uintptr_t SprjGaitemIns::getVtablePtr()
{
	return *(uintptr_t*)getAddress();
}

uintptr_t SprjGaitemIns::getAddress()
{
	return address;
}

}