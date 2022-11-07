#include "..\Headers\WordleAPI.hpp"



WordleAPI::Debug::Tree::Tree(const wchar_t* _Text, const uint16_t _Attribute, const bool _PrintKids) :
	Text(_Text), Attribute(_Attribute), PrintKids(_PrintKids), Kids()
{

}

WordleAPI::Debug::Tree::Tree(Tree&& _Other) noexcept :
	Text(_Other.Text), Attribute(_Other.Attribute), PrintKids(_Other.PrintKids), Kids(std::move(_Other.Kids))
{
	_Other.Text = nullptr;
	_Other.Attribute = 0;
	_Other.PrintKids = true;
}

WordleAPI::Debug::Tree::~Tree()
{

}

void WordleAPI::Debug::Tree::SetText(const wchar_t* _Text)
{
	Text = _Text;
}

void WordleAPI::Debug::Tree::SetAttribute(const uint16_t _Attribute)
{
	Attribute = _Attribute;
}

void WordleAPI::Debug::Tree::SetPrintKids(const bool _PrintKids)
{
	PrintKids = _PrintKids;
}

const wchar_t* WordleAPI::Debug::Tree::GetText() const
{
	return Text;
}

const unsigned short WordleAPI::Debug::Tree::GetAttribute() const
{
	return Attribute;
}

const bool WordleAPI::Debug::Tree::GetPrintKids() const
{
	return PrintKids;
}

std::vector<WordleAPI::Debug::Tree*>& WordleAPI::Debug::Tree::GetKids()
{
	return Kids;
}

const std::vector<WordleAPI::Debug::Tree*>& WordleAPI::Debug::Tree::GetKids() const
{
	return Kids;
}

const bool WordleAPI::Debug::Tree::LogToConsole(const uint64_t _Tab, const uint64_t _Level) const
{
	if (ConsoleOutHandle == INVALID_HANDLE_VALUE || ConsoleOutHandle == NULL)
	{
		return false;
	}

	if (!Text)
	{
		return false;
	}

	if (!SetTextAttribute(Attribute))
	{
		return false;
	}

	for (uint64_t i = 0; i < _Level * _Tab; i++)
	{
		std::wcout << L'\t';
	}

	std::wcout << Text << L'\n';

	if (PrintKids)
	{
		for (size_t i = 0; i < Kids.size(); i++)
		{
			if (!Kids[i]->LogToConsole(_Tab, _Level + 1))
			{
				return false;
			}
		}
	}

	return true;
}

const bool WordleAPI::Debug::Tree::LogToFile(std::wofstream* _FOut, const bool _LogAtribute, const uint64_t _Tab, const uint64_t _Level) const
{
	if (!_FOut)
	{
		return false;
	}

	if (!Text)
	{
		return false;
	}

	for (uint64_t i = 0; i < _Level * _Tab; i++)
	{
		*_FOut << L'\t';
	}

	if (_LogAtribute)
	{
		*_FOut << Attribute << L' ';
	}

	*_FOut << Text << L'\n';

	if (PrintKids)
	{
		for (size_t i = 0; i < Kids.size(); i++)
		{
			if (!Kids[i]->LogToFile(_FOut, _Tab, _Level + 1))
			{
				return false;
			}
		}
	}

	return true;
}

void WordleAPI::Debug::Tree::operator= (Tree&& _Other) noexcept
{
	Text = _Other.Text;
	Attribute = _Other.Attribute;
	PrintKids = _Other.PrintKids;
	Kids = std::move(_Other.Kids);

	_Other.Text = nullptr;
	_Other.Attribute = 0;
	_Other.PrintKids = true;
}



HANDLE _ConsoleOutHandle = NULL;
uint16_t _DefaultAttribute = 0;

const WordleAPI::ConstHandleRef WordleAPI::Debug::ConsoleOutHandle = _ConsoleOutHandle;
const WordleAPI::ConstUInt16Ref WordleAPI::Debug::DefaultAttribute = _DefaultAttribute;



void WordleAPI::Debug::Break(const wchar_t* _Msg)
{
	if (_Msg)
	{
		MessageBox(NULL, _Msg, L"Debug break!", MB_OK | MB_ICONERROR);
	}
	__debugbreak();
}

bool WordleAPI::Debug::Init()
{
	if (_ConsoleOutHandle != INVALID_HANDLE_VALUE && _ConsoleOutHandle != NULL)
	{
		return true;
	}

	_ConsoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		_ConsoleOutHandle = NULL;
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO _ConsoleInfo = { 0 };
	if (!GetConsoleScreenBufferInfo(_ConsoleOutHandle, &_ConsoleInfo))
	{
		CloseHandle(_ConsoleOutHandle);
		_ConsoleOutHandle = NULL;
		return false;
	}

	_DefaultAttribute = _ConsoleInfo.wAttributes;

	return true;
}

void WordleAPI::Debug::Stop()
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		return;
	}

	SetTextAttribute(_DefaultAttribute);
	_DefaultAttribute = 0;

	CloseHandle(_ConsoleOutHandle);
	_ConsoleOutHandle = NULL;
}

bool WordleAPI::Debug::GetConsoleAttribute(uint16_t& _Attribute)
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		return false;
	}
	CONSOLE_SCREEN_BUFFER_INFO _ConsoleInfo = { 0 };
	if (!GetConsoleScreenBufferInfo(_ConsoleOutHandle, &_ConsoleInfo))
	{
		return false;
	}
	_Attribute = _ConsoleInfo.wAttributes;
	return true;
}

bool WordleAPI::Debug::SetTextAttribute(const uint16_t _Attribute)
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		return false;
	}
	return SetConsoleTextAttribute(_ConsoleOutHandle, _Attribute);
}
