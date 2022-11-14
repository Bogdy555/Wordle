#include "..\Headers\Wordle.hpp"



Wordle::PlayMenu::PlayMenu() :
	WordleAPI::Menu(),
	IndexPreviousPreviousGuess(0), IndexPreviousGuess(0), IndexCurrentGuess(0),
	PreviousPreviousGuess(), PreviousGuess(), CurrentGuess(),
	AnimationTrigger(false), AnimationIsActive(false), AnimationTimeActive(0.0f), Animation()
{

}

Wordle::PlayMenu::~PlayMenu()
{

}

const uint64_t Wordle::PlayMenu::GetMenuType() const
{
	return _PlayMenu;
}

void Wordle::PlayMenu::Setup()
{
	IndexCurrentGuess = rand() % ((Application*)(GetApplicationObj()))->GetDatabaseCuvinte().size();

	WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtLightGreen));
	WORDLEAPI_LOG(WORDLEAPI_STRING("[LOG_TRACE] Current word is: "));
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);
	WORDLEAPI_LOG(WORDLEAPI_STRING('\n'));

	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(  0.0f, 0.0f * 0.5f, 0.1f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(-50.0f, 0.1f * 0.5f, 0.2f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(  0.0f, 0.2f * 0.5f, 0.3f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>( 50.0f, 0.3f * 0.5f, 0.4f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(  0.0f, 0.4f * 0.5f, 0.5f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(-50.0f, 0.5f * 0.5f, 0.6f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(  0.0f, 0.6f * 0.5f, 0.7f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>( 50.0f, 0.7f * 0.5f, 0.8f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(  0.0f, 0.8f * 0.5f, 0.9f * 0.5f));

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

	while (CurrentGuess.size() < 5)
	{
		if (!_WndUserData->Char.size())
		{
			break;
		}

		char _CurrentChar = _WndUserData->Char[0];

		if (_CurrentChar >= 'A' && _CurrentChar <= 'Z')
		{
			CurrentGuess.push_back(_CurrentChar);
		}
		else if (_CurrentChar >= 'a' && _CurrentChar <= 'z')
		{
			CurrentGuess.push_back(_CurrentChar - 'a' + 'A');
		}
		else if (_CurrentChar == '\b')
		{
			if (CurrentGuess.size())
			{
				CurrentGuess.erase(CurrentGuess.begin() + CurrentGuess.size() - 1);
			}
		}

		_WndUserData->Char.erase(_WndUserData->Char.begin());
	}

	for (size_t _Index = 0; _Index < _WndUserData->Char.size(); _Index++)
	{
		if (_WndUserData->Char[_Index] == '\b')
		{
			if (CurrentGuess.size())
			{
				CurrentGuess.erase(CurrentGuess.begin() + CurrentGuess.size() - 1);
			}
		}
	}

	_WndUserData->Char.clear();

	_WndUserData->MutexChar.unlock();

	if (!GetKeysPressed(VK_RETURN, WordleAPI::_Previous) && GetKeysPressed(VK_RETURN, WordleAPI::_Current))
	{
		if (CurrentGuess.size() == 5)
		{
			bool _Found = false;

			for (size_t _Index = 0; _Index < _Application->GetDatabaseCuvinte().size(); _Index++)
			{
				if (_Application->GetDatabaseCuvinte()[_Index] == CurrentGuess)
				{
					_Found = true;
					break;
				}
			}

			if (_Found)
			{
				IndexPreviousPreviousGuess = IndexPreviousGuess;
				PreviousPreviousGuess = PreviousGuess;

				IndexPreviousGuess = IndexCurrentGuess;
				PreviousGuess = CurrentGuess;

				CurrentGuess.clear();

				if (_Application->GetDatabaseCuvinte()[IndexPreviousGuess] == PreviousGuess)
				{
					IndexCurrentGuess = rand() % _Application->GetDatabaseCuvinte().size();

					WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtLightGreen));
					WORDLEAPI_LOG(WORDLEAPI_STRING("[LOG_TRACE] Current word is: "));
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);
					WORDLEAPI_LOG(WORDLEAPI_STRING('\n'));
				}
			}
			else
			{
				AnimationTrigger = true;
			}
		}
		else
		{
			AnimationTrigger = true;
		}
	}
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
	if (AnimationIsActive)
	{
		AnimationTimeActive += GetTimeStepRatio() * GetTimeStep();

		if (AnimationTimeActive < Animation.GetStates()[Animation.GetStates().size() - 1].End)
		{
			Animation.Update(GetTimeStepRatio() * GetTimeStep());
		}
		else
		{
			AnimationIsActive = false;
			AnimationTimeActive = 0.0f;
			Animation.Reset();
		}
	}

	if (AnimationTrigger)
	{
		AnimationTrigger = false;
		AnimationIsActive = true;
		AnimationTimeActive = 0.0f;
		Animation.Reset();
	}
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



	RenderBackground(_Width, _Height);
	RenderPreviousPreviousGuess(_Width, _Height);
	RenderPreviousGuess(_Width, _Height);
	RenderCurrentGuess(_Width, _Height);



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

void Wordle::PlayMenu::RenderBackground(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	_Application->RenderSquare(1, 1, WordleAPI::Vec2(1.0f, 1.0f), WordleAPI::Vec2(0.0f, 0.0f), WordleAPI::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
}

void Wordle::PlayMenu::RenderPreviousPreviousGuess(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	float _CharSize = 50.0f;

	WordleAPI::Vec2 _Size = WordleAPI::Vec2(_CharSize * 5.0f, _CharSize);
	WordleAPI::Vec2 _Position = WordleAPI::Vec2((float)(_Width) / 2.0f - _CharSize * 2.5f, 3.0f * (float)(_Height) / 4.0f - _CharSize / 2.0f);

	float _Radius = 0.2f;
	float _BackPanelBorderSize = _CharSize / 2.0f;
	float _FrontBackRatio = 0.8f;

	WordleAPI::Vec4 _ColorSquareBack = WordleAPI::Vec4(0.05f, 0.05f, 0.05f, 1.0f);
	WordleAPI::Vec4 _ColorSquareFront = WordleAPI::Vec4(0.1f, 0.1f, 0.1f, 1.0f);
	WordleAPI::Vec4 _ColorTextRight = WordleAPI::Vec4(0.2f, 0.7f, 0.2f, 1.0f);
	WordleAPI::Vec4 _ColorTextExist = WordleAPI::Vec4(0.8f, 0.6f, 0.2f, 1.0f);
	WordleAPI::Vec4 _ColorTextNone = WordleAPI::Vec4(0.15f, 0.15f, 0.15f, 1.0f);

	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize, _Position - _BackPanelBorderSize, _ColorSquareBack, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize));
	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize * _FrontBackRatio, _Position - _BackPanelBorderSize * _FrontBackRatio, _ColorSquareFront, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize * _FrontBackRatio));

	if (PreviousPreviousGuess.size() == 5)
	{
		for (size_t _Index = 0; _Index < 5; _Index++)
		{
			if (_Application->GetDatabaseCuvinte()[IndexPreviousPreviousGuess][_Index] == PreviousPreviousGuess[_Index])
			{
				_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousPreviousGuess[_Index], 1, _ColorTextRight);
			}
			else
			{
				bool _Exist = false;

				for (size_t _DataIndex = 0; _DataIndex < 5; _DataIndex++)
				{
					if (_Application->GetDatabaseCuvinte()[IndexPreviousPreviousGuess][_DataIndex] == PreviousPreviousGuess[_Index])
					{
						_Exist = true;
						break;
					}
				}

				if (_Exist)
				{
					_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousPreviousGuess[_Index], 1, _ColorTextExist);
				}
				else
				{
					_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousPreviousGuess[_Index], 1, _ColorTextNone);
				}
			}
		}
	}
}

void Wordle::PlayMenu::RenderPreviousGuess(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	float _CharSize = 50.0f;

	WordleAPI::Vec2 _Size = WordleAPI::Vec2(_CharSize * 5.0f, _CharSize);
	WordleAPI::Vec2 _Position = WordleAPI::Vec2((float)(_Width) / 2.0f - _CharSize * 2.5f, (float)(_Height) / 2.0f - _CharSize / 2.0f);

	float _Radius = 0.2f;
	float _BackPanelBorderSize = _CharSize / 2.0f;
	float _FrontBackRatio = 0.8f;

	WordleAPI::Vec4 _ColorSquareBack = WordleAPI::Vec4(0.05f, 0.05f, 0.05f, 1.0f);
	WordleAPI::Vec4 _ColorSquareFront = WordleAPI::Vec4(0.1f, 0.1f, 0.1f, 1.0f);
	WordleAPI::Vec4 _ColorTextRight = WordleAPI::Vec4(0.2f, 0.7f, 0.2f, 1.0f);
	WordleAPI::Vec4 _ColorTextExist = WordleAPI::Vec4(0.8f, 0.6f, 0.2f, 1.0f);
	WordleAPI::Vec4 _ColorTextNone = WordleAPI::Vec4(0.15f, 0.15f, 0.15f, 1.0f);

	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize, _Position - _BackPanelBorderSize, _ColorSquareBack, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize));
	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize * _FrontBackRatio, _Position - _BackPanelBorderSize * _FrontBackRatio, _ColorSquareFront, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize * _FrontBackRatio));

	if (PreviousGuess.size() == 5)
	{
		for (size_t _Index = 0; _Index < 5; _Index++)
		{
			if (_Application->GetDatabaseCuvinte()[IndexPreviousGuess][_Index] == PreviousGuess[_Index])
			{
				_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousGuess[_Index], 1, _ColorTextRight);
			}
			else
			{
				bool _Exist = false;

				for (size_t _DataIndex = 0; _DataIndex < 5; _DataIndex++)
				{
					if (_Application->GetDatabaseCuvinte()[IndexPreviousGuess][_DataIndex] == PreviousGuess[_Index])
					{
						_Exist = true;
						break;
					}
				}

				if (_Exist)
				{
					_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousGuess[_Index], 1, _ColorTextExist);
				}
				else
				{
					_Application->RenderText(_Width, _Height, WordleAPI::Vec2(_CharSize, _CharSize), _Position + WordleAPI::Vec2((float)(_Index)*_CharSize, 0.0f), &PreviousGuess[_Index], 1, _ColorTextNone);
				}
			}
		}
	}
}

void Wordle::PlayMenu::RenderCurrentGuess(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	float _CharSize = 50.0f;

	WordleAPI::Vec2 _Size = WordleAPI::Vec2(_CharSize * 5.0f, _CharSize);
	WordleAPI::Vec2 _Position = WordleAPI::Vec2((float)(_Width) / 2.0f - _CharSize * 2.5f, (float)(_Height) / 4.0f - _CharSize / 2.0f);

	if (AnimationIsActive)
	{
		_Position.x += Animation.GetCurrentState();
	}

	float _Radius = 0.2f;
	float _BackPanelBorderSize = _CharSize / 2.0f;
	float _FrontBackRatio = 0.8f;

	WordleAPI::Vec4 _ColorSquareBack = WordleAPI::Vec4(0.05f, 0.05f, 0.05f, 1.0f);
	WordleAPI::Vec4 _ColorSquareFront = WordleAPI::Vec4(0.1f, 0.1f, 0.1f, 1.0f);
	WordleAPI::Vec4 _ColorText = WordleAPI::Vec4(1.0f, 1.0f, 1.0f, 1.0f);

	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize, _Position - _BackPanelBorderSize, _ColorSquareBack, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize));
	_Application->RenderFancySquare(_Width, _Height, _Size + 2.0f * _BackPanelBorderSize * _FrontBackRatio, _Position - _BackPanelBorderSize * _FrontBackRatio, _ColorSquareFront, _Radius * (_Size.y + 2.0f * _BackPanelBorderSize * _FrontBackRatio));

	_Application->RenderText(_Width, _Height, _Size * WordleAPI::Vec2((float)(CurrentGuess.size()) / 5.0f, 1.0f), _Position, CurrentGuess, _ColorText);
}

bool& Wordle::PlayMenu::GetKeysPressed(const size_t _Key, const size_t _Frame)
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}

const bool& Wordle::PlayMenu::GetKeysPressed(const size_t _Key, const size_t _Frame) const
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}
