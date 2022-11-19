#include "..\Headers\Wordle.hpp"



Wordle::BotMenu::BotMenu() :
	WordleAPI::Menu(),
	IndexPreviousPreviousGuess(0), IndexPreviousGuess(0), IndexCurrentGuess(0),
	PreviousPreviousGuess(), PreviousGuess(), CurrentGuess(),
	AnimationTrigger(false), AnimationIsActive(false), AnimationTimeActive(0.0f), Animation(),
	BotProc(), BotSharedMemory(), BotSharedMutex(),
	ExecutionState(NULL),
	ListOfGuesses()
{

}

Wordle::BotMenu::~BotMenu()
{

}

const uint64_t Wordle::BotMenu::GetMenuType() const
{
	return _BotMenu;
}

void Wordle::BotMenu::Setup()
{
	IndexCurrentGuess = 0;

	WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtLightGreen));
	WORDLEAPI_LOG(WORDLEAPI_STRING("[LOG_TRACE] Current word is: "));
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
	WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);
	WORDLEAPI_LOG(WORDLEAPI_STRING('\n'));

	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(0.0f, 0.0f * 0.5f, 0.1f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(-50.0f, 0.1f * 0.5f, 0.2f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(0.0f, 0.2f * 0.5f, 0.3f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(50.0f, 0.3f * 0.5f, 0.4f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(0.0f, 0.4f * 0.5f, 0.5f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(-50.0f, 0.5f * 0.5f, 0.6f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(0.0f, 0.6f * 0.5f, 0.7f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(50.0f, 0.7f * 0.5f, 0.8f * 0.5f));
	Animation.GetStates().push_back(WordleAPI::AnimationState<float>(0.0f, 0.8f * 0.5f, 0.9f * 0.5f));

	{
		std::vector<std::vector<char>> _FirstList;

		std::vector<char> _Cuv;

		_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
		_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
		_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
		_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
		_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);

		_FirstList.push_back(_Cuv);

		ListOfGuesses.push_back(_FirstList);
	}

	if (!BotSharedMutex.Create(L"WordleBotComunicationMutex"))
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
		return;
	}

	if (!BotSharedMemory.Create(L"WordleBotComunicationMemory", 6))
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
		return;
	}

	BotSharedMutex.Lock();

	BotSharedMemory[0] = WordleAPI::_NullState;
	BotSharedMemory[1] = 0;
	BotSharedMemory[2] = 0;
	BotSharedMemory[3] = 0;
	BotSharedMemory[4] = 0;
	BotSharedMemory[5] = 0;

	BotSharedMutex.Unlock();

	if (!BotProc.Create(L".\\WordleBot.exe"))
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
		return;
	}

	ExecutionState = SetThreadExecutionState(ES_CONTINUOUS | ES_AWAYMODE_REQUIRED | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

	if (!ExecutionState)
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
		return;
	}

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
	if (ListOfGuesses.size() == ((Application*)(GetApplicationObj()))->GetDatabaseCuvinte().size())
	{
		SaveGuesses();
	}

	if (ExecutionState)
	{
		SetThreadExecutionState(ExecutionState);
		ExecutionState = NULL;
	}
	BotProc.Destroy(0);
	BotSharedMemory.Destroy();
	BotSharedMutex.Destroy();
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
		GetKeysPressed(_Index, WordleAPI::_Previous) = GetKeysPressed(_Index, WordleAPI::_Current);
		GetKeysPressed(_Index, WordleAPI::_Current) = _WndUserData->KeysPressed[_Index];
	}

	_WndUserData->MutexKeysPressed.unlock();
}

void Wordle::BotMenu::DeleteInputs()
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

void Wordle::BotMenu::Keys()
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

	_WndUserData->MutexError.lock();

	if (_WndUserData->Error)
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
	}

	_WndUserData->MutexError.unlock();

	if (!BotProc.UpdateStatus())
	{
		GetApplicationObj()->Close(WordleAPI::_ReturnError);
	}
	else
	{
		BotSharedMutex.Lock();

		if (BotSharedMemory[0] == WordleAPI::_WordState)
		{
			IndexPreviousPreviousGuess = IndexPreviousGuess;
			PreviousPreviousGuess = PreviousGuess;

			IndexPreviousGuess = IndexCurrentGuess;
			PreviousGuess = CurrentGuess;

			CurrentGuess.clear();

			if (PreviousGuess == _Application->GetDatabaseCuvinte()[IndexPreviousGuess])
			{
				IndexCurrentGuess++;

				if (IndexCurrentGuess == _Application->GetDatabaseCuvinte().size())
				{
					Close(_MainMenu);
				}
				else
				{
					CurrentGuess.push_back((char)(BotSharedMemory[1]));
					CurrentGuess.push_back((char)(BotSharedMemory[2]));
					CurrentGuess.push_back((char)(BotSharedMemory[3]));
					CurrentGuess.push_back((char)(BotSharedMemory[4]));
					CurrentGuess.push_back((char)(BotSharedMemory[5]));

					WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtLightGreen));
					WORDLEAPI_LOG(WORDLEAPI_STRING("[LOG_TRACE] Current word is: "));
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
					WORDLEAPI_LOG(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);
					WORDLEAPI_LOG(WORDLEAPI_STRING('\n'));

					{
						std::vector<std::vector<char>> _NextList;

						std::vector<char> _Cuv;

						_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][0]);
						_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][1]);
						_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][2]);
						_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][3]);
						_Cuv.push_back(((Application*)(GetApplicationObj()))->GetDatabaseCuvinte()[IndexCurrentGuess][4]);

						_NextList.push_back(_Cuv);

						ListOfGuesses.push_back(_NextList);
					}
				}
			}
			else
			{
				CurrentGuess.push_back((char)(BotSharedMemory[1]));
				CurrentGuess.push_back((char)(BotSharedMemory[2]));
				CurrentGuess.push_back((char)(BotSharedMemory[3]));
				CurrentGuess.push_back((char)(BotSharedMemory[4]));
				CurrentGuess.push_back((char)(BotSharedMemory[5]));
			}

			if (CurrentGuess.size())
			{
				WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtPurple));
				WORDLEAPI_LOG(WORDLEAPI_STRING("[LOG_TRACE] Current guess is: "));

				BotSharedMemory[0] = WordleAPI::_FeedbackState;

				for (size_t _Index = 0; _Index < 5; _Index++)
				{
					if (_Application->GetDatabaseCuvinte()[IndexCurrentGuess][_Index] == CurrentGuess[_Index])
					{
						WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtLightGreen));
						WORDLEAPI_LOG(CurrentGuess[_Index]);
						BotSharedMemory[_Index + 1] = WordleAPI::_Right;
					}
					else if (_Application->GetDatabaseCuvinte()[IndexCurrentGuess][0] == CurrentGuess[_Index] || _Application->GetDatabaseCuvinte()[IndexCurrentGuess][1] == CurrentGuess[_Index] || _Application->GetDatabaseCuvinte()[IndexCurrentGuess][2] == CurrentGuess[_Index] || _Application->GetDatabaseCuvinte()[IndexCurrentGuess][3] == CurrentGuess[_Index] || _Application->GetDatabaseCuvinte()[IndexCurrentGuess][4] == CurrentGuess[_Index])
					{
						WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtYellow));
						WORDLEAPI_LOG(CurrentGuess[_Index]);
						BotSharedMemory[_Index + 1] = WordleAPI::_Exists;
					}
					else
					{
						WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::SetTextAttribute(WordleAPI::_ConsoleTxtGrey));
						WORDLEAPI_LOG(CurrentGuess[_Index]);
						BotSharedMemory[_Index + 1] = WordleAPI::_Wrong;
					}
				}

				WORDLEAPI_LOG(WORDLEAPI_STRING('\n'));

				{
					std::vector<char> _Cuv;

					_Cuv.push_back(CurrentGuess[0]);
					_Cuv.push_back(CurrentGuess[1]);
					_Cuv.push_back(CurrentGuess[2]);
					_Cuv.push_back(CurrentGuess[3]);
					_Cuv.push_back(CurrentGuess[4]);

					ListOfGuesses[ListOfGuesses.size() - 1].push_back(_Cuv);
				}
			}
			else
			{
				BotSharedMemory[0] = WordleAPI::_NullState;
			}
		}

		BotSharedMutex.Unlock();
	}
}

void Wordle::BotMenu::Animations()
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

void Wordle::BotMenu::FrameBuild()
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
	RenderProgressBar(_Width, _Height);



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

void Wordle::BotMenu::RenderBackground(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	_Application->RenderSquare(1, 1, WordleAPI::Vec2(1.0f, 1.0f), WordleAPI::Vec2(0.0f, 0.0f), WordleAPI::Vec4(0.1f, 0.1f, 0.1f, 1.0f));
}

void Wordle::BotMenu::RenderPreviousPreviousGuess(const int32_t _Width, const int32_t _Height)
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

void Wordle::BotMenu::RenderPreviousGuess(const int32_t _Width, const int32_t _Height)
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

void Wordle::BotMenu::RenderCurrentGuess(const int32_t _Width, const int32_t _Height)
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

void Wordle::BotMenu::RenderProgressBar(const int32_t _Width, const int32_t _Height)
{
	Application* _Application = (Application*)(GetApplicationObj());

	WordleAPI::Vec2 _Size = WordleAPI::Vec2(30.0f, (float)((size_t)(LerpFloat(0.0f, (float)(_Height), (float)(IndexCurrentGuess) / (float)(_Application->GetDatabaseCuvinte().size())))));
	WordleAPI::Vec2 _Position = WordleAPI::Vec2(0.0f, 0.0f);
	WordleAPI::Vec4 _Color = WordleAPI::Vec4(0.2f, 0.7f, 0.2f, 1.0f);

	if (_Size.y)
	{
		_Application->RenderSquare(_Width, _Height, _Size, _Position, _Color);
	}
}

void Wordle::BotMenu::SaveGuesses()
{
	Application* _Application = (Application*)(GetApplicationObj());

	wchar_t _Path[MAX_PATH + 1];
	ZeroMemory(_Path, (MAX_PATH + 1) * sizeof(wchar_t));

	OPENFILENAME _OpenFileName = { 0 };

	_OpenFileName.lStructSize = sizeof(OPENFILENAME);
	_OpenFileName.hwndOwner = _Application->GetWnd();
	_OpenFileName.hInstance = _Application->GetHInstance();
	_OpenFileName.lpstrFilter = L"All files\0*.*\0Text\0*.txt\0";
	_OpenFileName.nFilterIndex = 1;
	_OpenFileName.lpstrFile = _Path;
	_OpenFileName.nMaxFile = MAX_PATH + 1;
	_OpenFileName.lpstrTitle = L"Save all of the guesses";
	_OpenFileName.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&_OpenFileName))
	{
		std::wofstream fOut;
		fOut.open(_Path, std::ios::binary);

		if (!fOut.is_open())
		{
			_Application->Close(WordleAPI::_ReturnError);
			return;
		}

		for (size_t _IndexList = 0; _IndexList < ListOfGuesses.size(); _IndexList++)
		{
			for (size_t _IndexGuess = 0; _IndexGuess < ListOfGuesses[_IndexList].size(); _IndexGuess++)
			{
				fOut << ListOfGuesses[_IndexList][_IndexGuess][0];
				fOut << ListOfGuesses[_IndexList][_IndexGuess][1];
				fOut << ListOfGuesses[_IndexList][_IndexGuess][2];
				fOut << ListOfGuesses[_IndexList][_IndexGuess][3];
				fOut << ListOfGuesses[_IndexList][_IndexGuess][4];

				if (_IndexGuess != ListOfGuesses[_IndexList].size() - 1)
				{
					fOut << L',';
					fOut << L' ';
				}
			}
			fOut << L"\r\n";
		}

		fOut.close();

		ShellExecute(_Application->GetWnd(), L"open", _Path, nullptr, nullptr, SW_SHOW);
	}
}

bool& Wordle::BotMenu::GetKeysPressed(const size_t _Key, const size_t _Frame)
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}

const bool& Wordle::BotMenu::GetKeysPressed(const size_t _Key, const size_t _Frame) const
{
	return ((Application*)(GetApplicationObj()))->GetKeysPressed(_Key, _Frame);
}
