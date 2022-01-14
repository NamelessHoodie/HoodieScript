#include "pch.h"
#include "OnRenderingFrame.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnRenderingFrame::OnRenderingFrameHandlers;

    int OnRenderingFrame::SubscribeToEventOnRenderingFrame(sol::function function)
    {
        OnRenderingFrameHandlers.push_back(std::tuple<sol::function>{ function});
        return 0;
    }

    void OnRenderingFrame::DoOnRenderingFrame(lua_State* L) {
        LuaStateThreadLock::Lock();
        sol::state_view lua(L);
        for (size_t i = 0; i < OnRenderingFrameHandlers.size(); ++i) {
            auto &[funRef] = OnRenderingFrame::OnRenderingFrameHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun();
            if (!result.valid())
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
        LuaStateThreadLock::Unlock();
    }
}
