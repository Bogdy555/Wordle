#ifndef WordleAPI_Animation_hpp

#define WordleAPI_Animation_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	template<typename T> struct AnimationState
	{
		T State;
		float Begin;
		float End;
	};

	template<typename T> class Animation
	{

	public:

		Animation() : Time(0.0f), States()
		{

		}

		Animation(const Animation& _Other) : Time(_Other.Time), States(_Other.States)
		{

		}

		Animation(Animation&& _Other) noexcept : Time(_Other.Time), States(std::move(_Other.States))
		{
			_Other.Time = 0.0f;
		}

		~Animation()
		{

		}

		void SetTime(const float _Time)
		{
			Time = _Time;
		}

		const float GetTime() const
		{
			return Time;
		}

		std::vector<AnimationState<T>>& GetStates()
		{
			return States;
		}

		const std::vector<AnimationState<T>>& GetStates() const
		{
			return States;
		}

		const T GetCurrentState() const
		{
			for (size_t _Index = 0; _Index < States.size(); _Index++)
			{
				if (States[_Index].Begin <= Time && States[_Index].End > Time)
				{
					return States[_Index].State;
				}
			}

			return T();
		}

		const size_t GetCurrentStateIndex() const
		{
			for (size_t _Index = 0; _Index < States.size(); _Index++)
			{
				if (States[_Index].Begin <= Time && States[_Index].End > Time)
				{
					return _Index;
				}
			}

			return (size_t)(-1);
		}

		void Update(const float _TimeStep)
		{
			Time += _TimeStep;

			while (Time >= States[States.size() - 1].End)
			{
				Time -= States[States.size() - 1].End;
			}
		}

		void Reset()
		{
			Time = 0.0f;
		}

		const Animation& operator= (const Animation& _Other)
		{
			Time = _Other.Time;
			States = _Other.States;
		}

		const Animation& operator= (Animation&& _Other) noexcept
		{
			Time = _Other.Time;
			States = std::move(_Other.States);

			_Other.Time = 0.0f;
		}

	private:

		float Time;
		std::vector<AnimationState<T>> States;

	};

	template<typename T, const T (*Lerper)(const T, const T, const float)> class AnimationLerp
	{

	public:

		AnimationLerp() : Time(0.0f), States()
		{

		}

		AnimationLerp(const AnimationLerp& _Other) : Time(_Other.Time), States(_Other.States)
		{

		}

		AnimationLerp(AnimationLerp&& _Other) noexcept : Time(_Other.Time), States(std::move(_Other.States))
		{
			_Other.Time = 0.0f;
		}

		~AnimationLerp()
		{

		}

		void SetTime(const float _Time)
		{
			Time = _Time;
		}

		const float GetTime() const
		{
			return Time;
		}

		std::vector<AnimationState<T>>& GetStates()
		{
			return States;
		}

		const std::vector<AnimationState<T>>& GetStates() const
		{
			return States;
		}

		const T GetCurrentState() const
		{
			for (size_t _Index = 0; _Index < States.size(); _Index++)
			{
				if (States[_Index].Begin <= Time && States[_Index].End > Time)
				{
					if (_Index != States.size() - 1)
					{
						return Lerper(States[_Index].State, States[_Index + 1].State, (Time - States[_Index].Begin) / (States[_Index].End - States[_Index].Begin));
					}
					else
					{
						return States[_Index].State;
					}
				}
			}

			return T();
		}

		const size_t GetCurrentStateIndex() const
		{
			for (size_t _Index = 0; _Index < States.size(); _Index++)
			{
				if (States[_Index].Begin <= Time && States[_Index].End > Time)
				{
					return _Index;
				}
			}

			return (size_t)(-1);
		}

		void Update(const float _TimeStep)
		{
			Time += _TimeStep;

			while (Time >= States[States.size() - 1].End)
			{
				Time -= States[States.size() - 1].End;
			}
		}

		void Reset()
		{
			Time = 0.0f;
		}

		const AnimationLerp& operator= (const AnimationLerp& _Other)
		{
			Time = _Other.Time;
			States = _Other.States;
		}

		const AnimationLerp& operator= (AnimationLerp&& _Other) noexcept
		{
			Time = _Other.Time;
			States = std::move(_Other.States);

			_Other.Time = 0.0f;
		}

	private:

		float Time;
		std::vector<AnimationState<T>> States;

	};

}



#endif
