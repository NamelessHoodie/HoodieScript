#include "pch.h"
#include "menu_isopen_getter_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
	menu_isopen_getter_hook* menu_isopen_getter_hook::_instance = nullptr;

	menu_isopen_getter_hook::menu_isopen_getter_hook() : jump_hook(0x14075ec70, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	int32_t menu_isopen_getter_hook::on_invoke(uint32_t index)
	{
		uint32_t returnValue = (uint32_t)call(_instance->get_original(), index);
		if (script_runtime::isGameInputLocked)
		{
			if (index == 8)
			{
				return 2;
			}
		}
		return returnValue;
	}
}
