#include "pch.h"
#include "OnHkbAnimation.h"

using namespace luabridge;

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

    int OnHkbAnimation::DoOnHkbAnimation(lua_State* L, PlayerIns hkbCharacter ,int animationId) {
        int i;
        for (i = 0; i < OnHkbAnimationEventSubscribersCount; ++i) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, OnHkbAnimationHandlers[i]);
            LuaRef a = LuaRef::fromStack(L);
            if (a.isFunction())
            {
                logging::write_line("Calling" + a.tostring());
                animationId = a(hkbCharacter, animationId);
            }
            else
            {
                logging::write_line("error calling lua fun");
            }
        }

        return animationId;
    }
}
