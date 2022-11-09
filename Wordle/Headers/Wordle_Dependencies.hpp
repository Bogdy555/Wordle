#ifndef Wordle_Dependencies_hpp

#define Wordle_Dependencies_hpp



#pragma comment(lib, "WordleAPI.lib")



#pragma pack(pop)



#include <WordleAPI.hpp>



#pragma pack(push, 1)



namespace Wordle
{

	enum _Menus : uint64_t
	{
		_MainMenu = 1,
		_PlayMenu = 2,
		_BotMenu = 3
	};

	struct WindowUserData;

	class Application;

	class MainMenu;

	class PlayMenu;

	class BotMenu;

}



#endif
