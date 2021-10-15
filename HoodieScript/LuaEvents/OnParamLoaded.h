#pragma once

namespace hoodie_script {
	class OnParamLoaded {
		public:
			static int SubscribeToEventOnParamLoaded(lua_State* L);
			static void DoOnParamLoaded(lua_State* L);
		private:
			static int OnParamLoadedHandlers[1024];
			static int OnParamLoadedEventSubscribersCount;
	};
}
