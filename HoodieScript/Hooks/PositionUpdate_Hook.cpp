#include "pch.h"
#include "PositionUpdate_Hook.h"
#include "script_runtime.h"

namespace hoodie_script
{
	PositionUpdate_Hook *PositionUpdate_Hook::_instance = nullptr;

	PositionUpdate_Hook::PositionUpdate_Hook() : jump_hook(0x14165b420, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	void PositionUpdate_Hook::on_invoke(uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2)
	{		
		script_runtime::on_position_update(CsHkCharacterProxy, SprjChrPhysicsModulePtr, unk0, unk1, unk2);
		call(_instance->get_original(), CsHkCharacterProxy, SprjChrPhysicsModulePtr, unk0, unk1, unk2);
	}
}
