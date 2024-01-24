#include "../headers/WindowContainer.h"

LRESULT WindowContainer::HandleMessageSetup(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	OutputDebugStringA("WINDOW PROC FROM WINDOW CONTAINER.\n");
	return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
}