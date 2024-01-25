#include "../headers/Engine.h"

bool Engine::Initialize(HINSTANCE _hInstance,
	std::string _window_title,
	std::string _window_class,
	int _width, int _height)
{
	return this->m_render_window.Initialize(this,_hInstance, _window_title, _window_class, _width, _height);
	// generally we would render all our graphics after initializing our window
}

bool Engine::ProcessMessages()
{
	return this->m_render_window.ProcessMessages();
}

void Engine::Update()
{
	while (!m_keyboard.CharBufferIsEmpty()) {
		unsigned char ch = m_keyboard.ReadChar();
		/*
		std::string outmsg = "Char: ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
		*/
	}

	while (!m_keyboard.KeyBufferIsEmpty()) {
		keyboard::KeyboardEvent kbe = m_keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		/*
		std::string outmsg = "";
		if (kbe.isPress()) { outmsg += "Key press: "; }
		if (kbe.isRelease()) { outmsg += "Key release: "; }
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
		*/
	}

	while (!m_mouse.EventBufferIsEmpty()) {
		mouse::MouseEvent me = m_mouse.ReadEvent();
		/*
		std::string outmsg = "X: ";
		outmsg += std::to_string(me.GetPosX());
		outmsg += ", Y: ";
		outmsg += std::to_string(me.GetPosY());
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
		*/
		/*
		if (me.GetType() == mouse::MouseEvent::EventType::WheelUp) {
			OutputDebugStringA("MouseWheelUp\n");
		}
		if (me.GetType() == mouse::MouseEvent::EventType::WheelDown) {
			OutputDebugStringA("MouseWheelDown\n");
		}
		*/
	}
}