#pragma once
#include <deque>
#include <stack>
#include <algorithm>
/*
#include <cstdlib>
#include <ctime>
*/
#include "Card.h"
#include "CardFactory.h"
#include "IGetStack.h"


class Deck {
private:
	CardFactory& fac;
	deque<Card*> card_deck;
	IGetStack& ref_field;

public:
	Deck(IGetStack& ref_field);
	Card* DrawTop();
	void TestViewDeck();

private:
	void Shuffle();
	void RandomizeDeck();
};




Deck::Deck(IGetStack& ref_field) : fac(CardFactory::GetInstance()), ref_field(ref_field) {

	for (int i = 0; i < 2; i++)  // JOKER 2°³
		card_deck.push_back(fac.MakeCard(Trump::JOKER, JOKER_NUM));


	for (int t = Trump::HEART; t <= Trump::CLOVER; t++) {
		for (int i = A; i <= K; i++)
			card_deck.push_back(fac.MakeCard((Trump)t, i));

		RandomizeDeck();
	}
}


Card* Deck::DrawTop() {
	if (card_deck.empty())
		Shuffle();
	Card* temp = card_deck.back();
	card_deck.pop_back();
	return temp;
}



void Deck::Shuffle() {
	auto used_stack = ref_field.GetStack();
	while (!used_stack->empty()) {
		card_deck.push_back(used_stack->top());
		used_stack->pop();
	}
	delete used_stack;
	RandomizeDeck();
}


void Deck::RandomizeDeck() {
	random_shuffle(card_deck.begin(), card_deck.end());
	/*for (int i = card_deck.size(); i > 0; i--) {
		int temp = rand() % i;
		card_deck.push_back(card_deck.at(temp));
		card_deck.erase(card_deck.begin() + temp);
		
	}*/
}


void Deck::TestViewDeck() {
	int i = 1;
	for (deque<Card*>::iterator iter = card_deck.begin(); iter < card_deck.end(); iter++) {
		cout.width(2); cout.fill(' ');
		cout << i++;
		cout << "   " << **iter << endl;
	}
}