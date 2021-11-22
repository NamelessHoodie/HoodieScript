/***
*         _ ____    _ _ _   _             _
*      __| |__ / __| / / | | |_  ___  ___| |__
*     / _` ||_ \/ _` | | | | ' \/ _ \/ _ \ / /
*     \__,_|___/\__,_|_|_| |_||_\___/\___/_\_\
*
*     D3D11Hook by Rebzzel
*	  Added ImGui + InputHook by Sh0ckFR - https://twitter.com/Sh0ckFR
*     For compile hook you need:
*      - DirectX SDK (https://www.microsoft.com/en-us/download/details.aspx?id=6812)
*      - Minhook (you can download in NuGet or github repository https://github.com/TsudaKageyu/minhook)
*     License: https://github.com/Rebzzel/Universal-D3D11-Hook#license
*/


#ifndef D3D11_HOOK_H_INCLUDED_
#define D3D11_HOOK_H_INCLUDED_

#define D3D11_HOOK_API
#include <d3d11.h>
#include <mutex>
#include "LuaEvents/OnRenderingFrame.h"
#include <HoodieScript-ImGui-Test/imgui_impl_dx11.h>
#include "minHook\MinHook.h"
#include "script_runtime.h"
#pragma comment(lib, "d3d11.lib")

struct ID3D11Device; // from d3d11.h
struct ID3D11DeviceContext; // from d3d11.h
struct IDXGISwapChain; // from d3d11.h

					   // Use for rendering graphical user interfaces (for example: ImGui) or other.
extern D3D11_HOOK_API void ImplHookDX11_Present(ID3D11Device *device, ID3D11DeviceContext *ctx, IDXGISwapChain *swap_chain);

DWORD __stdcall HookDX11_Init();

DWORD __stdcall HookDX11_UnInit();

// Use for initialize hook.
D3D11_HOOK_API bool	       ImplHookDX11_Init(HMODULE hModule, void *hwnd);

// Use for untialize hook (ONLY AFTER INITIALIZE).
D3D11_HOOK_API void	       ImplHookDX11_Shutdown();

#endif
