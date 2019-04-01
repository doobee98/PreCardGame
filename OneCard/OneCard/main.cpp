#include <iostream>
#include "GameController.h"
using namespace std;

int main(void) {
	cout << "Project Onecard" << endl;
	
	GameController& game = GameController::GetInstance();
	game.Run();
}