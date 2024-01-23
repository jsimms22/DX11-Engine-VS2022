#include "../headers/RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE _hInstance, 
	std::string _window_title, 
	std::string _window_class, 
	int _width, int _height)
{
	this->m_hInstance = _hInstance;
	this->m_width = _width;
	this->m_height = _height;
	this->m_window_title = _window_title;
	this->m_window_title_wide = StringConverter::StringToWide(this->m_window_title);
	this->m_window_class = _window_class;
	this->m_window_class_wide = StringConverter::StringToWide(this->m_window_class);

	this->RegisterWindowClass();



	return false;
}
