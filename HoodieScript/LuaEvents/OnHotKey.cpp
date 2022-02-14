#include "pch.h"
#include "OnHotkey.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function, VK, VK>> OnHotKey::OnHotKeyHandlers;
    std::deque<std::pair<sol::function, VK>> OnHotKey::OnHotKeyReleaseHandlers;

    int OnHotKey::RegisterHotkey(sol::function function, VK key, VK modifier)
    {
        OnHotKeyHandlers.push_back(std::make_tuple(function, key, modifier));
        return 1;
    }

    int OnHotKey::RegisterReleaseHotkey(sol::function function, VK key)
    {
        OnHotKeyReleaseHandlers.push_back(std::make_pair(function, key));
        return 1;
    }

    int OnHotKey::UnregisterHotkey(sol::function function)
    {
        for (size_t i = 0; i < OnHotKeyHandlers.size(); ++i)
        {
            auto& [funRef, key, modifier] = OnHotKey::OnHotKeyHandlers[i];
            if (funRef == function)
                OnHotKeyHandlers.erase(OnHotKeyHandlers.begin() + i--);
        }
        for (size_t i = 0; i < OnHotKeyReleaseHandlers.size(); ++i)
        {
            auto& [funRef, key] = OnHotKey::OnHotKeyReleaseHandlers[i];
            if (funRef == function)
                OnHotKeyReleaseHandlers.erase(OnHotKeyReleaseHandlers.begin() + i--);
        }
        return 1;
    }

    void OnHotKey::DoOnHotkey(lua_State* L) {
        auto lock = LuaStateThreadLock::GetLockObject();
        sol::state_view lua(L);
        for (size_t i = 0; i < OnHotKeyHandlers.size(); ++i) {
            auto& [funRef, key, modifier] = OnHotKey::OnHotKeyHandlers[i];
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
        for (size_t i = 0; i < OnHotKeyReleaseHandlers.size(); ++i) {
            auto& [funRef, key] = OnHotKey::OnHotKeyReleaseHandlers[i];

            if (HotKeyManager::WasKeyReleased(key))
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
    }
}
