#include "pch.h"
#include "OnSessionReceive.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnSessionReceive::OnSessionReceiveHandlers;

    int OnSessionReceive::SubscribeToEventOnSessionReceive(sol::function function)
    {
        OnSessionReceiveHandlers.push_back(std::tuple<sol::function>{ function });
        return 0;
    }

    int OnSessionReceive::DoOnSessionReceive(lua_State* L, uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength, uint32_t receiveLength)
    {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnSessionReceiveHandlers.size(); ++i) {
            auto& [funRef] = OnSessionReceive::OnSessionReceiveHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun(networkSession, (uintptr_t)networkHandle, id, (uintptr_t)buffer, maxLength, receiveLength);
            if (result.valid())
            {
                receiveLength = result;
            }
            else
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
        return receiveLength;
    }
}