#pragma once

#include "jump_hook.h"
#include "script_runtime.h"

namespace hoodie_script {
    class game_frame_hook : public jump_hook
    {
    public:
        game_frame_hook();
        static void on_invoke(void *rcx, void *rdx, void *r8, void *r9, void *rsp20);
    private:
        static game_frame_hook* _instance;
    };
}