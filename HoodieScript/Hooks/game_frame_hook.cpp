/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
#include "pch.h"
#include "game_frame_hook.h"
namespace hoodie_script {

GameFrameHook::GameFrameHook() : jump_hook(0x1423842C0, (uintptr_t)onGameFrame)
{
	_instance = this;
}

uintptr_t GameFrameHook::onGameFrame(uintptr_t self, int goodsId)
{
	uintptr_t(*originalFunction)(uintptr_t self, int id);
	*(uintptr_t*)&originalFunction = _instance->get_original();
	static uint64_t uniqueFrameClock = 0;
	uniqueFrameClock++;
	if (uniqueFrameClock % 2 == 0) logging::write_line("Frame");
	return originalFunction(self, goodsId);
}

GameFrameHook* GameFrameHook::_instance = nullptr;

}