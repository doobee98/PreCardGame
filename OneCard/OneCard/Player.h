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
	3. player controller 클래스 설계
	4. io controller 클래스 설계

	막힌부분: IO를 어디서 처리해줘야 하는가?
	Game 전체에 대한 정보는 GameController의 출력 메소드를 통해 얻어야함.
	IO Controller를 따로 둬야 하는가? 그렇다면 그 컨트롤러의 위치는? GameController와의 관계는?
*/

class Player {
private:
	string name;
	vector<Card*> hand; // sort, 출력 있어야함
	int finish_number; // 파산과 승리를 똑같이?
	Deck& ref_deck; // IDrawTop을 정의할 수 있으나, deck의 public method는 생성자를 제외하면 DrawTop밖에 없기에 그냥 deck 타입을 사용함

public:
	Player(string name, Deck& ref);
	void Draw(int num);
	void SortHand();
	Card* ChooseHand(int num) const;

	bool IsFinished() const;
	void TestViewHand();
};



Player::Player(string name, Deck& ref) : name(name), ref_deck(ref) {
	finish_number = 0;
}


bool Player::IsFinished() const { return finish_number != 0; }



void Player::Draw(int num) {
	for(int i = 0; i < num; i++)
		hand.push_back(ref_deck.DrawTop());
}

void Player::SortHand() {
	sort(hand.begin(), hand.end(), compare);
}


Card* Player::ChooseHand(int num) const {
	if (num < 1 || num > hand.size())
		throw "Player::ChooseHand : 핸드 사이즈에 벗어나는 입력이 들어왔습니다.";
	return hand.at(num - 1);
}


void Player::TestViewHand() {
	cout << name << endl;
	int i = 1;
	for (vector<Card*>::iterator iter = hand.begin(); iter != hand.end(); iter++) {
		cout.width(2); cout.fill(' ');
		cout << i++;
		cout << "   " << **iter << endl;
	}
}