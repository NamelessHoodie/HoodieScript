#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class jumptable_hook : public jump_hook
    {
    public:
        jumptable_hook();
        static jumptable_hook* _instance;
        static uintptr_t on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t unkData);
        std::string getName()
        {
            return "jumptable_hook";
        }
    private:
    };
}