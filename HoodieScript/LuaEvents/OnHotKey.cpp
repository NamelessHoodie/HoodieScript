#include "pch.h"
#include "OnHotkey.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function, VK, VK>> OnHotKey::OnHotKeyHandlers;

    int OnHotKey::RegisterHotkey(sol::function function, VK key, VK modifier)
    {
        OnHotKeyHandlers.push_back(std::tuple<sol::function, VK, VK>{ function, key, modifier});
        return 1;
    }

    int OnHotKey::UnregisterHotkey(sol::function function)
    {
        for (size_t i = 0; i < OnHotKeyHandlers.size(); i++)
        {
            auto& [funRef, key, modifier] = OnHotKey::OnHotKeyHandlers[i];
            if (funRef == function)
            {
                OnHotKeyHandlers.erase(OnHotKeyHandlers.begin() + i--);
            }
        }
        return 1;
    }

    void OnHotKey::DoOnHotkey(lua_State* L) {
        LuaStateThreadLock::Lock();
        sol::state_view lua(L);
        for (size_t i = 0; i < OnHotKeyHandlers.size(); ++i) {
            auto &[funRef, key, modifier] = OnHotKey::OnHotKeyHandlers[i];
            bool modifierKeyPressed = modifier != NULL ? HotKeyManager::IsKeyDown(modifier) : true;

            if (HotKeyManager::WasKeyPressed(key) && modifierKeyPressed)
            {
                sol::protected_function fun = funRef;
                sol::protected_function_result result = fun();
                if (!result.valid())
                {
                    sol::error error = result;
                    logging::write_line(error.what());
                }
            }
        }
        LuaStateThreadLock::Unlock();
    }
}
