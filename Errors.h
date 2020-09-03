//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>
#include<iostream>
using namespace std;

class Errors 
{

public:
    
    // Initializes error reports.
	static void InitErrorReporting()
	{
		m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
	}
    // Records an error message.
	static void RecordError(const string a_emsg) 
	{
		m_ErrorMsgs.push_back(a_emsg);
	}
	
	static bool WasThereErrors() //using this to check if there were any errors, returns true if error message vector is empty
	{ 
		return m_ErrorMsgs.empty();
	}
	
    // Displays the collected error message.
    static void DisplayErrors();

private:

    static vector<string> m_ErrorMsgs;
	
};
#endif