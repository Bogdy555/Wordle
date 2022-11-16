#include "..\Headers\WordleAPI.hpp"



WordleAPI::Multiprocessing::Process::Process() : ProcessInfo({ 0 }), Path(nullptr), Created(false), ReturnValue(_ReturnStillRunning)
{

}

WordleAPI::Multiprocessing::Process::Process(Process&& _Other) noexcept :
	ProcessInfo(_Other.ProcessInfo), Path(_Other.Path), Created(_Other.Created), ReturnValue(_Other.ReturnValue)
{
	_Other.ProcessInfo = { 0 };
	_Other.Path = nullptr;
	_Other.Created = false;
	_Other.ReturnValue = _ReturnStillRunning;
}

WordleAPI::Multiprocessing::Process::~Process()
{

}

bool WordleAPI::Multiprocessing::Process::Create(const wchar_t* _Path, STARTUPINFO* _StartInfo, const wchar_t* _WorkingDir, wchar_t* _CmdLine, unsigned long _Flags)
{
	ProcessInfo = { 0 };
	Created = false;
	ReturnValue = _ReturnStillRunning;
	Path = _Path;

	if (!_Path)
	{
		return false;
	}

	if (_StartInfo)
	{
		Created = CreateProcess(Path, _CmdLine, NULL, NULL, FALSE, _Flags, NULL, _WorkingDir, _StartInfo, &ProcessInfo);
	}
	else
	{
		STARTUPINFO _DefaultStartInfo = { 0 };
		_DefaultStartInfo.dwFlags = STARTF_FORCEOFFFEEDBACK;
		Created = CreateProcess(Path, _CmdLine, NULL, NULL, FALSE, _Flags, NULL, _WorkingDir, &_DefaultStartInfo, &ProcessInfo);
	}

	ReturnValue = _ReturnStillRunning;

	if (!Created)
	{
		ProcessInfo = { 0 };
		return false;
	}

	return true;
}

bool WordleAPI::Multiprocessing::Process::CreateElevated(const wchar_t* _Path, const int _ShowCmd, const wchar_t* _WorkingDir, wchar_t* _CmdLine)
{
	ProcessInfo = { 0 };
	Created = false;
	ReturnValue = _ReturnStillRunning;
	Path = _Path;

	if (!_Path)
	{
		return false;
	}

	SHELLEXECUTEINFO _ShellExInfo = { 0 };

	_ShellExInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	_ShellExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	_ShellExInfo.lpVerb = L"runas";
	_ShellExInfo.lpFile = _Path;
	_ShellExInfo.lpParameters = _CmdLine;
	_ShellExInfo.lpDirectory = _WorkingDir;
	_ShellExInfo.nShow = _ShowCmd;

	Created = ShellExecuteEx(&_ShellExInfo);

	ReturnValue = _ReturnStillRunning;

	if (Created)
	{
		if (_ShellExInfo.hProcess != NULL && _ShellExInfo.hProcess != INVALID_HANDLE_VALUE)
		{
			ProcessInfo.hProcess = _ShellExInfo.hProcess;
			ProcessInfo.dwProcessId = GetProcessId(_ShellExInfo.hProcess);
		}
	}
	else
	{
		ProcessInfo = { 0 };
		return false;
	}

	return true;
}

void WordleAPI::Multiprocessing::Process::Destroy(const int32_t _ReturnValue)
{
	if (ProcessInfo.hProcess)
	{
		if (TerminateProcess(ProcessInfo.hProcess, _ReturnValue))
		{
			ReturnValue = _ReturnValue;
		}
		else
		{
			ReturnValue = _ReturnStillRunning;
		}
	}
	else
	{
		ReturnValue = _ReturnStillRunning;
	}

	ProcessInfo = { 0 };
	Path = nullptr;
	Created = false;
}

bool WordleAPI::Multiprocessing::Process::UpdateStatus()
{
	if (!ProcessInfo.hProcess)
	{
		return false;
	}

	if (!GetExitCodeProcess(ProcessInfo.hProcess, (DWORD*)(&ReturnValue)))
	{
		ProcessInfo = { 0 };
		ReturnValue = _ReturnStillRunning;
		Created = false;
		return false;
	}

	if (ReturnValue != _ReturnStillRunning)
	{
		ProcessInfo = { 0 };
		Created = false;
	}

	return true;
}

const PROCESS_INFORMATION& WordleAPI::Multiprocessing::Process::GetProcessInfo() const
{
	return ProcessInfo;
}

const wchar_t* WordleAPI::Multiprocessing::Process::GetPath() const
{
	return Path;
}

const bool WordleAPI::Multiprocessing::Process::CheckCreated() const
{
	return Created;
}

const int32_t WordleAPI::Multiprocessing::Process::GetReturnValue() const
{
	return ReturnValue;
}

void WordleAPI::Multiprocessing::Process::operator= (Process&& _Other) noexcept
{
	ProcessInfo = _Other.ProcessInfo;
	Path = _Other.Path;
	Created = _Other.Created;
	ReturnValue = _Other.ReturnValue;

	_Other.ProcessInfo = { 0 };
	_Other.Path = nullptr;
	_Other.Created = false;
	_Other.ReturnValue = _ReturnStillRunning;
}



WordleAPI::Multiprocessing::SharedMemory::SharedMemory() : Created(false), hFile(NULL), Name(nullptr), Size(0), Buff(nullptr)
{

}

WordleAPI::Multiprocessing::SharedMemory::SharedMemory(SharedMemory&& _Other) noexcept :
	Created(_Other.Created), hFile(_Other.hFile), Name(_Other.Name), Size(_Other.Size), Buff(_Other.Buff)
{
	_Other.Created = false;
	_Other.hFile = NULL;
	_Other.Name = nullptr;
	_Other.Size = 0;
	_Other.Buff = nullptr;
}

WordleAPI::Multiprocessing::SharedMemory::~SharedMemory()
{
	Destroy();
}

bool WordleAPI::Multiprocessing::SharedMemory::Create(const wchar_t* _Name, const uint32_t _Size)
{
	if (Buff)
	{
		UnmapViewOfFile(Buff);
		Buff = nullptr;
	}
	if (hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}
	Created = false;
	Name = nullptr;
	Size = 0;

	if (!_Name || !_Size)
	{
		return false;
	}

	Name = _Name;
	Size = _Size;

	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size, Name);

	if (!hFile)
	{
		Created = false;
		Size = 0;
		return false;
	}

	Buff = (unsigned char*)(MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, Size));

	if (!Buff)
	{
		CloseHandle(hFile);
		hFile = NULL;
		Created = false;
		Size = 0;
		return false;
	}

	Created = true;

	return true;
}

void WordleAPI::Multiprocessing::SharedMemory::Destroy()
{
	if (Buff)
	{
		UnmapViewOfFile(Buff);
		Buff = nullptr;
	}
	if (hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}
	Created = false;
	Name = nullptr;
	Size = 0;
}

const bool WordleAPI::Multiprocessing::SharedMemory::CheckCreated() const
{
	return Created;
}

const wchar_t* WordleAPI::Multiprocessing::SharedMemory::GetName() const
{
	return Name;
}

const uint32_t WordleAPI::Multiprocessing::SharedMemory::GetSize() const
{
	return Size;
}

unsigned char* WordleAPI::Multiprocessing::SharedMemory::Data()
{
	return Buff;
}

const unsigned char* WordleAPI::Multiprocessing::SharedMemory::Data() const
{
	return Buff;
}

WordleAPI::Multiprocessing::SharedMemory::operator unsigned char* ()
{
	return Buff;
}

WordleAPI::Multiprocessing::SharedMemory::operator const unsigned char* () const
{
	return Buff;
}

unsigned char& WordleAPI::Multiprocessing::SharedMemory::operator* ()
{
	return *Buff;
}

const unsigned char& WordleAPI::Multiprocessing::SharedMemory::operator* () const
{
	return *Buff;
}

void WordleAPI::Multiprocessing::SharedMemory::operator= (SharedMemory&& _Other) noexcept
{
	hFile = _Other.hFile;
	Created = _Other.Created;
	Name = _Other.Name;
	Buff = _Other.Buff;
	Size = _Other.Size;

	_Other.hFile = NULL;
	_Other.Created = false;
	_Other.Name = nullptr;
	_Other.Buff = nullptr;
	_Other.Size = 0;
}



WordleAPI::Multiprocessing::SharedMutex::SharedMutex() : Handle(NULL), Name(nullptr)
{

}

WordleAPI::Multiprocessing::SharedMutex::SharedMutex(SharedMutex&& _Other) noexcept : Handle(_Other.Handle), Name(_Other.Name)
{
	_Other.Handle = NULL;
	_Other.Name = nullptr;
}

WordleAPI::Multiprocessing::SharedMutex::~SharedMutex()
{
	Destroy();
}

bool WordleAPI::Multiprocessing::SharedMutex::Create(const wchar_t* _Name)
{
	Destroy();

	Handle = CreateMutex(NULL, FALSE, _Name);

	if (!Handle)
	{
		return false;
	}

	Name = _Name;

	return true;
}

void WordleAPI::Multiprocessing::SharedMutex::Destroy()
{
	if (Handle)
	{
		CloseHandle(Handle);
		Handle = NULL;
	}
	Name = nullptr;
}

void WordleAPI::Multiprocessing::SharedMutex::Lock()
{
	if (!Handle)
	{
		return;
	}

	WaitForSingleObject(Handle, INFINITE);
}

void WordleAPI::Multiprocessing::SharedMutex::Unlock()
{
	if (!Handle)
	{
		return;
	}

	ReleaseMutex(Handle);
}

const HANDLE WordleAPI::Multiprocessing::SharedMutex::GetHandle() const
{
	return Handle;
}

const wchar_t* WordleAPI::Multiprocessing::SharedMutex::GetName() const
{
	return Name;
}

void WordleAPI::Multiprocessing::SharedMutex::operator= (SharedMutex&& _Other) noexcept
{
	Handle = _Other.Handle;
	Name = _Other.Name;

	_Other.Handle = NULL;
	_Other.Name = nullptr;
}
