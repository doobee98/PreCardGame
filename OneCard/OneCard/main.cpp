#include <iostream>
#include "Card.h"
using namespace std;

int main(void) {
	cout << "Project Onecard" << endl;
	
	Card c1(Trump::CLOVER, 4);
	Card c2(Trump::HEART, J);
	Card c3(Trump::JOKER, JOKER_NUM);

	cout << c1 << endl;
	cout << c2 << endl;
	cout << c3 << endl;
	
}