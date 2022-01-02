#pragma once

namespace hoodie_script {
	class OnHkbAnimation {
		public:
			static int SubscribeToEventOnHkbAnimation(sol::function function);
			static int DoOnHkbAnimation(lua_State* L, uintptr_t hkbCharacter, int animationId);
		private:
			static std::deque<std::tuple<sol::function>> OnHkbAnimationHandlers;
	};

}
