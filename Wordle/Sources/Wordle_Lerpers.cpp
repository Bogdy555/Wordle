#include "..\Headers\Wordle.hpp"



const float Wordle::LerpFloat(const float _A, const float _B, const float _Ratio)
{
	return _A + (_B - _A) * _Ratio;
}
