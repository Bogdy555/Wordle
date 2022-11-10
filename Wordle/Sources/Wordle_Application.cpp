#include "..\Headers\Wordle.hpp"



Wordle::Application::Application() : WordleAPI::Application(), Wnd(), WndUserData()
{

}

Wordle::Application::~Application()
{

}

WordleAPI::Window& Wordle::Application::GetWnd()
{
	return Wnd;
}

const WordleAPI::Window& Wordle::Application::GetWnd() const
{
	return Wnd;
}

Wordle::Window::UserData& Wordle::Application::GetWndUserData()
{
	return WndUserData;
}

const Wordle::Window::UserData& Wordle::Application::GetWndUserData() const
{
	return WndUserData;
}

void Wordle::Application::Setup()
{
	GetSharedInstanceMutex().Lock();

	if (*GetSharedInstanceMemory() > 1)
	{
		HWND _hWndFind = FindWindow(L"WndClassWordle", L"Wordle");

		if (_hWndFind)
		{
			SetForegroundWindow(_hWndFind);
		}

		GetSharedInstanceMutex().Unlock();

		return;
	}

	GetSharedInstanceMutex().Unlock();

	if (!InitWindow())
	{
		return;
	}

	if (!Wnd.Show(GetShowCmd()))
	{
		return;
	}

	TurnOn();
	SetCurrentMenu(_MainMenu);
}

void Wordle::Application::Update()
{
	switch (GetCurrentMenu())
	{
	case _MainMenu:
	{
		MainMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case _PlayMenu:
	{
		PlayMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case _BotMenu:
	{
		BotMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case WordleAPI::_NullMenu:
	{
		Close(WordleAPI::_ReturnError);
		break;
	}
	default:
	{
		Close(WordleAPI::_ReturnError);
		break;
	}
	}
}

void Wordle::Application::Stop()
{
	Wnd.Show(SW_HIDE);

	DestroyWindow();
}

bool Wordle::Application::InitWindow()
{
	WndUserData.hIcon = LoadIcon(GetHInstance(), MAKEINTRESOURCE(WORDLE_IDI_MAIN_ICON));

	if (!WndUserData.hIcon)
	{
		return false;
	}

	WndUserData.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!WndUserData.hCursor)
	{
		return false;
	}

	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	_WndClass.lpfnWndProc = Window::WndProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetHInstance();
	_WndClass.hIcon = WndUserData.hIcon;
	_WndClass.hCursor = WndUserData.hCursor;
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = L"WndClassWordle";
	_WndClass.hIconSm = WndUserData.hIcon;

	if (!RegisterClassEx(&_WndClass))
	{
		return false;
	}

	WndUserData.Close = false;
	WndUserData.Error = false;
	WndUserData.Focus = false;
	WndUserData.WndPlacement = { 0 };
	WndUserData.FullScreen = false;
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		WndUserData.KeysPressed[_Index] = false;
	}

	WordleAPI::WindowCreationDescriptor _Descriptor;

	_Descriptor.dwExStyle = NULL;
	_Descriptor.lpClassName = L"WndClassWordle";
	_Descriptor.lpWindowName = L"Wordle";
	_Descriptor.dwStyle = WS_OVERLAPPEDWINDOW;
	_Descriptor.X = CW_USEDEFAULT;
	_Descriptor.Y = CW_USEDEFAULT;
	_Descriptor.nWidth = CW_USEDEFAULT;
	_Descriptor.nHeight = CW_USEDEFAULT;
	_Descriptor.hWndParent = HWND_DESKTOP;
	_Descriptor.hMenu = NULL;
	_Descriptor.hInstance = GetHInstance();
	_Descriptor.lpParam = nullptr;
	_Descriptor.hAccel = NULL;
	_Descriptor.ShowCmd = SW_HIDE;
	_Descriptor.WndInitFunc = Window::Init;
	_Descriptor.UserData = &WndUserData;

	if (!Wnd.Create(&_Descriptor))
	{
		UnregisterClass(L"WndClassWordle", GetHInstance());
		return false;
	}

	return true;
}

void Wordle::Application::DestroyWindow()
{
	WndUserData.MutexContext.lock();

	WndUserData.Context.Destroy();

	WndUserData.MutexContext.unlock();

	if (Wnd.CheckOn())
	{
		Wnd.Destroy();
		UnregisterClass(L"WndClassWordle", GetHInstance());
	}
}
