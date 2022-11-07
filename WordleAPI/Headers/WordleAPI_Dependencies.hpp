#ifndef WordleAPI_Dependencies_hpp

#define WordleAPI_Dependencies_hpp



#pragma comment(lib, "WinMM.lib")



#pragma pack(pop)



#include "WordleAPI_WinTargetVer.hpp"
#include <Windows.h>

#include <iostream>
#include <fstream>

#include <cstring>
#include <string>

#include <vector>

#include <chrono>

#include <thread>
#include <future>
#include <mutex>
#include <atomic>

#define _USE_MATH_DEFINES
#include <math.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>



#pragma pack(push, 1)



#include "WordleAPI_Macros.hpp"



namespace WordleAPI
{

	enum _States : size_t
	{
		_Previous = 0,
		_Current = 1
	};

	enum _ReturnValues : const int32_t
	{
		_ReturnError = -1,
		_ReturnNoError = 0,
		_ReturnStillRunning = 259
	};

	enum _Menus : const uint64_t
	{
		_NullMenu = 0
	};

	enum _ConsoleTxtColor : const uint16_t
	{
		_ConsoleTxtBlack = 0,
		_ConsoleTxtBlue = 1,
		_ConsoleTxtGreen = 2,
		_ConsoleTxtAqua = 3,
		_ConsoleTxtRed = 4,
		_ConsoleTxtPurple = 5,
		_ConsoleTxtYellow = 6,
		_ConsoleTxtLightGrey = 7,
		_ConsoleTxtGrey = 8,
		_ConsoleTxtLightBlue = 9,
		_ConsoleTxtLightGreen = 10,
		_ConsoleTxtTurquoise = 11,
		_ConsoleTxtPink = 12,
		_ConsoleTxtLightPurple = 13,
		_ConsoleTxtLightYellow = 14,
		_ConsoleTxtWhite = 15
	};

	enum _ConsoleBkgColor : const uint16_t
	{
		_ConsoleBkgBlack = 0,
		_ConsoleBkgBlue = 16,
		_ConsoleBkgGreen = 32,
		_ConsoleBkgAqua = 48,
		_ConsoleBkgRed = 64,
		_ConsoleBkgPurple = 80,
		_ConsoleBkgYellow = 96,
		_ConsoleBkgLightGrey = 112,
		_ConsoleBkgGrey = 128,
		_ConsoleBkgLightBlue = 144,
		_ConsoleBkgLightGreen = 160,
		_ConsoleBkgTurquoise = 176,
		_ConsoleBkgPink = 192,
		_ConsoleBkgLightPurple = 208,
		_ConsoleBkgLightYellow = 224,
		_ConsoleBkgWhite = 240
	};

	typedef const tm& ConstTimeRef;

	typedef const bool& ConstBoolRef;

	typedef const TIMECAPS& ConstTimeCapsRef;

	typedef const HANDLE& ConstHandleRef;

	typedef const uint16_t& ConstUInt16Ref;

	namespace Debug
	{

		class Tree;

	}

	namespace Multiprocessing
	{

		class Process;

		class SharedMemory;

		class SharedMutex;

	}

	namespace Time
	{

		class Timer;

	}

	class Application;

	class Menu;

	class Window;

	typedef bool (*WindowInitFunc)(Window* _Wnd);

	struct WindowCreationDescriptor;

	namespace GL
	{

		class Context;

	}

}



#endif
