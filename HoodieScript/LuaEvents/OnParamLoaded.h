#pragma once

namespace hoodie_script {
	class OnParamLoaded {
		public:
			static int SubscribeToEventOnParamLoaded(sol::function function);
			static void DoOnParamLoaded(lua_State* L);
		private:
			static std::deque<std::tuple<sol::function>> OnParamLoadedHandlers;
	};
}
