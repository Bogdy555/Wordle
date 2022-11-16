#include "..\Headers\WordleAPI.hpp"



WordleAPI::Bot::Bot() : DatabaseCuvinte()
{

}

WordleAPI::Bot::Bot(const Bot& _Other) : DatabaseCuvinte(_Other.DatabaseCuvinte)
{

}

WordleAPI::Bot::Bot(Bot&& _Other) noexcept : DatabaseCuvinte(std::move(_Other.DatabaseCuvinte))
{

}

WordleAPI::Bot::~Bot()
{

}

void WordleAPI::Bot::Init(const std::vector<std::vector<char>>& _DatabaseCuvinte)
{
	DatabaseCuvinte = _DatabaseCuvinte;
}

void WordleAPI::Bot::Destroy()
{
	DatabaseCuvinte.clear();
}

const std::vector<char> WordleAPI::Bot::GetGuess()
{
	return DatabaseCuvinte[0];
}

void WordleAPI::Bot::SendFeedback(const std::vector<uint8_t>& _Feedback, const std::vector<char>& _Guess)
{
	for (size_t _Index = 0; _Index < 5; _Index++)
	{
		switch (_Feedback[_Index])
		{
		case _Wrong:
		{
			for (size_t _IndexDatabase = 0; _IndexDatabase < DatabaseCuvinte.size(); _IndexDatabase++)
			{
				if (DatabaseCuvinte[_IndexDatabase][0] == _Guess[_Index] || DatabaseCuvinte[_IndexDatabase][1] == _Guess[_Index] || DatabaseCuvinte[_IndexDatabase][2] == _Guess[_Index] || DatabaseCuvinte[_IndexDatabase][3] == _Guess[_Index] || DatabaseCuvinte[_IndexDatabase][4] == _Guess[_Index])
				{
					DatabaseCuvinte.erase(DatabaseCuvinte.begin() + _IndexDatabase);
				}
			}

			break;
		}
		case _Exists:
		{
			for (size_t _IndexDatabase = 0; _IndexDatabase < DatabaseCuvinte.size(); _IndexDatabase++)
			{
				if (DatabaseCuvinte[_IndexDatabase][0] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][1] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][2] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][3] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][4] != _Guess[_Index])
				{
					DatabaseCuvinte.erase(DatabaseCuvinte.begin() + _IndexDatabase);
				}
			}

			break;
		}
		case _Right:
		{
			for (size_t _IndexDatabase = 0; _IndexDatabase < DatabaseCuvinte.size(); _IndexDatabase++)
			{
				if (DatabaseCuvinte[_IndexDatabase][_Index] != _Guess[_Index])
				{
					DatabaseCuvinte.erase(DatabaseCuvinte.begin() + _IndexDatabase);
				}
			}

			break;
		}
		default:
		{
			break;
		}
		}
	}

	for (size_t _Index = 0; _Index < DatabaseCuvinte.size(); _Index++)
	{
		if (DatabaseCuvinte[_Index] == _Guess)
		{
			DatabaseCuvinte.erase(DatabaseCuvinte.begin() + _Index);
			break;
		}
	}
}

void WordleAPI::Bot::operator= (const Bot& _Other)
{
	DatabaseCuvinte = DatabaseCuvinte;
}

void WordleAPI::Bot::operator= (Bot&& _Other) noexcept
{
	DatabaseCuvinte = std::move(DatabaseCuvinte);
}
