#pragma once

#include "jump_hook.h"

namespace hoodie_script {
    class hkb_animation_hook : public jump_hook
    {
    public:
        static hkb_animation_hook* _instance;
        hkb_animation_hook();
        static void on_invoke(uintptr_t hkbCharacter, int32_t* animationId);
        std::string getName()
        {
            return "hkb_animation_hook";
        }
    private:
    };
}