#pragma once
#include "RenderWindow.h"
#include "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"

class WindowContainer
{
public:
	WindowContainer();
	LRESULT HandleMessageSetup(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
protected:
	RenderWindow m_render_window;
	keyboard::KeyboardClass m_keyboard;
	mouse::MouseClass m_mouse;
private:
};