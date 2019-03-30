#pragma once
#include "ConsoleConfig.h"

class IOController {
private:
	static IOController* instance;
	IOController();

public:
	static IOController& GetInstance();
	void ViewGame() const;
};



IOController* IOController::instance = NULL;


IOController::IOController() {}


IOController& IOController::GetInstance() {
	if (instance == NULL) {
		instance = new IOController();
	}
	return *instance;
}
