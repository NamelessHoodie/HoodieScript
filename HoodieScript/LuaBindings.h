#pragma once
#include "HotKeyManager.h"
#include "script_runtime.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "LuaEvents/OnSpeffectActive.h"
#include "Hooks/has_speffect_hook.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaObjects/LuaMemory.h"
#include "GameObjects/equip_inventory_data.h"
#include <GameObjects/player_game_data.h>

namespace hoodie_script
{
	class LuaBindings
	{
	public:
		static void initializeEnums(sol::state_view luaSol);
		static void initializeStaticFunctions(sol::state_view luaSol);
		static void initializeClasses(sol::state_view luaSol);
		static void Luaprint(sol::variadic_args va);
		static bool EntityHasSpEffectSafe(unsigned int entityId, int spEffect);
		static bool TryLockGameInputs();
		static bool TryUnlockGameInputs();
	private:
	};

}