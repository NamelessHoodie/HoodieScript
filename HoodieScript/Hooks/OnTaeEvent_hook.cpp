#include "pch.h"
#include "OnTaeEvent_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
	OnTaeEvent_hook* OnTaeEvent_hook::_instance = nullptr;

	OnTaeEvent_hook::OnTaeEvent_hook() : jump_hook(0x1409a8ac0, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	bool OnTaeEvent_hook::JumpTableEvent0(uintptr_t sprjChrTaeAnimEvent, TaeEvent* eventData, JumpTableArguments* jumpTableData, ChrIns& senderCharacter)
	{
		bool blockReturn = true;
		switch (jumpTableData->jumpTableId)
		{
		case 666:
		{
			logging::write_line("JumpTable - 666");
			PlayerIns a(senderCharacter.getAddress());
			if (PlayerIns::isPlayer(a.getAddress()))
			{
				a.ReplaceWeaponActiveRight(a.getRightHandWeaponActive(), jumpTableData->arg2);
			}
			else if (a.hasPlayerGameData())
			{
				logging::write_line(L"NPC : " + senderCharacter.getCharacterString());
				//std::cout << a.getRightHandWeapon(0) << std::endl;
				//std::cout << a.getRightHandWeapon(1) << std::endl;
				//std::cout << a.getRightHandWeapon(2) << std::endl;
				//a.setRightHandWeapon(0, jmpTableArgs->arg2);
			}
			break;
		}
		default:
			blockReturn = false;
			break;
		}
	}

	uintptr_t OnTaeEvent_hook::on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t** taeEventData)
	{
		TaeEvent* eventData = (TaeEvent*)taeEventData;
		ChrIns callerCharacterInstance(*(uintptr_t*)(sprjChrTaeAnimEvent + 0x10));
		switch (eventData->eventId)
		{
		case 0:
			if (JumpTableEvent0(sprjChrTaeAnimEvent, eventData, (JumpTableArguments*)(eventData->eventParameters), callerCharacterInstance))
				break;
		case 715:
			std::cout << "FoundTheCum = " << taeEventData << "\n";
			std::cout << "eventParametersAddress = " << eventData->eventParameters << std::endl;
			std::cout << "playbackFramePrevious = " << eventData->animationPlayBackTimePreviousFrame << std::endl;
			std::cout << "playbackFrameCurrent = " << eventData->animationPlayBackTimeCurrentFrame << std::endl;
			std::cout << "isFrameEnteringEvent = " << eventData->isFrameEnteringEvent << std::endl;
			std::cout << "isFrameExitingEvent = " << eventData->isFrameExitingEvent << std::endl;
			std::cout << "eventStartTime = " << eventData->times->eventStartTime << std::endl;
			std::cout << "eventEndTime = " << eventData->times->eventEndTime << std::endl;
			break;
		default:
			uintptr_t(*originalFunction)(uintptr_t sprjChrTaeAnimEvent, uintptr_t * *jumpTableDataAndExtraPointers);
			*(uintptr_t*)&originalFunction = _instance->get_original();
			return originalFunction(sprjChrTaeAnimEvent, taeEventData);
			break;
		}
		return false;
	}
}
