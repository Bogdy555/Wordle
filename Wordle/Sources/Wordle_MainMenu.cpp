#include "..\Headers\Wordle.hpp"



Wordle::MainMenu::MainMenu() : WordleAPI::Menu(), KeysPressed()
{

}

Wordle::MainMenu::~MainMenu()
{

}

void Wordle::MainMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void Wordle::MainMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::MainMenu::Stop()
{

}

void Wordle::MainMenu::Input()
{
	Application* _Application = (Application*)(GetApplicationObj());

	Window::UserData* _WndUserData = &_Application->GetWndUserData();

	_WndUserData->MutexFocus.lock();

	if (!_WndUserData->Focus)
	{
		_WndUserData->MutexFocus.unlock();

		DeleteInputs();

		return;
	}

	_WndUserData->MutexFocus.unlock();

	_WndUserData->MutexKeysPressed.lock();

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		KeysPressed[_Index][WordleAPI::_Previous] = KeysPressed[_Index][WordleAPI::_Current];
		KeysPressed[_Index][WordleAPI::_Current] = _WndUserData->KeysPressed[_Index];
	}

	_WndUserData->MutexKeysPressed.unlock();
}

void Wordle::MainMenu::DeleteInputs()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		KeysPressed[_Index][WordleAPI::_Previous] = false;
		KeysPressed[_Index][WordleAPI::_Current] = false;
	}
}

void Wordle::MainMenu::Keys()
{
	if (KeysPressed[VK_ESCAPE][WordleAPI::_Current])
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnNoError);
	}
}

void Wordle::MainMenu::Mouse()
{

}

void Wordle::MainMenu::Engine()
{
	Application* _Application = (Application*)(GetApplicationObj());

	Window::UserData* _WndUserData = &_Application->GetWndUserData();

	_WndUserData->MutexClose.lock();

	if (_WndUserData->Close)
	{
		_Application->Close(WordleAPI::_ReturnNoError);
	}

	_WndUserData->MutexClose.unlock();
}

void Wordle::MainMenu::Animations()
{

}

void Wordle::MainMenu::FrameBuild()
{
	Application* _Application = (Application*)(GetApplicationObj());

	WordleAPI::Window* _Wnd = &_Application->GetWnd();

	size_t _RefreshRate = _Wnd->GetRefreshRate();

	SetSync(_RefreshRate);
	SetTimeStep(1.0f / (float)(_RefreshRate));

	_Wnd->UpdateContent();
}
