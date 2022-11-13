#include "..\Headers\Wordle.hpp"



bool Wordle::Window::Init(WordleAPI::Window* _Wnd)
{
	if (!_Wnd)
	{
		return false;
	}

	Wordle::Window::UserData* _UserData = (Wordle::Window::UserData*)(_Wnd->GetUserData());

	if (!_UserData)
	{
		return false;
	}

	if (!_UserData->Context.Create(_Wnd))
	{
		return false;
	}

	return true;
}



LRESULT CALLBACK Wordle::Window::WndProc(_In_ HWND _hWnd, _In_ UINT _Msg, _In_ WPARAM _wParam, _In_ LPARAM _lParam)
{
	WordleAPI::Window* _Wnd = WordleAPI::Window::GetWindowPtr(_hWnd);

	if (!_Wnd)
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}

	Wordle::Window::UserData* _UserData = (Wordle::Window::UserData*)(_Wnd->GetUserData());

	if (!_UserData)
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}

	switch (_Msg)
	{
	case WM_CLOSE:
	{
		_UserData->MutexClose.lock();

		_UserData->Close = true;

		_UserData->MutexClose.unlock();

		break;
	}
	case WM_GETMINMAXINFO:
	{
		RECT _ClientAndWindowRect = { 0 };

		_ClientAndWindowRect.left = 0;
		_ClientAndWindowRect.right = 800;
		_ClientAndWindowRect.top = 0;
		_ClientAndWindowRect.bottom = 450;

		_UserData->MutexFullScreen.lock();

		if (_UserData->FullScreen)
		{
			AdjustWindowRectEx(&_ClientAndWindowRect, WS_POPUP, FALSE, NULL);
		}
		else
		{
			AdjustWindowRectEx(&_ClientAndWindowRect, WS_OVERLAPPEDWINDOW, FALSE, NULL);
		}

		_UserData->MutexFullScreen.unlock();

		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = _ClientAndWindowRect.right - _ClientAndWindowRect.left;
		_MinMaxInfo->ptMinTrackSize.y = _ClientAndWindowRect.bottom - _ClientAndWindowRect.top;

		break;
	}
	case WM_KEYDOWN:
	{
		_UserData->MutexKeysPressed.lock();

		_UserData->KeysPressed[_wParam] = true;

		_UserData->MutexKeysPressed.unlock();

		break;
	}
	case WM_KEYUP:
	{
		_UserData->MutexKeysPressed.lock();

		_UserData->KeysPressed[_wParam] = false;

		_UserData->MutexKeysPressed.unlock();

		break;
	}
	case WM_SETFOCUS:
	{
		_UserData->MutexFocus.lock();

		_UserData->Focus = true;

		_UserData->MutexFocus.unlock();

		break;
	}
	case WM_KILLFOCUS:
	{
		_UserData->MutexFocus.lock();

		_UserData->Focus = false;

		_UserData->MutexFocus.unlock();

		_UserData->MutexKeysPressed.lock();

		for (unsigned int _Index = 0; _Index < 256; _Index++)
		{
			_UserData->KeysPressed[_Index] = false;
		}

		_UserData->MutexKeysPressed.unlock();

		break;
	}
	case WM_CHAR:
	{
		_UserData->MutexChar.lock();

		_UserData->Char.push_back((char)(_wParam));

		_UserData->MutexChar.unlock();

		break;
	}
	case WM_ERASEBKGND:
	{
		break;
	}
	case WM_PAINT:
	{
		break;
	}
	default:
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	}

	return 0;
}
