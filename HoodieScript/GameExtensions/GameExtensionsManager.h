#pragma once
#include "GameObjects/player_ins.h"
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

	class GameExtensionManager
	{
	public:
		static void registerEmbeddedExtensions();
		static bool tryRegisterTaeEventExtension(int32_t extensionId, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)> extensionFunction);
		static bool tryRegisterTaeJumptableExtension(int32_t extensionId, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)> extensionFunction);
		static std::optional<std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)>> tryGetTaeEventExtension(int32_t extensionId);
		static std::optional<std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)>> tryGetTaeJumptablExtension(int32_t extensionId);
	private:
		static std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)>> taejumptableExtensions;
		static std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)>> taeEventExtensions;
	};
}