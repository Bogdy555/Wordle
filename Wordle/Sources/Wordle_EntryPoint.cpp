#include "..\Headers\Wordle.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!WordleAPI::Time::Init())
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	if (!WordleAPI::GL::Load())
	{
		WordleAPI::Time::Stop();
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	WORDLEAPI_DEBUG_CALL
	(
		if (!WordleAPI::Debug::Init())
		{
			WordleAPI::GL::Unload();
			WordleAPI::Time::Stop();
			MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
			return -1;
		}
	);

	Wordle::Application _Application;

	int32_t _ReturnVal = _Application.Run(_hInstance, _CmdLine, _ShowCmd, L"WordleMemory", L"WordleMutex");

	WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());

	WordleAPI::GL::Unload();

	WordleAPI::Time::Stop();

	return _ReturnVal;
}
