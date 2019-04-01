#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

enum class Color {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN,
	LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum Key {
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_S,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_ESC, KEY_UNDEFINED
};


namespace ConsoleConfig {
	void GotoXY(int x, int y) {
		COORD pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void XYPrint(int x, int y, std::string str) {
		GotoXY(x, y);
		std::cout << str;
	}

	void SetColor(Color _color = Color::LIGHTGRAY, Color _bgcolor = Color::BLACK) {
		int color = (int)_color;
		int bgcolor = (int)_bgcolor;
		color &= 0xf;
		bgcolor &= 0xf;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
	}

	void Clrscr() { system("cls"); }

	Key GetKey() {
		int key = _getch();
		if (key == 0) {
			key = _getch();
			switch (key) {
			case 59: return KEY_F1; case 60: return KEY_F2;
			case 61: return KEY_F3; case 62: return KEY_F4;
			case 63: return KEY_F5; default: return KEY_UNDEFINED;
			}
		}
		else if (key >= 'A' && key <= 'Z')
			key -= 'A' - 'a';
		
		switch (key) {
		case '1': return KEY_1; case '2': return KEY_2;
		case '3': return KEY_3; case '4': return KEY_4;
		case '5': return KEY_5; case '6': return KEY_6;
		case '7': return KEY_7; case '8': return KEY_8;
		case '9': return KEY_9; case '0': return KEY_0;
		case 'q': return KEY_Q; case 'w': return KEY_W;
		case 'e': return KEY_E; case 'r': return KEY_R;
		case 't': return KEY_T; case 's': return KEY_S;
		case 27: return KEY_ESC; default: return KEY_UNDEFINED;
		}
	}
};