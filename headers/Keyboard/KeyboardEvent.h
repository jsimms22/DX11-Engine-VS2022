#pragma once

namespace keyboard
{
	class KeyboardEvent
	{
	public:
		enum class EventType
		{
			Press,
			Release,
			Invalid
		};

		KeyboardEvent();
		KeyboardEvent(const KeyboardEvent::EventType _type, const unsigned char _key);
		bool isPress() const;
		bool isRelease() const;
		bool isValid() const;
		unsigned char GetKeyCode() const;

	private:
		EventType m_type;
		unsigned char m_key;
	};
}