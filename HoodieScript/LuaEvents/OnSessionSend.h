#pragma once

namespace hoodie_script {
	class OnSessionSend {
	public:
		static int SubscribeToEventOnSessionSend(sol::function function);
		static int DoOnSessionSend(lua_State* L, uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength);
	private:
		static std::deque<std::tuple<sol::function>> OnSessionSendHandlers;
	};
}