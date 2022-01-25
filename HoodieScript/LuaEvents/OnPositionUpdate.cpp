#include "pch.h"
#include "OnPositionUpdate.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function>> OnPositionUpdate::OnGameFrameHandlers;

    int OnPositionUpdate::SubscribeToEventOnPositionUpdate(sol::function function)
    {
        OnGameFrameHandlers.push_back(std::tuple<sol::function>{ function});
        return 0;
    }

    void OnPositionUpdate::DoOnPositionUpdate(lua_State* L, uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2) {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view sol(L);
        for (size_t i = 0; i < OnGameFrameHandlers.size(); ++i) {
            auto& [funRef] = OnPositionUpdate::OnGameFrameHandlers[i];
            sol::protected_function fun = funRef;
            sol::protected_function_result result = fun(CsHkCharacterProxy, SprjChrPhysicsModulePtr, unk0, unk1, unk2);
            if (result.valid())
            {
                sol::error error = result;
                logging::write_line(error.what());
            }
        }
    }
}
