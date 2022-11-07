#include "..\Headers\WordleAPI.hpp"



WordleAPI::Time::Timer::Timer(const int64_t _MicroSec, const bool _Feature) : Begin(), End()
{
	SetMicroSec(_MicroSec, _Feature);
}

WordleAPI::Time::Timer::Timer(const Timer& _Other) : Begin(_Other.Begin), End(_Other.End)
{

}

WordleAPI::Time::Timer::Timer(Timer&& _Other) noexcept : Begin(_Other.Begin), End(_Other.End)
{
	_Other.Reset();
}

WordleAPI::Time::Timer::~Timer()
{

}

void WordleAPI::Time::Timer::Start()
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now;
	End = _Now;
}

void WordleAPI::Time::Timer::Stop()
{
	End = std::chrono::system_clock::now();
}

void WordleAPI::Time::Timer::Reset()
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now;
	End = _Now;
}

void WordleAPI::Time::Timer::SetMicroSec(const int64_t _MicroSec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::microseconds(_MicroSec * (!_Feature));
	End = _Now + std::chrono::microseconds(_MicroSec * _Feature);
}

void WordleAPI::Time::Timer::SetMilliSec(const int64_t _MilliSec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::milliseconds(_MilliSec * (!_Feature));
	End = _Now + std::chrono::milliseconds(_MilliSec * _Feature);
}

void WordleAPI::Time::Timer::SetSec(const int64_t _Sec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::seconds(_Sec * (!_Feature));
	End = _Now + std::chrono::seconds(_Sec * _Feature);
}

void WordleAPI::Time::Timer::AddMicroSec(const int64_t _MicroSec, const bool _Feature)
{
	Begin -= std::chrono::microseconds(_MicroSec * (!_Feature));
	End += std::chrono::microseconds(_MicroSec * _Feature);
}

void WordleAPI::Time::Timer::AddMilliSec(const int64_t _MilliSec, const bool _Feature)
{
	Begin -= std::chrono::milliseconds(_MilliSec * (!_Feature));
	End += std::chrono::milliseconds(_MilliSec * _Feature);
}

void WordleAPI::Time::Timer::AddSec(const int64_t _Sec, const bool _Feature)
{
	Begin -= std::chrono::seconds(_Sec * (!_Feature));
	End += std::chrono::seconds(_Sec * _Feature);
}

const tm WordleAPI::Time::Timer::GetUTCBegin() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(Begin);
	gmtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm WordleAPI::Time::Timer::GetUTCEnd() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(End);
	gmtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm WordleAPI::Time::Timer::GetLocalBegin() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(Begin);
	localtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm WordleAPI::Time::Timer::GetLocalEnd() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(End);
	localtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

WordleAPI::Time::Timer::operator const float() const
{
	return std::chrono::duration<float>(End - Begin).count();
}

void WordleAPI::Time::Timer::operator= (const Timer& _Other)
{
	Begin = _Other.Begin;
	End = _Other.End;
}

void WordleAPI::Time::Timer::operator= (Timer&& _Other) noexcept
{
	Begin = _Other.Begin;
	End = _Other.End;

	_Other.Reset();
}



const float WordleAPI::Time::MicroToMilli = 0.001f;
const float WordleAPI::Time::MicroToSec = 0.000001f;

const float WordleAPI::Time::MilliToMicro = 1000.0f;
const float WordleAPI::Time::MilliToSec = 0.001f;

const float WordleAPI::Time::SecToMicro = 1000000.0f;
const float WordleAPI::Time::SecToMilli = 1000.0f;

static tm _UtcTime = { 0 };
static tm _LocalTime = { 0 };

const WordleAPI::ConstTimeRef WordleAPI::Time::UtcTime = _UtcTime;
const WordleAPI::ConstTimeRef WordleAPI::Time::LocalTime = _LocalTime;

static bool _Initialized = false;
static TIMECAPS _TimeCaps = { 0 };

const WordleAPI::ConstBoolRef WordleAPI::Time::Initialized = _Initialized;
const WordleAPI::ConstTimeCapsRef WordleAPI::Time::TimeCaps = _TimeCaps;



bool WordleAPI::Time::Init()
{
	if (Initialized)
	{
		return true;
	}

	if (timeGetDevCaps(&_TimeCaps, sizeof(TIMECAPS)) != MMSYSERR_NOERROR)
	{
		return false;
	}

	if (timeBeginPeriod(_TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		_TimeCaps = { 0 };
		return false;
	}

	_Initialized = true;

	return true;
}

void WordleAPI::Time::Stop()
{
	if (!Initialized)
	{
		return;
	}

	if (timeEndPeriod(_TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		return;
	}

	_TimeCaps = { 0 };
	_Initialized = false;
}



void WordleAPI::Time::GetTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	gmtime_s(&_UtcTime, &_Time);
	localtime_s(&_LocalTime, &_Time);
}

void WordleAPI::Time::GetUtcTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	gmtime_s(&_UtcTime, &_Time);
}

void WordleAPI::Time::GetLocalTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&_LocalTime, &_Time);
}



void WordleAPI::Time::SleepMicroSec(const uint64_t _MicroSec)
{
	std::this_thread::sleep_for(std::chrono::microseconds(_MicroSec));
}

void WordleAPI::Time::SleepMilliSec(const uint64_t _MilliSec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(_MilliSec));
}

void WordleAPI::Time::SleepSec(const uint64_t _Sec)
{
	std::this_thread::sleep_for(std::chrono::seconds(_Sec));
}



float WordleAPI::Time::FramesPerMicroSec(const float _MicroSecPerFrame, bool* _Error)
{
	if (!_MicroSecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _MicroSecPerFrame;
}

float WordleAPI::Time::FramesPerMilliSec(const float _MilliSecPerFrame, bool* _Error)
{
	if (!_MilliSecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _MilliSecPerFrame;
}

float WordleAPI::Time::FramesPerSec(const float _SecPerFrame, bool* _Error)
{
	if (!_SecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _SecPerFrame;
}
