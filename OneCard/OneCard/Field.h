#pragma once
#include <stack>
#include "Card.h"
#include "IPrint.h"
#include "IGetStack.h"

class Field : public IPrint, public IGetStack {
private:
	stack<const Card*> card_used;
	Trump lead_trump;
	Number lead_number;
	int draw_stack;
	Notice notice;


public:
	Field();
	void PlayCard(const Card* card);
	bool CanPlayCard(const Card* card) const;
	Notice NotifySpecial();
	const Card* GetOpenCard() const;
	void ResetDrawStack();
	int GetDrawStack() const;
	void Print(int x, int y) const;

private:
	void AddDrawStack(Attack atk);
	void SetLead(Trump t, Number n);
	stack<const Card*>* GetStack();
};


Field::Field() : lead_trump(JOKER_TRP), lead_number(JOKER_NUM), notice(Notice::NONE) {
	ResetDrawStack();
}


void Field::PlayCard(const Card* card) {
	AddDrawStack(card->GetAttack());
	SetLead(card->GetTrump(), card->GetNumber());
	switch (lead_number) {
	case NUM_7: notice = Notice::SEVEN; break;
	case J: notice = Notice::JACK; break;
	case Q: notice = Notice::QUEEN; break;
	case K: notice = Notice::KING; break;
	}
	card_used.push(card);
}


bool Field::CanPlayCard(const Card* card) const {
	if (draw_stack != 1 && card->GetAttack() == Attack::ATK_UNDEFINED) // attack field, but not attack card
		return false;
	else {
		if (lead_trump == Trump::JOKER_TRP || card->GetTrump() == Trump::JOKER_TRP)
			return true;
		else
			return lead_trump == card->GetTrump() || lead_number == card->GetNumber();
	}
}


Notice Field::NotifySpecial() {
	Notice message = notice;
	notice = Notice::NONE;
	return message;
}


const Card* Field::GetOpenCard() const {
	return card_used.top();
}


void Field::ResetDrawStack() {
	draw_stack = 1;
}


int Field::GetDrawStack() const {
	return draw_stack;
}


void Field::AddDrawStack(Attack atk) {
	if (atk != Attack::ATK_UNDEFINED) {
		if (draw_stack == 1)
			draw_stack = 0;
		draw_stack += atk;
	}
}


void Field::SetLead(Trump t, Number n) {
	lead_trump = t;
	lead_number = n;
}


stack<const Card*>* Field::GetStack() {
	if (card_used.empty())
		throw "Field::GetStack : 사용한 카드 스택이 비어 있습니다.";

	// reserve one card in used stack for players checking top card
	const Card* top_card = card_used.top();
	stack <const Card*>* temp = new stack <const Card*>();
	card_used.pop();

	while (!card_used.empty()) {
		temp->push(card_used.top());
		card_used.pop();
	}

	card_used.push(top_card);

	return temp;
}


void Field::Print(int x, int y) const {
	ConsoleConfig::GotoXY(x, y);
	cout << *GetOpenCard();
	ConsoleConfig::XYPrint(x + 7, y, CardConfig::TrumpToString(lead_trump)); 
	// ViewConfig 상수를 이용해서 7과 11 따위의 값을 설정하기
	if(draw_stack != 1)
		ConsoleConfig::XYPrint(x + 11, y, "Atk: " + to_string(draw_stack));
}