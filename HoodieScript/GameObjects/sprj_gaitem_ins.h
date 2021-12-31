/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once

namespace hoodie_script {

class SprjGaitemIns
{
public:
	SprjGaitemIns(uintptr_t address);
	uint32_t getDurability();
	void setDurability(uint32_t newDurability);
	bool isSprjGaiItemIns();
	int32_t getId();
	bool isValid();
	uintptr_t getVtablePtr();
	uintptr_t getAddress();
private:
	uintptr_t address;
};

}