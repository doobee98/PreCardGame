#pragma once
#include <stack>
#ifndef interface
#define interface class
#endif

class Card;


interface IGetStack {
public:
	virtual std::stack<const Card*>* GetStack() = 0;
};
