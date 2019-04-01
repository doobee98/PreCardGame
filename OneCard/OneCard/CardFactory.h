#pragma once
#include <iostream>
#include "Card.h"
#define MAX_CARD_NUM 54


class CardFactory {
private:
	static CardFactory* instance;
	CardFactory();
	~CardFactory();
	Card** card_list;
	int card_num;

public:
	static CardFactory& GetInstance();
	const Card* MakeCard(Trump trp, Number num);
};




CardFactory* CardFactory::instance = NULL;
CardFactory::CardFactory() {
	card_list = new Card*[MAX_CARD_NUM];
	card_num = 0;
}

CardFactory::~CardFactory() {
	delete[] card_list;
}

CardFactory& CardFactory::GetInstance() {
	if (instance == NULL) 
		instance = new CardFactory();
	
	return *instance;
}

const Card* CardFactory::MakeCard(Trump trp, Number num) {
	if (card_num >= MAX_CARD_NUM)
		throw "CardFactory::MakeCard - Over Max Card Num!";
	card_list[card_num++] = new Card(trp, num);
	return card_list[card_num - 1];
}