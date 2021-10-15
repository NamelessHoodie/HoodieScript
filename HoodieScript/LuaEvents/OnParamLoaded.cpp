#include "pch.h"
#include "OnParamLoaded.h"

namespace hoodie_script {

    int OnParamLoaded::OnParamLoadedHandlers[1024];
    int OnParamLoaded::OnParamLoadedEventSubscribersCount = 0;

    int OnParamLoaded::SubscribeToEventOnParamLoaded(lua_State* L)
    {
        if (!lua_isfunction(L, 1)) {
            luaL_argerror(L, 1, "expected function");
        }
        lua_pushvalue(L, -1);
        OnParamLoadedHandlers[OnParamLoadedEventSubscribersCount++] = luaL_ref(L, LUA_REGISTRYINDEX);
        return 0;
    }

    void OnParamLoaded::DoOnParamLoaded(lua_State* L) {
        int i;
        for (i = 0; i < OnParamLoadedEventSubscribersCount; ++i) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, OnParamLoadedHandlers[i]);
            lua_pcall(L, 0, 0, 0);
        }
    }
}
