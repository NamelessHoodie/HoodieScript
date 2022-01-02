#pragma once
#include "LuaObjects/LuaArgs.h"
#include "GameObjects/chr_ins.h"
namespace hoodie_script
{
//Lambda Arg Defines 
#define taeExpansionLambaArgs ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId
#define taeJumptableExpansionLambdaArgs ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId
#define hksActExpansionLambdaArgs ChrIns& senderCharacter, LuaArgs& luaArgs, int32_t extensionId
#define hksEnvExpansionLambdaArgs ChrIns& senderCharacter, LuaArgs& luaArgs, int32_t extensionId

//Lambda Defines
#define taeExpansionLambda std::function<void(taeExpansionLambaArgs)>
#define taeJumptableExpansionLambda std::function<void(taeJumptableExpansionLambdaArgs)>
#define hksActExpansionLambda std::function<void(hksActExpansionLambdaArgs)>
#define hksEnvExpansionLambda std::function<uint64_t(hksEnvExpansionLambdaArgs)>
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
		//RegisterExtensionMethods
		static bool tryRegisterHksActExtension(int32_t extensionId, hksActExpansionLambda);
		static bool tryRegisterHksEnvExtension(int32_t extensionId, hksEnvExpansionLambda);
		static bool tryRegisterTaeEventExtension(int32_t extensionId, taeExpansionLambda extensionFunction);
		static bool tryRegisterTaeJumptableExtension(int32_t extensionId, taeJumptableExpansionLambda extensionFunction);
		//GetExtensionMethods
		static std::optional<hksActExpansionLambda> tryGetHksActExpansionLambda(int32_t extensionId);
		static std::optional<hksEnvExpansionLambda> tryGetHksEnvExpansionLambda(int32_t extensionId);
		static std::optional<taeExpansionLambda> tryGetTaeEventExtension(int32_t extensionId);
		static std::optional<taeJumptableExpansionLambda> tryGetTaeJumptablExtension(int32_t extensionId);
	private:
		static std::unordered_map<int32_t, hksActExpansionLambda> hksActExtensions;
		static std::unordered_map<int32_t, hksEnvExpansionLambda> hksEnvExtensions;
		static std::unordered_map<int32_t, taeJumptableExpansionLambda> taejumptableExtensions;
		static std::unordered_map<int32_t, taeExpansionLambda> taeEventExtensions;
	};
}