#ifndef WordleAPI_Multiprocessing_hpp

#define WordleAPI_Multiprocessing_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	namespace Multiprocessing
	{

		class Process
		{

		public:

			Process();
			Process(const Process& _Other) = delete;
			Process(Process&& _Other) noexcept;
			~Process();

			bool Create(const wchar_t* _Path, STARTUPINFO* _StartInfo = nullptr, const wchar_t* _WorkingDir = nullptr, wchar_t* _CmdLine = nullptr, unsigned long _Flags = CREATE_NEW_CONSOLE);
			bool CreateElevated(const wchar_t* _Path, const int _ShowCmd = SW_NORMAL, const wchar_t* _WorkingDir = nullptr, wchar_t* _CmdLine = nullptr);
			void Destroy(const int32_t _ReturnValue);
			bool UpdateStatus();

			const PROCESS_INFORMATION& GetProcessInfo() const;
			const wchar_t* GetPath() const;
			const bool CheckCreated() const;
			const int32_t GetReturnValue() const;

			void operator= (const Process& _Other) = delete;
			void operator= (Process&& _Other) noexcept;

		private:

			PROCESS_INFORMATION ProcessInfo;
			const wchar_t* Path;
			bool Created;
			int32_t ReturnValue;

		};

		class SharedMemory
		{

		public:

			SharedMemory();
			SharedMemory(const SharedMemory& _Other) = delete;
			SharedMemory(SharedMemory&& _Other) noexcept;
			~SharedMemory();

			bool Create(const wchar_t* _Name, const uint32_t _Size);
			void Destroy();

			const bool CheckCreated() const;
			const wchar_t* GetName() const;
			const uint32_t GetSize() const;

			unsigned char* Data();
			const unsigned char* Data() const;

			operator unsigned char* ();
			operator const unsigned char* () const;

			unsigned char& operator* ();
			const unsigned char& operator* () const;

			void operator= (const SharedMemory& _Other) = delete;
			void operator= (SharedMemory&& _Other) noexcept;

		private:

			bool Created;

			HANDLE hFile;

			const wchar_t* Name;

			uint32_t Size;
			unsigned char* Buff;

		};

		class SharedMutex
		{

		public:

			SharedMutex();
			SharedMutex(const SharedMutex& _Other) = delete;
			SharedMutex(SharedMutex&& _Other) noexcept;
			~SharedMutex();

			bool Create(const wchar_t* _Name);
			void Destroy();

			void Lock();
			void Unlock();

			const HANDLE GetHandle() const;
			const wchar_t* GetName() const;

			void operator= (const SharedMutex& _Other) = delete;
			void operator= (SharedMutex&& _Other) noexcept;

		private:

			HANDLE Handle;
			const wchar_t* Name;

		};

	}

}



#endif
