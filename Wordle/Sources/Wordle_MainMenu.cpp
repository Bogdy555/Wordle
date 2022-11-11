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

	if (!KeysPressed[VK_F11][WordleAPI::_Previous] && KeysPressed[VK_F11][WordleAPI::_Current])
	{
		Application* _Application = (Application*)(GetApplicationObj());

		if (!_Application->UpdateFullScreen())
		{
			_Application->Close(WordleAPI::_ReturnError);
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

	Wordle::Window::UserData* _WndUserData = &_Application->GetWndUserData();



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



	float _Size = 300.0f;
	float _Ratio = 0.1f;
	float _Delta = 15.0f;

	_Application->RenderFancySquare(_Width, _Height, glm::vec2(_Size, _Size), glm::vec2(0.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), _Size * _Ratio);
	_Application->RenderFancySquare(_Width, _Height, glm::vec2(_Size - _Delta, _Size - _Delta), glm::vec2(_Delta / 2.0f, _Delta / 2.0f), glm::vec4(0.05f, 0.05f, 0.05f, 1.0f), (_Size - _Delta) * _Ratio);

	_Application->RenderTexture(_Width, _Height, glm::vec2(_Size, _Size), glm::vec2(0.0f, 0.0f), _Application->GetAlphabetTexture(), glm::vec2(1.0f / 6.0f, 1.0f / 6.0f), glm::vec2(1.0f / 6.0f, 1.0f / 6.0f));



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
