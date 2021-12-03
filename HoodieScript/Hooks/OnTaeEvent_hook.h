#pragma once

#include "jump_hook.h"
#include "GameObjects/chr_ins.h"
namespace hoodie_script {

    class OnTaeEvent_hook : public jump_hook
    {
    public:
        OnTaeEvent_hook();
        static OnTaeEvent_hook* _instance;
        static uintptr_t on_invoke(uintptr_t sprjChrTaeAnimEvent, uintptr_t ** jumpTableDataAndExtraPointers);
        std::string getName()
        {
            return "OnTaeEvent_hook";
        }
    private:
    };
}