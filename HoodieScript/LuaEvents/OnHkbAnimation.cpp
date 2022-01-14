#include "pch.h"
#include "OnHkbAnimation.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnHkbAnimation::OnHkbAnimationHandlers;

    int OnHkbAnimation::SubscribeToEventOnHkbAnimation(sol::function function)
    {
        OnHkbAnimationHandlers.push_back(std::tuple<sol::function>{ function});
        return 0;
    }

    int OnHkbAnimation::DoOnHkbAnimation(lua_State* L, uintptr_t chr ,int animationId) {
        LuaStateThreadLock::Lock();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnHkbAnimationHandlers.size(); ++i) {
            auto &[funRef] = OnHkbAnimation::OnHkbAnimationHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun(chr, animationId);
            if (result.valid())
            {
                animationId = result;
            }
            else
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
        LuaStateThreadLock::Unlock();
        return animationId;
    }
}
