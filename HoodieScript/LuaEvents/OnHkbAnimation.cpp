#include "pch.h"
#include "OnHkbAnimation.h"

namespace hoodie_script {

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

    int OnHkbAnimation::DoOnHkbAnimation(lua_State* L, int animationId) {
        int i;
        for (i = 0; i < OnHkbAnimationEventSubscribersCount; ++i) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, OnHkbAnimationHandlers[i]);
            lua_pushinteger(L, animationId);
            lua_pcall(L, 1, 1, 0);
            
            animationId = lua_tointeger(L, -1);
            lua_pop(L, 1);
        }

        return animationId;
    }
}
