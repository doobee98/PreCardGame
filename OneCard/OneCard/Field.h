#pragma once
#include <stack>
#include <utility>
#include "Card.h"
#include "CardConfig.h"
#include "IGetOpenCard.h"
#include "IGetStack.h"


class Field : public IGetOpenCard, public IGetStack {
private:
	stack <Card*> card_used;
	pair <Trump, int> lead;
	int draw_stack;

public:
	Field();
	virtual Card* GetOpenCard() const;
	void PlayCard(Card* c);


	void ResetDrawStack();
	int GetDrawStack() const;
	Trump GetLeadSuit() const;
	int GetLeadNumber() const;
	bool IsAttacking() const;

private:
	void SetLead(Trump t, int num);
	void AddDrawStack(Attack num);
	stack <Card*>* GetStack();
};




Field::Field() {
	SetLead(Trump::JOKER, JOKER_NUM);
	ResetDrawStack();
}


Card* Field::GetOpenCard() const {
	return card_used.top();
}


void Field::PlayCard(Card* c) {
	card_used.push(c);
	AddDrawStack(c->GetAtkValue());
	SetLead(c->GetTrump(), c->GetNumber());
	// 7의 경우 IOController에서 Trump를 결정하게 물어보도록 메소드를 호출할 것
}


void Field::ResetDrawStack() {
	draw_stack = 1;
}

int Field::GetDrawStack() const { return draw_stack; }
Trump Field::GetLeadSuit() const { return lead.first; }
int Field::GetLeadNumber() const { return lead.second; }


bool Field::IsAttacking() const {
	if (draw_stack == 1)
		return false;
	else
		return true;
}


void Field::SetLead(Trump t, int num) {
	lead.first = t;
	lead.second = num;
}

void Field::AddDrawStack(Attack num) {
	if (num != Attack::UNDEFINED) {
		if (draw_stack == 1)
			draw_stack--;
		draw_stack += static_cast<int>(num);
	}
}



stack <Card*>* Field::GetStack() {
	if (card_used.empty())
		throw "Field::GetStack : 사용한 카드 스택이 비어 있습니다.";

	// 맨 위 한장은 남기고 섞는다. 리드 카드를 확인해야 하기 때문
	Card* top_card = card_used.top();
	stack <Card*>* temp = new stack <Card*>();
	card_used.pop();

	while (!card_used.empty()) {
		temp->push(card_used.top());
		card_used.pop();
	}

	card_used.push(top_card);
	
	return temp;
}