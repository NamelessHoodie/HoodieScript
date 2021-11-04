#include "pch.h"
#include "jumptable_hook.h"

namespace hoodie_script {
	jumptable_hook* jumptable_hook::_instance = nullptr;
	
	jumptable_hook::jumptable_hook() : jump_hook(0x1409a8ac0, (uintptr_t) on_invoke)
	{
		_instance = this;
	}

	uintptr_t jumptable_hook::on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t unkData)
	{
		const int32_t jmpTableId = *accessMultilevelPointer<int32_t>(unkData + 8, 0);
		if (jmpTableId == 666)
		{

			//auto a = *(long long**)(*(long long*)(&DAT_00001f90 + *(long long*)(sprjChrTaeAnimEvent + 0x10)) + 0xb8);
			logging::write_line("JumpTable - 666");
			logging::write_line(std::to_string(*(long long*)(sprjChrTaeAnimEvent + 0x10)));
		}
		uintptr_t(*originalFunction)(uintptr_t sprjChrTaeAnimEvent, uintptr_t unkDatat);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(sprjChrTaeAnimEvent, unkData);
	}
}
