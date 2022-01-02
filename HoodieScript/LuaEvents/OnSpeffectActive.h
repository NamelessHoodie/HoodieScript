#pragma once

namespace hoodie_script {

	class OnSpeffectActive {
		public:
			static std::deque<std::tuple<sol::function,bool, unsigned int, int>> OnSpeffectSubscriptions;
			static int SubscribeToEventOnSpEffect(sol::function function, bool onSpEffectExist, unsigned int entityId, int speffect);
			static std::optional<bool> EntityHasSpEffectSafeOptionalReturn(unsigned int entityId, int spEffect);
			static void DoOnSpEffect(lua_State* L);
		private:
	};

}
