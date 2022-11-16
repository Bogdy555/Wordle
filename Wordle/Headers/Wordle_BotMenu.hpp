#ifndef Wordle_BotMenu_hpp

#define Wordle_BotMenu_hpp



#include "Wordle.hpp"



namespace Wordle
{

	class BotMenu : public WordleAPI::Menu
	{

	public:

		BotMenu();
		BotMenu(const BotMenu& _Other) = delete;
		BotMenu(BotMenu&& _Other) noexcept = delete;
		~BotMenu();

		const uint64_t GetMenuType() const;

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const BotMenu& _Other) = delete;
		void operator= (BotMenu&& _Other) noexcept = delete;

	private:

		void Input() override;
		void DeleteInputs() override;
		void Keys() override;
		void Mouse() override;
		void Engine() override;
		void Animations() override;
		void FrameBuild() override;

		void RenderBackground(const int32_t _Width, const int32_t _Height);
		void RenderPreviousPreviousGuess(const int32_t _Width, const int32_t _Height);
		void RenderPreviousGuess(const int32_t _Width, const int32_t _Height);
		void RenderCurrentGuess(const int32_t _Width, const int32_t _Height);
		void RenderProgressBar(const int32_t _Width, const int32_t _Height);

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

		WordleAPI::Multiprocessing::Process BotProc;
		WordleAPI::Multiprocessing::SharedMemory BotSharedMemory;
		WordleAPI::Multiprocessing::SharedMutex BotSharedMutex;

		EXECUTION_STATE ExecutionState;

	};

}



#endif
