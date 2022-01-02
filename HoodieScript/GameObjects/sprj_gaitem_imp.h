/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/
#include "sprj_gaitem_ins.h"

namespace hoodie_script {

class SprjGaitemImp
{
public:
	SprjGaitemImp(uintptr_t address);

	std::optional<SprjGaitemIns> getItemByUniqueId(uint32_t uniqueId);

	static SprjGaitemImp getInstance();

	static bool hasInstance();
private:
	uintptr_t address;
};

}