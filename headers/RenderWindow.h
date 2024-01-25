#pragma once
#include "ErrorLogger.h"

class WindowContainer; // forward declare

class RenderWindow
{
public:
	bool Initialize(WindowContainer* _ptrWinCon,
		HINSTANCE _hInstance,	// handle to window instance
		std::string _window_title,			// window title
		std::string _window_class,			// window class name
		int _width, int _height);			// assign window size
	// this process all messages sent to window, and dispatch them elsewhere
	// if returns false, then window should be closed
	// otherwise continue messaging loop
	bool ProcessMessages();
	HWND GetHWND() const;
	~RenderWindow();

private:
	// private to require Initialize fn
	void RegisterWindowClass();
	HWND m_handle = nullptr;			// Handle to this window
	HINSTANCE m_hInstance = nullptr;	// Handle to application instance
	std::string m_window_title = "";
	std::wstring m_window_title_wide = L""; // Wide string rep of window title
	std::string m_window_class = "";
	std::wstring m_window_class_wide = L""; // Wide string representation of window classe name
	int m_width = 0;
	int m_height = 0;
};