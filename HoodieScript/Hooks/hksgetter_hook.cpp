#include "pch.h"
#include "hksgetter_hook.h"

namespace hoodie_script {
	hksgetter_hook* hksgetter_hook::_instance = nullptr;

	hksgetter_hook::hksgetter_hook() : jump_hook(0x14098f3d0, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	uint64_t hksgetter_hook::on_invoke(int64_t** param_1, uint32_t param_2, int64_t param_3, uint64_t param_4)
	{
		//0x14112df50
		long long meme = call(0x140d9cca0, param_3, 2, 0x5a); //get second argument from lua function
		if (meme != 0x5a)
		{
			switch (param_2)
			{
			case 6798:
				//a = *new std::string((const char*)call(0x1410e48f0, param_3, 2, 4)); //Maybe Get String function from lua, does not actually work
				std::cout << "DebugIntegerPrint = " << std::dec << meme << std::endl;
				return 5;
			default:
				break;
			}
		}
		uint64_t(*originalFunction)(int64_t * *param_1, uint32_t param_2, int64_t param_3, uint64_t param_4);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(param_1, param_2, param_3, param_4);
	}
}
