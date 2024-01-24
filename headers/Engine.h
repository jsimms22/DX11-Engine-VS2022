#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer 
{
public:
	bool Initialize(HINSTANCE _hInstance,	// handle to window instance
		std::string _window_title,			// window title
		std::string _window_class,			// window class name
		int _width, int _height);			// assign window size
	bool ProcessMessages();
	void Update();
};