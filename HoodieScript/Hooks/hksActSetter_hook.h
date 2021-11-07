#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class hksActSetter : public jump_hook
    {
    public:
        hksActSetter();
        static hksActSetter* _instance;
        static void on_invoke(uintptr_t* chrInsPtr, int32_t actId, uintptr_t luaStatePtr);
        std::string getName()
        {
            return "jumptable_hook";
        }
    private:
    };
}