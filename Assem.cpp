/*
 * Assembler main program.
 */
#pragma once
#include "stdafx.h"  // This must be present if you use precompiled headers which you will use. 
#include <stdio.h>
#include "Assembler.h"
#include "Instruction.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Assembler VICVICassem(argc, argv);

    // Establish the location of the labels:
    VICVICassem.PassI();

    // Display the symbol table.
    VICVICassem.DisplaySymbolTable();
    system("pause");

    // Output the symbol table and the translation.
    VICVICassem.PassII();
    system("pause");

    // Run the emulator on the Quack3200 program that was generated in Pass II.
    VICVICassem.RunProgramInEmulator();

    // Terminate indicating all is well.  If there is an unrecoverable error, the 
    // program will terminate at the point that it occurred with an exit(1) call.
    return 0;
}
