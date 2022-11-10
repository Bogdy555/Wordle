#include "..\Headers\WordleAPI.hpp"



static HMODULE _hDll = NULL;

const WordleAPI::ConstHModuleRef WordleAPI::GL::hDll = _hDll;



void* (__stdcall* WordleAPI::GL::wglGetProcAddress)(const char*) = nullptr;
int (__stdcall* WordleAPI::GL::wglSwapIntervalEXT)(int) = nullptr;
void (__stdcall* WordleAPI::GL::glViewport)(int, int, int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glClearColor)(float, float, float, float) = nullptr;
void (__stdcall* WordleAPI::GL::glClear)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glUseProgram)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glBindVertexArray)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDrawElements)(unsigned int, int, unsigned int, const void*) = nullptr;
void (__stdcall* WordleAPI::GL::glEnable)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glBlendFunc)(unsigned int, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDepthFunc)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glGenBuffers)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glBindBuffer)(unsigned int, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glBufferData)(unsigned int, intptr_t, const void*, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glGenVertexArrays)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glEnableVertexAttribArray)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glVertexAttribPointer)(unsigned int, int, unsigned int, unsigned char, int, const void*) = nullptr;
unsigned int (__stdcall* WordleAPI::GL::glCreateProgram)() = nullptr;
unsigned int (__stdcall* WordleAPI::GL::glCreateShader)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glShaderSource)(unsigned int, int, const char* const*, int*) = nullptr;
void (__stdcall* WordleAPI::GL::glCompileShader)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glAttachShader)(unsigned int, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glLinkProgram)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glValidateProgram)(unsigned int) = nullptr;
int (__stdcall* WordleAPI::GL::glGetUniformLocation)(unsigned int, const char*) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform1f)(int, float) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform2f)(int, float, float) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform3f)(int, float, float, float) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform4f)(int, float, float, float, float) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform1i)(int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform2i)(int, int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform3i)(int, int, int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform4i)(int, int, int, int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glUniform1ui)(int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glUniformMatrix2fv)(int, int, unsigned char, const float*) = nullptr;
void (__stdcall* WordleAPI::GL::glUniformMatrix3fv)(int, int, unsigned char, const float*) = nullptr;
void (__stdcall* WordleAPI::GL::glUniformMatrix4fv)(int, int, unsigned char, const float*) = nullptr;
void (__stdcall* WordleAPI::GL::glDetachShader)(unsigned int, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDeleteBuffers)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glDeleteVertexArrays)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glDisableVertexAttribArray)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDeleteProgram)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDeleteShader)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glGetShaderiv)(unsigned int, unsigned int, int*) = nullptr;
void (__stdcall* WordleAPI::GL::glGetShaderInfoLog)(unsigned int, int, int*, char*) = nullptr;
void (__stdcall* WordleAPI::GL::glGetProgramiv)(unsigned int, unsigned int, int*) = nullptr;
void (__stdcall* WordleAPI::GL::glGetProgramInfoLog)(unsigned int, int, int*, char*) = nullptr;
void (__stdcall* WordleAPI::GL::glGenTextures)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glBindTexture)(unsigned int, unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glTexParameteri)(unsigned int, unsigned int, int) = nullptr;
void (__stdcall* WordleAPI::GL::glTexImage2D)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*) = nullptr;
void (__stdcall* WordleAPI::GL::glActiveTexture)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glDeleteTextures)(int, unsigned int*) = nullptr;
void (__stdcall* WordleAPI::GL::glCullFace)(unsigned int) = nullptr;
void (__stdcall* WordleAPI::GL::glFrontFace)(unsigned int) = nullptr;



static void* CustomGetProcAddress(const char* _Name)
{
	if (!_Name)
	{
		return nullptr;
	}

	void* _Rez = nullptr;

	if (WordleAPI::GL::wglGetProcAddress)
	{
		_Rez = WordleAPI::GL::wglGetProcAddress(_Name);
	}

	if (!_Rez)
	{
		_Rez = GetProcAddress(WordleAPI::GL::hDll, _Name);
	}

	return _Rez;
}

#define LOAD(Func, Type, Name) Func = (Type)(CustomGetProcAddress(Name));\
if (!Func)\
{\
	wglMakeCurrent(NULL, NULL);\
	wglDeleteContext(_wglContext);\
	ReleaseDC(_hWnd, _WndDC);\
	DestroyWindow(_hWnd);\
	UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);\
	Unload();\
	return false;\
}

bool WordleAPI::GL::Load()
{
	if (hDll)
	{
		return true;
	}

	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	_WndClass.lpfnWndProc = DefWindowProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetModuleHandle(nullptr);
	_WndClass.hIcon = NULL;
	_WndClass.hCursor = NULL;
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = L"DummyWndClass";
	_WndClass.hIconSm = NULL;

	if (!RegisterClassEx(&_WndClass))
	{
		return false;
	}

	HWND _hWnd = CreateWindowEx(NULL, _WndClass.lpszClassName, L"DummyWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, _WndClass.hInstance, nullptr);

	if (!_hWnd)
	{
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	HDC _WndDC = GetDC(_hWnd);

	if (!_WndDC)
	{
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	PIXELFORMATDESCRIPTOR _PFD = { 0 };

	_PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	_PFD.nVersion = 1;
	_PFD.iPixelType = PFD_TYPE_RGBA;
	_PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	_PFD.cColorBits = 32;
	_PFD.cAlphaBits = 8;
	_PFD.cDepthBits = 24;
	_PFD.cStencilBits = 8;
	_PFD.iLayerType = PFD_MAIN_PLANE;

	int _PForm = ChoosePixelFormat(_WndDC, &_PFD);

	if (!_PForm)
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	if (!SetPixelFormat(_WndDC, _PForm, &_PFD))
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	HGLRC _wglContext = wglCreateContext(_WndDC);

	if (!_wglContext)
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	if (!wglMakeCurrent(_WndDC, _wglContext))
	{
		wglDeleteContext(_wglContext);
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	_hDll = LoadLibrary(L"opengl32.dll");

	if (!hDll)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_wglContext);
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	LOAD(wglGetProcAddress, void* (__stdcall*)(const char*), "wglGetProcAddress");
	LOAD(wglSwapIntervalEXT, int(__stdcall*)(int), "wglSwapIntervalEXT");
	LOAD(glViewport, void(__stdcall*)(int, int, int, int), "glViewport");
	LOAD(glClearColor, void(__stdcall*)(float, float, float, float), "glClearColor");
	LOAD(glClear, void(__stdcall*)(unsigned int), "glClear");
	LOAD(glUseProgram, void(__stdcall*)(unsigned int), "glUseProgram");
	LOAD(glBindVertexArray, void(__stdcall*)(unsigned int), "glBindVertexArray");
	LOAD(glDrawElements, void(__stdcall*)(unsigned int, int, unsigned int, const void*), "glDrawElements");
	LOAD(glEnable, void(__stdcall*)(unsigned int), "glEnable");
	LOAD(glBlendFunc, void(__stdcall*)(unsigned int, unsigned int), "glBlendFunc");
	LOAD(glDepthFunc, void(__stdcall*)(unsigned int), "glDepthFunc");
	LOAD(glGenBuffers, void(__stdcall*)(int, unsigned int*), "glGenBuffers");
	LOAD(glBindBuffer, void(__stdcall*)(unsigned int, unsigned int), "glBindBuffer");
	LOAD(glBufferData, void(__stdcall*)(unsigned int, intptr_t, const void*, unsigned int), "glBufferData");
	LOAD(glGenVertexArrays, void(__stdcall*)(int, unsigned int*), "glGenVertexArrays");
	LOAD(glEnableVertexAttribArray, void(__stdcall*)(unsigned int), "glEnableVertexAttribArray");
	LOAD(glVertexAttribPointer, void(__stdcall*)(unsigned int, int, unsigned int, unsigned char, int, const void*), "glVertexAttribPointer");
	LOAD(glCreateProgram, unsigned int(__stdcall*)(), "glCreateProgram");
	LOAD(glCreateShader, unsigned int(__stdcall*)(unsigned int), "glCreateShader");
	LOAD(glShaderSource, void(__stdcall*)(unsigned int, int, const char* const*, int*), "glShaderSource");
	LOAD(glCompileShader, void(__stdcall*)(unsigned int), "glCompileShader");
	LOAD(glAttachShader, void(__stdcall*)(unsigned int, unsigned int), "glAttachShader");
	LOAD(glLinkProgram, void(__stdcall*)(unsigned int), "glLinkProgram");
	LOAD(glValidateProgram, void(__stdcall*)(unsigned int), "glValidateProgram");
	LOAD(glGetUniformLocation, int(__stdcall*)(unsigned int, const char*), "glGetUniformLocation");
	LOAD(glUniform1f, void(__stdcall*)(int, float), "glUniform1f");
	LOAD(glUniform2f, void(__stdcall*)(int, float, float), "glUniform2f");
	LOAD(glUniform3f, void(__stdcall*)(int, float, float, float), "glUniform3f");
	LOAD(glUniform4f, void(__stdcall*)(int, float, float, float, float), "glUniform4f");
	LOAD(glUniform1i, void(__stdcall*)(int, int), "glUniform1i");
	LOAD(glUniform2i, void(__stdcall*)(int, int, int), "glUniform2i");
	LOAD(glUniform3i, void(__stdcall*)(int, int, int, int), "glUniform3i");
	LOAD(glUniform4i, void(__stdcall*)(int, int, int, int, int), "glUniform4i");
	LOAD(glUniform1ui, void(__stdcall*)(int, int), "glUniform1ui");
	LOAD(glUniformMatrix2fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix2fv");
	LOAD(glUniformMatrix3fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix3fv");
	LOAD(glUniformMatrix4fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix4fv");
	LOAD(glDetachShader, void(__stdcall*)(unsigned int, unsigned int), "glDetachShader");
	LOAD(glDeleteBuffers, void(__stdcall*)(int, unsigned int*), "glDeleteBuffers");
	LOAD(glDeleteVertexArrays, void(__stdcall*)(int, unsigned int*), "glDeleteVertexArrays");
	LOAD(glDisableVertexAttribArray, void(__stdcall*)(unsigned int), "glDisableVertexAttribArray");
	LOAD(glDeleteProgram, void(__stdcall*)(unsigned int), "glDeleteProgram");
	LOAD(glDeleteShader, void(__stdcall*)(unsigned int), "glDeleteShader");
	LOAD(glGetShaderiv, void(__stdcall*)(unsigned int, unsigned int, int*), "glGetShaderiv");
	LOAD(glGetShaderInfoLog, void(__stdcall*)(unsigned int, int, int*, char*), "glGetShaderInfoLog");
	LOAD(glGetProgramiv, void(__stdcall*)(unsigned int, unsigned int, int*), "glGetProgramiv");
	LOAD(glGetProgramInfoLog, void(__stdcall*)(unsigned int, int, int*, char*), "glGetProgramInfoLog");
	LOAD(glGenTextures, void(__stdcall*)(int, unsigned int*), "glGenTextures");
	LOAD(glBindTexture, void(__stdcall*)(unsigned int, unsigned int), "glBindTexture");
	LOAD(glTexParameteri, void(__stdcall*)(unsigned int, unsigned int, int), "glTexParameteri");
	LOAD(glTexImage2D, void(__stdcall*)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*), "glTexImage2D");
	LOAD(glActiveTexture, void(__stdcall*)(unsigned int), "glActiveTexture");
	LOAD(glDeleteTextures, void(__stdcall*)(int, unsigned int*), "glDeleteTextures");
	LOAD(glCullFace, void(__stdcall*)(unsigned int), "glCullFace");
	LOAD(glFrontFace, void(__stdcall*)(unsigned int), "glFrontFace");

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(_wglContext);
	ReleaseDC(_hWnd, _WndDC);
	DestroyWindow(_hWnd);
	UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);

	return true;
}

#undef LOAD

#define UNLOAD(Func) Func = nullptr

void WordleAPI::GL::Unload()
{
	if (!hDll)
	{
		return;
	}

	FreeLibrary(hDll);
	_hDll = NULL;

	UNLOAD(wglGetProcAddress);
	UNLOAD(wglSwapIntervalEXT);
	UNLOAD(glViewport);
	UNLOAD(glClearColor);
	UNLOAD(glClear);
	UNLOAD(glUseProgram);
	UNLOAD(glBindVertexArray);
	UNLOAD(glDrawElements);
	UNLOAD(glEnable);
	UNLOAD(glBlendFunc);
	UNLOAD(glDepthFunc);
	UNLOAD(glGenBuffers);
	UNLOAD(glBindBuffer);
	UNLOAD(glBufferData);
	UNLOAD(glGenVertexArrays);
	UNLOAD(glEnableVertexAttribArray);
	UNLOAD(glVertexAttribPointer);
	UNLOAD(glCreateProgram);
	UNLOAD(glCreateShader);
	UNLOAD(glShaderSource);
	UNLOAD(glCompileShader);
	UNLOAD(glAttachShader);
	UNLOAD(glLinkProgram);
	UNLOAD(glValidateProgram);
	UNLOAD(glGetUniformLocation);
	UNLOAD(glUniform1f);
	UNLOAD(glUniform2f);
	UNLOAD(glUniform3f);
	UNLOAD(glUniform4f);
	UNLOAD(glUniform1i);
	UNLOAD(glUniform2i);
	UNLOAD(glUniform3i);
	UNLOAD(glUniform4i);
	UNLOAD(glUniform1ui);
	UNLOAD(glUniformMatrix2fv);
	UNLOAD(glUniformMatrix3fv);
	UNLOAD(glUniformMatrix4fv);
	UNLOAD(glDetachShader);
	UNLOAD(glDeleteBuffers);
	UNLOAD(glDeleteVertexArrays);
	UNLOAD(glDisableVertexAttribArray);
	UNLOAD(glDeleteProgram);
	UNLOAD(glDeleteShader);
	UNLOAD(glGetShaderiv);
	UNLOAD(glGetShaderInfoLog);
	UNLOAD(glGetProgramiv);
	UNLOAD(glGetProgramInfoLog);
	UNLOAD(glGenTextures);
	UNLOAD(glBindTexture);
	UNLOAD(glTexParameteri);
	UNLOAD(glTexImage2D);
	UNLOAD(glActiveTexture);
	UNLOAD(glDeleteTextures);
	UNLOAD(glCullFace);
	UNLOAD(glFrontFace);
}

#undef UNLOAD



WordleAPI::GL::Context::Context() : Handle(NULL), WndPtr(nullptr)
{

}

WordleAPI::GL::Context::Context(Context&& _Other) noexcept : Handle(_Other.Handle), WndPtr(_Other.WndPtr)
{
	_Other.Handle = NULL;
	_Other.WndPtr = nullptr;
}

WordleAPI::GL::Context::~Context()
{

}

bool WordleAPI::GL::Context::Create(Window* _WndPtr)
{
	if (Handle || !_WndPtr)
	{
		return false;
	}

	HWND _hWnd = _WndPtr->GetHandle();

	if (!_hWnd)
	{
		return false;
	}

	HDC _hWndDC = GetDC(_hWnd);

	if (!_hWndDC)
	{
		return false;
	}

	PIXELFORMATDESCRIPTOR _PFD = { 0 };

	_PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	_PFD.nVersion = 1;
	_PFD.iPixelType = PFD_TYPE_RGBA;
	_PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	_PFD.cColorBits = 32;
	_PFD.cAlphaBits = 8;
	_PFD.cDepthBits = 24;
	_PFD.cStencilBits = 8;
	_PFD.iLayerType = PFD_MAIN_PLANE;

	int _PixelFormatID = ChoosePixelFormat(_hWndDC, &_PFD);

	if (!_PixelFormatID)
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	if (!DescribePixelFormat(_hWndDC, _PixelFormatID, sizeof(PIXELFORMATDESCRIPTOR), &_PFD))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	if (!SetPixelFormat(_hWndDC, _PixelFormatID, &_PFD))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	Handle = wglCreateContext(_hWndDC);

	if (!Handle)
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	ReleaseDC(_hWnd, _hWndDC);

	WndPtr = _WndPtr;

	return true;
}

void WordleAPI::GL::Context::Destroy()
{
	if (!Handle)
	{
		return;
	}

	Unbind();

	wglDeleteContext(Handle);

	Handle = NULL;
	WndPtr = nullptr;
}

bool WordleAPI::GL::Context::Bind()
{
	if (!Handle)
	{
		return false;
	}

	HWND _hWnd = WndPtr->GetHandle();

	if (!_hWnd)
	{
		return false;
	}

	HDC _hWndDC = GetDC(_hWnd);

	if (!_hWndDC)
	{
		return false;
	}

	if (!wglMakeCurrent(_hWndDC, Handle))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	ReleaseDC(_hWnd, _hWndDC);

	return true;
}

const HGLRC WordleAPI::GL::Context::GetHandle() const
{
	return Handle;
}

WordleAPI::Window* WordleAPI::GL::Context::GetWndPtr()
{
	return WndPtr;
}

const WordleAPI::Window* WordleAPI::GL::Context::GetWndPtr() const
{
	return WndPtr;
}

WordleAPI::GL::Context::operator const HGLRC() const
{
	return Handle;
}

void WordleAPI::GL::Context::operator= (Context&& _Other) noexcept
{
	Handle = _Other.Handle;
	WndPtr = _Other.WndPtr;

	_Other.Handle = NULL;
	_Other.WndPtr = nullptr;
}

void WordleAPI::GL::Context::Unbind()
{
	wglMakeCurrent(NULL, NULL);
}



WordleAPI::GL::VertexBuffer::VertexBuffer() : ID(0)
{

}

WordleAPI::GL::VertexBuffer::VertexBuffer(VertexBuffer&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

WordleAPI::GL::VertexBuffer::~VertexBuffer()
{

}

bool WordleAPI::GL::VertexBuffer::Create(const VertexBufferCPUCash& _VBO_CPUCash)
{
	if (ID)
	{
		return false;
	}

	if (!_VBO_CPUCash.size())
	{
		return false;
	}

	glGenBuffers(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, ID);

	glBufferData(GL_ARRAY_BUFFER, _VBO_CPUCash.size() * sizeof(VertexData), _VBO_CPUCash.data(), GL_DYNAMIC_DRAW);

	return true;
}

void WordleAPI::GL::VertexBuffer::Destroy()
{
	if (!ID)
	{
		return;
	}

	Unbind();
	glDeleteBuffers(1, &ID);
	ID = 0;
}

bool WordleAPI::GL::VertexBuffer::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, ID);

	return true;
}

const bool WordleAPI::GL::VertexBuffer::CheckCreated() const
{
	return ID != 0;
}

const unsigned int WordleAPI::GL::VertexBuffer::GetID() const
{
	return ID;
}

void WordleAPI::GL::VertexBuffer::operator= (VertexBuffer&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void WordleAPI::GL::VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



WordleAPI::GL::IndexBuffer::IndexBuffer() : ID(0)
{

}

WordleAPI::GL::IndexBuffer::IndexBuffer(IndexBuffer&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

WordleAPI::GL::IndexBuffer::~IndexBuffer()
{

}

bool WordleAPI::GL::IndexBuffer::Create(const IndexBufferCPUCash& _IBO_CPUCash)
{
	if (ID)
	{
		return false;
	}

	if (!_IBO_CPUCash.size())
	{
		return false;
	}

	glGenBuffers(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _IBO_CPUCash.size() * sizeof(unsigned int), _IBO_CPUCash.data(), GL_DYNAMIC_DRAW);

	return true;
}

void WordleAPI::GL::IndexBuffer::Destroy()
{
	if (!ID)
	{
		return;
	}

	Unbind();
	glDeleteBuffers(1, &ID);
	ID = 0;
}

bool WordleAPI::GL::IndexBuffer::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	return true;
}

const bool WordleAPI::GL::IndexBuffer::CheckCreated() const
{
	return ID != 0;
}

const unsigned int WordleAPI::GL::IndexBuffer::GetID() const
{
	return ID;
}

void WordleAPI::GL::IndexBuffer::operator= (IndexBuffer&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void WordleAPI::GL::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



WordleAPI::GL::VertexAttribArray::VertexAttribArray() : ID(0)
{

}

WordleAPI::GL::VertexAttribArray::VertexAttribArray(VertexAttribArray&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

WordleAPI::GL::VertexAttribArray::~VertexAttribArray()
{

}

bool WordleAPI::GL::VertexAttribArray::Create()
{
	if (ID)
	{
		return false;
	}

	glGenVertexArrays(1, &ID);

	if (!ID)
	{
		return false;
	}

	return true;
}

void WordleAPI::GL::VertexAttribArray::Destroy()
{
	if (!ID)
	{
		return;
	}

	Unbind();
	glDeleteVertexArrays(1, &ID);
	ID = 0;
}

bool WordleAPI::GL::VertexAttribArray::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindVertexArray(ID);

	return true;
}

bool WordleAPI::GL::VertexAttribArray::EnableAttrib(const unsigned int _AttribID, const int _ElementsCount, const int _ElementsCountTotal, const size_t _Offset)
{
	if (!ID)
	{
		return false;
	}

	glEnableVertexAttribArray(_AttribID);
	glVertexAttribPointer(_AttribID, _ElementsCount, GL_FLOAT, GL_FALSE, sizeof(float) * _ElementsCountTotal, (const void*)(_Offset * sizeof(float)));

	return true;
}

bool WordleAPI::GL::VertexAttribArray::DisableAttrib(const unsigned int _AttribID)
{
	if (!ID)
	{
		return false;
	}

	glDisableVertexAttribArray(_AttribID);

	return true;
}

const bool WordleAPI::GL::VertexAttribArray::CheckCreated() const
{
	return ID != 0;
}

const unsigned int WordleAPI::GL::VertexAttribArray::GetID() const
{
	return ID;
}

void WordleAPI::GL::VertexAttribArray::operator= (VertexAttribArray&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void WordleAPI::GL::VertexAttribArray::Unbind()
{
	glBindVertexArray(0);
}



WordleAPI::GL::Shader::Shader() : ID(0)
{

}

WordleAPI::GL::Shader::Shader(Shader&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

WordleAPI::GL::Shader::~Shader()
{

}

bool WordleAPI::GL::Shader::Create(const char* _VS, const char* _FS)
{
	if (ID)
	{
		return false;
	}

	if (!_VS || !_FS)
	{
		return false;
	}

	ID = glCreateProgram();

	if (!ID)
	{
		return false;
	}

	const char** _VPtr = &_VS;
	const char** _FPtr = &_FS;

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);

	if (!vs)
	{
		glDeleteProgram(ID);
		ID = 0;
		return false;
	}

	glShaderSource(vs, 1, _VPtr, nullptr);

	glCompileShader(vs);

	{
		int _Result;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetShaderInfoLog(vs, _Len + 1, &_Len, _Msg);
			WORDLEAPI_LOG_LINE("Vertex shader error:");
			WORDLEAPI_LOG_LINE(_Msg);
			delete[] _Msg;

			glDeleteShader(vs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	if (!fs)
	{
		glDeleteShader(vs);
		glDeleteProgram(ID);
		ID = 0;
		return false;
	}

	glShaderSource(fs, 1, _FPtr, nullptr);

	glCompileShader(fs);

	{
		int _Result;
		glGetShaderiv(fs, GL_COMPILE_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetShaderInfoLog(fs, _Len + 1, &_Len, _Msg);
			WORDLEAPI_LOG_LINE("Fragment shader error:");
			WORDLEAPI_LOG_LINE(_Msg);
			delete[] _Msg;

			glDeleteShader(vs);
			glDeleteShader(fs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	glAttachShader(ID, vs);
	glAttachShader(ID, fs);

	glLinkProgram(ID);

	{
		int _Result;
		glGetProgramiv(ID, GL_LINK_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetProgramInfoLog(ID, _Len + 1, &_Len, _Msg);
			WORDLEAPI_LOG_LINE("Link error:");
			WORDLEAPI_LOG_LINE(_Msg);
			delete[] _Msg;

			glDetachShader(ID, vs);
			glDeleteShader(vs);
			glDetachShader(ID, fs);
			glDeleteShader(fs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	glValidateProgram(ID);

	glDetachShader(ID, vs);
	glDeleteShader(vs);
	glDetachShader(ID, fs);
	glDeleteShader(fs);

	return true;
}

void WordleAPI::GL::Shader::Destroy()
{
	if (!ID)
	{
		return;
	}

	Unbind();
	glDeleteProgram(ID);
	ID = 0;
}

bool WordleAPI::GL::Shader::Bind()
{
	if (!ID)
	{
		return false;
	}

	glUseProgram(ID);

	return true;
}

const bool WordleAPI::GL::Shader::CheckCreated() const
{
	return ID != 0;
}

const unsigned int WordleAPI::GL::Shader::GetID() const
{
	return ID;
}

void WordleAPI::GL::Shader::operator= (Shader&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void WordleAPI::GL::Shader::Unbind()
{
	glUseProgram(0);
}



WordleAPI::GL::Uniform::Uniform() : ID(-1)
{

}

WordleAPI::GL::Uniform::Uniform(Uniform&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = -1;
}

WordleAPI::GL::Uniform::~Uniform()
{

}

bool WordleAPI::GL::Uniform::GetLocation(const Shader& _Shader, const char* _Name)
{
	if (ID != -1)
	{
		return false;
	}

	if (!_Name)
	{
		return false;
	}

	ID = glGetUniformLocation(_Shader.GetID(), _Name);

	if (ID == -1)
	{
		return false;
	}

	return true;
}

void WordleAPI::GL::Uniform::ReleaseLocation()
{
	ID = -1;
}

const bool WordleAPI::GL::Uniform::CheckBind() const
{
	return ID != -1;
}

const int WordleAPI::GL::Uniform::GetID() const
{
	return ID;
}

bool WordleAPI::GL::Uniform::Set1f(const float _x)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1f(ID, _x);

	return true;
}

bool WordleAPI::GL::Uniform::Set2f(const float _x, const float _y)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform2f(ID, _x, _y);

	return true;
}

bool WordleAPI::GL::Uniform::Set3f(const float _x, const float _y, const float _z)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform3f(ID, _x, _y, _z);

	return true;
}

bool WordleAPI::GL::Uniform::Set4f(const float _x, const float _y, const float _z, const float _w)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform4f(ID, _x, _y, _z, _w);

	return true;
}

bool WordleAPI::GL::Uniform::Set1i(const int _x)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1i(ID, _x);

	return true;
}

bool WordleAPI::GL::Uniform::Set2i(const int _x, const int _y)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform2i(ID, _x, _y);

	return true;
}

bool WordleAPI::GL::Uniform::Set3i(const int _x, const int _y, const int _z)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform3i(ID, _x, _y, _z);

	return true;
}

bool WordleAPI::GL::Uniform::Set4i(const int _x, const int _y, const int _z, const int _w)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform4i(ID, _x, _y, _z, _w);

	return true;
}

bool WordleAPI::GL::Uniform::Set1b(const bool _Value)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1i(ID, _Value);

	return true;
}

bool WordleAPI::GL::Uniform::Set1ui(const unsigned int _Value)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1ui(ID, _Value);

	return true;
}

bool WordleAPI::GL::Uniform::SetMatrix2fv(const float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix2fv(ID, 1, GL_TRUE, _Data);

	return true;
}

bool WordleAPI::GL::Uniform::SetMatrix3fv(const float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix3fv(ID, 1, GL_TRUE, _Data);

	return true;
}

bool WordleAPI::GL::Uniform::SetMatrix4fv(const float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix4fv(ID, 1, GL_TRUE, _Data);

	return true;
}

void WordleAPI::GL::Uniform::operator= (Uniform&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = -1;
}



WordleAPI::GL::Texture2D::Texture2D() : ID(0)
{

}

WordleAPI::GL::Texture2D::Texture2D(Texture2D&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

WordleAPI::GL::Texture2D::~Texture2D()
{

}

bool WordleAPI::GL::Texture2D::Create(const TextureData& _TexData)
{
	if (ID)
	{
		return false;
	}

	if (!_TexData.Width || !_TexData.Height || !_TexData.Data)
	{
		return false;
	}

	glGenTextures(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _TexData.WrapSType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _TexData.WrapTType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _TexData.MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _TexData.MagFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _TexData.Width, _TexData.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _TexData.Data);

	return true;
}

void WordleAPI::GL::Texture2D::Destroy()
{
	if (!ID)
	{
		return;
	}

	Unbind();
	glDeleteTextures(1, &ID);
	ID = 0;
}

bool WordleAPI::GL::Texture2D::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, ID);

	return true;
}

const bool WordleAPI::GL::Texture2D::CheckCreated() const
{
	return ID != 0;
}

const unsigned int WordleAPI::GL::Texture2D::GetID() const
{
	return ID;
}

void WordleAPI::GL::Texture2D::operator= (Texture2D&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void WordleAPI::GL::Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



const std::string WordleAPI::GL::GetUniformIndexName(const std::string _Name, const size_t _Index)
{
	return _Name + std::string("[") + std::to_string(_Index) + std::string("]");
}



bool WordleAPI::GL::LoadTexture(TextureData& _TexData, const wchar_t* _FileName)
{
	if (_TexData.Data || _TexData.Width || _TexData.Height)
	{
		return false;
	}

	if (!_FileName)
	{
		return false;
	}

	HBITMAP _hBmp = (HBITMAP)(LoadImage(NULL, _FileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE));

	if (!_hBmp)
	{
		return false;
	}

	BITMAP _Bmp = { 0 };

	if (!GetObject(_hBmp, sizeof(BITMAP), &_Bmp))
	{
		DeleteObject(_hBmp);
		return false;
	}

	_TexData.Data = new unsigned char[(size_t)(_Bmp.bmWidth) * (size_t)(_Bmp.bmHeight) * 4];

	if (!_TexData.Data)
	{
		DeleteObject(_hBmp);
		return false;
	}

	if (!GetBitmapBits(_hBmp, _Bmp.bmWidth * _Bmp.bmHeight * 4, _TexData.Data))
	{
		delete[] _TexData.Data;
		DeleteObject(_hBmp);
		return false;
	}

	for (size_t _Index = 0; _Index < (size_t)(_Bmp.bmWidth) * (size_t)(_Bmp.bmHeight); _Index++)
	{
		unsigned char _Aux = _TexData.Data[_Index * 4 + 0];
		_TexData.Data[_Index * 4 + 0] = _TexData.Data[_Index * 4 + 2];
		_TexData.Data[_Index * 4 + 2] = _Aux;
		_TexData.Data[_Index * 4 + 3] = 255;
	}

	for (size_t _Y = 0; _Y < (size_t)(_Bmp.bmHeight / 2); _Y++)
	{
		for (size_t _X = 0; _X < (size_t)(_Bmp.bmWidth); _X++)
		{
			unsigned char _Aux0 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 0];
			unsigned char _Aux1 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 1];
			unsigned char _Aux2 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 2];
			unsigned char _Aux3 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 3];

			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 0] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 0];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 1] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 1];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 2] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 2];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 3] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 3];

			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 0] = _Aux0;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 1] = _Aux1;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 2] = _Aux2;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 3] = _Aux3;
		}
	}

	_TexData.Width = _Bmp.bmWidth;
	_TexData.Height = _Bmp.bmHeight;

	DeleteObject(_hBmp);

	return true;
}



bool WordleAPI::GL::LoadTextureFromResource(TextureData& _TexData, HINSTANCE _hInstance, size_t _ResName)
{
	if (_TexData.Data || _TexData.Width || _TexData.Height)
	{
		return false;
	}

	HBITMAP _hBmp = (HBITMAP)(LoadImage(_hInstance, MAKEINTRESOURCE(_ResName), IMAGE_BITMAP, 0, 0, 0));

	if (!_hBmp)
	{
		return false;
	}

	BITMAP _Bmp = { 0 };

	if (!GetObject(_hBmp, sizeof(BITMAP), &_Bmp))
	{
		DeleteObject(_hBmp);
		return false;
	}

	_TexData.Data = new unsigned char[(size_t)(_Bmp.bmWidth) * (size_t)(_Bmp.bmHeight) * 4];

	if (!_TexData.Data)
	{
		DeleteObject(_hBmp);
		return false;
	}

	if (!GetBitmapBits(_hBmp, _Bmp.bmWidth * _Bmp.bmHeight * 4, _TexData.Data))
	{
		delete[] _TexData.Data;
		DeleteObject(_hBmp);
		return false;
	}

	for (size_t _Index = 0; _Index < (size_t)(_Bmp.bmWidth) * (size_t)(_Bmp.bmHeight); _Index++)
	{
		unsigned char _Aux = _TexData.Data[_Index * 4 + 0];
		_TexData.Data[_Index * 4 + 0] = _TexData.Data[_Index * 4 + 2];
		_TexData.Data[_Index * 4 + 2] = _Aux;
		_TexData.Data[_Index * 4 + 3] = 255;
	}

	for (size_t _Y = 0; _Y < (size_t)(_Bmp.bmHeight / 2); _Y++)
	{
		for (size_t _X = 0; _X < (size_t)(_Bmp.bmWidth); _X++)
		{
			unsigned char _Aux0 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 0];
			unsigned char _Aux1 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 1];
			unsigned char _Aux2 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 2];
			unsigned char _Aux3 = _TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 3];

			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 0] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 0];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 1] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 1];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 2] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 2];
			_TexData.Data[(_X + _Y * _Bmp.bmWidth) * 4 + 3] = _TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 3];

			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 0] = _Aux0;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 1] = _Aux1;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 2] = _Aux2;
			_TexData.Data[(_X + (_Bmp.bmHeight - _Y - 1) * _Bmp.bmWidth) * 4 + 3] = _Aux3;
		}
	}

	_TexData.Width = _Bmp.bmWidth;
	_TexData.Height = _Bmp.bmHeight;

	DeleteObject(_hBmp);

	return true;
}



char* WordleAPI::GL::LoadShaderSourceFromResource(HINSTANCE _hInstance, size_t _ResName)
{
	HRSRC _hResource = FindResource(_hInstance, MAKEINTRESOURCE(_ResName), MAKEINTRESOURCE(WORDLEAPI_SHADER_RES));

	if (!_hResource)
	{
		return nullptr;
	}

	size_t _Len = SizeofResource(_hInstance, _hResource);

	if (!_Len)
	{
		return nullptr;
	}

	HGLOBAL _hGlobal = LoadResource(_hInstance, _hResource);

	if (!_hGlobal)
	{
		return nullptr;
	}

	const unsigned char* _ResourcePtr = (const unsigned char*)(LockResource(_hGlobal));

	if (!_ResourcePtr)
	{
		FreeResource(_hGlobal);
		return nullptr;
	}

	char* _Buff = new char[_Len + 1];

	if (!_Buff)
	{
		UnlockResource(_hGlobal);
		FreeResource(_hGlobal);
		return nullptr;
	}

	_Buff[_Len] = '\0';

	for (size_t _Index = 0; _Index < _Len; _Index++)
	{
		_Buff[_Index] = _ResourcePtr[_Index];
	}

	UnlockResource(_hGlobal);
	FreeResource(_hGlobal);

	return _Buff;
}
