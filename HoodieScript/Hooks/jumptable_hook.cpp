#include "pch.h"
#include "jumptable_hook.h"

namespace hoodie_script {
	jumptable_hook* jumptable_hook::_instance = nullptr;
	
	jumptable_hook::jumptable_hook() : jump_hook(0x1409a8ac0, (uintptr_t) on_invoke)
	{
		_instance = this;
	}
	
	struct JumpTableArguments 
	{
		int32_t jumpTableId;
		float arg1;
		int32_t arg2;
		uint8_t arg3;
		uint8_t arg4;
		int16_t arg5;
	};

	uintptr_t jumptable_hook::on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t **jumpTableDataAndExtraPointers)
	{
		JumpTableArguments* jmpTableArgs = (JumpTableArguments*)(jumpTableDataAndExtraPointers[1]);
		ChrIns callerCharacterInstance(*(uintptr_t*)(sprjChrTaeAnimEvent + 0x10));
		if (jmpTableArgs->jumpTableId == 666)
		{
			logging::write_line("JumpTable - 666");
			std::cout << std::dec;
			std::cout << jmpTableArgs->jumpTableId << std::endl;
			std::cout << jmpTableArgs->arg1 << std::endl;
			std::cout << jmpTableArgs->arg2 << std::endl;
			std::cout << unsigned(jmpTableArgs->arg3) << std::endl;
			std::cout << unsigned(jmpTableArgs->arg4) << std::endl;
			std::cout << jmpTableArgs->arg5 << std::endl;
		}
		uintptr_t(*originalFunction)(uintptr_t sprjChrTaeAnimEvent, uintptr_t **jumpTableDataAndExtraPointers);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(sprjChrTaeAnimEvent, jumpTableDataAndExtraPointers);
	}
}
