#include "pch.h"
#include "OnHkbAnimation.h"

namespace hoodie_script {

    MyClass::MyClass(float valueFun)
    {
        value = valueFun;
    }

    float MyClass::GetValue()
    {
        return value;
    }

    MyClass a(16);

    int OnHkbAnimation::OnHkbAnimationHandlers[1024];
    int OnHkbAnimation::OnHkbAnimationEventSubscribersCount = 0;

    int OnHkbAnimation::SubscribeToEventOnHkbAnimation(lua_State* L)
    {
        if (!lua_isfunction(L, 1)) {
            luaL_argerror(L, 1, "expected function");
        }
        lua_pushvalue(L, -1);
        OnHkbAnimationHandlers[OnHkbAnimationEventSubscribersCount++] = luaL_ref(L, LUA_REGISTRYINDEX);
        return 0;
    }

    int OnHkbAnimation::DoOnHkbAnimation(lua_State* L, PlayerIns chr ,int animationId) {
        int i;
        sol::state_view sol(L);
        for (i = 0; i < OnHkbAnimationEventSubscribersCount; ++i) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, OnHkbAnimationHandlers[i]);
            sol::protected_function fun = sol::stack::get<sol::reference>(L, sol.stack_top());;
            sol::protected_function_result result = fun(chr, animationId);
            if (result.valid())
            {
                animationId = result;
            }
            lua_pop(L, 1);
        }
        return animationId;
    }
}
