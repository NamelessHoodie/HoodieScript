#include "pch.h"
#include "OnSpeffectActive.h"

namespace hoodie_script {

    std::deque<std::tuple<sol::function, bool ,unsigned int, int>> OnSpeffectActive::OnSpeffectSubscriptions;

    int OnSpeffectActive::SubscribeToEventOnSpEffect(sol::function function, bool onSpEffectExist , unsigned int handle, int speffect)
    {
        OnSpeffectSubscriptions.push_back(std::tuple<sol::function, bool, unsigned int, int>{ function, onSpEffectExist, handle, speffect });
        return 0;
    }

    std::optional<bool> OnSpeffectActive::HandleHasSpEffectSafe(unsigned int handle, int spEffect)
    {
        auto worldChrManPointer = (uintptr_t*)DataBaseAddress::WorldChrMan;
        if (*worldChrManPointer != NULL)
        {
            return script_runtime::DoesHandleHaveSpEffectUnsafe(handle, spEffect);
        }
        return std::nullopt;
    }

    void OnSpeffectActive::DoOnSpEffect(lua_State* L) {
        sol::state_view sol(L);
        for (size_t i = 0; i < OnSpeffectActive::OnSpeffectSubscriptions.size(); i++)
        {
            auto [funRef, leBool, handleFilter, spEffectFilter] = OnSpeffectActive::OnSpeffectSubscriptions[i];
            auto hasSpEffect = OnSpeffectActive::HandleHasSpEffectSafe(handleFilter, spEffectFilter);
            if (hasSpEffect)
            {
                if (*hasSpEffect == leBool)
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
