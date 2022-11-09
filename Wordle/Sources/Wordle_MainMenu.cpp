#include "..\Headers\Wordle.hpp"



Wordle::MainMenu::MainMenu() : WordleAPI::Menu()
{

}

Wordle::MainMenu::~MainMenu()
{

}

void Wordle::MainMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void Wordle::MainMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Engine();
	Animations();
	FrameBuild();
}

void Wordle::MainMenu::Stop()
{

}

void Wordle::MainMenu::Input()
{

}

void Wordle::MainMenu::DeleteInputs()
{

}

void Wordle::MainMenu::Keys()
{

}

void Wordle::MainMenu::Mouse()
{

}

void Wordle::MainMenu::Engine()
{

}

void Wordle::MainMenu::Animations()
{

}

void Wordle::MainMenu::FrameBuild()
{

}
