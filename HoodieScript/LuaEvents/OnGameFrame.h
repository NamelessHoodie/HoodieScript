#pragma once

namespace hoodie_script {
	class OnGameFrame {
		public:
			static int SubscribeToEventOnGameFrame(sol::function function);
			static void DoOnGameFrame(lua_State* L);
		private:
			static std::deque<std::tuple<sol::function>> OnGameFrameHandlers;
	};
}
