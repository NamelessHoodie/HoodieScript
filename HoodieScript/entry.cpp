#include "pch.h"
#include "entry.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        attach();
        break;
    case DLL_PROCESS_DETACH:
        detach();
        break;
    default:
        break;
    }
    return TRUE;
}

void attach()
{
    prepare_console();
    hoodie_script::logging::init();
    hoodie_script::logging::write_line("Attached HoodieScriptExtender");

    // Set up minhook
    if (MH_Initialize() != MH_OK) {
        hoodie_script::logging::write_line("Hook initialization failed");
    } else {
        hoodie_script::logging::write_line("Minhook set up");
    }

    auto luaHelper = new hoodie_script::Ds3LuaHelper();
    luaHelper->Initialize();

    goodsUseHook = new hoodie_script::goods_use_hook();
    hoodie_script::logging::write_line("Prememe");
    goodsUseHook->install();
    hoodie_script::logging::write_line("Realmeme");
}

void detach()
{
    goodsUseHook->uninstall();
    hoodie_script::logging::write_line("Detached HoodieScriptExtender");
    free_console();
}

void prepare_console() {
    if (GetConsoleWindow() != nullptr) {
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    }
    else {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    }
}

void free_console() {
    if (GetConsoleWindow() != nullptr) {
        FreeConsole();
    }
}