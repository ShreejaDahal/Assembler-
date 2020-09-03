#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

/**/
/*
void Errors::DisplayErrors()
NAME
	void Errors::DisplayErrors() - Prints out the errors

SYNOPSIS
	void Errors::DisplayErrors()

DESCRIPTION
	This function prints out all of the existing errors after translating the code

RETURNS
	VOID


*/
/**/

void Errors::DisplayErrors() {
	for (int i = 0; i < m_ErrorMsgs.size(); i++)
	{
		cout << m_ErrorMsgs[i] << endl;
	}
} /* void Errors::DisplayErrors()*/
