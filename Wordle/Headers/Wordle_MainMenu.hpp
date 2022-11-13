#ifndef Wordle_MainMenu_hpp

#define Wordle_MainMenu_hpp



#include "Wordle.hpp"



namespace Wordle
{

	class MainMenu : public WordleAPI::Menu
	{

	public:

		MainMenu();
		MainMenu(const MainMenu& _Other) = delete;
		MainMenu(MainMenu&& _Other) noexcept = delete;
		~MainMenu();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const MainMenu& _Other) = delete;
		void operator= (MainMenu&& _Other) noexcept = delete;

	private:

		void Input() override;
		void DeleteInputs() override;
		void Keys() override;
		void Mouse() override;
		void Engine() override;
		void Animations() override;
		void FrameBuild() override;

		void RenderBackground(int32_t _Width, int32_t _Height);
		void RenderTitle(int32_t _Width, int32_t _Height);
		void RenderConsoleInput(int32_t _Width, int32_t _Height);

		bool& GetKeysPressed(const size_t _Key, const size_t _Frame);
		const bool& GetKeysPressed(const size_t _Key, const size_t _Frame) const;

		std::vector<char> ConsoleInput;

	};

}



#endif
