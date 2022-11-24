#include "..\Headers\Wordle.hpp"



Wordle::Application::Application() : WordleAPI::Application(), Wnd(), WndUserData(), Quad(), VAO(), TextureShader(), ColorShader(), CircleShader(), AlphabetTexture(), DatabaseCuvinte(), KeysPressed()
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

WordleAPI::GL::Mesh& Wordle::Application::GetQuad()
{
	return Quad;
}

const WordleAPI::GL::Mesh& Wordle::Application::GetQuad() const
{
	return Quad;
}

WordleAPI::GL::VertexAttribArray& Wordle::Application::GetVAO()
{
	return VAO;
}

const WordleAPI::GL::VertexAttribArray& Wordle::Application::GetVAO() const
{
	return VAO;
}

WordleAPI::GL::Shader& Wordle::Application::GetTextureShader()
{
	return TextureShader;
}

const WordleAPI::GL::Shader& Wordle::Application::GetTextureShader() const
{
	return TextureShader;
}

WordleAPI::GL::Shader& Wordle::Application::GetColorShader()
{
	return ColorShader;
}

const WordleAPI::GL::Shader& Wordle::Application::GetColorShader() const
{
	return ColorShader;
}

WordleAPI::GL::Shader& Wordle::Application::GetCircleShader()
{
	return CircleShader;
}

const WordleAPI::GL::Shader& Wordle::Application::GetCircleShader() const
{
	return CircleShader;
}

WordleAPI::GL::Texture2D& Wordle::Application::GetAlphabetTexture()
{
	return AlphabetTexture;
}

const WordleAPI::GL::Texture2D& Wordle::Application::GetAlphabetTexture() const
{
	return AlphabetTexture;
}

std::vector<std::vector<char>>& Wordle::Application::GetDatabaseCuvinte()
{
	return DatabaseCuvinte;
}

const std::vector<std::vector<char>>& Wordle::Application::GetDatabaseCuvinte() const
{
	return DatabaseCuvinte;
}

bool& Wordle::Application::GetKeysPressed(const size_t _Key, const size_t _Frame)
{
	return KeysPressed[_Key][_Frame];
}

const bool& Wordle::Application::GetKeysPressed(const size_t _Key, const size_t _Frame) const
{
	return KeysPressed[_Key][_Frame];
}

void Wordle::Application::RenderSquare(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color)
{
	ColorShader.Bind();
	VAO.Bind();
	Quad.VBO.Bind();
	Quad.IBO.Bind();

	WordleAPI::GL::Uniform u_WndSize;
	WordleAPI::GL::Uniform u_Size;
	WordleAPI::GL::Uniform u_Position;
	WordleAPI::GL::Uniform u_Color;

	u_WndSize.GetLocation(ColorShader, "u_WndSize");
	u_Size.GetLocation(ColorShader, "u_Size");
	u_Position.GetLocation(ColorShader, "u_Position");
	u_Color.GetLocation(ColorShader, "u_Color");

	u_WndSize.Set2f((float)(_Width), (float)(_Height));
	u_Size.Set2f(_Size.x, _Size.y);
	u_Position.Set2f(_Position.x, _Position.y);
	u_Color.Set4f(_Color.x, _Color.y, _Color.z, _Color.w);

	u_WndSize.ReleaseLocation();
	u_Size.ReleaseLocation();
	u_Position.ReleaseLocation();
	u_Color.ReleaseLocation();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Wordle::Application::RenderCircle(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color)
{
	CircleShader.Bind();
	VAO.Bind();
	Quad.VBO.Bind();
	Quad.IBO.Bind();

	WordleAPI::GL::Uniform u_WndSize;
	WordleAPI::GL::Uniform u_Size;
	WordleAPI::GL::Uniform u_Position;
	WordleAPI::GL::Uniform u_Color;

	u_WndSize.GetLocation(ColorShader, "u_WndSize");
	u_Size.GetLocation(ColorShader, "u_Size");
	u_Position.GetLocation(ColorShader, "u_Position");
	u_Color.GetLocation(ColorShader, "u_Color");

	u_WndSize.Set2f((float)(_Width), (float)(_Height));
	u_Size.Set2f(_Size.x, _Size.y);
	u_Position.Set2f(_Position.x, _Position.y);
	u_Color.Set4f(_Color.x, _Color.y, _Color.z, _Color.w);

	u_WndSize.ReleaseLocation();
	u_Size.ReleaseLocation();
	u_Position.ReleaseLocation();
	u_Color.ReleaseLocation();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Wordle::Application::RenderTexture(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::GL::Texture2D& _Texture, WordleAPI::Vec2 _TextureMultiplier, WordleAPI::Vec2 _TextureOffset, WordleAPI::Vec4 _Color)
{
	TextureShader.Bind();
	VAO.Bind();
	Quad.VBO.Bind();
	Quad.IBO.Bind();
	WordleAPI::GL::glActiveTexture(GL_TEXTURE0);
	_Texture.Bind();

	WordleAPI::GL::Uniform u_WndSize;
	WordleAPI::GL::Uniform u_Size;
	WordleAPI::GL::Uniform u_Position;
	WordleAPI::GL::Uniform u_Texture;
	WordleAPI::GL::Uniform u_TextureMultiplier;
	WordleAPI::GL::Uniform u_TextureOffset;
	WordleAPI::GL::Uniform u_Color;

	u_WndSize.GetLocation(TextureShader, "u_WndSize");
	u_Size.GetLocation(TextureShader, "u_Size");
	u_Position.GetLocation(TextureShader, "u_Position");
	u_Texture.GetLocation(TextureShader, "u_Texture");
	u_TextureMultiplier.GetLocation(TextureShader, "u_TextureMultiplier");
	u_TextureOffset.GetLocation(TextureShader, "u_TextureOffset");
	u_Color.GetLocation(TextureShader, "u_Color");

	u_WndSize.Set2f((float)(_Width), (float)(_Height));
	u_Size.Set2f(_Size.x, _Size.y);
	u_Position.Set2f(_Position.x, _Position.y);
	u_Texture.Set1i(0);
	u_TextureMultiplier.Set2f(_TextureMultiplier.x, _TextureMultiplier.y);
	u_TextureOffset.Set2f(_TextureOffset.x, _TextureOffset.y);
	u_Color.Set4f(_Color.x, _Color.y, _Color.z, _Color.w);

	u_WndSize.ReleaseLocation();
	u_Size.ReleaseLocation();
	u_Position.ReleaseLocation();
	u_Texture.ReleaseLocation();
	u_TextureMultiplier.ReleaseLocation();
	u_TextureOffset.ReleaseLocation();
	u_Color.ReleaseLocation();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Wordle::Application::RenderFancySquare(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color, float _Radius)
{
	RenderSquare(_Width, _Height, WordleAPI::Vec2(_Size.x - 2.0f * _Radius, _Size.y - 2.0f * _Radius), WordleAPI::Vec2(_Position.x + _Radius, _Position.y + _Radius), _Color);

	RenderSquare(_Width, _Height, WordleAPI::Vec2(_Radius, _Size.y - 2.0f * _Radius), WordleAPI::Vec2(_Position.x, _Position.y + _Radius), _Color); // Stanga
	RenderSquare(_Width, _Height, WordleAPI::Vec2(_Radius, _Size.y - 2.0f * _Radius), WordleAPI::Vec2(_Position.x + _Size.x - _Radius, _Position.y + _Radius), _Color); // Dreapta
	RenderSquare(_Width, _Height, WordleAPI::Vec2(_Size.x - 2.0f * _Radius, _Radius), WordleAPI::Vec2(_Position.x + _Radius, _Position.y), _Color); // Jos
	RenderSquare(_Width, _Height, WordleAPI::Vec2(_Size.x - 2.0f * _Radius, _Radius), WordleAPI::Vec2(_Position.x + _Radius, _Position.y + _Size.y - _Radius), _Color); // Sus

	RenderCircle(_Width, _Height, WordleAPI::Vec2(2.0f * _Radius, 2.0f * _Radius), WordleAPI::Vec2(_Position.x, _Position.y), _Color); // Stanga Jos
	RenderCircle(_Width, _Height, WordleAPI::Vec2(2.0f * _Radius, 2.0f * _Radius), WordleAPI::Vec2(_Position.x, _Position.y + _Size.y - 2.0f * _Radius), _Color); // Stanga Sus
	RenderCircle(_Width, _Height, WordleAPI::Vec2(2.0f * _Radius, 2.0f * _Radius), WordleAPI::Vec2(_Position.x + _Size.x - 2.0f * _Radius, _Position.y), _Color); // Dreapta Jos
	RenderCircle(_Width, _Height, WordleAPI::Vec2(2.0f * _Radius, 2.0f * _Radius), WordleAPI::Vec2(_Position.x + _Size.x - 2.0f * _Radius, _Position.y + _Size.y - 2.0f * _Radius), _Color); // Dreapta Sus
}

void Wordle::Application::RenderText(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, std::vector<char>& _Cuv, WordleAPI::Vec4 _Color)
{
	for (size_t _Index = 0; _Index < _Cuv.size(); _Index++)
	{
		if (_Cuv[_Index] >= 'A' && _Cuv[_Index] <= 'Z')
		{
			size_t _X = ((size_t)(_Cuv[_Index]) - (size_t)('A')) % 6;
			size_t _Y = 5 - ((size_t)(_Cuv[_Index]) - (size_t)('A')) / 6;
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_Cuv.size()), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_Cuv.size()), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2((float)(_X) / 6.0f, (float)(_Y) / 6.0f), _Color);
		}
		else if (_Cuv[_Index] == '>')
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_Cuv.size()), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_Cuv.size()), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(3.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
		else if (_Cuv[_Index] == ' ')
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_Cuv.size()), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_Cuv.size()), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(4.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
		else
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_Cuv.size()), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index) * _Size.x / (float)(_Cuv.size()), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(2.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
	}
}

void Wordle::Application::RenderText(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, char* _Cuv, size_t _LenCuv, WordleAPI::Vec4 _Color)
{
	for (size_t _Index = 0; _Index < _LenCuv; _Index++)
	{
		if (_Cuv[_Index] >= 'A' && _Cuv[_Index] <= 'Z')
		{
			size_t _X = ((size_t)(_Cuv[_Index]) - (size_t)('A')) % 6;
			size_t _Y = 5 - ((size_t)(_Cuv[_Index]) - (size_t)('A')) / 6;
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_LenCuv), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_LenCuv), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2((float)(_X) / 6.0f, (float)(_Y) / 6.0f), _Color);
		}
		else if (_Cuv[_Index] == '>')
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_LenCuv), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_LenCuv), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(3.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
		else if (_Cuv[_Index] == ' ')
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_LenCuv), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_LenCuv), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(4.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
		else
		{
			RenderTexture(_Width, _Height, WordleAPI::Vec2(_Size.x / (float)(_LenCuv), _Size.y), WordleAPI::Vec2(_Position.x + (float)(_Index)*_Size.x / (float)(_LenCuv), _Position.y), AlphabetTexture, WordleAPI::Vec2(1.0f / 6.0f, 1.0f / 6.0f), WordleAPI::Vec2(2.0f / 6.0f, 1.0f / 6.0f), _Color);
		}
	}
}

bool Wordle::Application::UpdateFullScreen()
{
	WndUserData.MutexFullScreen.lock();

	WndUserData.FullScreen = !WndUserData.FullScreen;

	if (WndUserData.FullScreen)
	{
		WndUserData.MutexFullScreen.unlock();

		WndUserData.MutexWndPlacement.lock();

		if (!GetWindowPlacement(Wnd, &WndUserData.WndPlacement))
		{
			WndUserData.MutexWndPlacement.unlock();
			return false;
		}

		WndUserData.MutexWndPlacement.unlock();

		WndUserData.MutexWndRect.lock();

		if (!GetWindowRect(Wnd, &WndUserData.WndRect))
		{
			WndUserData.MutexWndRect.unlock();
			return false;
		}

		WndUserData.MutexWndRect.unlock();

		HMONITOR _hMonitor = MonitorFromWindow(Wnd, MONITOR_DEFAULTTOPRIMARY);

		if (!_hMonitor)
		{
			return false;
		}

		MONITORINFOEX _MonitorInfo = { 0 };

		_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

		if (!GetMonitorInfo(_hMonitor, &_MonitorInfo))
		{
			return false;
		}

		if (!SetWindowLongPtr(Wnd, GWL_STYLE, WS_POPUP))
		{
			return false;
		}

		if (!SetWindowPos(Wnd, HWND_TOP, _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.top, _MonitorInfo.rcMonitor.right - _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.bottom - _MonitorInfo.rcMonitor.top, SWP_ASYNCWINDOWPOS))
		{
			return false;
		}

		if (!Wnd.Show(SW_SHOW))
		{
			return false;
		}
	}
	else
	{
		WndUserData.MutexFullScreen.unlock();

		if (!SetWindowLongPtr(Wnd, GWL_STYLE, WS_OVERLAPPEDWINDOW))
		{
			return false;
		}

		WndUserData.MutexWndPlacement.lock();

		if (WndUserData.WndPlacement.showCmd != SW_NORMAL)
		{
			if (!SetWindowPos(Wnd, HWND_TOP, WndUserData.WndPlacement.rcNormalPosition.left, WndUserData.WndPlacement.rcNormalPosition.top, WndUserData.WndPlacement.rcNormalPosition.right - WndUserData.WndPlacement.rcNormalPosition.left, WndUserData.WndPlacement.rcNormalPosition.bottom - WndUserData.WndPlacement.rcNormalPosition.top, SWP_ASYNCWINDOWPOS))
			{
				WndUserData.MutexWndPlacement.unlock();
				return false;
			}

			if (!Wnd.Show(WndUserData.WndPlacement.showCmd))
			{
				WndUserData.MutexWndPlacement.unlock();
				return false;
			}

			WndUserData.MutexWndPlacement.unlock();
		}
		else
		{
			WndUserData.MutexWndPlacement.unlock();

			WndUserData.MutexWndRect.lock();

			if (!SetWindowPos(Wnd, HWND_TOP, WndUserData.WndRect.left, WndUserData.WndRect.top, WndUserData.WndRect.right - WndUserData.WndRect.left, WndUserData.WndRect.bottom - WndUserData.WndRect.top, SWP_ASYNCWINDOWPOS))
			{
				WndUserData.MutexWndRect.unlock();
				return false;
			}

			if (!Wnd.Show(SW_SHOW))
			{
				WndUserData.MutexWndRect.unlock();
				return false;
			}

			WndUserData.MutexWndRect.unlock();
		}
	}

	return true;
}

void Wordle::Application::Setup()
{
	if (GetArgC() != 1)
	{
		Close(WordleAPI::_ReturnError);
		return;
	}

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

	if (!SuitableScreenSize())
	{
		Close(WordleAPI::_ReturnError);
		return;
	}

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

	if (!LoadDatabaseCuvinte())
	{
		Close(WordleAPI::_ReturnError);
		return;
	}

	srand((unsigned int)(time(nullptr)));

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

	DestroyDatabaseCuvinte();

	DestroyOpenGL();

	DestroyWindow();
}

bool Wordle::Application::SuitableScreenSize()
{
	RECT _WndRect = { 0 };

	_WndRect.left = 0;
	_WndRect.right = 800;
	_WndRect.top = 0;
	_WndRect.bottom = 450;

	if (!AdjustWindowRectEx(&_WndRect, WS_OVERLAPPEDWINDOW, false, NULL))
	{
		return false;
	}

	HMONITOR _hMonitor = MonitorFromPoint(POINT(0, 0), MONITOR_DEFAULTTOPRIMARY);

	if (!_hMonitor)
	{
		return false;
	}

	MONITORINFOEX _MonitorInfo = { 0 };

	_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

	if (!GetMonitorInfo(_hMonitor, &_MonitorInfo))
	{
		return false;
	}

	int32_t _Offset = 50;

	if (_MonitorInfo.rcMonitor.right - _MonitorInfo.rcMonitor.left < _WndRect.right - _WndRect.left + _Offset || _MonitorInfo.rcMonitor.bottom - _MonitorInfo.rcMonitor.top < _WndRect.bottom - _WndRect.top + _Offset)
	{
		return false;
	}

	return true;
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

		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(WordleAPI::Vec2(0.0f, 1.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(WordleAPI::Vec2(1.0f, 1.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(WordleAPI::Vec2(0.0f, 0.0f)));
		_MeshCPUCash.VBO.push_back(WordleAPI::GL::VertexData(WordleAPI::Vec2(1.0f, 0.0f)));

		_MeshCPUCash.IBO.push_back(0);
		_MeshCPUCash.IBO.push_back(1);
		_MeshCPUCash.IBO.push_back(2);
		_MeshCPUCash.IBO.push_back(1);
		_MeshCPUCash.IBO.push_back(3);
		_MeshCPUCash.IBO.push_back(2);

		if (!Quad.VBO.Create(_MeshCPUCash.VBO))
		{
			return false;
		}

		if (!Quad.IBO.Create(_MeshCPUCash.IBO))
		{
			return false;
		}
	}

	if (!VAO.Create())
	{
		return false;
	}

	if (!VAO.Bind())
	{
		return false;
	}

	if (!VAO.EnableAttrib(0, 2, sizeof(WordleAPI::GL::VertexData) / sizeof(float), offsetof(WordleAPI::GL::VertexData, WordleAPI::GL::VertexData::Position) / sizeof(float)))
	{
		return false;
	}

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_CIRCLE_VS);

		if (!_VS)
		{
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_CIRCLE_FS);

		if (!_FS)
		{
			delete[] _VS;
			return false;
		}

		if (!CircleShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
			return false;
		}

		delete[] _VS;
		delete[] _FS;
	}

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_COLOR_VS);

		if (!_VS)
		{
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_COLOR_FS);

		if (!_FS)
		{
			delete[] _VS;
			return false;
		}

		if (!ColorShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
			return false;
		}

		delete[] _VS;
		delete[] _FS;
	}

	{
		const char* _VS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_TEXTURE_VS);

		if (!_VS)
		{
			return false;
		}

		const char* _FS = WordleAPI::GL::LoadShaderSourceFromResource(GetHInstance(), WORDLE_IDS_TEXTURE_FS);

		if (!_FS)
		{
			delete[] _VS;
			return false;
		}

		if (!TextureShader.Create(_VS, _FS))
		{
			delete[] _VS;
			delete[] _FS;
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
			return false;
		}

		delete[] _TexData.Data;
	}

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

bool Wordle::Application::LoadDatabaseCuvinte()
{
	HRSRC _hResource = FindResource(GetHInstance(), MAKEINTRESOURCE(WORDLE_IDT_WORDLIST), MAKEINTRESOURCE(WORDLEAPI_TEXT_RES));

	if (!_hResource)
	{
		return false;
	}

	size_t _Len = SizeofResource(GetHInstance(), _hResource);

	if (!_Len || _Len % 7 != 0)
	{
		return false;
	}

	HGLOBAL _hGlobal = LoadResource(GetHInstance(), _hResource);

	if (!_hGlobal)
	{
		return false;
	}

	const unsigned char* _ResourcePtr = (const unsigned char*)(LockResource(_hGlobal));

	if (!_ResourcePtr)
	{
		FreeResource(_hGlobal);
		return false;
	}

	for (size_t _Index = 0; _Index < _Len / 7; _Index++)
	{
		DatabaseCuvinte.push_back(std::vector<char>());
	}

	for (size_t _Index = 0; _Index < _Len; _Index++)
	{
		if (_Index % 7 < 5)
		{
			DatabaseCuvinte[_Index / 7].push_back(_ResourcePtr[_Index]);
		}
	}

	UnlockResource(_hGlobal);
	FreeResource(_hGlobal);

	return true;
}

void Wordle::Application::DestroyDatabaseCuvinte()
{
	for (size_t _Index = 0; _Index < DatabaseCuvinte.size(); _Index++)
	{
		DatabaseCuvinte[_Index].clear();
	}

	DatabaseCuvinte.clear();
}
