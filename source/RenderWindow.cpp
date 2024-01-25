#include "../headers/WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* _ptrWinCon,
	HINSTANCE _hInstance, 
	std::string _window_title, 
	std::string _window_class, 
	int _width, int _height)
{
	this->m_hInstance = _hInstance;
	this->m_width = _width;
	this->m_height = _height;
	this->m_window_title = _window_title;
	this->m_window_title_wide = StringConverter::StringToWide(this->m_window_title);
	this->m_window_class = _window_class;
	this->m_window_class_wide = StringConverter::StringToWide(this->m_window_class);

	this->RegisterWindowClass();

	// returns handle if created, otherwise null
	this->m_handle = CreateWindowEx(0, // Extended Windows style - this is the default
		this->m_window_class_wide.c_str(), // window class name (long)
		this->m_window_title_wide.c_str(), // window title name (long)
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // Windows style
		100, // window x-pos
		100, // window y-pos
		this->m_width, 
		this->m_height,
		nullptr, // handle to parent window
		nullptr, // handle to child window
		this->m_hInstance, // handle to the instance of module to be used with this window
		_ptrWinCon); // param to create window\

	if (this->m_handle == nullptr) {
		// GetLastError() allows us to retrieve the HRESULT from CreateWindowEx
		ErrorLogger::Log(GetLastError(), "CreateWindowEx Failed for Window: " + this->m_window_title);
		return false;
	}

	// bring window up and set it as main focus
	ShowWindow(this->m_handle, SW_SHOW);
	SetForegroundWindow(this->m_handle);
	SetFocus(this->m_handle);

	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg) {
	case WM_CLOSE:
		DestroyWindow(_hwnd);
		return 0;
	default:
	{
		// Retrieve ptr to window class
		WindowContainer* ptrWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
		// Forward message to window class handler
		return ptrWindow->HandleMessageSetup(_hwnd, _uMsg, _wParam, _lParam);
	}
	}
}

// Our custom window proc
// Where all of our messages get dispatched to
LRESULT CALLBACK HandleMessageSetup(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	//return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	switch (_uMsg) {
	/*
	case WM_CHAR:
	// useful for typing words in a chat message
	// knows whether it is capital or not
	{
		unsigned char letter = static_cast<unsigned char>(_wParam);
		return 0;
	}
	case WM_KEYDOWN:
	// usefule for controls where we want to hold down a key
	// always the capitalized version of the key
	{
		unsigned char keycode = static_cast<unsigned char>(_wParam);
		return 0;
	}
	*/
	case WM_NCCREATE:
	{
		//OutputDebugStringA("The window was created.\n");
		const CREATESTRUCTW* const ptrCreate = reinterpret_cast<CREATESTRUCTW*>(_lParam);
		WindowContainer* ptrWindow = reinterpret_cast<WindowContainer*>(ptrCreate->lpCreateParams);
		if (ptrWindow == nullptr)
		{
			ErrorLogger::Log("Critical Error: Pointer to window container is nullptr during WM_CREATE.");
			exit(-1);
		}
		SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptrWindow));
		SetWindowLongPtr(_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return ptrWindow->HandleMessageSetup(_hwnd, _uMsg, _wParam, _lParam);
	}
	default:
		return DefWindowProc(_hwnd, _uMsg, _wParam, _lParam);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc; // Our Window Class (this has to be filled before our window cann be created)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Flags (redraw on width/height change from resize/movement)
	wc.lpfnWndProc = HandleMessageSetup;	// Pointer to Window Proc Function for handling messages from this window
	wc.cbWndExtra = 0; // # of extra bytes to allocate following the window-class structure
	wc.cbClsExtra = 0; // # of extra bytes to allocate following the window instance.
	wc.hInstance = this->m_hInstance;	
	wc.hIcon = nullptr; // Icon handler
	wc.hIconSm = nullptr; // Icon handler small
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // Default cursor
	wc.hbrBackground = nullptr; // Handle to the class background brush for the window's background color
	wc.lpszMenuName = nullptr; // Pointer a null terminated character string for the menu
	wc.lpszClassName = this->m_window_class_wide.c_str(); // Pointer to null terminated string of our class name for the window
	wc.cbSize = sizeof(WNDCLASSEX); // Need to fill in the size of our struct for sbSize
	RegisterClassEx(&wc); // Register the clas so that it is usable
}

bool RenderWindow::ProcessMessages()
// Handles our windows messages
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure

	// Using Peek to avoid blocking with GetMessage()
	// We may have multiple messages in queue, if restricts to one message processed per frame
	while (PeekMessage(&msg,
		this->m_handle, // Handle to window for peeking messages, 
						// If you want all messages use null
		0, // Max filter msg value - we are not filtering for a specific message
		0, // Max filter msg value
		PM_REMOVE)) // Remove message after capturing it via PeekMessage
	{
		TranslateMessage(&msg); // Translate msg from virtual key messages into char messages so can
		DispatchMessage(&msg); // Dispatch message to our Window Proc for this window
	}

	// Check if window was closed
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->m_handle)) {
			this->m_handle = nullptr; // Message processing loop takes care of destroying this window
			UnregisterClass(this->m_window_class_wide.c_str(), this->m_hInstance);
			return false;
		}
	}

	return true;
}

HWND RenderWindow::GetHWND() const { return this->m_handle; }

RenderWindow::~RenderWindow()
{
	if (this->m_handle != nullptr) {
		UnregisterClass(this->m_window_class_wide.c_str(), this->m_hInstance);
		DestroyWindow(this->m_handle);
	}
}

