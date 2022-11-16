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

	{
		WordleAPI::Multiprocessing::SharedMutex _Mutex;
		WordleAPI::Multiprocessing::SharedMemory _Memory;

		if (!_Mutex.Create(L"WordleMutex"))
		{
			WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());
			WordleAPI::Time::Stop();
			return -1;
		}

		if (!_Memory.Create(L"WordleMemory", 1))
		{
			_Mutex.Destroy();
			WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());
			WordleAPI::Time::Stop();
			return -1;
		}

		_Mutex.Lock();

		if (!*_Memory)
		{
			_Mutex.Unlock();
			_Memory.Destroy();
			_Mutex.Destroy();
			WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());
			WordleAPI::Time::Stop();
			return -1;
		}

		_Mutex.Unlock();

		_Memory.Destroy();
		_Mutex.Destroy();
	}

	WordleAPI::Multiprocessing::SharedMutex _SharedMutex;
	WordleAPI::Multiprocessing::SharedMemory _SharedMemory;

	if (!_SharedMutex.Create(L"WordleBotComunicationMutex"))
	{
		WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());
		WordleAPI::Time::Stop();
		return -1;
	}

	if (!_SharedMemory.Create(L"WordleBotComunicationMemory", 6))
	{
		_SharedMutex.Destroy();
		WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());
		WordleAPI::Time::Stop();
		return -1;
	}

	const std::vector<std::vector<char>> _Database = WordleBot::LoadDatabase(_hInstance);

	WordleAPI::Bot _Bot;

	_Bot.Init(_Database);



	while (true)
	{
		const std::vector<char> _Guess = _Bot.GetGuess();

		_SharedMutex.Lock();

		_SharedMemory[0] = WordleAPI::_WordState;

		_SharedMemory[1] = _Guess[0];
		_SharedMemory[2] = _Guess[1];
		_SharedMemory[3] = _Guess[2];
		_SharedMemory[4] = _Guess[3];
		_SharedMemory[5] = _Guess[4];

		_SharedMutex.Unlock();



		_SharedMutex.Lock();

		while (_SharedMemory[0] == WordleAPI::_WordState)
		{
			_SharedMutex.Unlock();

			WordleAPI::Time::SleepMicroSec(1);

			_SharedMutex.Lock();
		}

		_SharedMutex.Unlock();



		_SharedMutex.Lock();

		if (_SharedMemory[0] != WordleAPI::_FeedbackState)
		{
			break;
		}

		std::vector<uint8_t> _Feedback;

		_Feedback.push_back(_SharedMemory[1]);
		_Feedback.push_back(_SharedMemory[2]);
		_Feedback.push_back(_SharedMemory[3]);
		_Feedback.push_back(_SharedMemory[4]);
		_Feedback.push_back(_SharedMemory[5]);

		_SharedMutex.Unlock();

		if (_Feedback[0] == WordleAPI::_Right && _Feedback[1] == WordleAPI::_Right && _Feedback[2] == WordleAPI::_Right && _Feedback[3] == WordleAPI::_Right && _Feedback[4] == WordleAPI::_Right)
		{
			_Bot.Destroy();
			_Bot.Init(_Database);
		}
		else
		{
			_Bot.SendFeedback(_Feedback, _Guess);
		}
	}



	_Bot.Destroy();

	_SharedMemory.Destroy();

	_SharedMutex.Destroy();

	WORDLEAPI_DEBUG_CALL(WordleAPI::Debug::Stop());

	WordleAPI::Time::Stop();

	return 0;
}
