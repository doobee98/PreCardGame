#pragma once
#include "CardConfig.h"
#ifndef interface
#define interface class
#endif

class IChangeField {
public:
	virtual void SetLeadSuit(Trump t) = 0;
	virtual void SetLeadNumber(int number) = 0;
};