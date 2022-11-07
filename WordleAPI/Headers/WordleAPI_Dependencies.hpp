#ifndef WordleAPI_Dependencies_hpp

#define WordleAPI_Dependencies_hpp



#pragma comment(lib, "WinMM.lib")



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



#include "WordleAPI_Macros.hpp"



namespace WordleAPI
{

	namespace Debug
	{



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

	namespace GL
	{

		class Context;

	}

}



#endif
