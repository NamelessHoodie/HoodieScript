#pragma once

namespace hoodie_script {
	class OnSessionReceive {
	public:
		static int SubscribeToEventOnSessionReceive(sol::function function);
		static int DoOnSessionReceive(lua_State* L, uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength, uint32_t receiveLength);
	private:
		static std::deque<std::tuple<sol::function>> OnSessionReceiveHandlers;
	};
}