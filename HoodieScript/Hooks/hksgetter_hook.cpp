#include "pch.h"
#include "hksgetter_hook.h"
#include "GameExtensions/GameExtensionsManager.h"
#include "LuaEvents/LuaStateThreadLock.h"
//#include "script_runtime.h"

namespace hoodie_script {
	hksEnvGetter_hook* hksEnvGetter_hook::_instance = nullptr;

	hksEnvGetter_hook::hksEnvGetter_hook() : jump_hook(0x14098f3d0, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	uint64_t hksEnvGetter_hook::on_invoke(uintptr_t* ptrToChrIns, uint32_t envId, int64_t luaStatePtr)
	{
		auto lock = LuaStateThreadLock::GetLockObject();
		uint64_t resultBuffer;
		ChrIns characterInstance(*ptrToChrIns);
		LuaArgs luaArgs(luaStatePtr);
		auto extension = GameExtensionManager::tryGetHksEnvExpansionLambda(envId);
		if (extension.has_value())
		{
			//LuaStateThreadLock::Lock();
			resultBuffer = extension.value()(characterInstance, luaArgs, envId);
			//LuaStateThreadLock::Unlock();
		}
		else
		{
			resultBuffer = call(_instance->get_original(), ptrToChrIns, envId, luaStatePtr);
		}


		return resultBuffer;
	}
}
