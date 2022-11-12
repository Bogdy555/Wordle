#include "..\Headers\Wordle.hpp"



Wordle::PlayMenu::PlayMenu() : WordleAPI::Menu()
{

}

Wordle::PlayMenu::~PlayMenu()
{

}

void Wordle::PlayMenu::Setup()
{
	TurnOn();
}

void Wordle::PlayMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::PlayMenu::Stop()
{

}

void Wordle::PlayMenu::Input()
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

void Wordle::PlayMenu::DeleteInputs()
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

void Wordle::PlayMenu::Keys()
{
	if (!GetKeysPressed(VK_ESCAPE, WordleAPI::_Previous) && GetKeysPressed(VK_ESCAPE, WordleAPI::_Current))
	{
		Close(_MainMenu);
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

	_WndUserData->Char.clear();

	_WndUserData->MutexChar.unlock();
}

void Wordle::PlayMenu::Mouse()
{

}

void Wordle::PlayMenu::Engine()
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

void Wordle::PlayMenu::Animations()
{

}

void Wordle::PlayMenu::FrameBuild()
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
	WordleAPI::GL::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	WordleAPI::GL::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// TODO



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

bool& Wordle::PlayMenu::GetKeysPressed(const size_t _Key, const size_t _Frame)
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}

const bool& Wordle::PlayMenu::GetKeysPressed(const size_t _Key, const size_t _Frame) const
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}
