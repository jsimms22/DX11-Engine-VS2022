#pragma once
#include "KeyboardEvent.h"
#include <array>
#include <queue>

namespace keyboard
{
	class KeyboardClass
	{
	public:
		KeyboardClass();
		bool KeyIsPressed(const unsigned char _keycode);
		bool KeyBufferIsEmpty();
		bool CharBufferIsEmpty();
		KeyboardEvent ReadKey();
		unsigned char ReadChar();
		void OnKeyPressed(const unsigned char _key);
		void OnKeyReleased(const unsigned char _key);
		void OnChar(const unsigned char key);
		void EnableAutoRepeatKeys();
		void DisableAutoRepeatKeys();
		void EnableAutoRepeatChars();
		void DisableAutoRepeatChars();
		bool IsKeyAutoRepeat();
		bool IsCharsAutoRepeat();
	private:
		bool m_autoRepeatKeys = false;
		bool m_autoRepeatChars = false;
		std::array<bool, 256> m_keyStates;
		std::queue<KeyboardEvent> m_keyBuffer;
		std::queue<unsigned char> m_charBuffer;
	};
}