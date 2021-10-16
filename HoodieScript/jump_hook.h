#pragma once

#include <memory>
#include "minhook/MinHook.h"

namespace hoodie_script {
    class jump_hook {
    public:
        jump_hook(uintptr_t original, uintptr_t replacement);
        ~jump_hook();

        bool install();
        bool uninstall();
        uintptr_t get_original();
        virtual std::string getName() = 0;

    private:
        uintptr_t _target;
        uintptr_t _replacement;
        void* _original;
    };
}
