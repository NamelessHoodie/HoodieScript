#pragma once
#include "GameObjects/player_ins.h"
#include "Hooks/has_speffect_hook.h"

namespace hoodie_script {

	class OnSpeffectActive {
		public:
			static std::deque<std::tuple<sol::function,bool, unsigned int, int>> OnSpeffectSubscriptions;
			static int SubscribeToEventOnSpEffect(sol::function function, bool onSpEffectExist, unsigned int handle, int speffect);
			static std::optional<bool> HandleHasSpEffectSafe(unsigned int handle, int spEffect);
			static void DoOnSpEffect(lua_State* L);
		private:
	};

}
