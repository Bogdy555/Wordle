#include "..\Headers\Wordle.hpp"



Wordle::BotMenu::BotMenu() : WordleAPI::Menu(), KeysPressed()
{

}

Wordle::BotMenu::~BotMenu()
{

}

void Wordle::BotMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void Wordle::BotMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::BotMenu::Stop()
{

}

void Wordle::BotMenu::Input()
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

void Wordle::BotMenu::DeleteInputs()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		KeysPressed[_Index][WordleAPI::_Previous] = false;
		KeysPressed[_Index][WordleAPI::_Current] = false;
	}
}

void Wordle::BotMenu::Keys()
{

}

void Wordle::BotMenu::Mouse()
{

}

void Wordle::BotMenu::Engine()
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

void Wordle::BotMenu::Animations()
{

}

void Wordle::BotMenu::FrameBuild()
{
	Application* _Application = (Application*)(GetApplicationObj());

	WordleAPI::Window* _Wnd = &_Application->GetWnd();

	_Wnd->UpdateContent();
}
