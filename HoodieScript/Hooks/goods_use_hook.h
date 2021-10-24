#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class goods_use_hook : public jump_hook
    {
    public:
        goods_use_hook();
        static uintptr_t on_invoke(uintptr_t self, int goodsId);
        std::string getName()
        {
            return "goods_use_hook";
        }
    private:
        static goods_use_hook* _instance;
    };
}