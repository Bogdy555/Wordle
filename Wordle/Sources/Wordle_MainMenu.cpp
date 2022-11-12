#include "..\Headers\Wordle.hpp"



Wordle::MainMenu::MainMenu() : WordleAPI::Menu(), ConsoleInput()
{

}

Wordle::MainMenu::~MainMenu()
{

}

void Wordle::MainMenu::Setup()
{
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
		GetKeysPressed(_Index, WordleAPI::_Previous) = GetKeysPressed(_Index, WordleAPI::_Current);
		GetKeysPressed(_Index, WordleAPI::_Current) = _WndUserData->KeysPressed[_Index];
	}

	_WndUserData->MutexKeysPressed.unlock();
}

void Wordle::MainMenu::DeleteInputs()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		GetKeysPressed(_Index, WordleAPI::_Previous) = false;
		GetKeysPressed(_Index, WordleAPI::_Current) = false;
	}

	Application* _Application = (Application*)(GetApplicationObj());

	Window::UserData* _WndUserData = &_Application->GetWndUserData();

	_WndUserData->MutexChar.lock();

	_WndUserData->Char.clear();

	_WndUserData->MutexChar.unlock();
}

void Wordle::MainMenu::Keys()
{
	if (!GetKeysPressed(VK_ESCAPE, WordleAPI::_Previous) && GetKeysPressed(VK_ESCAPE, WordleAPI::_Current))
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnNoError);
	}

	if (!GetKeysPressed(VK_F11, WordleAPI::_Previous) && GetKeysPressed(VK_F11, WordleAPI::_Current))
	{
		Application* _Application = (Application*)(GetApplicationObj());

		if (!_Application->UpdateFullScreen())
		{
			_Application->Close(WordleAPI::_ReturnError);
		}
	}

	Application* _Application = (Application*)(GetApplicationObj());

	Window::UserData* _WndUserData = &_Application->GetWndUserData();

	_WndUserData->MutexChar.lock();

	while (ConsoleInput.size() < 8)
	{
		if (!_WndUserData->Char.size())
		{
			break;
		}

		char _CurrentChar = _WndUserData->Char[0];

		if ((_CurrentChar >= 'A' && _CurrentChar <= 'Z') || _CurrentChar == ' ')
		{
			ConsoleInput.push_back(_CurrentChar);
		}
		else if (_CurrentChar >= 'a' && _CurrentChar <= 'z')
		{
			ConsoleInput.push_back(_CurrentChar - 'a' + 'A');
		}
		else if (_CurrentChar == '\b')
		{
			if (ConsoleInput.size())
			{
				ConsoleInput.erase(ConsoleInput.begin() + ConsoleInput.size() - 1);
			}
		}

		_WndUserData->Char.erase(_WndUserData->Char.begin());
	}

	for (size_t _Index = 0; _Index < _WndUserData->Char.size(); _Index++)
	{
		if (_WndUserData->Char[_Index] == '\b')
		{
			if (ConsoleInput.size())
			{
				ConsoleInput.erase(ConsoleInput.begin() + ConsoleInput.size() - 1);
			}
		}
	}

	_WndUserData->Char.clear();

	_WndUserData->MutexChar.unlock();

	if (!GetKeysPressed(VK_RETURN, WordleAPI::_Previous) && GetKeysPressed(VK_RETURN, WordleAPI::_Current))
	{
		ConsoleInput.push_back('\0');

		if (strcmp(ConsoleInput.data(), "RUN GAME") == 0)
		{
			ConsoleInput.erase(ConsoleInput.begin() + ConsoleInput.size() - 1);

			Close(_PlayMenu);
		}
		else if (strcmp(ConsoleInput.data(), "RUN BOT") == 0)
		{
			ConsoleInput.erase(ConsoleInput.begin() + ConsoleInput.size() - 1);

			Close(_BotMenu);
		}
		else if (strcmp(ConsoleInput.data(), "EXIT") == 0)
		{
			ConsoleInput.erase(ConsoleInput.begin() + ConsoleInput.size() - 1);

			GetApplicationObj()->Close(WordleAPI::_ReturnNoError);
		}
		else
		{
			ConsoleInput.clear();

			ConsoleInput.push_back('E');
			ConsoleInput.push_back('R');
			ConsoleInput.push_back('R');
			ConsoleInput.push_back('O');
			ConsoleInput.push_back('R');
		}
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

	_WndUserData->MutexError.lock();

	if (_WndUserData->Error)
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
	}

	_WndUserData->MutexError.unlock();
}

void Wordle::MainMenu::Animations()
{

}

void Wordle::MainMenu::FrameBuild()
{
	Application* _Application = (Application*)(GetApplicationObj());

	WordleAPI::Window* _Wnd = &_Application->GetWnd();

	Window::UserData* _WndUserData = &_Application->GetWndUserData();



	int32_t _Width = 0;
	int32_t _Height = 0;

	_Wnd->GetClientSize(_Width, _Height);



	size_t _RefreshRate = _Wnd->GetRefreshRate();

	SetSync(_RefreshRate);
	SetTimeStep(1.0f / (float)(_RefreshRate));



	PAINTSTRUCT _PaintStr = { 0 };

	_WndUserData->MutexContext.lock();

	_WndUserData->Context.Bind();

	_WndUserData->MutexContext.unlock();

	HDC _hWndDC = BeginPaint(*_Wnd, &_PaintStr);



	WordleAPI::GL::glEnable(GL_BLEND);
	WordleAPI::GL::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	WordleAPI::GL::glViewport(0, 0, _Width, _Height);
	WordleAPI::GL::glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	WordleAPI::GL::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	std::vector<char> _PromptStr;
	_PromptStr.push_back('>');

	_Application->RenderText(_Width, _Height, glm::vec2(40.0f * _PromptStr.size(), 40.0f), glm::vec2(10.0f, 10.0f), _PromptStr);
	_Application->RenderText(_Width, _Height, glm::vec2(40.0f * ConsoleInput.size(), 40.0f), glm::vec2(10.0f + 40.0f * _PromptStr.size(), 10.0f), ConsoleInput);



	WordleAPI::GL::wglSwapIntervalEXT(1);

	SwapBuffers(_hWndDC);

	EndPaint(*_Wnd, &_PaintStr);

	WordleAPI::GL::VertexBuffer::Unbind();
	WordleAPI::GL::IndexBuffer::Unbind();
	WordleAPI::GL::VertexAttribArray::Unbind();
	WordleAPI::GL::Shader::Unbind();
	WordleAPI::GL::Texture2D::Unbind();
	WordleAPI::GL::Context::Unbind();
}

bool& Wordle::MainMenu::GetKeysPressed(const size_t _Key, const size_t _Frame)
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}

const bool& Wordle::MainMenu::GetKeysPressed(const size_t _Key, const size_t _Frame) const
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}
