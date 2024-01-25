#include "../headers/WindowContainer.h"
#include <memory>

WindowContainer::WindowContainer()
{
	static bool raw_input_initialized = false;
	if (raw_input_initialized == false) {
		RAWINPUTDEVICE rid[1];
		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x02;
		rid[0].dwFlags = 0;//RIDEV_NOLEGACY;
		rid[0].hwndTarget = 0;

		if (RegisterRawInputDevices(rid, 1, sizeof(rid)) == false)
		{
			ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
			exit(-1);
			// Registration failed. Call LastError for the cause.
		}
		raw_input_initialized = true;
	}
}

LRESULT WindowContainer::HandleMessageSetup(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	//OutputDebugStringA("WINDOW PROC FROM WINDOW CONTAINER.\n");
	//return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);

	switch (_uMsg) {
	// Keyboard Messages
	case WM_KEYDOWN:
	{
		unsigned char ch = static_cast<unsigned char>(_wParam);
		if (m_keyboard.IsKeyAutoRepeat()) {
			m_keyboard.OnKeyPressed(ch);
		} else {
			const bool wasPressed = _lParam & 0x40000000;
			if (!wasPressed) {
				m_keyboard.OnKeyPressed(ch);
			}
		}
		return 0;
	}
	case WM_KEYUP:
	{
		unsigned char ch = static_cast<unsigned char>(_wParam);
		m_keyboard.OnKeyReleased(ch);
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(_wParam);
		if (m_keyboard.IsCharsAutoRepeat()) {
			m_keyboard.OnChar(ch);
		} else {
			const bool wasPressed = _lParam & 0x40000000;
			if (!wasPressed) {
				m_keyboard.OnChar(ch);
			}
		}
		return 0;
	}
	// Mouse Messages
	case WM_MOUSEMOVE:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnMouseMove(x, y);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnLeftPressed(x, y);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnRightPressed(x, y);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnMiddlePressed(x, y);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnLeftReleased(x, y);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnRightReleased(x, y);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		m_mouse.OnMiddleReleased(x, y);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x{ LOWORD(_lParam) };
		int y{ HIWORD(_lParam) };
		if (GET_WHEEL_DELTA_WPARAM(_wParam) > 0) {
			m_mouse.OnWheelUp(x, y);
		} else if (GET_WHEEL_DELTA_WPARAM(_wParam) < 0) {
			m_mouse.OnWheelDown(x, y);
		}
		break;
	}
	case WM_INPUT:
	{
		UINT dataSize;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

		if (dataSize > 0) {
			std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);

			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) != dataSize) {
				OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));
			}

			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(_lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER) == dataSize)) {
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE) {
					m_mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}
		// MS documentation requires DefWindowProc for both wParam cases for raw input
		return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	}
	default:
		return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	}
}