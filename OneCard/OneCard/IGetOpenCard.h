#pragma once
#include "Card.h"
#ifndef interface
#define interface class
#endif



class IGetOpenCard {
public:
	virtual Card* GetOpenCard() const = 0;
};