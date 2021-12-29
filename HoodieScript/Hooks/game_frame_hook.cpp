#include "pch.h"
#include "game_frame_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
	game_frame_hook* game_frame_hook::_instance = nullptr;
	
	game_frame_hook::game_frame_hook() : jump_hook(0x1423842C0, (uintptr_t) on_invoke)
	{
		_instance = this;
	}

	void game_frame_hook::on_invoke(void* rcx, void* rdx, void* r8, void* r9, void* rsp20)
	{
		// Thanks Amir
		script_runtime::on_game_frame();
		call(_instance->get_original(), rcx, rdx, r8, r9, rsp20);
		//if (ds3runtime_global->getGameThreadId() == 0) ds3runtime_global->setGameThreadId(GetCurrentThreadId());
	}
}
