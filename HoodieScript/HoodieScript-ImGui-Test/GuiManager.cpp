#include "pch.h"
#include "GuiManager.h"
namespace hoodie_script
{

	HWND GuiManager::window = NULL;
	WNDPROC GuiManager::oWndProc = NULL;
	ID3D11Device* GuiManager::pDevice = nullptr;
	ID3D11DeviceContext* GuiManager::pContext = nullptr;
	ID3D11RenderTargetView* GuiManager::mainRenderTargetView = nullptr;
	IDXGISwapChain* GuiManager::pSwapChainS = nullptr;
	Present GuiManager::oPresent = NULL;

	void GuiManager::Init()
	{
		bool init_hook = false;
		do
		{
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
			{
				kiero::bind(8, (void**)&oPresent, hkPresent);
				init_hook = true;
			}
		} while (!init_hook);
	}

	void GuiManager::Uninit()
	{
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChainS->GetDesc(&sd);
		window = sd.OutputWindow;
		kiero::unbind(8);
		pDevice->Release();
		pContext->Release();
		pSwapChainS->Release();
		ImGui::DestroyContext();
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	}

	void GuiManager::InitImGui()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}

	LRESULT __stdcall GuiManager::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	HRESULT __stdcall GuiManager::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		static bool init = false;
		if (!init)
		{
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
			{

				pSwapChainS = pSwapChain;
				pDevice->GetImmediateContext(&pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				pSwapChain->GetDesc(&sd);
				window = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				pBackBuffer->Release();
				oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
				InitImGui();
				ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
				init = true;
			}

			else
				return oPresent(pSwapChain, SyncInterval, Flags);
		}
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		hoodie_script::script_runtime::OnRenderFrame();

		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return oPresent(pSwapChain, SyncInterval, Flags);
	}
}