#include "pch.h"
#include "hksActSetter_hook.h"
#include "GameExtensions/GameExtensionsManager.h"
//#include "script_runtime.h"

namespace hoodie_script {
	hksActSetter_hook* hksActSetter_hook::_instance = nullptr;

	hksActSetter_hook::hksActSetter_hook() : jump_hook(0x14098C510, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	void hksActSetter_hook::on_invoke(uintptr_t* chrInsPtr, int32_t actId, uintptr_t luaStatePtr)
	{
		ChrIns characterInstance(*chrInsPtr);
		LuaArgs luaArgs(luaStatePtr);
		auto extension = GameExtensionManager::tryGetHksActExpansionLambda(actId);
		if (extension.has_value())
		{
			extension.value()(characterInstance, luaArgs, actId);
		}
		else
		{
			call(_instance->get_original(), chrInsPtr, actId, luaStatePtr);
		}
	}
}
