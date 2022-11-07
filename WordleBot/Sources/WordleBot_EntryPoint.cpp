#include "..\Headers\WordleBot.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!WordleAPI::Time::Init())
	{
		return -1;
	}

	WORDLEAPI_DEBUG_CALL
	(
		if (!WordleAPI::Debug::Init())
		{
			WordleAPI::Time::Stop();
			return -1;
		}
	);

	WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());

	WordleAPI::Time::Stop();

	return 0;
}
