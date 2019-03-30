#pragma once
#include "ConsoleConfig.h"
#include "PlayerController.h"


class UserController : public PlayerController {
public:
	virtual int GetKey() const;
	void UserScreen() const;
};

int UserController::GetKey() const {

}

void UserController::UserScreen() const {

}