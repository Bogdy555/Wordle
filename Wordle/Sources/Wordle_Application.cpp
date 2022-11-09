#include "..\Headers\Wordle.hpp"



Wordle::Application::Application() : WordleAPI::Application()
{

}

Wordle::Application::~Application()
{

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

}
