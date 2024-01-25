#pragma once
#include "MouseEvent.h"
#include <queue>

namespace mouse 
{
	class MouseClass
	{
	public:
		void OnLeftPressed(int _x, int _y);
		void OnLeftReleased(int _x, int _y);
		void OnRightPressed(int _x, int _y);
		void OnRightReleased(int _x, int _y);
		void OnMiddlePressed(int _x, int _y);
		void OnMiddleReleased(int _x, int _y);
		void OnWheelUp(int _x, int _y);
		void OnWheelDown(int _x, int _y);
		void OnMouseMove(int _x, int _y);
		void OnMouseMoveRaw(int _x, int _y);

		bool IsLeftDown();
		bool IsMiddleDown();
		bool IsRightDown();

		int GetPosX();
		int GetPosY();
		mouse::Point GetPos();

		bool EventBufferIsEmpty();
		MouseEvent ReadEvent();

	private:
		std::queue<MouseEvent> m_eventBuffer;
		bool m_leftIsDown = false;
		bool m_rightIsDown = false;
		bool m_middleIsDown = false;
		int m_x = 0;
		int m_y = 0;
	};
}