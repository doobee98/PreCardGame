#pragma once
#ifndef interface
#define interface class
#endif

class Card;

interface IDrawTop {
public:
	virtual const Card* DrawTop() = 0;
};