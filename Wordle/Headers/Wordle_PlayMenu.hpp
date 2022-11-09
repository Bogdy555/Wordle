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

	};

}



#endif
