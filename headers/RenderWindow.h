#pragma once
#include "ErrorLogger.h"

class RenderWindow
{
public:
	bool Initialize(HINSTANCE _hInstance, 
		std::string _window_title, 
		std::string _window_class, 
		int _width, int _height);
	bool ProcessMessages();
	~RenderWindow();

private:
	void RegisterWindowClass();
	HWND m_handle = nullptr;	// Handle to this window
	HINSTANCE m_hInstance = nullptr;	// Handle to application instance
	std::string m_window_title = "";
	std::wstring m_window_title_wide = L""; // Wide string rep of window title
	std::string m_window_class = "";
	std::wstring m_window_class_wide = L""; // Wide string representation of window classe name
	int m_width = 0;
	int m_height = 0;
};