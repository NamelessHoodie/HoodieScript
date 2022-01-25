#pragma once

//Hooks
#include "hooks/goods_use_hook.h"
#include "hooks/game_frame_hook.h"
#include "hooks/hkb_animation_hook.h"
#include "hooks/session_send_hook.h"
#include "Hooks/has_speffect_hook.h"
#include "Hooks/OnTaeEvent_hook.h"
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
		static void on_position_update(uintptr_t CsHkCharacterProxy, uintptr_t* SprjChrPhysicsModulePtr, uintptr_t unk0, uintptr_t unk1, uintptr_t unk2);
		static void on_speffect(unsigned int handle, int speffect);
		static void on_game_frame();
		static void OnRenderFrame();
		static bool initialize_file(std::filesystem::path file);
		static void InitializeFunctionLuaBindings();
		static void InitializeLuaEmbeddedFiles();
		static void initialize();
		static void LuaSetPath(lua_State* L);
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
		static OnTaeEvent_hook* onTaeEvent_hook_instance;
		static hksEnvGetter_hook* hksget_hook;
		static hksActSetter_hook* hksActSet_hook;
		static menu_isopen_getter_hook* menu_isopen_getter_hook;
		static bool isGameInputLocked;
	private:
		static void handle_error(lua_State *luaState);
	};
}