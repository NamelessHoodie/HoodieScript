#include "pch.h"
#include "OnGameFrame.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnGameFrame::OnGameFrameHandlers;

    int OnGameFrame::SubscribeToEventOnGameFrame(sol::function function)
    {
        OnGameFrameHandlers.push_back(std::tuple<sol::function>{ function});
        return 0;
    }

    void OnGameFrame::DoOnGameFrame(lua_State* L) {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnGameFrameHandlers.size(); ++i) {
            auto& [funRef] = OnGameFrame::OnGameFrameHandlers[i];
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
