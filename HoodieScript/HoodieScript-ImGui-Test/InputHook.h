#pragma once
#include "imgui_impl_dx11.h"

class InputHook
{
public:
	void Init(HWND hWindow);
	void Remove(HWND hWindow);
};

static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

