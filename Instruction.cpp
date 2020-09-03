
#include "stdafx.h"
#include <sstream>
#include "Instruction.h"
#include "Errors.h"
using namespace std;

Instruction:: Instruction()
{
	m_IsNumericOperand = true; // == true if the operand is numeric.
	ASSEMBLY_LANGUAGE_OPCODE = {"dc", "ds", "org", "end" };
	MACHINE_LANGUAGE_OPCODE = { "add", "sub", "mult", "div", "load", "store", "read", "write", "b", "bm", "bz", "bp", "halt" };
};

/**/
/*
 Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
 NAME
	ParseInstruction(string &a_buff)
 
 SYNOPSIS
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
	a_buff --> The original statement that needs to be parsed
 
 DESCRIPTION
	This function checks if the opCode is in machine language, assembly language, a comment
		or an end instruction.
 RETURN
	The enum type of instruction (ST_MachineLanguage, ST_AssemblerInstr, ST_Comment, ST_End, or ST_Illegal)

*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string a_buff)
{
	// Make copy of original instruction
	m_instruction = a_buff;
	int count = 0;

	if (a_buff.empty())
	{
		return ST_Illegal;
	}

	if (a_buff[0] == ';')
	{
		m_type = InstructionType::ST_Comment;
		return m_type;
	}

	a_buff = a_buff.substr(0, a_buff.find(';'));
	
	// Parse instruction into basic elements.
	GetLabelOpcodeEtc(a_buff);
	return m_type;
}/*Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)*/

/**/
/*
 void Instruction::GetLabelOpcodeEtc(const string &a_buff)
 NAME
	GetLabelOpcodeEtc(const string &a_buff)
 
 SYNOPSIS
	void Instruction::GetLabelOpcodeEtc(const string &a_buff)
	a_buff --> The statement that contains the label, opcode, and operand
 
 DESCRIPTION
	This function identifies the label, opcode and operand and determines their numerical value.
 
 RETURN
	VOID

*/
/**/

void Instruction::GetLabelOpcodeEtc(const string& a_buff)
{
	m_Label = m_OpCode = m_Register = m_Operand = "";
	istringstream ins(a_buff);

	string a1, a2, a3, a4;
	ins >> a1 >> a2 >> a3 >> a4;
	int count = 0;

	for (int i = 1; a_buff[i] != '\0'; i++)
	{
		if (a_buff[i] == ' ') {
			count++;
		}
	}
	if (a_buff[0] != ' ' && a_buff[0] != '\t')
	{
		m_Label = a1;
		m_OpCode = a2;
		m_Operand = a3;
		if (a4 != "")
		{
			Errors::RecordError("Invalid instruction");
		}

	}
	else
	{
		m_OpCode = a1;
		m_Operand = a2;
		if (a3 != "")
		{
		Errors::RecordError("Invalid Instruction");
		}
	}
		// Check operand for comma and parse accordingly 
		size_t icomma = m_Operand.find(',');
		if (icomma != string::npos)
		{
			m_Register = m_Operand.substr(0, icomma);
			m_Operand = m_Operand.substr(icomma + 1);
		}
		else
		{
			m_Register = "9";
		}

		if (count == 2)
		{
			if (find(MACHINE_LANGUAGE_OPCODE.begin(), MACHINE_LANGUAGE_OPCODE.end(), m_OpCode) == MACHINE_LANGUAGE_OPCODE.end()) {
				if (find(ASSEMBLY_LANGUAGE_OPCODE.begin(), ASSEMBLY_LANGUAGE_OPCODE.end(), m_OpCode) == ASSEMBLY_LANGUAGE_OPCODE.end()) {
					m_Operand = m_OpCode;
					m_OpCode = m_Label;
					m_Label = "";
				}
			}
		}
		else if (count == 1)
		{
			m_OpCode = m_Label;
			m_Label = "";
		}

		for (int i = 0; i < m_OpCode.length(); i++)
		{
			m_OpCode[i] = tolower(m_OpCode[i]);
		}

		if (find(MACHINE_LANGUAGE_OPCODE.begin(), MACHINE_LANGUAGE_OPCODE.end(), m_OpCode) != MACHINE_LANGUAGE_OPCODE.end()) {
			m_type = ST_MachineLanguage;
			m_NumOpCode = distance(MACHINE_LANGUAGE_OPCODE.begin(), find(MACHINE_LANGUAGE_OPCODE.begin(), MACHINE_LANGUAGE_OPCODE.end(), m_OpCode)) + 1;
		}
		else if (m_OpCode == "end") {
			m_type = ST_End;
		}
		else if (find(ASSEMBLY_LANGUAGE_OPCODE.begin(), ASSEMBLY_LANGUAGE_OPCODE.end(), m_OpCode) != ASSEMBLY_LANGUAGE_OPCODE.end()) {
			m_type = ST_AssemblerInstr;
		}

		else {
			m_type = ST_Illegal;
		}

		// Try to check if the Operand is a numeric value and store it if it is true.
		try {
			m_OperandValue = stoi(m_Operand);
		}
		catch (invalid_argument&) {
			m_IsNumericOperand = false;
		}

		//getting integer value 
		m_NumRegister = stoi(m_Register);
	
}/*void Instruction::GetLabelOpcodeEtc(const string &a_buff)*/




