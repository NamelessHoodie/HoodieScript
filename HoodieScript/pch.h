// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define NOMINMAX
#define _USE_MATH_DEFINES

#include <windows.h>
#include "framework.h"
#include "lua/lua.hpp"
#include <list>
#include <string>
#include <iostream>
#include "logging.h"
#include <algorithm>
#include "LeCG/ParamPatcher.h"
#include <math.h>
#include <TlHelp32.h>
#include <DXGI.h>
#include <d3d11.h>
#include <deque>
#include "databaseaddress.h"
#include "HoodieScript-ImGui-Test/sol_ImGui.h"


	//macro from amir who got it from someone
#define call(f,...) (((intptr_t(*)(uintptr_t,...))(f))((uintptr_t)__VA_ARGS__))

extern "C" {
	#include "lua/lua.h"
	#include "lua/lauxlib.h"
	#include "lua/lualib.h"
}

#endif //PCH_H