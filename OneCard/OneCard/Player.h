#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Deck.h"

#define MAX_HAND 15

/*
	설계에 있어 Player를 정확히 고민해볼 것
	Deck까지는 맞음.
	Controller의 역할까지 주어야 하는지를 고민하자. (Hand 분리?)
	Field와 Deck을 인자로 전달받아야 하는가?

	또, vector를 굳이 써야 하는가? deque로 대체할 수 없나?
*/

class Player {
private:
	string name;
	vector<Card*> hand;
	int finish_number; // 파산과 승리를 똑같이?
	Deck& deck_ref;

public:
	Player(string name, Deck& ref);
	bool IsFinished() const;
	void Draw(Field f);
	void Sort();
	void TestViewHand();

private:
	void Draw(int num);
};



Player::Player(string name, Deck& ref) : name(name), deck_ref(ref) {
	finish_number = 0;
}


bool Player::IsFinished() const { return finish_number != 0; }


void Player::Draw(Field f) {
	if (f.IsAttacking()) {
		Draw(f.GetAtkStack());
		f.ResetAtkStack();
	}
	else {
		Draw(1);
	}
}


void Player::Draw(int num) {
	for (int i = 0; i < num; i++) {
		hand.push_back(deck_ref.DrawTop());
	}
}


void Player::Sort() {
	sort(hand.begin(), hand.end(), compare);
}


void Player::TestViewHand() {
	int i = 1;
	for (vector<Card*>::iterator iter = hand.begin(); iter != hand.end(); iter++) {
		cout.width(2); cout.fill(' ');
		cout << i++;
		cout << "   " << **iter << endl;
	}
}