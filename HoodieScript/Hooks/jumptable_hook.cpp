#include "pch.h"
#include "jumptable_hook.h"
#include "script_runtime.h"

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

	void DeepDive(void* pointer, int depth) {
		void* data;
		std::vector<void*> loopcheck;
		std::cout << "DeepDive\n";
		for (int i = 0; i < depth; i++) {
			data = ((void**)pointer)[i];
			std::cout << "[" << i << "]" << data;
			while (!IsBadReadPtr((void*)data, sizeof(void*))) {
				if (loopcheck.size() < depth) {
					loopcheck.push_back(data);
				}
				else {
					if (std::count(loopcheck.begin(), loopcheck.end(), data)) { break; }
				}
				data = *(void**)data;
				std::cout << "-> " << data;
			}
			loopcheck.clear();
			std::cout << "\n";
		}
	}

	uintptr_t jumptable_hook::on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t **jumpTableDataAndExtraPointers)
	{
		JumpTableArguments* jmpTableArgs = (JumpTableArguments*)(jumpTableDataAndExtraPointers[1]);
		ChrIns callerCharacterInstance(*(uintptr_t*)(sprjChrTaeAnimEvent + 0x10));
		if (jmpTableArgs->jumpTableId == 666)
		{
			logging::write_line("JumpTable - 666");
			//std::cout << std::dec;
			//std::cout << jmpTableArgs->jumpTableId << std::endl;
			//std::cout << jmpTableArgs->arg1 << std::endl;
			//std::cout << jmpTableArgs->arg2 << std::endl;
			//std::cout << unsigned(jmpTableArgs->arg3) << std::endl;
			//std::cout << unsigned(jmpTableArgs->arg4) << std::endl;
			//std::cout << jmpTableArgs->arg5 << std::endl;
			PlayerIns a(callerCharacterInstance.getAddress());
			if (PlayerIns::isPlayer(a.getAddress()))
			{
				a.ReplaceWeaponActiveRight(a.getRightHandWeaponActive(), jmpTableArgs->arg2);
			}
			else if (a.hasPlayerGameData())
			{
				logging::write_line(L"NPC : " + callerCharacterInstance.getCharacterString());
				//std::cout << a.getRightHandWeapon(0) << std::endl;
				//std::cout << a.getRightHandWeapon(1) << std::endl;
				//std::cout << a.getRightHandWeapon(2) << std::endl;
				//a.setRightHandWeapon(0, jmpTableArgs->arg2);
			}
		}
		uintptr_t(*originalFunction)(uintptr_t sprjChrTaeAnimEvent, uintptr_t **jumpTableDataAndExtraPointers);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(sprjChrTaeAnimEvent, jumpTableDataAndExtraPointers);
	}
}
