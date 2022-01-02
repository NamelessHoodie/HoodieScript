#pragma once

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