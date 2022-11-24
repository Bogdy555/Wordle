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
	WordHas.reset();
	for (size_t _Index = 0; _Index < 5; ++_Index)
	{
		NotOnPos[_Index].reset();
	}
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

// TO BE CHANGED
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

				if (curr[i] == _Guess[i])
					found = false;

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
			if (_Guess[_IndexI] == _Guess[_IndexJ])
			{
				if (_Pattern[_IndexI] == _Wrong && _Pattern[_IndexJ] != _Wrong || (_Pattern[_IndexI] != _Wrong && _Pattern[_IndexJ] == _Wrong))
				{
					return false;
				}
			}
		}
	}

	for (size_t _Index = 0; _Index < _Guess.size(); ++_Index)
	{
		if (_Pattern[_Index] == _Wrong && WordHas[_Guess[_Index] - 'A'])
		{
			return false;
		}

		if (_Pattern[_Index] != _Wrong && NotOnPos[_Index][_Guess[_Index] - 'A'])
		{
			return false;
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

		double_t _Probability = (double_t)_NumOfRemWords / DatabaseCuvinte.size();
		double_t _InformationQuantity = -log2(_Probability);

		_CurrentEntropy += _Probability * _InformationQuantity;
	}

	return _CurrentEntropy;
}

const std::vector<char> WordleAPI::Bot::GetGuess()
{
	if (FirstGuess) 
	{
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
	std::vector<std::vector<char> > _NewList;
	for (size_t _WordIndex = 0; _WordIndex < DatabaseCuvinte.size(); ++_WordIndex) 
	{
		bool _ValidWord = true;
		for (size_t _FeedbackIndex = 0; _FeedbackIndex < _Feedback.size() && _ValidWord; ++_FeedbackIndex) 
		{
			switch (_Feedback[_FeedbackIndex])
			{
			case _Wrong:
			{
				for (size_t _LetterIndex = 0; _LetterIndex < DatabaseCuvinte[_WordIndex].size(); ++_LetterIndex)
				{
					if (DatabaseCuvinte[_WordIndex][_LetterIndex] == _Guess[_FeedbackIndex])
					{
						_ValidWord = false;
						break;
					}
				}
				break;
			}
			case _Exists:
			{
				WordHas[_Guess[_FeedbackIndex] - 'A'] = 1;
				NotOnPos[_FeedbackIndex][_Guess[_FeedbackIndex] - 'A'] = 1;
				bool _FoundLetter = false;
				for (size_t _LetterIndex = 0; _LetterIndex < DatabaseCuvinte[_WordIndex].size(); ++_LetterIndex)
				{
					if (DatabaseCuvinte[_WordIndex][_LetterIndex] == _Guess[_FeedbackIndex])
					{
						_FoundLetter = true;
						break;
					}
				}

				if (!_FoundLetter || DatabaseCuvinte[_WordIndex][_FeedbackIndex] == _Guess[_FeedbackIndex])
				{
					_ValidWord = false;
				}
				break;
			}
			case _Right: 
			{
				WordHas[_Guess[_FeedbackIndex] - 'A'] = 1;
				if (DatabaseCuvinte[_WordIndex][_FeedbackIndex] != _Guess[_FeedbackIndex])
				{
					_ValidWord = false;
				}
				break;
			}
			default: 
			{
				break;
			}
			}
		}

		if (_ValidWord)
		{
			_NewList.push_back(DatabaseCuvinte[_WordIndex]);
		}
	}

	DatabaseCuvinte = _NewList;
}

void WordleAPI::Bot::operator= (const Bot& _Other)
{
	DatabaseCuvinte = DatabaseCuvinte;
}

void WordleAPI::Bot::operator= (Bot&& _Other) noexcept
{
	DatabaseCuvinte = std::move(DatabaseCuvinte);
}
