#include "pch.h"
#include "script_runtime.h"

namespace hoodie_script {
	lua_State* script_runtime::_luaState = nullptr;

	void script_runtime::initialize()
	{
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		_luaState = L;

		lua_getglobal(_luaState, "_G");

		//Define print()
		static const struct luaL_Reg printlib[] = { {"print", Luaprint}, {NULL, NULL} };
		luaL_setfuncs(_luaState, printlib, 0);

		//Define SubscribeToEventOnParamLoaded
		//lua_register(LuaHandle, "SubscribeToEventOnParamLoaded", SubscribeToEventOnParamLoaded);

		lua_pop(_luaState, 1);
	}

	void script_runtime::handle_error(lua_State* luaState)
	{
		logging::write_line("Got error: %s", lua_tostring(_luaState, -1));
		lua_pop(_luaState, 1);
	}

	// TODO: cache the loadfile output so we don't do duplicate work
	// TODO: make every lua file have its own state
	bool script_runtime::initialize_file(std::filesystem::path file)
	{
		auto filePath = file.string().c_str();
		if (luaL_loadfile(_luaState, filePath) != LUA_OK ) {
			logging::write_line("Could not load LUA file %s", file.string().c_str());
			handle_error(_luaState);
			return false;
		}

		/*
		lua_newtable(_luaState);
		lua_newtable(_luaState);
		lua_getglobal(_luaState, "_G");
		lua_setfield(_luaState, -2, "__index");
		lua_setmetatable(_luaState, -2);
		lua_setfield(_luaState, LUA_REGISTRYINDEX, filePath);
		lua_getfield(_luaState, LUA_REGISTRYINDEX, filePath);
		lua_setupvalue(_luaState, 1, 1);
		*/

		if (lua_pcall(_luaState, 0, LUA_MULTRET, 0)) {
			logging::write_line("Could not init LUA file %s", file.string().c_str());
			handle_error(_luaState);
			return false;
		}
		return true;
	}

	int script_runtime::Luaprint(lua_State* L) {
		int nargs = lua_gettop(L);

		for (int i = 1; i <= nargs; i++) {
			if (lua_isstring(L, i)) {
				std::cout << lua_tostring(L, i);
			} else {
				/* Do something with non-strings if you like */
			}

			if (i == nargs)
			{
				std::cout << std::endl;
			}
		}

		return 0;
	}

	void script_runtime::on_goods_use(int goodsId) {
		for (auto file : script_repository::get_files()) {
			if (!initialize_file(file)) {
				continue;
			}

			lua_getglobal(_luaState, "on_goods_use");
			lua_pushinteger(_luaState, goodsId);
			if (lua_pcall(_luaState, 1, 0, 0) != LUA_OK) {
				logging::write_line("Could not invoke LUA %s - on_goods_use", file.string().c_str());
				handle_error(_luaState);
			}
		}
	}

	int script_runtime::on_hkb_animation(uintptr_t hbkCharacter, int animationId)
	{
		for (auto file : script_repository::get_files()) {
			if (!initialize_file(file)) {
				continue;
			}

			lua_getglobal(_luaState, "on_hkb_animation");
			lua_pushinteger(_luaState, animationId);
			if (lua_pcall(_luaState, 1, 1, 0) != LUA_OK) {
				logging::write_line("Could not invoke LUA %s - on_hkb_animation", file.string().c_str());
				handle_error(_luaState);
				continue;
			}

			if (!lua_isinteger(_luaState, -1)) {
				logging::write_line("Invoked LUA does not return an integer %s - on_hkb_animation");
				lua_pop(_luaState, 1);
				continue;
			}

			animationId = lua_tointeger(_luaState, -1);
			lua_pop(_luaState, 1);
		}

		return animationId;
	}

	void script_runtime::on_game_frame()
	{
		for (auto file : script_repository::get_files()) {
			if (!initialize_file(file)) {
				continue;
			}

			lua_getglobal(_luaState, "on_game_frame");
			if (lua_pcall(_luaState, 0, 0, 0) != LUA_OK) {
				logging::write_line("Could not invoke LUA %s - on_game_frame", file.string().c_str());
				handle_error(_luaState);
			}
		}
	}
}