#include "../../headers/Mouse/MouseEvent.h"

namespace mouse
{
	MouseEvent::MouseEvent()
		:m_type{ EventType::Invalid }, m_x{ 0 }, m_y{ 0 } { }
	
	MouseEvent::MouseEvent(const EventType _type, const int _x, const int _y)
		:m_type{_type}, m_x{_x}, m_y{_y} { }

	bool MouseEvent::IsValid() const { return this->m_type != EventType::Invalid; }

	MouseEvent::EventType MouseEvent::GetType() const { return this->m_type; }

	Point MouseEvent::GetPos() const { return {this->m_x, this->m_y}; }

	int MouseEvent::GetPosX() const { return this->m_x; }

	int MouseEvent::GetPosY() const { return this->m_y; }
}