#ifndef Wordle_PlayMenu_hpp

#define Wordle_PlayMenu_hpp



#include "Wordle.hpp"



namespace Wordle
{

	class PlayMenu : public WordleAPI::Menu
	{

	public:

		PlayMenu();
		PlayMenu(const PlayMenu& _Other) = delete;
		PlayMenu(PlayMenu&& _Other) noexcept = delete;
		~PlayMenu();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const PlayMenu& _Other) = delete;
		void operator= (PlayMenu&& _Other) noexcept = delete;

	private:

		void Input() override;
		void DeleteInputs() override;
		void Keys() override;
		void Mouse() override;
		void Engine() override;
		void Animations() override;
		void FrameBuild() override;

		void RenderBackground(int32_t _Width, int32_t _Height);
		void RenderPreviousPreviousGuess(int32_t _Width, int32_t _Height);
		void RenderPreviousGuess(int32_t _Width, int32_t _Height);
		void RenderCurrentGuess(int32_t _Width, int32_t _Height);

		bool& GetKeysPressed(const size_t _Key, const size_t _Frame);
		const bool& GetKeysPressed(const size_t _Key, const size_t _Frame) const;

		size_t IndexPreviousPreviousGuess;
		size_t IndexPreviousGuess;
		size_t IndexCurrentGuess;

		std::vector<char> PreviousPreviousGuess;
		std::vector<char> PreviousGuess;
		std::vector<char> CurrentGuess;

		bool AnimationTrigger;
		bool AnimationIsActive;
		float AnimationTimeActive;
		WordleAPI::AnimationLerp<float, LerpFloat> Animation;

	};

}



#endif
