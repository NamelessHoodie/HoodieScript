// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <windows.h>
#undef min
#undef max
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <unordered_set>
#include "ds3runtime/dependencies/detours/detours.h"
#include <memory>
#include <functional>
#include <string_view>
#include <optional>
#include <algorithm>
#include <execution>
#include "ds3runtime/dependencies/spdlog/spdlog.h"
#include "ds3runtime/dependencies/spdlog/sinks/basic_file_sink.h"
#include "ds3runtime/dependencies/spdlog/sinks/stdout_color_sinks.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include <filesystem>
#include "ds3runtime/dependencies/fmod/fmod.hpp"
#include "ds3runtime/dependencies/fmod/fmod_errors.h"
#include <cmath>

#endif //PCH_H
