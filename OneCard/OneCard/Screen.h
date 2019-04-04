#pragma once
#include <Windows.h>


namespace Screen {
	int g_nScreenIndex;
	HANDLE g_hScreen[2];


	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenGotoXY(int x, int y);
	void ScreenPrint(int x, int y, char* string);
	void SetColor(unsigned short color);
}


void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	//화면 버퍼 2개를 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void Screen::ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void Screen::ScreenClear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	int size = 80 * 30;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(g_hScreen[g_nScreenIndex], &info);

	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', size, Coor, &dw);
	FillConsoleOutputAttribute(g_hScreen[g_nScreenIndex], info.wAttributes, size, Coor, &dw);
}

void Screen::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void Screen::ScreenGotoXY(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
}


void Screen::ScreenPrint(int x, int y, char* string)
{
	ScreenGotoXY(x, y);
	DWORD dw;
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);

}

void Screen::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}
