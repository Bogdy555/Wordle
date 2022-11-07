#include "..\Headers\WordleAPI.hpp"



WordleAPI::Application::Application() :
	On(false), ReturnValue(_ReturnError),
	CurrentMenu(_NullMenu), CurrentMenuObj(nullptr),
	SharedInstanceMemory(), SharedInstanceMutex(),
	FrameTime(), TimeStep(1.0f / 60.0f), LagTime(1.0f / 10.0f), Sync(60),
	hInstance(NULL), CmdLine(nullptr), ShowCmd(SW_HIDE)
{

}

WordleAPI::Application::~Application()
{

}

const bool WordleAPI::Application::CheckOn() const
{
	return On;
}

const int32_t WordleAPI::Application::GetReturnValue() const
{
	return ReturnValue;
}

const uint64_t WordleAPI::Application::GetCurrentMenu() const
{
	return CurrentMenu;
}

WordleAPI::Menu* WordleAPI::Application::GetCurrentMenuObj()
{
	return CurrentMenuObj;
}

const WordleAPI::Menu* WordleAPI::Application::GetCurrentMenuObj() const
{
	return CurrentMenuObj;
}

WordleAPI::Multiprocessing::SharedMemory& WordleAPI::Application::GetSharedInstanceMemory()
{
	return SharedInstanceMemory;
}

const WordleAPI::Multiprocessing::SharedMemory& WordleAPI::Application::GetSharedInstanceMemory() const
{
	return SharedInstanceMemory;
}

WordleAPI::Multiprocessing::SharedMutex& WordleAPI::Application::GetSharedInstanceMutex()
{
	return SharedInstanceMutex;
}

const WordleAPI::Multiprocessing::SharedMutex& WordleAPI::Application::GetSharedInstanceMutex() const
{
	return SharedInstanceMutex;
}

WordleAPI::Time::Timer& WordleAPI::Application::GetFrameTime(const size_t _Index)
{
	return FrameTime[_Index];
}

const WordleAPI::Time::Timer& WordleAPI::Application::GetFrameTime(const size_t _Index) const
{
	return FrameTime[_Index];
}

const float WordleAPI::Application::GetTimeStep() const
{
	return TimeStep;
}

const float WordleAPI::Application::GetTimeStepRatio() const
{
	if (LagTime != 0.0f && FrameTime[_Previous] >= LagTime)
	{
		return 1.0f;
	}
	return FrameTime[_Previous] / TimeStep;
}

const float WordleAPI::Application::GetLagTime() const
{
	return LagTime;
}

const uint64_t WordleAPI::Application::GetSync() const
{
	return Sync;
}

const HINSTANCE WordleAPI::Application::GetHInstance() const
{
	return hInstance;
}

const LPWSTR WordleAPI::Application::GetCmdLine() const
{
	return CmdLine;
}

const int WordleAPI::Application::GetShowCmd() const
{
	return ShowCmd;
}

const size_t WordleAPI::Application::GetArgC() const
{
	return __argc;
}

const wchar_t* WordleAPI::Application::GetWArgV(const size_t _Index) const
{
	return __wargv[_Index];
}

void WordleAPI::Application::TurnOn()
{
	On = true;
}

void WordleAPI::Application::Close(const int32_t _ReturnValue)
{
	On = false;
	ReturnValue = _ReturnValue;
}

void WordleAPI::Application::SetCurrentMenu(const uint64_t _CurrentMenu)
{
	CurrentMenu = _CurrentMenu;
}

void WordleAPI::Application::SetCurrentMenuObj(Menu* _CurrentMenuObj)
{
	CurrentMenuObj = _CurrentMenuObj;
}

void WordleAPI::Application::UpdateCurrentFrameTime()
{
	FrameTime[_Current].Stop();
}

void WordleAPI::Application::SetTimeStep(const float _TimeStep)
{
	TimeStep = _TimeStep;
}

void WordleAPI::Application::SetLagTime(const float _LagTime)
{
	LagTime = _LagTime;
}

void WordleAPI::Application::SetSync(const uint64_t _Sync)
{
	Sync = _Sync;
}

int32_t WordleAPI::Application::Run(const HINSTANCE _hInstance, const LPWSTR _CmdLine, const int _ShowCmd, const wchar_t* _SharedMemoryAndMutexName)
{
	if (!_SharedMemoryAndMutexName)
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return _ReturnError;
	}

	if (!SharedInstanceMutex.Create(_SharedMemoryAndMutexName))
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return _ReturnError;
	}

	if (!SharedInstanceMemory.Create(_SharedMemoryAndMutexName, 1))
	{
		SharedInstanceMutex.Destroy();
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return _ReturnError;
	}

	SharedInstanceMutex.Lock();
	*SharedInstanceMemory = *SharedInstanceMemory + 1;
	SharedInstanceMutex.Unlock();

	On = false;
	ReturnValue = _ReturnError;
	CurrentMenu = _NullMenu;
	CurrentMenuObj = nullptr;
	FrameTime[_Previous].Reset();
	FrameTime[_Current].Reset();
	TimeStep = 1.0f / 60.0f;
	LagTime = 1.0f / 10.0f;
	Sync = 60;
	hInstance = _hInstance;
	CmdLine = _CmdLine;
	ShowCmd = _ShowCmd;

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	On = false;
	CurrentMenu = _NullMenu;
	CurrentMenuObj = nullptr;
	FrameTime[_Previous].Reset();
	FrameTime[_Current].Reset();
	TimeStep = 1.0f / 60.0f;
	LagTime = 1.0f / 10.0f;
	Sync = 60;
	hInstance = NULL;
	CmdLine = nullptr;
	ShowCmd = SW_HIDE;

	SharedInstanceMutex.Lock();
	*SharedInstanceMemory = *SharedInstanceMemory - 1;
	SharedInstanceMutex.Unlock();

	SharedInstanceMemory.Destroy();
	SharedInstanceMutex.Destroy();

	if (ReturnValue == _ReturnError)
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
	}

	return ReturnValue;
}
