#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <wchar.h>
#include "dinput8/dinputWrapper.h"
#include "MinHook/include/MinHook.h"

tDirectInput8Create oDirectInput8Create;

const LPCWSTR AppWindowTitle = L"DARK SOULS III";
HWND g_hWnd = NULL;

DWORD WINAPI MainThread(HMODULE hModule)
{   
    //delay patching process
    while (!g_hWnd)
       g_hWnd = FindWindow(0, AppWindowTitle);

    MH_Initialize();

    /* patch things here */

    DWORD oldProtect;

    if (!VirtualProtect((LPVOID)0x140F09A52, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
        return true;
    *(unsigned int*)0x140F09A52 = GetPrivateProfileIntW(L"Misc", L"MaximumHkobjects", 8192, L".\\HoodiePatcher.ini");
    VirtualProtect((LPVOID)0x140F09A52, 4, oldProtect, &oldProtect);

    if (!VirtualProtect((LPVOID)0x144768F85, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
        return true;
    *(unsigned char*)0x144768F85 = GetPrivateProfileIntW(L"Misc", L"EnableDebugAnimSpeedPlayer", 0, L".\\HoodiePatcher.ini");
    VirtualProtect((LPVOID)0x144768F85, 1, oldProtect, &oldProtect);

    if (!VirtualProtect((LPVOID)0x144768F81, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
        return true;
    *(unsigned char*)0x144768F81 = GetPrivateProfileIntW(L"Misc", L"EnableDebugAnimSpeedEnemy", 0, L".\\HoodiePatcher.ini");
    VirtualProtect((LPVOID)0x144768F81, 1, oldProtect, &oldProtect);

    return S_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    HANDLE thread;
    static HMODULE dinput8dll = nullptr;
    HMODULE chainModule = NULL;
    wchar_t chainPath[MAX_PATH];
    wchar_t dllPath[MAX_PATH];

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        GetPrivateProfileStringW(L"Misc", L"ChainloadDinput8dll", L"", chainPath, MAX_PATH, L".\\HoodiePatcher.ini");

        if (chainPath && wcscmp(chainPath, L""))
        {
            GetCurrentDirectoryW(MAX_PATH, dllPath);
            wcscat_s(dllPath, MAX_PATH, L"\\");
            wcscat_s(dllPath, MAX_PATH, chainPath);
            chainModule = LoadLibraryW(dllPath);

            if (chainModule)
            {
                oDirectInput8Create = (tDirectInput8Create)GetProcAddress(chainModule, "DirectInput8Create");
            }
        }

        if (!chainModule)
        {
            wchar_t path[MAX_PATH];
            GetSystemDirectoryW(path, MAX_PATH);
            wcscat_s(path, MAX_PATH, L"\\dinput8.dll");
            dinput8dll = LoadLibraryW(path);

            if (dinput8dll)
            {
                oDirectInput8Create = (tDirectInput8Create)GetProcAddress(dinput8dll, "DirectInput8Create");
            }
        }

        thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
        
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        if (chainModule)
        {
            FreeLibrary(chainModule);
        }
        else {
            FreeLibrary(dinput8dll);
        }

        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        
        break;
    }
    return TRUE;
}

