#include "pch.h"
#include "jump_hook.h"

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

        return true;
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
