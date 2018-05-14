#pragma once

#include "TLink.h"
#include <stack>
#include <fstream>
#include <iostream>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

using namespace std;

class TText {
protected:
	TLink *pFirst, *pCurr;
	stack <TLink*> st;
	int level;

public:

	TText();
	void GoNextLink();
	void GoDownLink();
	void GoPrevLink();
	void InsNextLine(char *s);
	void InsNextSection(char *s);
	void InsDownLine(char *s);
	void InsDownSection(char *s);
	void DelNext();
	void DelDown();

	TLink* ReadRec(ifstream& file);
	void Read(char *fn);
	void PrintText(TLink *tmp);
	void Print();
	void SaveText(TLink *tmp, ofstream& f);
	void Save(char *name);

	void Reset();
	bool IsEnd();
	void GoNext();

	void MarkCurr() { pCurr->flag = true; }
};
