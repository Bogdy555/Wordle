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
