#include "TLink.h"
#include "TText.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

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

std::wstring SToWs(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

char* To_Char(std::string str)
{
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());

	return cstr;
}

void PrintMenu()
{
	std::cout
		<< "0 - print menu\n"
		<< "dwn_arrow - go next header\n"
		<< "up_arrow - go prev\n"
		<< "right_arrow - go inside header\n"
		<< "1 - new header\n"
		<< "2 - new body\n"
		<< "3 - new section\n"
		<< "4 - delete header\n"
		<< "5 - delete body\n"
		<< "6 - save\n"
		<< "7 - print free mem\n"
		<< std::endl;
}

TMem TLink::mem;

istream& operator >> (istream& input, string &s)
{
	
}

void main()
{
	TLink::InitMem(100);

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	TText text;
	char file[] = "D:\\Vstudio\\Git\\MyText\\text.txt";

	int inputKey;
	int x = 0, y = 0, free;

	std::string title = "MyTextProg";
	std::string tmp;
	std::wstring stemp = SToWs(title);
	LPCWSTR result = stemp.c_str();

	SetConsoleTitle(result);
	SetConsoleOutputCP(1251);

	PrintMenu();
	text.Read(file);
	text.Print();
	gotoxy(0, 0);

	while (true)
	{
		inputKey = GetKey();

		tmp = "";
		switch (inputKey)
		{
		case 48 : 
			PrintMenu();
			break;
		case 49:
			Sleep(100);
			clrscr();
			cout << "Enter header name\n";
			cin >> tmp;
			if (tmp == "") tmp = "NewTitle";
			text.InsNextLine(To_Char(tmp));
			text.Print();
			break;
		}
	}
}




