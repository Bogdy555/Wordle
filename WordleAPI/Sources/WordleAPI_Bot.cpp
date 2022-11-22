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
	FirstGuess = true;
	std::vector<uint8_t> _CurrentPattern;
	GenerateFeedbacks(_CurrentPattern, _DatabaseCuvinte[0].size());
}

void WordleAPI::Bot::Destroy()
{
	DatabaseCuvinte.clear();
	PossibleFeedbacks.clear();
}

void WordleAPI::Bot::GenerateFeedbacks(std::vector<uint8_t> _CurrentPattern, uint16_t _WordSize)
{
	if (_CurrentPattern.size() == _WordSize)
	{
		PossibleFeedbacks.push_back(_CurrentPattern);
		return;
	}
		
	for (int _LetterFeedback = 0; _LetterFeedback < 3; ++_LetterFeedback)
	{
		_CurrentPattern.push_back(_LetterFeedback);
		GenerateFeedbacks(_CurrentPattern, _WordSize);
		_CurrentPattern.pop_back();
	}
}

int32_t WordleAPI::Bot::RemainingWords(std::vector<uint8_t> _Pattern, std::vector<char> _Guess) 
{
	uint32_t _DeletedWords = 0;
	for (std::vector <char> curr : DatabaseCuvinte) {
		bool validWord = true;
		for (int i = 0; i < _Pattern.size() && validWord; ++i) {
			if (_Pattern[i] == _Wrong) {
				for (char c : curr) {
					if (c == _Guess[i]) {
						validWord = false;
					}
				}
			}
			else if (_Pattern[i] == _Exists) {
				bool found = false;
				for (char c : curr)
					if (c == _Guess[i])
						found = true;

				if (!found)
					validWord = false;
			}
			else {
				if (curr[i] != _Guess[i])
					validWord = false;
			}
		}

		if (!validWord)
			++_DeletedWords;
	}

	return (DatabaseCuvinte.size() - _DeletedWords);
}

bool WordleAPI::Bot::ValidPattern(std::vector<uint8_t> _Pattern, std::vector<char> _Guess) 
{
	for (size_t _IndexI = 0; _IndexI < _Guess.size(); ++_IndexI)
	{
		for (size_t _IndexJ = 0; _IndexJ < _Guess.size(); ++_IndexJ)
		{
			if (_Guess[_IndexJ] == _Guess[_IndexJ])
			{
				if (_Pattern[_IndexI] == _Wrong && _Pattern[_IndexJ] != _Wrong || (_Pattern[_IndexI] != _Wrong && _Pattern[_IndexJ] == _Wrong))
				{
					return false;
				}
			}
		}
	}

	return true;
}

double_t WordleAPI::Bot::ComputeEntropy(std::vector<char> _Guess) 
{
	double_t _CurrentEntropy = 0;
	for (std::vector<uint8_t> _Feedback : PossibleFeedbacks)
	{
		if (!ValidPattern(_Feedback, _Guess))
		{
			continue;
		}

		int32_t _NumOfRemWords = RemainingWords(_Feedback, _Guess);

		if (!_NumOfRemWords)
		{
			continue;
		}
		if (!DatabaseCuvinte.size())
		{
			continue;
		}

		double_t _Probability = (double_t)_NumOfRemWords / DatabaseCuvinte.size();
		double_t _InformationQuantity = -log2(_Probability);

		_CurrentEntropy += _Probability * _InformationQuantity;
	}
	

	return _CurrentEntropy;
}

const std::vector<char> WordleAPI::Bot::GetGuess()
{
	std::cout << DatabaseCuvinte.size() << '\n';
	if (FirstGuess) {
		FirstGuess = false;
		return FIRST_GUESS;
	}

	if (DatabaseCuvinte.size() == 1)
	{
		return DatabaseCuvinte[0];
	}

	double_t _MaxEntropy = 0;
	std::vector<char> _Guess;
	for (size_t _Index = 0; _Index < DatabaseCuvinte.size(); ++_Index) 
	{
		double_t _CurrentEntropy = ComputeEntropy(DatabaseCuvinte[_Index]);

		if (_CurrentEntropy > _MaxEntropy)
		{
			_MaxEntropy = _CurrentEntropy;
			_Guess = DatabaseCuvinte[_Index];
		}
	}

	return _Guess;
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
				if (DatabaseCuvinte[_IndexDatabase][_Index] == _Guess[_Index]) 
				{
					DatabaseCuvinte.erase(DatabaseCuvinte.begin() + _IndexDatabase);
				}
				else if (DatabaseCuvinte[_IndexDatabase][0] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][1] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][2] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][3] != _Guess[_Index] && DatabaseCuvinte[_IndexDatabase][4] != _Guess[_Index])
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
}

void WordleAPI::Bot::operator= (const Bot& _Other)
{
	DatabaseCuvinte = DatabaseCuvinte;
}

void WordleAPI::Bot::operator= (Bot&& _Other) noexcept
{
	DatabaseCuvinte = std::move(DatabaseCuvinte);
}
