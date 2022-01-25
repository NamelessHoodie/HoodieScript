#pragma once

namespace hoodie_script {
	class OnPositionUpdate {
		public:
			static int SubscribeToEventOnPositionUpdate(sol::function function);
			static void DoOnPositionUpdate(lua_State* L, uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2);
		private:
			static std::deque<std::tuple<sol::function>> OnGameFrameHandlers;
	};
}
