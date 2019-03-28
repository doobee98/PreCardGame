#pragma once
#include "Card.h"
#define TOTAL_CARD_NUM 54

class CardFactory {
	static CardFactory* instance;
private:
	Card** card_list;
	int card_list_count;
	CardFactory();
	~CardFactory();

public:
	static CardFactory& GetInstance(); // 싱글톤 패턴
	Card* MakeCard(Trump t, int num);
};



CardFactory* CardFactory::instance = NULL;
CardFactory& CardFactory::GetInstance() {
	if (instance == NULL) {
		instance = new CardFactory();
	}
	return *instance;
}


CardFactory::CardFactory() {
	card_list = new Card*[TOTAL_CARD_NUM];
	card_list_count = 0;
}


CardFactory::~CardFactory() {
	delete[] card_list;
}


Card* CardFactory::MakeCard(Trump t, int num) {
	Card* temp = new Card(t, num);
	if (card_list_count >= TOTAL_CARD_NUM)
		throw "CardFactory::MakeCard : TOTAL_CARD_NUM가 넘는 수의 Card 객체가 생성되었습니다.";
	card_list[card_list_count++] = temp;
	return temp;
}
