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

		bool KeysPressed[256][2];

	};

}



#endif
