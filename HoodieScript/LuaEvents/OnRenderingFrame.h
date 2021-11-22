#pragma once

namespace hoodie_script {
	class OnRenderingFrame {
		public:
			static int SubscribeToEventOnRenderingFrame(sol::function function);
			static void DoOnRenderingFrame(lua_State* L);
		private:
			static std::deque<std::tuple<sol::function>> OnRenderingFrameHandlers;
	};

}
