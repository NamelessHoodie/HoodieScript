#pragma once
#include "HotKeyManager.h"

namespace hoodie_script {
	class OnHotKey {
		public:
			static int RegisterHotkey(sol::function function, VK key, VK modifier);
			static int UnregisterHotkey(sol::function function);
			static void DoOnHotkey(lua_State* L);
		private:
			static std::deque<std::tuple<sol::function, VK, VK>> OnHotKeyHandlers;
	};

}
