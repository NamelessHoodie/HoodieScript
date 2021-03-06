#pragma once

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace hoodie_script {
	class script_repository
	{
	public:
		static lua_State* _luaState;
		void initialize();
		static void load_files();
		static std::vector<std::filesystem::path> get_files();
		static std::string get_scripts_path();
	private:
		static std::vector<std::filesystem::path> _luaFiles;
	};
}