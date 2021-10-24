#pragma once

#include <cstdio>
#include "logging.h"
#include "minhook/MinHook.h"
#include "script_repository.h"
#include "script_runtime.h"
#include "hooks/goods_use_hook.h"
#include "hooks/game_frame_hook.h"
#include "hooks/hkb_animation_hook.h"
#include "hooks/session_send_hook.h"
#include "Hooks/has_speffect_hook.h"

void attach();
void detach();
void prepare_console();
void free_console();

DWORD WINAPI init_thread(void* lpParam);
LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS*);

// TODO: move these to a repository of their own?
hoodie_script::goods_use_hook *goodsUseHook = nullptr;
hoodie_script::hkb_animation_hook *hkbAnimationHook = nullptr;
hoodie_script::game_frame_hook *gameFrameHook = nullptr;
hoodie_script::session_send_hook* sessionsendhook = nullptr;
hoodie_script::has_speffect_hook * hasspeffecthook = nullptr;