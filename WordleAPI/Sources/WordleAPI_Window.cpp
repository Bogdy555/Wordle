#include "..\Headers\WordleAPI.hpp"



WordleAPI::Window* WordleAPI::Window::LastWnd = nullptr;
std::mutex WordleAPI::Window::LastWndPtrMutex;



WordleAPI::Window::Window() : On(false), hWnd(NULL), WndThread(), UserData(nullptr)
{

}

WordleAPI::Window::Window(Window&& _Other) noexcept : On(_Other.On), hWnd(_Other.hWnd), WndThread(std::move(_Other.WndThread)), UserData(_Other.UserData)
{
	_Other.On = false;
	_Other.hWnd = NULL;
	_Other.UserData = nullptr;
}

WordleAPI::Window::~Window()
{

}

const bool WordleAPI::Window::CheckOn() const
{
	return On;
}

const HWND WordleAPI::Window::GetHandle() const
{
	return hWnd;
}

void* WordleAPI::Window::GetUserData()
{
	return UserData;
}

const void* WordleAPI::Window::GetUserData() const
{
	return UserData;
}

bool WordleAPI::Window::Create(const WindowCreationDescriptor* _Descriptor)
{
	if (On)
	{
		return false;
	}

	bool _Done = false;
	bool _Fail = false;

	LastWndPtrMutex.lock();

	WndThread = std::move(std::thread(WndThreadFunc, &_Done, &_Fail, this, _Descriptor));

	while (!_Done)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	LastWndPtrMutex.unlock();

	if (_Fail)
	{
		WndThread.join();
	}

	return 1 - _Fail;
}

void WordleAPI::Window::Destroy()
{
	if (!On)
	{
		return;
	}

	On = false;
	DestroyWindow(hWnd);
	WndThread.join();
	UserData = nullptr;
	hWnd = NULL;
}

bool WordleAPI::Window::Show(const int _ShowCmd)
{
	if (!hWnd)
	{
		return false;
	}

	return ShowWindowAsync(hWnd, _ShowCmd);
}

bool WordleAPI::Window::UpdateContent()
{
	if (!hWnd)
	{
		return false;
	}

	if (!InvalidateRect(hWnd, nullptr, false))
	{
		return false;
	}

	return UpdateWindow(hWnd);
}

const bool WordleAPI::Window::GetClientSize(int32_t& _Width, int32_t& _Height) const
{
	if (!hWnd)
	{
		return false;
	}

	RECT _ClientRect = { 0 };

	if (!GetClientRect(hWnd, &_ClientRect))
	{
		return false;
	}

	_Width = _ClientRect.right - _ClientRect.left;
	_Height = _ClientRect.bottom - _ClientRect.top;

	return true;
}

const bool WordleAPI::Window::GetWindowSize(int32_t& _Width, int32_t& _Height) const
{
	if (!hWnd)
	{
		return false;
	}

	RECT _WindowRect = { 0 };

	if (!GetWindowRect(hWnd, &_WindowRect))
	{
		return false;
	}

	_Width = _WindowRect.right - _WindowRect.left;
	_Height = _WindowRect.bottom - _WindowRect.top;

	return true;
}

WordleAPI::Window::operator const HWND() const
{
	return hWnd;
}

void WordleAPI::Window::operator= (Window&& _Other) noexcept
{
	On = _Other.On;
	hWnd = _Other.hWnd;
	WndThread = std::move(_Other.WndThread);
	UserData = _Other.UserData;

	_Other.On = false;
	_Other.hWnd = NULL;
	_Other.UserData = nullptr;
}

WordleAPI::Window* WordleAPI::Window::GetWindowPtr(const HWND _hWnd)
{
	if (!_hWnd)
	{
		return LastWnd;
	}

	Window* _WndPtr = (Window*)(GetWindowLongPtr(_hWnd, GWLP_USERDATA));

	if (!_WndPtr)
	{
		return LastWnd;
	}

	return _WndPtr;
}

void WordleAPI::Window::WndThreadFunc(bool* _Done, bool* _Fail, Window* _Wnd, const WindowCreationDescriptor* _Descriptor)
{
	_Wnd->UserData = _Descriptor->UserData;

	LastWnd = _Wnd;

	_Wnd->hWnd = CreateWindowEx(_Descriptor->dwExStyle, _Descriptor->lpClassName, _Descriptor->lpWindowName, _Descriptor->dwStyle, _Descriptor->X, _Descriptor->Y, _Descriptor->nWidth, _Descriptor->nHeight, _Descriptor->hWndParent, _Descriptor->hMenu, _Descriptor->hInstance, _Descriptor->lpParam);

	LastWnd = nullptr;

	if (!_Wnd->hWnd)
	{
		_Wnd->UserData = nullptr;

		*_Fail = true;
		*_Done = true;

		return;
	}

	SetLastError(0);

	if (!SetWindowLongPtr(_Wnd->hWnd, GWLP_USERDATA, (LONG_PTR)(_Wnd)))
	{
		if (GetLastError())
		{
			DestroyWindow(_Wnd->hWnd);
			_Wnd->hWnd = NULL;

			_Wnd->UserData = nullptr;

			*_Fail = true;
			*_Done = true;

			return;
		}
	}

	if (_Descriptor->WndInitFunc)
	{
		if (!_Descriptor->WndInitFunc(_Wnd))
		{
			DestroyWindow(_Wnd->hWnd);
			_Wnd->hWnd = NULL;

			_Wnd->UserData = nullptr;

			*_Fail = true;
			*_Done = true;

			return;
		}
	}

	MSG _Msg = { 0 };

	_Wnd->On = true;

	if (_Descriptor->ShowCmd != SW_HIDE)
	{
		_Wnd->Show(_Descriptor->ShowCmd);
	}

	HACCEL _hAccel = _Descriptor->hAccel;

	*_Fail = false;
	*_Done = true;

	while (_Wnd->On)
	{
		if (GetMessage(&_Msg, NULL, 0, 0))
		{
			if (_Msg.hwnd == _Wnd->hWnd)
			{
				if (_hAccel)
				{
					if (!TranslateAccelerator(_Msg.hwnd, _hAccel, &_Msg))
					{
						TranslateMessage(&_Msg);
						DispatchMessage(&_Msg);
					}
				}
				else
				{
					TranslateMessage(&_Msg);
					DispatchMessage(&_Msg);
				}
			}
			else
			{
				TranslateMessage(&_Msg);
				DispatchMessage(&_Msg);
			}
		}
	}
}
