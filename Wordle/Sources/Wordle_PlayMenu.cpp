#include "..\Headers\Wordle.hpp"



Wordle::PlayMenu::PlayMenu() : WordleAPI::Menu()
{

}

Wordle::PlayMenu::~PlayMenu()
{

}

void Wordle::PlayMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void Wordle::PlayMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::PlayMenu::Stop()
{

}

void Wordle::PlayMenu::Input()
{

}

void Wordle::PlayMenu::DeleteInputs()
{

}

void Wordle::PlayMenu::Keys()
{

}

void Wordle::PlayMenu::Mouse()
{

}

void Wordle::PlayMenu::Engine()
{

}

void Wordle::PlayMenu::Animations()
{

}

void Wordle::PlayMenu::FrameBuild()
{

}
