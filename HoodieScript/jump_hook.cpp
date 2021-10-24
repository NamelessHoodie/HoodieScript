#include "pch.h"
#include "jump_hook.h"

namespace hoodie_script {
    jump_hook::jump_hook(uintptr_t target, uintptr_t replacement) {
        _target = target;
        _replacement = replacement;
        if (MH_CreateHook((void*)_target, (void*)_replacement, &_original) != MH_OK) {
            logging::write_line("Failed to create hook at : " + std::to_string(_target) + " HookName = " + getName());
        }
    }

    jump_hook::~jump_hook() { }

    bool jump_hook::install() {
        if (MH_EnableHook((void*)_target) != MH_OK) {
            logging::write_line("Failed to enable hook at : " + std::to_string(_target) + " HookName = " + getName());
            return false;
        }

        return true;
    }

    bool jump_hook::uninstall() {
        if (MH_DisableHook((void*)_target) != MH_OK) {
            logging::write_line("Failed to disable hook at : " + std::to_string(_target) + " HookName = " + getName());
            return false;
        }

        return true;
    }

    uintptr_t jump_hook::get_original() {
        return (uintptr_t)_original;
    }
}
