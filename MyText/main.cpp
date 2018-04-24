#include "TLink.h"
#include "TText.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int GetKey(){
	int i = 0;
	while (i < 256)
	{
		if (GetAsyncKeyState(i))
			return i;
		i++;
	}
}

void clrscr(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);

	DWORD count;
	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &count);
	SetConsoleCursorPosition(console, zpos);
}

void clreol(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);
	WORD attr;
	DWORD count;
	COORD zpos;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &count);
	SetConsoleCursorPosition(console, buf.dwCursorPosition);
}

void gotoxy(int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console)
		return;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(console, pos);
}




