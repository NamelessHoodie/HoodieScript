#pragma once

#include "script_repository.h"

namespace hoodie_script {
	class script_runtime
	{
	public:
		static void on_goods_use(int goodsId);
		static int on_hkb_animation(uintptr_t hbkCharacter, int animationId);
		static void on_game_frame();
		static bool initialize_file(std::filesystem::path file);
		static void InitializeFunctionLuaBindings();
		static int Luaprint(lua_State* L);
		static void initialize();
		static lua_State* _luaState;
	private:
		static void handle_error(lua_State *luaState);
	};
}