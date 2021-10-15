#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class hkb_animation_hook : public jump_hook
    {
    public:
        hkb_animation_hook();
        static void on_invoke(uintptr_t hkbCharacter, int32_t* animationId);
    private:
        static hkb_animation_hook *_instance;
    };
}