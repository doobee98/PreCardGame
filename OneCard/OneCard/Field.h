#pragma once
#include "CardConfig.h"

class Field {
private:
	Trump lead_suit;
	int lead_number;
	int atk_stack;

public:
	Field();
	Trump GetLeadSuit() const;
	void SetLeadSuit(Trump t);
	int GetLeadNumber() const;
	void SetLeadNumber(int num);
	void ResetAtkStack();
	void AddAtkStack(Attack num);
	bool IsAttacking() const;
};




Field::Field() {
	SetLeadSuit(Trump::JOKER);
	ResetAtkStack();
}


Trump Field::GetLeadSuit() const { return lead_suit; }
void Field::SetLeadSuit(Trump t) {
	lead_suit = t;
}


int Field::GetLeadNumber() const { return lead_number; }
void Field::SetLeadNumber(int num) {
	lead_number = num;
}


void Field::AddAtkStack(Attack num) {
	atk_stack += static_cast<int>(num);
}
void Field::ResetAtkStack() {
	atk_stack = 0;
}


bool Field::IsAttacking() const {
	if (atk_stack == 0)
		return false;
	else
		return true;
}

