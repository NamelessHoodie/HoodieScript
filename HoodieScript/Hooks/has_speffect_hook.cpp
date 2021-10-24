#include "pch.h"
#include "has_speffect_hook.h"

namespace hoodie_script {
	has_speffect_hook* has_speffect_hook::_instance = nullptr;
	
	has_speffect_hook::has_speffect_hook() : jump_hook(0x140529560, (uintptr_t) on_invoke)
	{
		_instance = this;
	}

	bool has_speffect_hook::on_invoke(unsigned int handle, int speffect)
	{
		//logging::write_line("Le Handle : " + std::to_string(handle));
		script_runtime::on_speffect(handle, speffect);
		uintptr_t(*originalFunction)(unsigned int handle, int speffect);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(handle, speffect);
	}
}
