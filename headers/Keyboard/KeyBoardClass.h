#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
public:
	KeyboardClass();
	bool KeyIsPressed(const unsigned char _keycode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent readKey();
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
	bool m_keyStates[256];
	std::queue<KeyboardEvent> m_keyBuffer;
	std::queue<unsigned char> m_charbuffer;
};