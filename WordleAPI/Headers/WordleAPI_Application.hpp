#ifndef WordleAPI_Application_hpp

#define WordleAPI_Application_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	class Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		virtual ~Application();

		const bool CheckOn() const;
		const int32_t GetReturnValue() const;

		const uint64_t GetCurrentMenu() const;
		Menu* GetCurrentMenuObj();
		const Menu* GetCurrentMenuObj() const;

		Multiprocessing::SharedMemory& GetSharedInstanceMemory();
		const Multiprocessing::SharedMemory& GetSharedInstanceMemory() const;
		Multiprocessing::SharedMutex& GetSharedInstanceMutex();
		const Multiprocessing::SharedMutex& GetSharedInstanceMutex() const;

		Time::Timer& GetFrameTime(const size_t _Index);
		const Time::Timer& GetFrameTime(const size_t _Index) const;
		const float GetTimeStep() const;
		const float GetTimeStepRatio() const;
		const float GetLagTime() const;
		const uint64_t GetSync() const;

		const HINSTANCE GetHInstance() const;
		const LPWSTR GetCmdLine() const;
		const int GetShowCmd() const;
		const size_t GetArgC() const;
		const wchar_t* GetWArgV(const size_t _Index) const;

		void TurnOn();
		void Close(const int32_t _ReturnValue);

		void SetCurrentMenu(const uint64_t _CurrentMenu);
		void SetCurrentMenuObj(Menu* _CurrentMenuObj);

		void UpdateCurrentFrameTime();
		void SetTimeStep(const float _TimeStep = 1.0f / 60.0f);
		void SetLagTime(const float _LagTime = 1.0f / 10.0f);
		void SetSync(const uint64_t _Sync = 60);

		int32_t Run(const HINSTANCE _hInstance, const LPWSTR _CmdLine, const int _ShowCmd, const wchar_t* _SharedMemoryName, const wchar_t* _SharedMutexName);

		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool On;
		int32_t ReturnValue;

		uint64_t CurrentMenu;
		Menu* CurrentMenuObj;

		Multiprocessing::SharedMemory SharedInstanceMemory;
		Multiprocessing::SharedMutex SharedInstanceMutex;

		Time::Timer FrameTime[2];
		float TimeStep;
		float LagTime;
		uint64_t Sync;

		HINSTANCE hInstance;
		LPWSTR CmdLine;
		int ShowCmd;

	};

}



#endif
