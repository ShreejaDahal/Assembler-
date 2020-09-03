//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( string &a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) 
	{

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
void SymbolTable::DisplaySymbolTable()
NAME
	void Errors::DisplaySymbolTable() - Displays the symbol table

SYNOPSIS
	void Errors::DisplayErrors()

DESCRIPTION
	This function displays the symbol number, symbol itself, and the location of the symbol

RETURNS
	VOID


*/
/**/

void SymbolTable::DisplaySymbolTable()
{
	int count = 0;
	map<string, int>::iterator it;

	cout << "Output from test program" << endl;
	cout << "Symbol#    Symbol      Location" << endl;

	for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++)
	{
		cout << count++ << "\t   " << it->first << "\t    " << it->second << endl;
	}
}/*void SymbolTable::DisplaySymbolTable() */

/**/
/*
 bool SymbolTable:: LookupSymbol(string &a_symbol, int &a_loc)
 NAME
	LookupSymbol- Looks for symbol in the symbol table
 
 SYNOPSIS
	bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
	a_symbol       -->       The Symbol to look for
	a_loc          -->       If the symbol is found places the symbol's location in a_loc

DESCRIPTION
	Looks up if a symbol exists in the symbol table.
 
RETURN
	Returns true if symbol exists, false otherwise

AUTHOR
	Shreeja Dahal
DATE
	7:24 PM 5/13/2020
*/
/**/
bool SymbolTable::LookupSymbol(const string &a_symbol, int &a_loc) {
	
	//checking the existence of the symbol in the symbol table 
	if (m_symbolTable.find(a_symbol) != m_symbolTable.end()) {
		//getting the location and status of the symbol
		a_loc = m_symbolTable[a_symbol];
		return true;
	}
	return false;
}/*bool SymbolTable:: LookupSymbol(string &a_symbol, int &a_loc)*/
