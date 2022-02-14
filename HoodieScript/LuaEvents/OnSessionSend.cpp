#include "pch.h"
#include "OnSessionSend.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnSessionSend::OnSessionSendHandlers;

    int OnSessionSend::SubscribeToEventOnSessionSend(sol::function function)
    {
        OnSessionSendHandlers.push_back(std::tuple<sol::function>{ function });
        return 0;
    }

    int OnSessionSend::DoOnSessionSend(lua_State* L, uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength) {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnSessionSendHandlers.size(); ++i) {
            auto& [funRef] = OnSessionSend::OnSessionSendHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun(networkSession, (uintptr_t)networkHandle, id, (uintptr_t)buffer, maxLength);
            if (result.valid())
            {
                maxLength = result;
            }
            else
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
        return maxLength;
    }
}