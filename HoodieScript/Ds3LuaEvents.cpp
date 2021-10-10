#include <list>
#include "Lua/include/lua.hpp"

static int OnParamLoadedHandlers[1024];
int OnParamLoadedEventSubscribersCount = 0;
static int SubscribeToEventOnParamLoaded(lua_State* L)
{
    if (!lua_isfunction(L, 1)) {
        luaL_argerror(L, 1, "expected function");
    }
    lua_pushvalue(L, -1);
    OnParamLoadedHandlers[OnParamLoadedEventSubscribersCount++] = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}
// call the registered handlers
static void DoOnParamLoaded(lua_State* L) {
    int i;
    for (i = 0; i < OnParamLoadedEventSubscribersCount; ++i) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, OnParamLoadedHandlers[i]);
        lua_pcall(L, 0, 0, 0);
    }
}
