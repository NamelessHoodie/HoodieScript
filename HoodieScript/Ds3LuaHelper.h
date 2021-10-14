#pragma once

#include <fstream>
#include <filesystem>
#include "logging.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace hoodie_script {
	class Ds3LuaHelper {
	public:
		lua_State* LuaHandle;
		std::list<std::string> LoadedLuaFiles;

		Ds3LuaHelper();
		void Initialize();
	private:
		void InitializeNativeFunctionsToLuaBindings();
	};

	static int Luaprint(lua_State* L);
}