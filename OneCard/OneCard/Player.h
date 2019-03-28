#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Deck.h"


enum Player_Config {
	MAX_HAND = 15, START_DRAW_SIZE = 5
};


/*
	해야할 것:
	1. player 클래스 설계 정리. 특히 hand
	2. card 클래스 메소드 정리
	3. player controller 클래스 설계
	4. io controller 클래스 설계
*/

class Player {
private:
	string name;
	vector<Card*> hand;
	int finish_number; // 파산과 승리를 똑같이?
	Deck& ref_deck; // IDrawTop을 정의할 수 있으나, deck의 public method는 생성자를 제외하면 DrawTop밖에 없기에 그냥 deck 타입을 사용함

public:
	Player(string name, Deck& ref);
	bool IsFinished() const;
	void Draw(int num);
	void Sort();
	void TestViewHand();

	void Action(int magic_number);
};



Player::Player(string name, Deck& ref) : name(name), ref_deck(ref) {
	finish_number = 0;
}


bool Player::IsFinished() const { return finish_number != 0; }



void Player::Draw(int num) {
	for(int i = 0; i < num; i++)
		hand.push_back(ref_deck.DrawTop());
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