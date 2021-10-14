#pragma once

namespace hoodie_script {
	static int OnParamLoadedHandlers[1024];
	static int OnParamLoadedEventSubscribersCount = 0;
	int SubscribeToEventOnParamLoaded(lua_State* L);
	void DoOnParamLoaded(lua_State* L);
}