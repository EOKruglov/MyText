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
		<< "\nDown Arrow - Go Next Title\n"
		<< "Up Arrow - Go Previous\n"
		<< "Right Arrow - Go Down Line\n"
		<< "0 - Print Menu\n"
		<< "1 - Next Line\n"
		<< "2 - Down Line\n"
		<< "3 - New Section\n"
		<< "4 - Delete Next\n"
		<< "5 - Delete Down\n"
		<< "6 - Save\n"
		<< "7 - Print Free Memory\n"
		<< endl;
}

TMem TLink::mem;

void main()
{
	TLink::InitMem(100);

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	TText text;
	char file[] = "C:\\Users\\Ёльдорадо\\Documents\\git\\MyText\\text.txt";

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
		case 38: //uparrow
			text.GoPrevLink();
			clrscr();
			text.Print();
			break;
		case 40: //downarrow
			text.GoNextLink();
			clrscr();
			text.Print();
			break;
		case 39: //rightarrow
			text.GoDownLink();
			clrscr();
			text.Print();
			break;
		case 48 : //0
			PrintMenu();
			break;
		case 49: //1
			Sleep(100);
			clrscr();
			tmp = "New Title";
			text.InsNextLine(To_Char(tmp));
			text.Print();
			break;
		case 50: //2
			Sleep(100);
			clrscr();
			tmp = "New Body";
			text.InsDownLine(To_Char(tmp));
			text.Print();
			break;
		case 51: //3
			Sleep(100);
			clrscr();
			tmp = "New Section";
			text.InsNextSection(To_Char(tmp));
			text.Print();
			break;
		case 52: //4
			clrscr();
			text.DelNext();
			text.Print();
			break;
		case 53: //5
			clrscr();
			text.DelDown();
			text.Print();
			break;
		case 54: //6
			text.Save("C:\\Users\\Ёльдорадо\\Documents\\git\\MyText\\text.txt");
			break;
		case 55: //7
			clrscr();
			free = TLink::PrintFree(text);
			
			text.Print();
			cout << "free mem " << free << endl;
			TLink::PrintFree2();
			TLink::MemClean(text);
			cout << endl;
			cout << endl;
			cout << endl;
			TLink::PrintFree2();
			break;
		case 56: //8
			TLink::MemClean(text);
			break;
		}
		Sleep(300);
	}
	_getch();
}




