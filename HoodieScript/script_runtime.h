#pragma once

#include "script_repository.h"
#include "LuaEvents/OnParamLoaded.h"
#include "LuaEvents/OnGameFrame.h"
#include "LuaEvents/OnHkbAnimation.h"
#include "LuaEvents/OnSpeffectActive.h"
#include "LuaEvents/OnRenderingFrame.h"
#include "LuaEvents/OnHotkey.h"
#include "GameDebugClasses/world_chr_man.h"
#include "GameObjects/sprj_chr_data_module.h"
#include "GameDebugClasses/Bullet_Spawn.h"
#include "LuaBindings.h"
#include <random>
#include "HotKeyManager.h"

//Hooks
#include "hooks/goods_use_hook.h"
#include "hooks/game_frame_hook.h"
#include "hooks/hkb_animation_hook.h"
#include "hooks/session_send_hook.h"
#include "Hooks/has_speffect_hook.h"
#include "Hooks/jumptable_hook.h"
#include "Hooks/hksgetter_hook.h"
#include "Hooks/hksActSetter_hook.h"
#include "Hooks/menu_isopen_getter_hook.h"

namespace hoodie_script {
	class script_runtime
	{
	public:
		typedef bool (*DoesHandleHaveSpEffect_t)(unsigned int, int);
		static void on_goods_use(int goodsId);
		static int on_hkb_animation(uintptr_t hbkCharacter, int animationId);
		static void on_speffect(unsigned int handle, int speffect);
		static void on_game_frame();
		static void OnRenderFrame();
		static bool initialize_file(std::filesystem::path file);
		static void InitializeFunctionLuaBindings();
		static void initialize();
		static void initializeHooks();
		static void refreshHooks();
		static void deinitializeHooks();
		static lua_State* _luaState;
		static ParamPatcher *paramPatcher;
		// TODO: move these to a repository of their own?
		static goods_use_hook* goodsUseHook;
		static hkb_animation_hook* hkbAnimationHook;
		static game_frame_hook* gameFrameHook;
		static session_send_hook* sessionsendhook;
		static has_speffect_hook* hasspeffecthook;
		static jumptable_hook* jumptable_hook;
		static hksEnvGetter_hook* hksget_hook;
		static hksActSetter_hook* hksActSet_hook;
		static menu_isopen_getter_hook* menu_isopen_getter_hook;
		static bool isGameInputLocked;
	private:
		static void handle_error(lua_State *luaState);
	};
}