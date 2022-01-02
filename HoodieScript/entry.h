#pragma once

void attach();
void detach();
void prepare_console();
void free_console();

DWORD WINAPI init_thread(void* lpParam);
LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS*);
HMODULE hModuleS;