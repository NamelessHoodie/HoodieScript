#include "pch.h"
#include "GameExtensionsManager.h"

namespace hoodie_script
{
	std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)>> GameExtensionManager::taejumptableExtensions;
	std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)>> GameExtensionManager::taeEventExtensions;
	void GameExtensionManager::registerEmbeddedExtensions()
	{
		tryRegisterTaeEventExtension(715, 
		[](ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)
		{
			std::cout << "eventParametersAddress = " << eventData->eventParameters << std::endl;
			std::cout << "playbackFramePrevious = " << eventData->animationPlayBackTimePreviousFrame << std::endl;
			std::cout << "playbackFrameCurrent = " << eventData->animationPlayBackTimeCurrentFrame << std::endl;
			std::cout << "isFrameEnteringEvent = " << eventData->isFrameEnteringEvent << std::endl;
			std::cout << "isFrameExitingEvent = " << eventData->isFrameExitingEvent << std::endl;
			std::cout << "eventStartTime = " << eventData->times->eventStartTime << std::endl;
			std::cout << "eventEndTime = " << eventData->times->eventEndTime << std::endl;
		});

		tryRegisterTaeJumptableExtension(666,
		[](ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)
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
		});
	}
	bool GameExtensionManager::tryRegisterTaeEventExtension(int32_t extensionId, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)> extensionFunction)
	{
		if (taeEventExtensions.find(extensionId) == taeEventExtensions.end())
		{
			taeEventExtensions.insert({extensionId, extensionFunction});
			return true;
		}
		return false;
	}
	bool GameExtensionManager::tryRegisterTaeJumptableExtension(int32_t extensionId, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)> extensionFunction)
	{
		if (taejumptableExtensions.find(extensionId) == taejumptableExtensions.end())
		{
			taejumptableExtensions.insert({extensionId, extensionFunction});
			return true;
		}
		return false;
	}

	std::optional<std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)>> GameExtensionManager::tryGetTaeEventExtension(int32_t extensionId)
	{
		std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)>> ::iterator tryFetch = taeEventExtensions.find(extensionId);
		if (tryFetch != taeEventExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
	std::optional<std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)>> GameExtensionManager::tryGetTaeJumptablExtension(int32_t extensionId)
	{
		std::unordered_map<int32_t, std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, JumpTableArguments* jumpTableData, int32_t extensionId)>>::iterator tryFetch = taejumptableExtensions.find(extensionId);
		if (tryFetch != taejumptableExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
}