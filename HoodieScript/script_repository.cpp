#include "pch.h"
#include "script_repository.h"

namespace hoodie_script {
	std::vector<std::filesystem::path> script_repository::_luaFiles;

	void script_repository::load_files()
	{
		auto pathStr = get_scripts_path();
		logging::write_line("Found lua file %s", pathStr.c_str());
		for (const auto& entry : std::filesystem::directory_iterator(pathStr)) {
			if (entry.path().string().ends_with(".lua")) {
				auto path = entry.path();
				if (script_runtime::initialize_file(path))
				{
					_luaFiles.emplace_back(path);
				}
			}
		}
	}

	std::vector<std::filesystem::path> script_repository::get_files()
	{
		return _luaFiles;
	}

	std::string script_repository::get_scripts_path()
	{
		LPSTR  dllPath = new CHAR[_MAX_PATH];
		GetModuleFileNameA((HINSTANCE)&__ImageBase, dllPath, _MAX_PATH);
		std::string pathStr(dllPath);
		return std::filesystem::path(pathStr).remove_filename().string() + std::filesystem::path("HoodieScripts").string();
	}
}