#ifndef WordleAPI_Menu_hpp

#define WordleAPI_Menu_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	class Menu
	{

	public:

		Menu();
		Menu(const Menu& _Other) = delete;
		Menu(Menu&& _Other) noexcept = delete;
		virtual ~Menu();

		virtual const uint64_t GetMenuType() const;

		const bool CheckOn() const;
		const uint64_t GetNextMenu() const;
		const uint64_t GetQueuedMenu() const;

		Application* GetApplicationObj();
		const Application* GetApplicationObj() const;

		Menu* GetPreviousMenuObj();
		const Menu* GetPreviousMenuObj() const;

		Time::Timer& GetFrameTime(const size_t _Index);
		const Time::Timer& GetFrameTime(const size_t _Index) const;
		const float GetTimeStep() const;
		const float GetTimeStepRatio() const;
		const float GetLagTime() const;
		const uint64_t GetSync() const;

		void TurnOn();
		void Close(const uint64_t _NextMenu = _NullMenu);
		void SetQueuedMenu(const uint64_t _QueuedMenu);

		void BindApplication(Application* _ApplicationObj);

		void UpdateCurrentFrameTime();
		void SetTimeStep(const float _TimeStep = 1.0f / 60.0f);
		void SetLagTime(const float _LagTime = 1.0f / 10.0f);
		void SetSync(const uint64_t _Sync = 60);

		void Run(Application* _ApplicationObj);

		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;

		void operator= (const Menu& _Other) = delete;
		void operator= (Menu&& _Other) noexcept = delete;

	protected:

		virtual void Input() = 0;
		virtual void DeleteInputs() = 0;
		virtual void Keys() = 0;
		virtual void Mouse() = 0;
		virtual void Controller() = 0;
		virtual void Engine() = 0;
		virtual void Sound() = 0;
		virtual void Rumble() = 0;
		virtual void Animations() = 0;
		virtual void FrameBuild() = 0;
		virtual void QueuedMenus() = 0;

	private:

		bool On;
		uint64_t NextMenu;
		uint64_t QueuedMenu;

		Application* ApplicationObj;
		Menu* PreviousMenuObj;

	};

}



#endif
