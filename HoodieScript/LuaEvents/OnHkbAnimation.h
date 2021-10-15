#pragma once

namespace hoodie_script {
	class OnHkbAnimation {
		public:
			static int SubscribeToEventOnHkbAnimation(lua_State* L);
			static int DoOnHkbAnimation(lua_State* L, int animationId);
		private:
			static int OnHkbAnimationHandlers[1024];
			static int OnHkbAnimationEventSubscribersCount;
	};
}
