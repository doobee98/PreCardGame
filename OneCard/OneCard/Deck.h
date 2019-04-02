#pragma once
#include <deque>
#include <stack>
#include <ctime>
#include <cstdlib>
#include "CardFactory.h"
#include "IPrint.h"
#include "IGetStack.h"


class Deck : public IPrint, public IDrawTop {
private:
	CardFactory& fac;
	deque<const Card*> card_deck;
	IGetStack& ref_field;

public:
	Deck(IGetStack& field);
	void Shuffle();
	const Card* DrawTop();
	void Print(int x, int y) const;

private:
	void RandomizeDeck();
};





Deck::Deck(IGetStack& field) 
	: fac(CardFactory::GetInstance()),
	card_deck(),
	ref_field(field) 
{
	srand((unsigned int)time(NULL));
	for(int i = 0; i < 2; i++)
		card_deck.push_back(fac.MakeCard(JOKER_TRP, JOKER_NUM));
	for (int t = Trump::SPADE; t <= Trump::DIAMOND; t++) {
		for(int n = A; n <= K; n++)
			card_deck.push_back(fac.MakeCard((Trump)t, (Number)n));
	}
	RandomizeDeck();
}


void Deck::Shuffle() {
	stack<const Card*>* ptr_used_stack = ref_field.GetStack();
	while (!ptr_used_stack->empty()) {
		card_deck.push_back(ptr_used_stack->top());
		ptr_used_stack->pop();
	}
	delete ptr_used_stack;
	RandomizeDeck();
}


const Card* Deck::DrawTop() {
	if (card_deck.empty())
		Shuffle();
	const Card* temp = card_deck.back();
	card_deck.pop_back();
	return temp;
}


void Deck::RandomizeDeck() {
	for (int i = card_deck.size(); i > 0; i--) {
		int temp = rand() % i;
		card_deck.push_back(card_deck.at(temp));
		card_deck.erase(card_deck.begin() + temp);
	}
}


void Deck::Print(int x, int y) const {
	ConsoleConfig::XYPrint(x, y, "|" + to_string(card_deck.size()) + "|");
}
