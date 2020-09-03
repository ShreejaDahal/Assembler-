//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"
#include <iostream>
using namespace std;

// Don't forget to comment the function headers.

/**/
/*
FileAccess::FileAccess(int argc, char *argv[])
NAME
    FileAccess::FileAccess(int argc, char *argv[]) - Initiates the access to the given file name

 SYNOPSIS
    FileAccess::FileAccess(int argc, char *argv[])
    argc		-->			Total number of arguments
    argv		-->			User entered array of characters

DESCRIPTION

    This function is the constructor for FileAccess class that aims to open the file.

RETURNS
    VOID

*/
/**/

FileAccess::FileAccess( int argc, char *argv[] )
{
    
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem  <filename>" << endl;
        exit(1);
    }
    
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
   // ifstream m_sfile(arg);
    m_sfile.open(argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( !m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated." << endl;
        cerr << argv[1] << endl;
        exit( 1 ); 
    }
}/* FileAccess::FileAccess(int argc, char *argv[]) */

/**/
/*
FileAccess::~FileAccess()
NAME
    FileAccess::~FileAccess() - Closes the open file

SYNOPSIS
    FileAccess::~FileAccess()

DESCRIPTION
    This function is the destructor of the FileAcess

RETURNS
    VOID


*/
/**/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}/* FileAccess::~FileAccess() */

/**/
/*
bool FileAccess::GetNextLine(string &a_buff)
NAME
    FileAccess::GetNextLine(string &a_buff) - Gets the next line from the text file

SYNOPSIS
    bool FileAccess::GetNextLine(string &a_buff)
    a_buff		-->			Contains the string of the line

DESCRIPTION
    This function reads the next line from the open file if any other lines exist

RETURNS
    Returns true if it successfully get the next line, false if next line doesn't exit


*/
/**/

// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_buff ); 
    // Return indicating success.
    return true;
}/* bool FileAccess::GetNextLine(string &a_buff) */

/**/
/*
void FileAccess::rewind()
NAME
    FileAccess::rewind() - It rewinds the pointer to beginnning of the file

SYNOPSIS
    void FileAccess::rewind()

DESCRIPTION
    This function rewinds the pointer to the beginning of the file

RETURNS
    VOID

/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}/* void FileAccess::rewind() */
    
