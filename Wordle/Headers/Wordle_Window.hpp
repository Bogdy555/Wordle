#ifndef Wordle_Window_hpp

#define Wordle_Window_hpp



#include "Wordle.hpp"



namespace Wordle
{

	namespace Window
	{

		struct UserData
		{
			std::mutex MutexContext;
			WordleAPI::GL::Context Context;

			std::mutex MutexClose;
			bool Close = false;

			std::mutex MutexError;
			bool Error = false;

			std::mutex MutexKeysPressed;
			bool KeysPressed[256];

			std::mutex MutexFocus;
			bool Focus = false;

			std::mutex MutexWndPlacement;
			WINDOWPLACEMENT WndPlacement = { 0 };

			std::mutex MutexWndRect;
			RECT WndRect = { 0 };

			std::mutex MutexFullScreen;
			bool FullScreen = false;

			std::mutex MutexHIcon;
			HICON hIcon = NULL;
		};

		bool Init(WordleAPI::Window* _Wnd);

		LRESULT CALLBACK WndProc(_In_ HWND _hWnd, _In_ UINT _Msg, _In_ WPARAM _wParam, _In_ LPARAM _lParam);

	}

}



#endif
