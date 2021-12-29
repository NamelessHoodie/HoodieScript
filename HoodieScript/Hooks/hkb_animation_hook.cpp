#include "pch.h"
#include "hkb_animation_hook.h"
#include "script_runtime.h"

namespace hoodie_script
{
	hkb_animation_hook *hkb_animation_hook::_instance = nullptr;

	hkb_animation_hook::hkb_animation_hook() : jump_hook(0x140D84870, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	void hkb_animation_hook::on_invoke(uintptr_t hkbCharacter, int32_t* animationId)
	{		
		*animationId = script_runtime::on_hkb_animation(hkbCharacter, *animationId);
		call(_instance->get_original(), hkbCharacter, animationId);
	}
}
