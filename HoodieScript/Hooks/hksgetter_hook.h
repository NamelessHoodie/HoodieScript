#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class hksgetter_hook : public jump_hook
    {
    public:
        hksgetter_hook();
        static hksgetter_hook* _instance;
        static uint64_t on_invoke(uintptr_t* chrInsPtr, uint32_t envId, int64_t luaStatePtr);
        std::string getName()
        {
            return "jumptable_hook";
        }
    private:
    };
}