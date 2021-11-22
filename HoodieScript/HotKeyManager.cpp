#include "pch.h"
#include "HotKeyManager.h"

namespace hoodie_script
{
	byte HotKeyManager::_keysPressed[256];
	byte HotKeyManager::_keysPressedPreviousFrame[256];
	HWND HotKeyManager::_windowHandle = NULL;

	void HotKeyManager::Init(HWND windowHandle) 
	{
		_windowHandle = windowHandle;
		GetKeyboardState(_keysPressed);
	}

	void HotKeyManager::Update()
	{
		memcpy(_keysPressedPreviousFrame, _keysPressed, sizeof(_keysPressed));
		GetKeyboardState(_keysPressed);
	}

	bool HotKeyManager::IsKeyDown(VK key)
	{
		if (GetForegroundWindow() == _windowHandle)
		{
			KeyStruct* keyPressedState = (KeyStruct*)&_keysPressed[key];
			return keyPressedState->active;
		}
		return false;
	}

	bool HotKeyManager::WasKeyPressed(VK key)
	{
		if (GetForegroundWindow() == _windowHandle)
		{
			KeyStruct* keyPressedStateLastFrame = (KeyStruct*)&_keysPressedPreviousFrame[key];
			KeyStruct* keyPressedState = (KeyStruct*)&_keysPressed[key];
			if (keyPressedState->active && !keyPressedStateLastFrame->active)
			{
				return true;
			}
		}
		return false;
	}

	bool HotKeyManager::WasKeyReleased(VK key)
	{
		if (GetForegroundWindow() == _windowHandle)
		{
			KeyStruct* keyPressedStateLastFrame = (KeyStruct*)&_keysPressedPreviousFrame[key];
			KeyStruct* keyPressedState = (KeyStruct*)&_keysPressed[key];
			if (!keyPressedState->active && keyPressedStateLastFrame->active)
			{
				return true;
			}
		}
		return false;
	}
}