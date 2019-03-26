#pragma once
#include <deque>
#include <cstdlib>
#include <ctime>
#include "Card.h"


class Deck {
private:
	Card** card_ptr; // 소멸 담당 리스트
	int card_ptr_size;

	deque<Card*> card_deck;
	deque<Card*> card_used;
	Card* recent_card;
public:
	Deck();
	~Deck();
	Card* DrawTop();
	void AddUsed(Card* c);
	Card* GetRecentCard() const;
	void Shuffle();
	void TestView();

private:
	void RandomizeDeck();
};




Deck::Deck() {
	card_ptr = new Card*[54];
	card_ptr_size = 0;

	for (int i = 0; i < 2; i++) { // JOKER 2개
		Card* temp = new Card(Trump::JOKER, JOKER_NUM);
		card_deck.push_back(temp);
		card_ptr[card_ptr_size++] = temp;
	}

	for (int t = Trump::HEART; t <= Trump::CLOVER; t++) {
		for (int i = A; i <= K; i++) {
			Card* temp = new Card((Trump)t, i);
			card_deck.push_back(temp);
			card_ptr[card_ptr_size++] = temp;
		}
	}

	RandomizeDeck();
}

Deck::~Deck() {
	delete[] card_ptr;
}


Card* Deck::DrawTop() {
	if (card_deck.empty())
		Shuffle();
	Card* temp = card_deck.back();
	card_deck.pop_back();
	return temp;
}


void Deck::AddUsed(Card* c) {
	card_used.push_back(c);
	recent_card = c;
}


Card* Deck::GetRecentCard() const { return recent_card; }


void Deck::Shuffle() {
	card_deck = card_used;
	card_used.clear();
	card_used.push_back(recent_card);
	card_deck.pop_front();
	RandomizeDeck();
}


void Deck::RandomizeDeck() {
	for (int i = card_deck.size(); i > 0; i--) {
		int temp = rand() % i;
		card_deck.push_back(card_deck.at(temp));
		card_deck.erase(card_deck.begin() + temp);
	}
}


void Deck::TestView() {
	int i = 1;
	for (deque<Card*>::iterator iter = card_deck.begin(); iter < card_deck.end(); iter++) {
		cout.width(2); cout.fill(' ');
		cout << i++;
		cout << "   " << **iter << endl;
	}
}