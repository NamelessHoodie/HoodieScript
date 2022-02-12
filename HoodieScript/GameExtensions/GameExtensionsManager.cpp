#include "pch.h"
#include "GameExtensionsManager.h"
#include <GameObjects/sprj_chr_data_module.h>
#include <GameObjects/player_ins.h>
#include "GameUtilities/PlayerUtilities.h"

namespace hoodie_script
{
	std::unordered_map<int32_t, hksActExpansionLambda> GameExtensionManager::hksActExtensions;
	std::unordered_map<int32_t, hksEnvExpansionLambda> GameExtensionManager::hksEnvExtensions;
	std::unordered_map<int32_t, taeJumptableExpansionLambda> GameExtensionManager::taejumptableExtensions;
	std::unordered_map<int32_t, taeExpansionLambda> GameExtensionManager::taeEventExtensions;

	void GameExtensionManager::registerEmbeddedExtensions()
	{
		tryRegisterTaeEventExtension(716, 
		[](taeExpansionLambaArgs) {
			std::cout << "eventParametersAddress = " << eventData->eventParameters << std::endl;
			std::cout << "playbackFramePrevious = " << eventData->animationPlayBackTimePreviousFrame << std::endl;
			std::cout << "playbackFrameCurrent = " << eventData->animationPlayBackTimeCurrentFrame << std::endl;
			std::cout << "isFrameEnteringEvent = " << eventData->isFrameEnteringEvent << std::endl;
			std::cout << "isFrameExitingEvent = " << eventData->isFrameExitingEvent << std::endl;
			std::cout << "eventStartTime = " << eventData->times->eventStartTime << std::endl;
			std::cout << "eventEndTime = " << eventData->times->eventEndTime << std::endl;
		});

		tryRegisterTaeJumptableExtension(666,
		[](taeJumptableExpansionLambdaArgs) {
			if (eventData->isFrameEnteringEvent)
			{
				PlayerIns a(senderCharacter.getAddress());
				if (PlayerIns::isPlayer(a.getAddress()))
				{
					logging::write_line("JumpTable : 666 - MainPlayer");
					PlayerUtilities::ReplaceWeaponRightActiveNetworked(a.getRightHandWeaponActive(), jumpTableData->arg2);
				}
				else if (a.hasPlayerGameData())
				{
					logging::write_line(L"JumpTable : 666 - " + senderCharacter.getCharacterString());
					//std::cout << a.getRightHandWeapon(a.GetActiveWeaponSlotRightHand()) << std::endl;
					auto slot = a.GetActiveWeaponSlotRightHand();
					auto currentWeapon = a.getRightHandWeapon(slot);
					auto newWeapon = jumpTableData->arg2;
					logging::write_line(std::format("Slot = {0}, CW = {1}, NW = {2}", slot, currentWeapon, newWeapon));
					a.setRightHandWeapon(slot, newWeapon);
					logging::write_line(std::format("WP0 = {0}, WP1 = {1}, WP2 = {2}", a.getRightHandWeapon(0), a.getRightHandWeapon(1), a.getRightHandWeapon(2)));
					//a.setRightHandWeapon(0, jmpTableArgs->arg2);
				}
			}
		});

		tryRegisterHksActExtension(421,
		[](hksActExpansionLambdaArgs) {
			if (luaArgs.HasUint64(2))
			{
				float* helpMe = (float*)luaArgs.GetUint64(2);
				logging::write_line(std::format("HKSAct Print = {0}", (long long)helpMe));
			}
		});

		tryRegisterHksActExtension(666,
		[](hksActExpansionLambdaArgs) {
			if (luaArgs.HasUint64(2))
			{
				//std::wcout << characterInstance.getCharacterString() << "-HPAct = " << meme << std::endl;

				auto chrData = SprjChrDataModule(senderCharacter.getSprjChrDataModule());
				chrData.setHealth((const uint32_t)luaArgs.GetUint64(2));
			}
		});

		tryRegisterHksActExtension(9000,
		[](hksActExpansionLambdaArgs) {
			logging::write_line(std::format("HKS Act9000 Print = {0}", luaArgs.GetString0(2)));
		});

		tryRegisterHksEnvExtension(420,
		[](hksEnvExpansionLambdaArgs) {
			return SprjChrDataModule(senderCharacter.getSprjChrDataModule()).getHealth();
		});

		tryRegisterHksEnvExtension(421,
		[](hksEnvExpansionLambdaArgs) {
			return 9;
		});
	}
	bool GameExtensionManager::tryRegisterHksActExtension(int32_t extensionId, hksActExpansionLambda extensionFunction)
	{
		if (hksActExtensions.find(extensionId) == hksActExtensions.end())
		{
			hksActExtensions.insert({ extensionId, extensionFunction });
			return true;
		}
		return false;
	}
	bool GameExtensionManager::tryRegisterHksEnvExtension(int32_t extensionId, hksEnvExpansionLambda extensionFunction)
	{
		if (hksEnvExtensions.find(extensionId) == hksEnvExtensions.end())
		{
			hksEnvExtensions.insert({ extensionId, extensionFunction });
			return true;
		}
		return false;
	}
	bool GameExtensionManager::tryRegisterTaeEventExtension(int32_t extensionId, taeExpansionLambda extensionFunction)
	{
		if (taeEventExtensions.find(extensionId) == taeEventExtensions.end())
		{
			taeEventExtensions.insert({extensionId, extensionFunction});
			return true;
		}
		return false;
	}
	bool GameExtensionManager::tryRegisterTaeJumptableExtension(int32_t extensionId, taeJumptableExpansionLambda extensionFunction)
	{
		if (taejumptableExtensions.find(extensionId) == taejumptableExtensions.end())
		{
			taejumptableExtensions.insert({extensionId, extensionFunction});
			return true;
		}
		return false;
	}

	std::optional<hksActExpansionLambda> GameExtensionManager::tryGetHksActExpansionLambda(int32_t extensionId)
	{
		std::unordered_map<int32_t, hksActExpansionLambda>::iterator tryFetch = hksActExtensions.find(extensionId);
		if (tryFetch != hksActExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
	std::optional<hksEnvExpansionLambda> GameExtensionManager::tryGetHksEnvExpansionLambda(int32_t extensionId)
	{
		std::unordered_map<int32_t, hksEnvExpansionLambda>::iterator tryFetch = hksEnvExtensions.find(extensionId);
		if (tryFetch != hksEnvExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
	std::optional<taeExpansionLambda> GameExtensionManager::tryGetTaeEventExtension(int32_t extensionId)
	{
		std::unordered_map<int32_t, taeExpansionLambda>::iterator tryFetch = taeEventExtensions.find(extensionId);
		if (tryFetch != taeEventExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
	std::optional<taeJumptableExpansionLambda> GameExtensionManager::tryGetTaeJumptablExtension(int32_t extensionId)
	{
		std::unordered_map<int32_t, taeJumptableExpansionLambda>::iterator tryFetch = taejumptableExtensions.find(extensionId);
		if (tryFetch != taejumptableExtensions.end())
		{
			return tryFetch->second;
		}
		return std::nullopt;
	}
}