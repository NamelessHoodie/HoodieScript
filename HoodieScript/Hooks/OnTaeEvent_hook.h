#pragma once

#include "jump_hook.h"
#include "GameObjects/chr_ins.h"

namespace hoodie_script {
	struct JumpTableArguments
	{
		int32_t jumpTableId;
		float arg1;
		int32_t arg2;
		uint8_t arg3;
		uint8_t arg4;
		int16_t arg5;
	};

	struct TaeEventStartEndTimes
	{
		float eventStartTime;
		int32_t padding1;
		float eventEndTime;
	};

	struct TaeEvent
	{
		int32_t eventId;
		int32_t padding1;
		uintptr_t* eventParameters;
		float animationPlayBackTimePreviousFrame;
		float animationPlayBackTimeCurrentFrame;
		bool isFrameEnteringEvent;
		bool isFrameExitingEvent;
		int32_t padding2;
		TaeEventStartEndTimes* times;
	};

    class OnTaeEvent_hook : public jump_hook
    {
    public:
        OnTaeEvent_hook();
        static OnTaeEvent_hook* _instance;
        static uintptr_t on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t ** jumpTableDataAndExtraPointers);
        static bool JumpTableEvent0(uintptr_t sprjChrTaeAnimEvent, TaeEvent* eventData, JumpTableArguments* jumpTableData, ChrIns& senderCharacter);
        std::string getName()
        {
            return "OnTaeEvent_hook";
        }
    private:
    };
}