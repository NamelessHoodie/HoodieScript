#pragma once

namespace hoodie_script
{
	class GuiManager
	{
	public:
		static void Init();
		static void Uninit();
	private:
		static HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void InitImGui();
		static void PushDefaultTheme();
		static Present oPresent;
		static HWND window;
		static WNDPROC oWndProc;
		static IDXGISwapChain* pSwapChainS;
		static ID3D11Device* pDevice;
		static ID3D11DeviceContext* pContext;
		static ID3D11RenderTargetView* mainRenderTargetView;
	};


	//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

}