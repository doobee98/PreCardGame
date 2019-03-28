#pragma once
#include <stack>
#include "Card.h"
#ifndef interface
#define interface class
#endif

class IGetStack {
public:
	virtual stack <Card*>* GetStack() = 0;
};
