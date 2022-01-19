#include "pch.h"
#include "OnParamLoaded.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnParamLoaded::OnParamLoadedHandlers;


    int OnParamLoaded::SubscribeToEventOnParamLoaded(sol::function function)
    {
        OnParamLoadedHandlers.push_back(std::tuple<sol::function>{ function});
        return 0;
    }

    void OnParamLoaded::DoOnParamLoaded(lua_State* L) {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnParamLoadedHandlers.size(); ++i) {
            auto& [funRef] = OnParamLoaded::OnParamLoadedHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun();
            if (!result.valid())
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
    }
}
