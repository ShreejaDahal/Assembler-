#include "Emulator.h"
#include "stdafx.h"
#include "Errors.h"

/**/
/*
bool emulator::runProgram()
NAME
	emulator::runProgram() - Runs the emulator.

SYNOPSIS
	bool emulator::runProgram()

DESCRIPTION
	This function runs the emulator for the assembler

RETURNS
	Returns true if the program runs successfully, returns false otherwise.

*/
/**/

bool emulator::runProgram()
{
		int userInput = 0;
		int opcode = 0;
		int address = 0;
		int reg = 0;

		for (int loc = 0; loc < MEMSZ; loc++)
		{
			int contents = m_memory[loc];
			if (contents != 0)
			{
				opcode = contents / 1000000;
				reg = (contents / 100000) % 10; // 14
				address = contents % 100000;

				switch (opcode)
				{
				case 1:
					//Adding the content of register and memory location
					// ACC <-- content(ACC) + c(ADDR)
					m_reg[reg] += m_memory[address];
					break;
				case 2:
					//Subtracting the content of the register and the memory location provided
					// ACC <-- content(ACC) - c(ADDR)
					m_reg[reg] -= m_memory[address];
					break;
				case 3:
					//multiplying the content of the register and memory location provided
					// ACC <--content(ACC) * c(ADDR)
					m_reg[reg] *= m_memory[address];
					break;
				case 4:
					//dividing the contents of the register and memory location provided
					// ACC <--content(ACC) / c(ADDR)
					m_reg[reg] /= m_memory[address];
					break;
				case 5:
					//loads the contents of the address into the register 
					// ACC <--c(ADDR)
					m_reg[reg] = m_memory[address];
					break;
				case 6:
					//the contents of the address is stored in the address provided
					// ADDR<--c(ACC)
					m_memory[address] = m_reg[reg];
					break;
				case 7:
					//reading a line and placing the first 6 digits in a specified address
					cout << "?";
					cin >> userInput;
					userInput %= 1000000;
					m_memory[address] = userInput;
					break;

				case 8:
					//display the content of register 
					// c(ADDR) is displayed
					cout << m_memory[address] << endl;
					break;

				case 9:
					//Changing the index to the location
					// Go to ADDR for next instruction
					loc = address;
					break;
				case 10:
					//Goes to the address if content of the register is less than 0
					// Go to ADDR if c(ACC) < 0
					if (m_reg[reg] < 0)
					{
						loc = address - 1;
					}
					break;
				case 11:
					// Goes to the address if c(ACC) = 0
					if (m_reg[reg] == 0)
					{
						loc = address - 1;
					}
					break;
				case 12:
					// Goes to the address if c(ACC) > 0 
					if (m_reg[reg] > 0)
					{
						loc = address - 1;
					}
					break;

				case 13:
					//terminate the execution
					loc = 1000000;
					break;
				}
			}
		}
			return false;
	}/* bool Emulator::runProgram()*/
