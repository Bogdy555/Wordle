#include "..\Headers\Wordle.hpp"



Wordle::Application::Application() : WordleAPI::Application(), Wnd(), WndUserData(), Quad(), VAO(), TextureShader(), ColorShader(), CircleShader(), AlphabetTexture()
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

		Close(WordleAPI::_ReturnNoError);
		return;
	}

	GetSharedInstanceMutex().Unlock();

	if (!InitWindow())
	{
		Close(WordleAPI::_ReturnError);
		return;
	}

	if (!InitOpenGL())
	{
		Close(WordleAPI::_ReturnError);
		return;
	}

	if (!Wnd.Show(GetShowCmd()))
	{
		Close(WordleAPI::_ReturnError);
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

	DestroyOpenGL();

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

bool Wordle::Application::InitOpenGL()
{
	if (!WndUserData.Context.Bind())
	{
		return false;
	}

	{
		WordleAPI::GL::MeshCPUCash _MeshCPUCash;

		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec2(0.0f, 1.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(glm::vec3( 1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f)));

		_MeshCPUCash.IBO.push_back(0);
		_MeshCPUCash.IBO.push_back(1);
		_MeshCPUCash.IBO.push_back(2);
		_MeshCPUCash.IBO.push_back(1);
		_MeshCPUCash.IBO.push_back(3);
		_MeshCPUCash.IBO.push_back(2);

		if (!Quad.VBO.Create(_MeshCPUCash.VBO))
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		WordleAPI::GL::VertexBuffer::Unbind();

		if (!Quad.IBO.Create(_MeshCPUCash.IBO))
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		WordleAPI::GL::IndexBuffer::Unbind();
	}

	if (!VAO.Create())
	{
		WordleAPI::GL::Context::Unbind();
		return false;
	}

	if (!VAO.Bind())
	{
		WordleAPI::GL::Context::Unbind();
		return false;
	}

	if (!VAO.EnableAttrib(0, 3, sizeof(WordleAPI::GL::VertexData) / sizeof(float), offsetof(WordleAPI::GL::VertexData, WordleAPI::GL::VertexData::Position) / sizeof(float)))
	{
		WordleAPI::GL::VertexAttribArray::Unbind();
		WordleAPI::GL::Context::Unbind();
		return false;
	}

	if (!VAO.EnableAttrib(1, 2, sizeof(WordleAPI::GL::VertexData) / sizeof(float), offsetof(WordleAPI::GL::VertexData, WordleAPI::GL::VertexData::TextureCoords) / sizeof(float)))
	{
		WordleAPI::GL::VertexAttribArray::Unbind();
		WordleAPI::GL::Context::Unbind();
		return false;
	}

	WordleAPI::GL::VertexAttribArray::Unbind();

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_CIRCLE_VS);

		if (!_VS)
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_CIRCLE_FS);

		if (!_FS)
		{
			delete[] _VS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		if (!CircleShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		delete[] _VS;
		delete[] _FS;
	}

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_COLOR_VS);

		if (!_VS)
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_COLOR_FS);

		if (!_FS)
		{
			delete[] _VS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		if (!ColorShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		delete[] _VS;
		delete[] _FS;
	}

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_TEXTURE_VS);

		if (!_VS)
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_TEXTURE_FS);

		if (!_FS)
		{
			delete[] _VS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		if (!TextureShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		delete[] _VS;
		delete[] _FS;
	}

	{
		WordleAPI::GL::TextureData _TexData;

		_TexData.WrapSType = GL_CLAMP_TO_EDGE;
		_TexData.WrapTType = GL_CLAMP_TO_EDGE;
		_TexData.MinFilter = GL_NEAREST;
		_TexData.MagFilter = GL_NEAREST;

		if (!WordleAPI::GL::LoadTextureFromResource(_TexData, GetHInstance(), WORDLE_IDB_ALPHABET))
		{
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		for (size_t _Index = 0; _Index < (size_t)(_TexData.Width) * (size_t)(_TexData.Height); _Index++)
		{
			if (_TexData.Data[_Index * 4 + 0] == _TexData.Data[_Index * 4 + 1] && _TexData.Data[_Index * 4 + 1] == _TexData.Data[_Index * 4 + 2] && _TexData.Data[_Index * 4 + 0] == 0)
			{
				_TexData.Data[_Index * 4 + 0] = 0;
				_TexData.Data[_Index * 4 + 1] = 0;
				_TexData.Data[_Index * 4 + 2] = 0;
				_TexData.Data[_Index * 4 + 3] = 0;
			}
			else
			{
				_TexData.Data[_Index * 4 + 0] = 255;
				_TexData.Data[_Index * 4 + 1] = 255;
				_TexData.Data[_Index * 4 + 2] = 255;
				_TexData.Data[_Index * 4 + 3] = 255;
			}
		}

		if (!AlphabetTexture.Create(_TexData))
		{
			delete[] _TexData.Data;
			WordleAPI::GL::Context::Unbind();
			return false;
		}

		delete[] _TexData.Data;

		WordleAPI::GL::Texture2D::Unbind();
	}

	WordleAPI::GL::Context::Unbind();

	return true;
}

void Wordle::Application::DestroyOpenGL()
{
	Quad.VBO.Destroy();
	Quad.IBO.Destroy();
	VAO.Destroy();
	TextureShader.Destroy();
	ColorShader.Destroy();
	CircleShader.Destroy();
	AlphabetTexture.Destroy();
}
