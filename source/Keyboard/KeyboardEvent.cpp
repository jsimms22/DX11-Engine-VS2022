#include "../../headers/Keyboard/KeyboardEvent.h"

namespace keyboard
{
	KeyboardEvent::KeyboardEvent()
		:m_type{ EventType::Invalid }, m_key{ 0u } { }

	KeyboardEvent::KeyboardEvent(const EventType _type, const unsigned char _key)
		:m_type{ _type }, m_key{ _key } { }

	bool KeyboardEvent::isPress() const { return this->m_type == EventType::Press; }

	bool KeyboardEvent::isRelease() const { return this->m_type == EventType::Release; }

	bool KeyboardEvent::isValid() const { return this->m_type == EventType::Invalid; }

	unsigned char KeyboardEvent::GetKeyCode() const { return this->m_key; }
}