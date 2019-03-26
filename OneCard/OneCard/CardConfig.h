#pragma once
#include <string>

enum class Trump {
	JOKER, HEART, DIAMOND, SPADE, CLOVER, MAX
};

enum NUMBER {
	A = 1, J = 11, Q = 12, K = 13, JOKER_NUM = 14
};

inline std::string PRINT_TRUMP(Trump t) {
	switch (t) {
		case Trump::JOKER: return "¡Ú";
		case Trump::HEART: return "¢¾";
		case Trump::DIAMOND: return "¡ß";
		case Trump::SPADE: return "¢¼";
		case Trump::CLOVER: return "¢À";
		default: throw "Config.h / PrintTrump : Trump == MAX";
	}
}

enum class Attack {
	ACE = 3, TWO = 2, JOKER = 5, UNDEFINED = 0
};