//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Instruction.h"
#include "Emulator.h"


/**/
/*
Assembler:: Assembler(int argc, char *argv[])

NAME
	Assembler::Assembler(int argc, char *argv[]) - Constructor for the assembler. Takes argc and argv  as its arguments

SYNOPSIS

	Assembler:: Assembler(int argc, char *argv[])
	argc        -->            Total number of arguments in the command line
	argv        -->			   User input array of strings

DESCRIPTION
	This is the constructor of the Assembler class. 

RETURNS
	VOID


*/
/**/

Assembler::Assembler( int argc, char *argv[] )
	: m_facc(argc, argv)
{
    // Nothing else to do here at this point.
} /* Assembler::Assembler(int argc, char *argv[]) */

// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.

/**/
/*
void Assembler::PassI()

NAME
	Assembler::PassI() - Populates the symbol. 

SYNOPSIS
	void Assembler::PassI()

DESCRIPTION
	This function establishes the location of the labels. It stores the location for all the labels required for
	the assembler and records errors, if found.

RETURNS
	VOID

*/
/**/
void Assembler::PassI( ) 
{

	Errors::InitErrorReporting();
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    while( true ) {
		
        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine(line) ) 
		{

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
		}
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel()) {
            m_symtab.AddSymbol( m_inst.GetLabel(), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}/* void Assembler::PassI() */

/**/
/*
void Assembler::PassII()
NAME
	Assembler::PassII() - Does the translation for the assembler code 

SYNOPSIS
	void Assembler::PassII()

DESCRIPTION
	This function translates the code from the text file provided by the user to machine language by 
	computing the content of the machine code.

RETURNS
	VOID


*/
/**/
void Assembler:: PassII()
{
	Errors::InitErrorReporting();
	
	m_facc.rewind();
	int loc = 0;
	
	cout << "TRANSLATION OF THE PROGRAM: " << endl;
	cout << setw(10) << "Location" << setw(8) << "   Contents" << setw(36) << "Original Statement" << endl;
	while (true)
	{
		int values = 0;

		string line;
		if (!m_facc.GetNextLine(line))
		{
			Errors::RecordError("    Missing an End Statement!");
			break;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		//Checking the size of label to make sure it's not too big
		if (m_inst.GetLabel().length() > 10)
		{
			Errors::RecordError(" Illegal. The label size is too big for " + m_inst.GetLabel());
			m_inst.SetLabel("?");
			break;
		}
		//checking too see if a label is a number
		else if (m_inst.GetLabel()[0] >= '0' && m_inst.GetLabel()[0] <= '9')
		{
			Errors::RecordError("Illegal. This label " + m_inst.GetLabel()+ " cannot start with a number.");
			break;
		}
		
		//checking the last statement to see if it is END
		if (st == Instruction::ST_End)
		{
			cout << "\t \t" << m_inst.GetInstruction() << endl;
			break;
		}
		//checking if the isntruction type is illegal
		if (st == Instruction::ST_Illegal)
		{
			Errors::RecordError(m_inst.GetOpCode() + "   Illegal opcode!");
		}

		//if memory address exceeds 100,000, report error
		if (m_inst.isNumericOperand())
		{
			if (m_inst.GetOperandValue() > 100000)
			{
				Errors::RecordError("The value of " + m_inst.GetOpCode() + "    is too high. Illegal");
			}
		}
		//skip instruction types that are not machine language or assembler language
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			cout << "\t\t\t" << m_inst.GetInstruction() << endl;
			continue;
		}

		values = 1000000 * m_inst.getOpCodeValue() + m_inst.GetRegisterValue() * 100000;
	
		//checking if the Opcode is an assembly language instruction
		if (st == Instruction::ST_AssemblerInstr)
		{

			//check if the opcode is "end" and is operand is empty
			if (m_inst.GetOpCode() != "end" && m_inst.GetOperand().empty())
			{
				Errors::RecordError("Empty operand for" + m_inst.getOpCodeValue());
			}

			else if (m_inst.GetOpCode() == "org")
			{
				values = 0;
			}

			else if (m_inst.GetLabel().empty())
			{
				//report error for labels if opcode is not "org" or "ds"
				if (m_inst.GetOpCode() != "org" && m_inst.GetOpCode() != "ds")
				{
					Errors::RecordError("  Error. Label for " + m_inst.GetOpCode() + " missing");
				}
			}
			else {
				if (m_inst.GetOpCode() == "dc")
				{
					values = m_inst.GetOperandValue();
				}
				
				else 
				{
					values = 0;
				}

			}
		}
		//if the Opcode is a machine language, determine contents for the machine language instructions 
		else 
		{
			
			if (m_inst.GetOperand().empty() && m_inst.getOpCodeValue() != 13)
			{
				Errors::RecordError(m_inst.GetOpCode() + "  is Illegal. Missing Operand.");
			}


			else
			{ 
				//report errors for no operand
				if (!m_inst.isNumericOperand() && !m_inst.GetOperand().empty())
				{
					int location = 0;

					if (!m_symtab.LookupSymbol(m_inst.GetOperand(), location))
					{
						Errors::RecordError("  Illegal. Symbol " + m_inst.GetOperand() + " not found");
						location = 99999;
					}

					else
					{
						values += location;
					}
				}
			}
		}
		//pass the contents to the emulator
		m_emul.insertMemory(loc, values);
		
		cout << setfill(' ') << setw(5) << loc << "\t";
		if (values != 0)
		{
			string StringHas = string(8 - to_string(values).length(), '0') + to_string(values);
			cout << "     " << StringHas;

		}

		else
		{
			cout << "\t";
		}

		cout << "\t" << m_inst.GetInstruction() << endl;

		//compute the location of the next instruction
		loc = m_inst.LocationNextInstruction(loc);
	}
	Errors::DisplayErrors();
}/*  void Assembler::PassII()*/

/**/
/*
void Assembler::RunProgramInEmulator()
NAME
	Assembler::RunProgramInEmulator() - Checks if there are any errors and runs the emulator is none are found.

SYNOPSIS
	void Assembler::RunProgramInEmulator()

DESCRIPTION
	This function checks for errors and runs the emulator if there no errors are found. 

RETURNS
	VOID


*/
/**/

void Assembler:: RunProgramInEmulator()
{
	cout << "Results from Emulating Program" << endl;
	if(!Errors:: WasThereErrors())
	{
		cout << "Emulator couldn't start because of errors "<< endl;
	}
	
	else{
		m_emul.runProgram();
	}

	cout << endl;
	cout << "END OF EMULATION! ";
}	
/* void Assembler::RunProgramInEmulator() */
		
	
		
		
		
		
		
		
