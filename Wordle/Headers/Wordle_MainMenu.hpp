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

		const uint64_t GetMenuType() const;

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

		void RenderBackground(const int32_t _Width, const int32_t _Height);
		void RenderTitle(const int32_t _Width, const int32_t _Height);
		void RenderConsoleInput(const int32_t _Width, const int32_t _Height);

		bool& GetKeysPressed(const size_t _Key, const size_t _Frame);
		const bool& GetKeysPressed(const size_t _Key, const size_t _Frame) const;

		std::vector<char> ConsoleInput;

		bool AnimationTrigger;
		bool AnimationIsActive;
		float AnimationTimeActive;
		WordleAPI::AnimationLerp<float, LerpFloat> Animation;

	};

}



#endif
