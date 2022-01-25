#pragma once

#include "jump_hook.h"

namespace hoodie_script {
    class PositionUpdate_Hook : public jump_hook
    {
    public:
        static PositionUpdate_Hook* _instance;
        PositionUpdate_Hook();
        static void on_invoke(uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2);
        std::string getName()
        {
            return "PositionUpdate_Hook";
        }
    private:
    };
}