#pragma once

#include "TLink.h"
#include <stack>
#include <fstream>
using namespace std;

class TText {
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
};
