#include "..\Headers\WordleBot.hpp"



const std::vector<std::vector<char>> WordleBot::LoadDatabase(const HINSTANCE _hInstance)
{
	std::vector<std::vector<char>> _Database;

	HRSRC _hResource = FindResource(_hInstance, MAKEINTRESOURCE(WORDLEBOT_IDT_WORDLIST), MAKEINTRESOURCE(WORDLEAPI_TEXT_RES));

	if (!_hResource)
	{
		return std::vector<std::vector<char>>();
	}

	size_t _Len = SizeofResource(_hInstance, _hResource);

	if (!_Len || _Len % 7 != 0)
	{
		return std::vector<std::vector<char>>();
	}

	HGLOBAL _hGlobal = LoadResource(_hInstance, _hResource);

	if (!_hGlobal)
	{
		return std::vector<std::vector<char>>();
	}

	const unsigned char* _ResourcePtr = (const unsigned char*)(LockResource(_hGlobal));

	if (!_ResourcePtr)
	{
		FreeResource(_hGlobal);
		return std::vector<std::vector<char>>();
	}

	for (size_t _Index = 0; _Index < _Len / 7; _Index++)
	{
		_Database.push_back(std::vector<char>());
	}

	for (size_t _Index = 0; _Index < _Len; _Index++)
	{
		if (_Index % 7 < 5)
		{
			_Database[_Index / 7].push_back(_ResourcePtr[_Index]);
		}
	}

	UnlockResource(_hGlobal);
	FreeResource(_hGlobal);

	return _Database;
}
