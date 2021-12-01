#pragma once

#include <cstdio>
#include "logging.h"
#include "minhook/include/MinHook.h"
#include "script_repository.h"
#include "script_runtime.h"
#include "HotKeyManager.h"
#include "HoodieScript-ImGui-Test/GuiManager.h"

void attach();
void detach();
void prepare_console();
void free_console();

DWORD WINAPI init_thread(void* lpParam);
LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS*);
HMODULE hModuleS;