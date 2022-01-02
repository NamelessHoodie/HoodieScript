#include "pch.h"
#include "OnSpeffectActive.h"
#include "LuaBindings.h"
#include "GameObjects/player_ins.h"
#include "Hooks/has_speffect_hook.h"
#include "script_runtime.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function, bool ,unsigned int, int>> OnSpeffectActive::OnSpeffectSubscriptions;

    int OnSpeffectActive::SubscribeToEventOnSpEffect(sol::function function, bool onSpEffectExist , unsigned int entityId, int speffect)
    {
        OnSpeffectSubscriptions.push_back(std::tuple<sol::function, bool, unsigned int, int>{ function, onSpEffectExist, entityId, speffect });
        return 0;
    }

    std::optional<bool> OnSpeffectActive::EntityHasSpEffectSafeOptionalReturn(unsigned int entityId, int spEffect)
    {
        auto worldChrManPointer = (uintptr_t*)DataBaseAddress::WorldChrMan;
        if (*worldChrManPointer != NULL)
        {
            return LuaBindings::EntityHasSpEffectSafe(entityId, spEffect);
        }
        return std::nullopt;
    }

    void OnSpeffectActive::DoOnSpEffect(lua_State* L) {
        sol::state_view sol(L);
        for (size_t i = 0; i < OnSpeffectActive::OnSpeffectSubscriptions.size(); i++)
        {
            auto [funRef, onSpeffectActive, handleFilter, spEffectFilter] = OnSpeffectActive::OnSpeffectSubscriptions[i];
            auto hasSpEffect = OnSpeffectActive::EntityHasSpEffectSafeOptionalReturn(handleFilter, spEffectFilter);
            if (hasSpEffect)
            {
                if (*hasSpEffect == onSpeffectActive)
                {
                    sol::protected_function function = funRef;
                    sol::protected_function_result funResult = function(handleFilter, spEffectFilter);
                    if (funResult.valid())
                    {
                        sol::object a = funResult;
                        if ((bool)funResult == true || !a.is<bool>())
                        {
                            OnSpeffectSubscriptions.erase(OnSpeffectSubscriptions.begin() + i--);
                        }
                    }
                    else
                    {
                        sol::error error = funResult;
                        logging::write_line(error.what());
                        OnSpeffectSubscriptions.erase(OnSpeffectSubscriptions.begin() + i--);
                    }
                }
            }
        }
        return;
    }
}
