#pragma once
#include "ConsoleConfig.h"
#ifndef interface
#define interface class
#endif
namespace CS = ConsoleConfig;

interface IPrint {
public:
	virtual void Print(int x, int y) const = 0;
};