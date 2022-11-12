#ifndef WordleAPI_Debug_hpp

#define WordleAPI_Debug_hpp



#include "WordleAPI.hpp"



#ifdef UNICODE

#define WORDLEAPI_STRING(X) L ## X

#endif

#ifndef UNICODE

#define WORDLEAPI_STRING(X) X

#endif



#define WORDLEAPI_PRINT_A(X) std::cout << X
#define WORDLEAPI_PRINT_W(X) std::wcout << X

#ifdef UNICODE

#define WORDLEAPI_PRINT(X) WORDLEAPI_PRINT_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_PRINT(X) WORDLEAPI_PRINT_A(X)

#endif

#define WORDLEAPI_PRINT_LINE_A(X) std::cout << X << '\n'
#define WORDLEAPI_PRINT_LINE_W(X) std::wcout << X << L'\n'

#ifdef UNICODE

#define WORDLEAPI_PRINT_LINE(X) WORDLEAPI_PRINT_LINE_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_PRINT_LINE(X) WORDLEAPI_PRINT_LINE_A(X)

#endif



#ifdef _DEBUG

#define WORDLEAPI_LOG_A(X) std::cout << X
#define WORDLEAPI_LOG_W(X) std::wcout << X

#ifdef UNICODE

#define WORDLEAPI_LOG(X) WORDLEAPI_LOG_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_LOG(X) WORDLEAPI_LOG_A(X)

#endif

#define WORDLEAPI_LOG_LINE_A(X) std::cout << X << '\n'
#define WORDLEAPI_LOG_LINE_W(X) std::wcout << X << L'\n'

#ifdef UNICODE

#define WORDLEAPI_LOG_LINE(X) WORDLEAPI_LOG_LINE_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_LOG_LINE(X) WORDLEAPI_LOG_LINE_A(X)

#endif

#endif

#ifndef _DEBUG

#define WORDLEAPI_LOG_A(X)
#define WORDLEAPI_LOG_W(X)
#define WORDLEAPI_LOG(X)

#define WORDLEAPI_LOG_LINE_A(X)
#define WORDLEAPI_LOG_LINE_W(X)
#define WORDLEAPI_LOG_LINE(X)

#endif



#ifdef _DEBUG

#define WORDLEAPI_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)
#define WORDLEAPI_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)

#ifdef UNICODE

#define WORDLEAPI_OUTPUT_DEBUG_STR(X) WORDLEAPI_OUTPUT_DEBUG_STR_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_OUTPUT_DEBUG_STR(X) WORDLEAPI_OUTPUT_DEBUG_STR_A(X)

#endif

#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")
#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")

#ifdef UNICODE

#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE(X) WORDLEAPI_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef UNICODE

#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE(X) WORDLEAPI_OUTPUT_DEBUG_STR_LINE_A(X)

#endif

#endif

#ifndef _DEBUG

#define WORDLEAPI_OUTPUT_DEBUG_STR_A(X)
#define WORDLEAPI_OUTPUT_DEBUG_STR_W(X)
#define WORDLEAPI_OUTPUT_DEBUG_STR(X)

#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE_A(X)
#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE_W(X)
#define WORDLEAPI_OUTPUT_DEBUG_STR_LINE(X)

#endif



#ifdef _DEBUG

#define WORDLEAPI_DEBUG_BREAK() WordleAPI::Debug::Break()

#define WORDLEAPI_DEBUG_BREAK_MSG_A(Msg) MessageBoxA(NULL, Msg, "Debug break!", MB_OK | MB_ICONERROR); WordleAPI::Debug::Break()
#define WORDLEAPI_DEBUG_BREAK_MSG_W(Msg) MessageBoxW(NULL, Msg, L"Debug break!", MB_OK | MB_ICONERROR); WordleAPI::Debug::Break()

#ifdef UNICODE

#define WORDLEAPI_DEBUG_BREAK_MSG(Msg) WORDLEAPI_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef UNICODE

#define WORDLEAPI_DEBUG_BREAK_MSG(Msg) WORDLEAPI_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef _DEBUG

#define WORDLEAPI_DEBUG_BREAK()
#define WORDLEAPI_DEBUG_BREAK_MSG_A(Msg)
#define WORDLEAPI_DEBUG_BREAK_MSG_W(Msg)
#define WORDLEAPI_DEBUG_BREAK_MSG(Msg)

#endif



#ifdef _DEBUG

#define WORDLEAPI_ASSERT(Condition) if (!(Condition))\
{\
	WORDLEAPI_DEBUG_BREAK();\
}

#define WORDLEAPI_ASSERT_MSG_A(Condition, Msg) if (!(Condition))\
{\
	WORDLEAPI_DEBUG_BREAK_MSG_A(Msg);\
}

#define WORDLEAPI_ASSERT_MSG_W(Condition, Msg) if (!(Condition))\
{\
	WORDLEAPI_DEBUG_BREAK_MSG_W(Msg);\
}

#ifdef UNICODE

#define WORDLEAPI_ASSERT_MSG(Condition, Msg) WORDLEAPI_ASSERT_MSG_W(Condition, Msg)

#endif

#ifndef UNICODE

#define WORDLEAPI_ASSERT_MSG(Condition, Msg) WORDLEAPI_ASSERT_MSG_A(Condition, Msg)

#endif

#endif

#ifndef _DEBUG

#define WORDLEAPI_ASSERT(Condition)
#define WORDLEAPI_ASSERT_MSG_A(Condition, Msg)
#define WORDLEAPI_ASSERT_MSG_W(Condition, Msg)
#define WORDLEAPI_ASSERT_MSG(Condition, Msg)

#endif



namespace WordleAPI
{

	namespace Debug
	{

		class Tree
		{

		public:

			Tree(const wchar_t* _Text = nullptr, const uint16_t _Attribute = _ConsoleTxtTurquoise | _ConsoleBkgBlack, const bool _PrintKids = true);
			Tree(const Tree& _Other) = delete;
			Tree(Tree&& _Other) noexcept;
			~Tree();

			void SetText(const wchar_t* _Text);
			void SetAttribute(const uint16_t _Attribute);

			void SetPrintKids(const bool _PrintKids);

			const wchar_t* GetText() const;
			const uint16_t GetAttribute() const;

			const bool GetPrintKids() const;

			std::vector<Tree*>& GetKids();
			const std::vector<Tree*>& GetKids() const;

			const bool LogToConsole(const uint64_t _Tab = 1, const uint64_t _Level = 0) const;
			const bool LogToFile(std::wofstream* _FOut, const bool _LogAtribute = false, const uint64_t _Tab = 1, const uint64_t _Level = 0) const;

			void operator= (const Tree& _Other) = delete;
			void operator= (Tree&& _Other) noexcept;

		private:

			const wchar_t* Text;
			uint16_t Attribute;

			bool PrintKids;

			std::vector<Tree*> Kids;

		};

		extern const ConstHandleRef ConsoleOutHandle;
		extern const ConstUInt16Ref DefaultAttribute;

		void Break(const wchar_t* _Msg = nullptr);

		bool Init();
		void Stop();

		bool GetConsoleAttribute(uint16_t& _Attribute);
		bool SetTextAttribute(const uint16_t _Attribute);

	}

}



#endif
