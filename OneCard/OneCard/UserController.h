#pragma once
#include "ConsoleConfig.h"
#include "PlayerController.h"


class UserController : public PlayerController {
public:
	virtual int GetKey() const;
};

int UserController::GetKey() const {

}