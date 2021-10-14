/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
#include "pch.h"

namespace hoodie_script {

typedef void (*gameFrame)(void*, void*, void*, void*, void*);

class GameFrameHook : public jump_hook
{
public:
	GameFrameHook();

	static uintptr_t onGameFrame(uintptr_t self, int goodsId);

	std::string getName()
	{
		return "game_frame_hook";
	}
private:
	static GameFrameHook* _instance;
};

}