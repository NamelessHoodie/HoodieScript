#pragma once

#include <memory>
#include "minhook/include/MinHook.h"

namespace hoodie_script {
    class jump_hook {
    public:
        jump_hook(uintptr_t original, uintptr_t replacement);
        ~jump_hook();

        bool install();
        bool tryRefresh();
        bool uninstall();
        uintptr_t get_original();
        virtual std::string getName() 
        {
            return "jump_hook";
        }
    private:
        uintptr_t _target;
        uintptr_t _replacement;
        void* _original;
        char instructionBackup[5];
    };
}
