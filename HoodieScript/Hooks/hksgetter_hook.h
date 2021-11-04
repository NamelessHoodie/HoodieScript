#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class hksgetter_hook : public jump_hook
    {
    public:
        hksgetter_hook();
        static hksgetter_hook* _instance;
        static uint64_t on_invoke(int64_t** param_1, uint32_t param_2, int64_t param_3, uint64_t param_4);
        std::string getName()
        {
            return "jumptable_hook";
        }
    private:
    };
}