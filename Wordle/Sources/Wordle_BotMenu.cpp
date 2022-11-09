#include "..\Headers\Wordle.hpp"



Wordle::BotMenu::BotMenu() : WordleAPI::Menu()
{

}

Wordle::BotMenu::~BotMenu()
{

}

void Wordle::BotMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void Wordle::BotMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::BotMenu::Stop()
{

}

void Wordle::BotMenu::Input()
{

}

void Wordle::BotMenu::DeleteInputs()
{

}

void Wordle::BotMenu::Keys()
{

}

void Wordle::BotMenu::Mouse()
{

}

void Wordle::BotMenu::Engine()
{

}

void Wordle::BotMenu::Animations()
{

}

void Wordle::BotMenu::FrameBuild()
{

}
