#pragma once

namespace hoodie_script {
	class OnGameFrame {
		public:
			static int SubscribeToEventOnGameFrame(lua_State* L);
			static void DoOnGameFrame(lua_State* L);
		private:
			static int OnGameFrameHandlers[1024];
			static int OnGameFrameEventSubscribersCount;
	};
}
