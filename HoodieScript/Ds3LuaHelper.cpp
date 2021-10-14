#include "pch.h"
#include "Ds3LuaHelper.h"

namespace hoodie_script {
	Ds3LuaHelper::Ds3LuaHelper()
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		LuaHandle = L;
	}

	void Ds3LuaHelper::Initialize() {
		logging::write_line("Initing Lua");
		InitializeNativeFunctionsToLuaBindings();

		luaL_dostring(LuaHandle, R"(print("TestPrintFromLua"))");

		logging::write_line("Memes");

		LPTSTR  dllPath = new TCHAR[_MAX_PATH];
		GetModuleFileName((HINSTANCE)&__ImageBase, dllPath, _MAX_PATH);
		const wchar_t* txt = dllPath;
		std::wstring ws(dllPath);
		ws = std::filesystem::path(ws).remove_filename().wstring() + std::filesystem::path("HoodieScripts").wstring();

		std::list<std::string> stringList;
		int i = 1;
		for (const auto& entry : std::filesystem::directory_iterator(ws)) {
			if (entry.path().string().ends_with(".lua")) {
				std::string buf("LuaFile");
				buf.append(std::to_string(i));
				stringList.push_back(buf);
				luaL_loadfile(LuaHandle, entry.path().string().c_str());
				lua_newtable(LuaHandle);
				lua_newtable(LuaHandle);
				lua_getglobal(LuaHandle, "_G");
				lua_setfield(LuaHandle, -2, "__index");
				lua_setmetatable(LuaHandle, -2);
				lua_setfield(LuaHandle, LUA_REGISTRYINDEX, buf.c_str());
				lua_getfield(LuaHandle, LUA_REGISTRYINDEX, buf.c_str());
				lua_setupvalue(LuaHandle, 1, 1);
				lua_pcall(LuaHandle, 0, LUA_MULTRET, 0);
			}
		}
		LoadedLuaFiles = stringList;
	}

	void Ds3LuaHelper::InitializeNativeFunctionsToLuaBindings() {
		lua_getglobal(LuaHandle, "_G");

		//Define print()
		static const struct luaL_Reg printlib[] = { {"print", Luaprint}, {NULL, NULL} };
		luaL_setfuncs(LuaHandle, printlib, 0);

		//Define SubscribeToEventOnParamLoaded
		//lua_register(LuaHandle, "SubscribeToEventOnParamLoaded", SubscribeToEventOnParamLoaded);

		lua_pop(LuaHandle, 1);
	}

	int Luaprint(lua_State* L) {
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
}