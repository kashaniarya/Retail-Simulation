// kashAI.hpp
// Arya Kashani
// akashan1
// 10847777
// Project 2

#include "OthelloAI.hpp"

namespace akashan1 {
	
	class kashAI : public OthelloAI {
		public:
			virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		private:
			int eval(const OthelloGameState& state, char c);
			std::vector<std::pair<int, int>> getValidMoves(const OthelloGameState& s);
			int search(const OthelloGameState& state, int depth, char c, int first_time);
			int maximus(int* a, int size, std::vector<std::pair<int, int>> vm);
			int minimal(int* a, int size);
	};
}