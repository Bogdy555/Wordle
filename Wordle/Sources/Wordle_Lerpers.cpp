#include "..\Headers\Wordle.hpp"



const float Wordle::LerpFloat(const float _A, const float _B, const float _Ratio)
{
	return _A + (_B - _A) * _Ratio;
}

const WordleAPI::Vec4 Wordle::LerpVec4(const WordleAPI::Vec4 _A, const WordleAPI::Vec4 _B, const float _Ratio)
{
	return _A + (_B - _A) * _Ratio;
}
