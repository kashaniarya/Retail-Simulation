// kashAI.cpp
// Arya Kashani
// akashan1
// 10847777
// Project 2

#include <ics46/factory/DynamicFactory.hpp>
#include "kashAI.hpp"
#include "OthelloCell.hpp"
#include <vector>
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, akashan1::kashAI, "Thanos with all 6 Infinity Stones(Required)");



int akashan1::kashAI::eval(const OthelloGameState& state, char c) {
	// number of tiles belonging to me - number of tiles belonging to opponent
	int black = state.blackScore();
	int white = state.whiteScore();
	if(c == 'b') {
		return black - white;
	}
	else {
		return white - black;
	}
}

std::vector<std::pair<int, int>> akashan1::kashAI::getValidMoves(const OthelloGameState& state) {
	std::vector<std::pair<int, int>> vd;
	int w = state.board().width();
	int h = state.board().height();
	for(int i=0; i < h; i++) {
		for(int j=0; j < w; j++) {
			if(state.isValidMove(j,i)) {
				vd.push_back(std::make_pair(j,i));
			}
		}
	}
	return vd;
}

int akashan1::kashAI::maximus(int* a, int size, std::vector<std::pair<int, int>> vm) {
	int index = 0;
	int m = *a;
	a++;
	int i = 1;
	while(i < size) {
		if(*a > m) {
			m = *a;
			index = i;
		}
		else if(*a == m) {
			if(vm[i] == std::make_pair(5,2) || vm[i] == std::make_pair(2,5) || vm[i] == std::make_pair(5,5) || vm[i] == std::make_pair(2,2)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(2,0)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(5,0)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(0,2)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(0,5)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(2,7)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(7,2)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(7,5)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(5,7)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(0,0)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(7,0)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(0,7)) {
				m = *a;
				index = i;
			}
			else if(vm[i] == std::make_pair(7,7)) {
				m = *a;
				index = i;
			}
		}
		i++;
		a++;
	}
	return index;
}

int akashan1::kashAI::minimal(int* a, int size) {
	int m = *a;
	a++;
	int i = 1;
	while(i < size) {
		if(*a < m) {
			m = *a;
		}
		i++;
		a++;
	}
	return m;
}

int akashan1::kashAI::search(const OthelloGameState& s, int depth, char c, int first_time) {
	if(depth == 0) {
		return akashan1::kashAI::eval(s, c);
	}
	else {
		// get validMoves		
		std::vector<std::pair<int, int>> validMoves = akashan1::kashAI::getValidMoves(s);
		int max[validMoves.size()];
		if(first_time == 0) {
			first_time++;
			// for each validMove in validMoves
			for(int xy = 0; xy < validMoves.size(); xy++) {
				// make that move on s' yeilding a state
				std::unique_ptr<OthelloGameState> state = s.clone();
				state->makeMove(validMoves[xy].first, validMoves[xy].second);
				// search(s', depth-1)
				max[xy] = akashan1::kashAI::search(*state, depth-1, c, first_time);
			}
			// return max val returned from recursive search calls
			return akashan1::kashAI::maximus(max, validMoves.size(), validMoves);
		}
		else { // is opponent turn
			//for each move my opponent can make
			for(int xy = 0; xy < validMoves.size(); xy++) {
				//make it
				std::unique_ptr<OthelloGameState> state = s.clone();
				state->makeMove(validMoves[xy].first, validMoves[xy].second);
				//search
				max[xy] = akashan1::kashAI::search(*state, depth-1, c, first_time);
			}
			// return min 
			return akashan1::kashAI::minimal(max, validMoves.size());
		}
	}
}

std::pair<int, int> akashan1::kashAI::chooseMove(const OthelloGameState& state) {
	char c;
	if(state.isBlackTurn()) {
		c = 'b';
	}
	else {
		c = 'w';
	}
	std::vector<std::pair<int, int>> validMoves = akashan1::kashAI::getValidMoves(state);
	int index = akashan1::kashAI::search(state, 4, c, 0);
	return std::make_pair(validMoves[index].first, validMoves[index].second);
}