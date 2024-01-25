#include "../../headers/Mouse/MouseClass.h"

namespace mouse
{
	void MouseClass::OnLeftPressed(int _x, int _y) 
	{ 
		this->m_leftIsDown = true;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, _x, _y));
	}

	void MouseClass::OnLeftReleased(int _x, int _y) 
	{
		this->m_leftIsDown = false;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, _x, _y));
	}

	void MouseClass::OnRightPressed(int _x, int _y) 
	{
		this->m_rightIsDown = true;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, _x, _y));
	}

	void MouseClass::OnRightReleased(int _x, int _y) 
	{
		this->m_rightIsDown = false;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, _x, _y));
	}

	void MouseClass::OnMiddlePressed(int _x, int _y) 
	{
		this->m_middleIsDown = true;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, _x, _y));
	}

	void MouseClass::OnMiddleReleased(int _x, int _y) 
	{
		this->m_middleIsDown = false;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, _x, _y));
	}

	void MouseClass::OnWheelUp(int _x, int _y) { this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, _x, _y)); }

	void MouseClass::OnWheelDown(int _x, int _y) { this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, _x, _y)); }

	void MouseClass::OnMouseMove(int _x, int _y) 
	{ 
		this->m_x = _x;
		this->m_y = _y;
		this->m_eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, _x, _y));
	}

	bool MouseClass::IsLeftDown() { return this->m_leftIsDown; }

	bool MouseClass::IsMiddleDown() { return this->m_middleIsDown; }

	bool MouseClass::IsRightDown() { return this->m_rightIsDown; }

	int MouseClass::GetPosX() { return this->m_x; }

	int MouseClass::GetPosY() { return this->m_y; }

	mouse::Point MouseClass::GetPos() { return mouse::Point{this->m_x, this->m_y}; }

	bool MouseClass::EventBufferIsEmpty() { return this->m_eventBuffer.empty(); }

	MouseEvent MouseClass::ReadEvent() { 
		if (this->EventBufferIsEmpty() == true) {
			return MouseEvent();
		} else {
			MouseEvent e = this->m_eventBuffer.front();
			this->m_eventBuffer.pop();
			return e;
		}
	}
}