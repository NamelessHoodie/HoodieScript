#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class hksEnvGetter_hook : public jump_hook
    {
    public:
        hksEnvGetter_hook();
        static hksEnvGetter_hook* _instance;
        static uint64_t on_invoke(uintptr_t* chrInsPtr, uint32_t envId, int64_t luaStatePtr);
        std::string getName()
        {
            return "hksEnvGetter_hook";
        }
    private:
    };
}