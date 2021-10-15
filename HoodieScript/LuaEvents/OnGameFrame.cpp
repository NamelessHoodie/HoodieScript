#include "pch.h"
#include "OnGameFrame.h"

namespace hoodie_script {

    int OnGameFrame::OnGameFrameHandlers[1024];
    int OnGameFrame::OnGameFrameEventSubscribersCount = 0;

    int OnGameFrame::SubscribeToEventOnGameFrame(lua_State* L)
    {
        if (!lua_isfunction(L, 1)) {
            luaL_argerror(L, 1, "expected function");
        }
        lua_pushvalue(L, -1);
        OnGameFrameHandlers[OnGameFrameEventSubscribersCount++] = luaL_ref(L, LUA_REGISTRYINDEX);
        return 0;
    }

    void OnGameFrame::DoOnGameFrame(lua_State* L) {
        int i;
        for (i = 0; i < OnGameFrameEventSubscribersCount; ++i) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, OnGameFrameHandlers[i]);
            lua_pcall(L, 0, 0, 0);
        }
    }
}
