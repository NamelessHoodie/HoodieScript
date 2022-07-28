#pragma once

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI init_thread(void* lpParam);

void attach();
void detach();
void prepare_console();
void free_console();

