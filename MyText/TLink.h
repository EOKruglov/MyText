#pragma once
#include <stdlib.h>
#include <string.h>

class TLink {

public:
	char str[80];
	TLink* pNext, *pDown;
	

	TLink(char *s = NULL, TLink * pN = NULL, TLink *pD = NULL);
	~TLink();
	void SetLine(char *s);
	char* GetLine();
};
