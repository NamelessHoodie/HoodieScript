#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class has_speffect_hook : public jump_hook
    {
    public:
        has_speffect_hook();
        static has_speffect_hook* _instance;
        static bool on_invoke(unsigned int handle, int speffect);
        std::string getName()
        {
            return "has_speffect_hook";
        }
    private:
    };
}