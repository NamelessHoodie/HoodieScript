#include "pch.h"
#include "jump_hook.h"
#include <memory>
#include "minhook/include/MinHook.h"

namespace hoodie_script {
    jump_hook::jump_hook(uintptr_t target, uintptr_t replacement) {
        _target = target;
        _replacement = replacement;
    }

    jump_hook::~jump_hook() { }

    bool jump_hook::install() {
        if (MH_CreateHook((void*)_target, (void*)_replacement, &_original)) {
            logging::write_line("Hook failed to create : " + getName());
            return false;
        }

        if (MH_EnableHook((void*)_target) != MH_OK) {
            logging::write_line("Hook failed to enable : " + getName());
            return false;
        }
        logging::write_line("Hook successfully created and enabled : " + getName());
        memcpy((void*)instructionBackup, (void*)_target, sizeof(instructionBackup));
        return true;
    }

    bool jump_hook::tryRefresh()
    {
        if (memcmp((void*)instructionBackup, (void*)_target, sizeof(instructionBackup)) != 0)
        {
            DWORD oldProtect;
            DWORD oldProtectUseless;
            logging::write_line("Refreshing hook... : " + getName());
            VirtualProtect((void*)_target, sizeof(instructionBackup), PAGE_EXECUTE_READWRITE, &oldProtect);
            memcpy((void*)_target, (void*)instructionBackup, sizeof(instructionBackup));
            VirtualProtect((void*)_target, sizeof(instructionBackup), oldProtect, &oldProtectUseless);
            return true;
        }
        return false;
    }

    bool jump_hook::uninstall() {
        if (MH_DisableHook((void*)_target) != MH_OK) {
            logging::write_line("Hook failed to disable : " + std::to_string(_target) + " HookName = " + getName());
            return false;
        }
        logging::write_line("Hook successfully disabled : " + getName());

        return true;
    }

    uintptr_t jump_hook::get_original() {
        return (uintptr_t)_original;
    }
}
