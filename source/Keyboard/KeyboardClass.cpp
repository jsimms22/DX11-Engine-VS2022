#include "../../headers/Keyboard/KeyboardClass.h"


KeyboardClass::KeyboardClass() { }

bool KeyboardClass::KeyIsPressed(const unsigned char _keycode) { }

bool KeyboardClass::KeyBufferIsEmpty() { }

bool KeyboardClass::CharBufferIsEmpty() { }

KeyboardEvent KeyboardClass::readKey() { }

unsigned char KeyboardClass::ReadChar() { }

void KeyboardClass::OnKeyPressed(const unsigned char _key) { }

void KeyboardClass::OnKeyReleased(const unsigned char _key) { }

void KeyboardClass::OnChar(const unsigned char key) { }

void KeyboardClass::EnableAutoRepeatKeys() { }

void KeyboardClass::DisableAutoRepeatKeys() { }

void KeyboardClass::EnableAutoRepeatChars() { }

void KeyboardClass::DisableAutoRepeatChars() { }

bool KeyboardClass::IsKeyAutoRepeat() { }

bool KeyboardClass::IsCharsAutoRepeat() { }