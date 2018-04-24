#include "TText.h"
#include "TLink.h"
#include <iostream>

using namespace std;


TText::TText(){}

void TText::GoNextLink() {
	if (this->pCurr->pNext != NULL)
	{
		st.push(this->pCurr);
		pCurr = this->pCurr->pNext;
	}
}


void TText::GoDownLink() {
	if (this->pCurr->pDown != NULL)
	{
		st.push(this->pCurr);
		pCurr = this->pCurr->pDown;
	}
}

void TText::GoPrevLink() {
	if (!st.empty())
	{
		this->pCurr = st.top();
		st.pop();
	}
}

void TText::InsNextLine(char *s) {
	TLink *p = new TLink(s, pCurr->pNext, NULL);
	pCurr->pNext = p;
}

void TText::InsNextSection(char *s) {
	TLink *p = new TLink(s, NULL, pCurr->pNext);
	pCurr->pNext = p;
}

void TText::InsDownLine(char *s) {
	TLink *p = new TLink(s, pCurr->pDown, NULL);
	pCurr->pDown = p;
}

void TText::InsDownSection(char *s) {
	TLink *p = new TLink(s, NULL, pCurr->pDown);
	pCurr->pDown = p;
}

void TText::DelNext() {
	if (pCurr->pNext != NULL)
	{
		TLink *p = pCurr->pNext;
		pCurr->pNext = p->pNext;
		delete p;
	}
}

void TText::DelDown() {
	if (pCurr->pDown != NULL)
	{
		TLink *p = pCurr->pDown;
		pCurr->pDown = p->pDown;
		delete p;
	}
}


TLink* TText::ReadRec(ifstream& file) {
	char buf[80];
	TLink *tmp, *first = NULL;

	while (!file.eof())
	{
		file.getline(buf, 80, '\n');
		if (buf[0] == '}')
			break;
		else
			if (buf[0] == '{')
			tmp->pDown = ReadRec(file);
			else
				if (first == NULL)
				{
					first = new TLink(buf);
					tmp = first;
				}
				else
				{
					tmp->pNext = new TLink(buf);
					tmp = tmp->pNext;
				}
	}
	return first;
}

void TText::Read(char *fn) {
	ifstream ifs(fn);
	pFirst = ReadRec(ifs);
}

void TText::Print() {
	level = 0;
	PrintText(pFirst);
}

void TText::PrintText(TLink *tmp) {
	if (tmp != NULL)
	{
		cout << tmp->str << endl;
		for (int i = 0; i < level; i++)
			cout << "_";
		level++;
		PrintText(tmp->pDown);
		level--;
		PrintText(tmp->pNext);
	}
}


void TText::SaveText(TLink *tmp, ofstream& f) {
	f << tmp->str << endl;
	if (tmp->pDown != NULL)
	{
		f << "{\n";
		SaveText(tmp->pDown, f);
		f << "}\n";
	}
	if (tmp->pNext != NULL)
		SaveText(tmp -> pNext, f);
}

void TText::Save(char *name) {
	ofstream ofs(name);
	SaveText(pFirst, ofs);
}

void TText::Reset() {
	while (!st.empty())
		st.pop();

	pCurr = pFirst;
	st.push(pCurr);
	if (pFirst->pDown != NULL)
		st.push(pFirst->pDown);

	if (pFirst->pNext != NULL)
		st.push(pFirst->pNext);
}

bool TText::IsEnd() {
	return st.empty();
}

void TText::GoNext() {
	if (!st.empty())
	{
		pCurr = st.top();
		st.pop();
	}

	if (pCurr != pFirst)
	{
		if (pCurr->pNext != NULL)
			st.push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			st.push(pCurr->pDown);
	}
}


