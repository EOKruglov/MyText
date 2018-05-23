
#include "TLink.h"
#include "TText.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
class TLink;
class TText;


TLink:: ~TLink(){}

void TLink::SetLine(char *s) {
	int i = 0, size = 1;
	while (s[i] != '\0')
	{
		size++;
		i++;
	}
	for (i = 0; i < size; i++)
		str[i] = s[i];
}

char* TLink::GetLine() {
	return str;
}

void* TLink::operator new(size_t s)
{
	TLink *tmp = mem.pFree;
	if (mem.pFree != NULL)
		mem.pFree = mem.pFree->pNext;
	return tmp;
}

void TLink::operator delete(void* p)
{
	TLink *tmp = (TLink*)p;
	tmp->pNext = mem.pFree;
	mem.pFree = tmp;
}

void TLink::InitMem(int s)
{
	mem.pFirst = (TLink*) new char[sizeof(TLink)*s];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + (s - 1);
	TLink *tmp = mem.pFree;
	for (int i = 0; i < s - 1; i++)
	{
		tmp->str[0] = '\0';
		tmp->pNext = tmp + 1;
		tmp++;
	}
	tmp->str[0] = '\0';
	mem.pLast->pNext = NULL;
}

int TLink::PrintFree(TText &t)
{
	int result = 0;
	TLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		result++;
		tmp = tmp->pNext;
	}
	result++;
	return result;
}
void TLink::PrintFree2()
{
	TLink *tmp = mem.pFree;
	int i = 1;

	while(tmp != NULL)
	{
		if (tmp->str != NULL)
		{
			cout << i << "  " << tmp->str << endl;
			tmp = tmp->pNext;
			i++;
		}
	}
}
void TLink::MemClean(TText &t)
{
	for (t.Reset(); !t.IsEnd(); t.GoNext())
		t.MarkCurr();
	TLink* tmp;
	tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = true;
		tmp = tmp->pNext;
	}
	tmp->flag = true;
	tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		if (!tmp->flag)
		{
			TLink* buf = mem.pFree;
			mem.pFree = tmp;
			mem.pFree->pNext = buf;
		}
		tmp->flag = false;
		tmp = tmp++;
	}
	if (!tmp->flag)
	{
		TLink* buf = mem.pFree;
		mem.pFree = tmp;
		mem.pFree->pNext = buf;
	}
	tmp->flag = false;

	/*for (t.Reset(); !t.IsEnd(); t.GoNext())
		strcat(t.GetCurr()->str, "-->");
	TLink *tmp = mem.pFree;
	while (tmp != NULL)
	{
		strcpy(tmp->str, "-->");
		tmp = tmp->pNext;
	}
	tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		if (strstr(tmp->str, "-->") == NULL)
			tmp->str[strlen(tmp->str) - 1] = '\0';
		tmp++;
	}*/
}


