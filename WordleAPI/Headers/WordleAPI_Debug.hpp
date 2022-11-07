#ifndef WordleAPI_Debug_hpp

#define WordleAPI_Debug_hpp



#include "WordleAPI.hpp"



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
