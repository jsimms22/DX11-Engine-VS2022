#pragma once
#include "RenderWindow.h"

class WindowContainer
{
public:
	LRESULT HandleMessageSetup(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
	//Mouse
	//Keyboard
protected:
	RenderWindow render_window;
private:
};