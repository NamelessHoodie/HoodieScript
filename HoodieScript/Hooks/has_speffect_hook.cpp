#include "pch.h"
#include "has_speffect_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
	has_speffect_hook* has_speffect_hook::_instance = nullptr;
	
	has_speffect_hook::has_speffect_hook() : jump_hook(0x140529560, (uintptr_t) on_invoke)
	{
		_instance = this;
	}

	bool has_speffect_hook::on_invoke(unsigned int entityId, int speffect)
	{
		script_runtime::on_speffect(entityId, speffect);
		return call(_instance->get_original(), entityId, speffect);
	}
}
