#pragma once

#include "script_repository.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "LuaEvents/OnSpeffectActive.h"
#include "GameObjects/player_ins.h"
#include "GameObjects/chr_ins.h"
#include "GameDebugClasses/world_chr_man.h"
#include "databaseaddress.h"

namespace hoodie_script {
	class script_runtime
	{
	public:
		typedef bool (*DoesHandleHaveSpEffect_t)(unsigned int, int);
		static DoesHandleHaveSpEffect_t DoesHandleHaveSpEffectUnsafe;
		static bool EntityHasSpEffectSafe(unsigned int entityId, int spEffect);
		static void on_goods_use(int goodsId);
		static int on_hkb_animation(uintptr_t hbkCharacter, int animationId);
		static void on_speffect(unsigned int handle, int speffect);
		static void on_game_frame();
		static bool initialize_file(std::filesystem::path file);
		static void InitializeFunctionLuaBindings();
		static void Luaprint(sol::variadic_args va, std::string);
		static void initialize();
		static lua_State* _luaState;
		static ParamPatcher *paramPatcher;
	private:
		static void handle_error(lua_State *luaState);
	};
}