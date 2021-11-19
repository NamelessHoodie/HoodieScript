#pragma once

#include "jump_hook.h"

namespace hoodie_script {
    class hksActSetter_hook : public jump_hook
    {
    public:
        hksActSetter_hook();
        static hksActSetter_hook* _instance;
        static void on_invoke(uintptr_t* chrInsPtr, int32_t actId, uintptr_t luaStatePtr);
        std::string getName()
        {
            return "hksActSetter_hook";
        }
    private:
    };
}