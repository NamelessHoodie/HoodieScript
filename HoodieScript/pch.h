// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define NOMINMAX
#define _USE_MATH_DEFINES

#include "HoodieScript-ImGui-Test/kiero/kiero.h"
#include "HoodieScript-ImGui-Test/imgui/imgui.h"
#include "HoodieScript-ImGui-Test/imgui/imgui_impl_win32.h"
#include "HoodieScript-ImGui-Test/imgui/imgui_impl_dx11.h"
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

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

#endif //PCH_H