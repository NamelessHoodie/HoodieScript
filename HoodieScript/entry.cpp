#include "pch.h"
#include "entry.h"
#include "vendor/DInput8/DInput8Proxy.h"
#include "LuaEvents/OnParamLoaded.h"
#include <Amir/ds3runtime.h>

#define EXCEPTION_STRING_SIZE    1024

std::shared_ptr<hoodie_script::DS3RuntimeScripting> hoodie_script::ds3runtime_global;;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    HANDLE thread;
    static HMODULE dinput8dll = nullptr;
    HMODULE chainModule = NULL;
    wchar_t chainPath[MAX_PATH];
    wchar_t dllPath[MAX_PATH];

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        GetPrivateProfileStringW(L"Misc", L"ChainloadDinput8dll", L"", chainPath, MAX_PATH, L".\\HoodieScript.ini");

        if (chainPath && wcscmp(chainPath, L""))
        {
            GetCurrentDirectoryW(MAX_PATH, dllPath);
            wcscat_s(dllPath, MAX_PATH, L"\\");
            wcscat_s(dllPath, MAX_PATH, chainPath);
            chainModule = LoadLibraryW(dllPath);

            if (chainModule)
            {
                DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(chainModule, "DirectInput8Create");
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
                DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(dinput8dll, "DirectInput8Create");
            }
        }
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

// Should do hook and LUA init
DWORD WINAPI init_thread(void* lpParam)
{
    // TODO: refactor these to fit in the script_runtime somehow
    goodsUseHook = new hoodie_script::goods_use_hook();
    hkbAnimationHook = new hoodie_script::hkb_animation_hook();
    gameFrameHook = new hoodie_script::game_frame_hook();
    //sessionsendhook = new hoodie_script::session_send_hook();
    hasspeffecthook = new hoodie_script::has_speffect_hook();
    jumptable_hook = new hoodie_script::jumptable_hook();
    hksget_hook = new hoodie_script::hksEnvGetter_hook();
    hksActSet_hook = new hoodie_script::hksActSetter_hook();

    hoodie_script::script_runtime::initialize();
    hoodie_script::script_repository::load_files();

    goodsUseHook->install();
    hkbAnimationHook->install();
    gameFrameHook->install();
    //sessionsendhook->install();
    hasspeffecthook->install();
    jumptable_hook->install();
    hksget_hook->install();
    hksActSet_hook->install();

    return S_OK;
}

void attach()
{
    prepare_console();
    hoodie_script::logging::init();
    hoodie_script::logging::write_line("Attached HoodieScriptExtender");
    SetUnhandledExceptionFilter(exception_handler);

    // Set up minhook
    if (MH_Initialize() != MH_OK) {
        hoodie_script::logging::write_line("Hook initialization failed");
    } else {
        hoodie_script::logging::write_line("Minhook set up");
    }

    CreateThread(nullptr, 0x1000, &init_thread, nullptr, 0, nullptr);
}

void detach()
{
    // TODO: keep track of all the hooks in a centralized place so we can roll them back in batch
    goodsUseHook->uninstall();
    hkbAnimationHook->uninstall();
    gameFrameHook->uninstall();
    //sessionsendhook->uninstall();
    hasspeffecthook->uninstall();
    jumptable_hook->uninstall();
    hksget_hook->uninstall();
    hksActSet_hook->uninstall();

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

LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS* exception) {
    PEXCEPTION_RECORD record = exception->ExceptionRecord;
    PCONTEXT context = exception->ContextRecord;
    char exception_text[EXCEPTION_STRING_SIZE];

    switch (record->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:
        snprintf(
            exception_text,
            EXCEPTION_STRING_SIZE,
            "Access violation!\n\n"
            "Instruction at 0x%p\n"
            "attempted to %s\n"
            "memory at 0x%p\n\n"
            "Register dump:\n"
            "RAX = 0x%p\n" "RBX = 0x%p\n" "RCX = 0x%p\n" "RDX = 0x%p\n"
            "RSI = 0x%p\n" "RDI = 0x%p\n" "RBP = 0x%p\n" "RSP = 0x%p\n"
            "R8  = 0x%p\n" "R9  = 0x%p\n" "R10 = 0x%p\n" "R11 = 0x%p\n"
            "R12 = 0x%p\n" "R13 = 0x%p\n" "R14 = 0x%p\n" "R15 = 0x%p\n",
            record->ExceptionAddress,
            record->ExceptionInformation[0] ? "WRITE" : "READ",
            record->ExceptionInformation[1],
            context->Rax, context->Rbx, context->Rcx, context->Rdx,
            context->Rsi, context->Rdi, context->Rbp, context->Rsp,
            context->R8, context->R9, context->R10, context->R11,
            context->R12, context->R13, context->R14, context->R15
        );
        break;
    default:
        snprintf(
            exception_text,
            EXCEPTION_STRING_SIZE,
            "Caught unhandled exception\n"
            "Code: %x\n"
            "Address: %p",
            record->ExceptionCode,
            record->ExceptionAddress
        );
        break;
    }

    hoodie_script::logging::write_line(exception_text);
    MessageBoxA(NULL, exception_text, "Error Dump", MB_ICONERROR | MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
}