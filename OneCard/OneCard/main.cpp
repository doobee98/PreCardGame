#include <iostream>
#include "Player.h"
using namespace std;

int main(void) {
	cout << "Project Onecard" << endl;

	srand((unsigned int)time(NULL));
	
	Field f;
	f.AddAtkStack(Attack::JOKER);
	Deck d;
	Player p1("ÀÌµÎ¼·", d);
	p1.Draw(f);
	p1.TestViewHand();
}