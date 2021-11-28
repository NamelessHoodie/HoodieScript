#pragma once

#include "jump_hook.h"

namespace hoodie_script {
    class menu_isopen_getter_hook : public jump_hook
    {
    public:
        menu_isopen_getter_hook();
        static menu_isopen_getter_hook* _instance;
        static int32_t on_invoke(uint32_t index);
        std::string getName()
        {
            return "menu_isopen_getter_hook";
        }
    private:
    };
}