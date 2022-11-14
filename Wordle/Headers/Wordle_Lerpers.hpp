#ifndef Wordle_Lerpers_hpp

#define Wordle_Lerpers_hpp



#include "Wordle.hpp"



namespace Wordle
{

	const float LerpFloat(const float _A, const float _B, const float _Ratio);
	const WordleAPI::Vec4 LerpVec4(const WordleAPI::Vec4 _A, const WordleAPI::Vec4 _B, const float _Ratio);

}



#endif
