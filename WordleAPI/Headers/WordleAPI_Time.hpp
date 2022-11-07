#ifndef WordleAPI_Time_hpp

#define WordleAPI_Time_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	namespace Time
	{

		class Timer
		{

		public:

			Timer(const int64_t _MicroSec = 0, const bool _Feature = false);
			Timer(const Timer& _Other);
			Timer(Timer&& _Other) noexcept;
			~Timer();

			void Start();
			void Stop();
			void Reset();

			void SetMicroSec(const int64_t _MicroSec, const bool _Feature = false);
			void SetMilliSec(const int64_t _MilliSec, const bool _Feature = false);
			void SetSec(const int64_t _Sec, const bool _Feature = false);

			void AddMicroSec(const int64_t _MicroSec, const bool _Feature = false);
			void AddMilliSec(const int64_t _MilliSec, const bool _Feature = false);
			void AddSec(const int64_t _Sec, const bool _Feature = false);

			const tm GetUTCBegin() const;
			const tm GetUTCEnd() const;
			const tm GetLocalBegin() const;
			const tm GetLocalEnd() const;

			operator const float() const;

			void operator= (const Timer& _Other);
			void operator= (Timer&& _Other) noexcept;

		private:

			std::chrono::time_point<std::chrono::system_clock> Begin;
			std::chrono::time_point<std::chrono::system_clock> End;

		};

		extern const float MicroToMilli;
		extern const float MicroToSec;

		extern const float MilliToMicro;
		extern const float MilliToSec;

		extern const float SecToMicro;
		extern const float SecToMilli;

		extern const ConstTimeRef UtcTime;
		extern const ConstTimeRef LocalTime;

		extern const ConstBoolRef Initialized;
		extern const ConstTimeCapsRef TimeCaps;

		bool Init();
		void Stop();

		void GetTime();
		void GetUtcTime();
		void GetLocalTime();

		void SleepMicroSec(const uint64_t _MicroSec);
		void SleepMilliSec(const uint64_t _MilliSec);
		void SleepSec(const uint64_t _Sec);

		float FramesPerMicroSec(const float _MicroSecPerFrame, bool* _Error = nullptr);
		float FramesPerMilliSec(const float _MilliSecPerFrame, bool* _Error = nullptr);
		float FramesPerSec(const float _SecPerFrame, bool* _Error = nullptr);

	}

}



#endif
