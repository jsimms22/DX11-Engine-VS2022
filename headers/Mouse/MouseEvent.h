#pragma once

namespace mouse
{
	struct Point
	{
		int x;
		int y;
	};

	class MouseEvent
	{
	public:
		enum class EventType
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			MPress,
			MRelease,
			WheelDown,
			WheelUp,
			Move,
			RAW_MOVE,
			Invalid
		};

		MouseEvent();
		MouseEvent(const EventType _type, const int _x, const int _y);
		bool IsValid() const;
		EventType GetType() const;
		Point GetPos() const;
		int GetPosX() const;
		int GetPosY() const;
	private:
		EventType m_type;
		int m_x;
		int m_y;
	};
}