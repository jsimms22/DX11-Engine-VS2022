#include "../../headers/Keyboard/KeyboardClass.h"

namespace keyboard
{
	KeyboardClass::KeyboardClass() { for (bool key : this->m_keyStates) { key = false; } }

	bool KeyboardClass::KeyIsPressed(const unsigned char _keycode) { return this->m_keyStates[_keycode]; }

	bool KeyboardClass::KeyBufferIsEmpty() { return this->m_keyBuffer.empty(); }

	bool KeyboardClass::CharBufferIsEmpty() { return this->m_charBuffer.empty(); }

	KeyboardEvent KeyboardClass::ReadKey()
	{
		if (m_keyBuffer.empty()) {
			return KeyboardEvent();
		}
		else {
			KeyboardEvent e = this->m_keyBuffer.front(); // Get first keyboard event from queue
			this->m_keyBuffer.pop(); // Remove first item from queue
			return e; // Returns keyboard event
		}
	}

	unsigned char KeyboardClass::ReadChar()
	{
		if (m_charBuffer.empty()) {
			return 0u;
		}
		else {
			unsigned char e = this->m_charBuffer.front(); // Get first char from queue
			this->m_charBuffer.pop(); // Remove char from queue
			return e; // Returns char
		}
	}

	void KeyboardClass::OnKeyPressed(const unsigned char _key)
	{
		this->m_keyStates[_key] = true;
		this->m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, _key));
	}

	void KeyboardClass::OnKeyReleased(const unsigned char _key)
	{
		this->m_keyStates[_key] = false;
		this->m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, _key));
	}

	void KeyboardClass::OnChar(const unsigned char _key) { this->m_charBuffer.push(_key); }

	void KeyboardClass::EnableAutoRepeatKeys() { this->m_autoRepeatKeys = true; }

	void KeyboardClass::DisableAutoRepeatKeys() { this->m_autoRepeatKeys = false; }

	void KeyboardClass::EnableAutoRepeatChars() { this->m_autoRepeatChars = true; }

	void KeyboardClass::DisableAutoRepeatChars() { this->m_autoRepeatChars = false; }

	bool KeyboardClass::IsKeyAutoRepeat() { return this->m_autoRepeatKeys; }

	bool KeyboardClass::IsCharsAutoRepeat() { return this->m_autoRepeatChars; }
}