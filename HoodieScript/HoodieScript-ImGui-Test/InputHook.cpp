#include "pch.h"
#include "InputHook.h"

using namespace ImGui;

WNDPROC	oWndProc;

void InputHook::Init(HWND hWindow)
{
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
}

void InputHook::Remove(HWND hWindow)
{
	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
		GetIO().AddInputCharacter(wParam);
		break;
	case WM_LBUTTONDOWN:
		GetIO().MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		GetIO().MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		GetIO().MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		GetIO().MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		GetIO().MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		GetIO().MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		GetIO().MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		GetIO().MousePos.x = (signed short)(lParam); GetIO().MousePos.y = (signed short)(lParam >> 16); return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_QUIT:
		break;
	}
	//ImGuiIO io = GetIO();
	//std::cout << io.KeyMap[ImGuiKey_Backspace] << " KEY " << VK_BACK << "\n";
	//io.KeyMap[ImGuiKey_Tab] = VK_TAB;
	//io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
	//io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
	//io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
	//io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
	//io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
	//io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
	//io.KeyMap[ImGuiKey_Home] = VK_HOME;
	//io.KeyMap[ImGuiKey_End] = VK_END;
	//io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
	//io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
	//io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
	//io.KeyMap[ImGuiKey_Space] = VK_SPACE;
	//io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
	//io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
	//io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
	//io.KeyMap[ImGuiKey_A] = 'A';
	//io.KeyMap[ImGuiKey_C] = 'C';
	//io.KeyMap[ImGuiKey_V] = 'V';
	//io.KeyMap[ImGuiKey_X] = 'X';
	//io.KeyMap[ImGuiKey_Y] = 'Y';
	//io.KeyMap[ImGuiKey_Z] = 'Z';
	//switch (wParam)
	//{
	//case '0':
	//	GetIO().AddInputCharacter('0');
	//	break;
	//case '1':
	//	GetIO().AddInputCharacter('1');
	//	break;
	//case '2':
	//	GetIO().AddInputCharacter('2');
	//	break;
	//case '3':
	//	GetIO().AddInputCharacter('3');
	//	break;
	//case '4':
	//	GetIO().AddInputCharacter('4');
	//	break;
	//case '5':
	//	GetIO().AddInputCharacter('5');
	//	break;
	//case '6':
	//	GetIO().AddInputCharacter('6');
	//	break;
	//case '7':
	//	GetIO().AddInputCharacter('7');
	//	break;
	//case '8':
	//	GetIO().AddInputCharacter('8');
	//	break;
	//case '9':
	//	GetIO().AddInputCharacter('9');
	//	break;
	//default:
	//	break;
	//}
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}