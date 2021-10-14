#pragma once

#include <string>
#include "logging.h"
#include "jump_hook.h"

namespace hoodie_script {
    class goods_use_hook : public jump_hook
    {
    public:
        goods_use_hook();
        static uintptr_t on_invoke(uintptr_t self, int goodsId);
    private:
        static goods_use_hook* _instance;
    };
}