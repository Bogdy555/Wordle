#ifndef WordleAPI_Bot_hpp

#define WordleAPI_Bot_hpp



#include "WordleAPI.hpp"



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

		std::vector<std::vector<char>> DatabaseCuvinte;

	};

}



#endif
