#include <stdlib.h>
#include "TLink.h"
#include <string.h>

TLink::TLink(char *s = NULL, TLink * pN = NULL, TLink *pD = NULL) {
	pNext = pN;
	pDown = pD;

	if (s == NULL)
		str[0] = '\0';
	strcpy(str, s);

}

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




