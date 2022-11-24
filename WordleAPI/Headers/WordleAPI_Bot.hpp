#ifndef WordleAPI_Bot_hpp

#define WordleAPI_Bot_hpp



#include "WordleAPI.hpp"
#include <bitset>



namespace WordleAPI
{

	class Bot
	{

	public:

		Bot();
		Bot(const Bot& _Other);
		Bot(Bot&& _Other) noexcept;
		~Bot();

		void Init(const std::vector<std::vector<char>>& _DatabaseCuvinte);
		void Destroy();

		const std::vector<char> GetGuess();

		void SendFeedback(const std::vector<uint8_t>& _Feedback, const std::vector<char>& _Guess);

		void operator= (const Bot& _Other);
		void operator= (Bot&& _Other) noexcept;

	private:

		static const std::vector<char> FIRST_GUESS;

		std::vector<std::vector<char>> DatabaseCuvinte;
		std::vector<std::vector<uint8_t>> PossibleFeedbacks;
		std::bitset<26> WordHas, NotOnPos[5];
		bool FirstGuess = true;

		void GenerateFeedbacks(std::vector<uint8_t> _Current, size_t _Size);
		double_t ComputeEntropy(std::vector<char> _Guess);
		bool ValidPattern(std::vector<uint8_t> _Pattern, std::vector<char> _Guess);
		int32_t RemainingWords(std::vector<uint8_t> _Pattern, std::vector<char> _Guess);

	};

}



#endif
