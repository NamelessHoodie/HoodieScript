/*
    * DS3RuntimeScripting
    * Contributers: Amir
*/

#pragma once

#include "jump_hook.h"

namespace hoodie_script {
    class session_receive_hook : public jump_hook
    {
    public:
        static session_receive_hook* _instance;
        session_receive_hook();
        static uint32_t on_invoke(uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength);
        std::string getName()
        {
            return "session_receive_hook";
        }
    private:
    };
}