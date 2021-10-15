#pragma once

#include "script_repository.h"

namespace hoodie_script {
	class script_runtime
	{
	public:
		static void initialize();
		static void on_goods_use(int goodsId);
		static int on_hkb_animation(uintptr_t hbkCharacter, int animationId);
		static void on_game_frame();
	private:
		static lua_State *_luaState;
		static void handle_error(lua_State *luaState);
		static bool initialize_file(std::filesystem::path file);

		static int Luaprint(lua_State* L);	
	};
}