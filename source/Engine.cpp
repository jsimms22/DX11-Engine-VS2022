#include "../headers/Engine.h"

bool Engine::Initialize(HINSTANCE _hInstance,
	std::string _window_title,
	std::string _window_class,
	int _width, int _height)
{
	return this->render_window.Initialize(this,_hInstance, _window_title, _window_class, _width, _height);
	// generally we would render all our graphics after initializing our window
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}

void Engine::Update()
{

}