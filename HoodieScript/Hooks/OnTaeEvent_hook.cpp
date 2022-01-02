#include "pch.h"
#include "OnTaeEvent_hook.h"
#include "script_runtime.h"
#include "GameObjects/chr_ins.h"
#include "GameExtensions/GameExtensionsManager.h"

namespace hoodie_script {
	OnTaeEvent_hook* OnTaeEvent_hook::_instance = nullptr;

	OnTaeEvent_hook::OnTaeEvent_hook() : jump_hook(0x1409a8ac0, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	uintptr_t OnTaeEvent_hook::on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t** taeEventData)
	{
		TaeEvent* eventData = (TaeEvent*)taeEventData;
		ChrIns callerCharacterInstance(*(uintptr_t*)(sprjChrTaeAnimEvent + 0x10));
		
		if (eventData->eventId == 0)
		{
			JumpTableArguments* jumpTableStruct = (JumpTableArguments*)eventData->eventParameters;
			auto extension = GameExtensionManager::tryGetTaeJumptablExtension(jumpTableStruct->jumpTableId);
			if (extension.has_value())
			{
				extension.value()(callerCharacterInstance, eventData, jumpTableStruct, jumpTableStruct->jumpTableId);
			}
			else
			{
				return call(_instance->get_original(), sprjChrTaeAnimEvent, taeEventData);
			}
		}
		else
		{
			auto extension = GameExtensionManager::tryGetTaeEventExtension(eventData->eventId);
			if (extension.has_value())
			{
				extension.value()(callerCharacterInstance, eventData, eventData->eventId);
			}
			else
			{
				return call(_instance->get_original(), sprjChrTaeAnimEvent, taeEventData);
			}
		}
		return false;
	}
}
