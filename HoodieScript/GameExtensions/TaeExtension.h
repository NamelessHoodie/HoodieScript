#pragma once
#include "GameObjects/chr_ins.h"
namespace hoodie_script
{
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

	class TaeExtension
	{
	public:
		TaeExtension(std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)> extensionFunction);
		void CallExtension(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId);
	private:
		std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)> taeExtensionFunction;
	};
}