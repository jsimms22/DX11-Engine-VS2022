#pragma once


class KeyboardEvent
{
public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};

	KeyboardEvent();
	KeyboardEvent(const EventType _type, const unsigned char _key);
	bool isPress() const;
	bool isRelease() const;
	bool isValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType m_type;
	unsigned char m_key;
};