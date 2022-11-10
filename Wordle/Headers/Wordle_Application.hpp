#ifndef Wordle_Application_hpp

#define Wordle_Application_hpp



#include "Wordle.hpp"



namespace Wordle
{

	class Application : public WordleAPI::Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		~Application();

		WordleAPI::Window& GetWnd();
		const WordleAPI::Window& GetWnd() const;

		Window::UserData& GetWndUserData();
		const Window::UserData& GetWndUserData() const;

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool InitWindow();
		void DestroyWindow();

		WordleAPI::Window Wnd;
		Window::UserData WndUserData;

	};

}



#endif
