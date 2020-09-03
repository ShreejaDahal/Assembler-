//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once
#include"stdafx.h"

// The elements of an instruction.
class Instruction {

public:

    Instruction();
    ~Instruction() { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType {
        ST_MachineLanguage, 		// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End,
        ST_Illegal
    };
    // Parse the Instruction.
    InstructionType ParseInstruction(string a_buff);

   
    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc) {
        //return a_loc + 1;
        if (m_OpCode == "org" || m_OpCode == "ds")
        {
            return a_loc + m_OperandValue;
        }
        
        return ++a_loc;
    }
    

    // To access the label
    inline string& GetLabel() {

        return m_Label;
    };
    
    inline bool isLabel() {

        return !m_Label.empty();
    };

    inline string& GetInstruction() {
        return m_instruction;
    }

    inline int getOpCodeValue() {
        return m_NumOpCode;
    }

    inline int GetOperandValue() {
        return m_OperandValue;
    }

    inline string GetOperand() {
        return m_Operand;
    }

    inline bool isNumericOperand() {
        return m_IsNumericOperand;
    }

    inline string GetOpCode() {
        return m_OpCode;
    }

    inline void SetOpCode(string str) {
        m_OpCode = str;
    }

    inline void SetLabel(string str) {
        m_Label = str;
    }

    inline void SetOperand(string str) {
        m_Operand = str;
    }

    inline int GetRegisterValue()
    {
        return m_NumRegister;

    }


private:

	void GetLabelOpcodeEtc( const string &a_buff);
	vector<string>ASSEMBLY_LANGUAGE_OPCODE;
    vector<string>MACHINE_LANGUAGE_OPCODE;


    // The elemements of a instruction
    string m_Label;         // The label.
    string m_OpCode;        // The symbolic op code.
    string m_Register;      // The register value.
    string m_Operand;       // The operand.


    string m_instruction;   // The original instruction.

    // Derived values.
    int m_NumOpCode;        // The numerical value of the op code.
    int m_NumRegister;	    // the numeric value for the register.
    InstructionType m_type; // The type of instruction.

    bool m_IsNumericOperand; // == true if the operand is numeric.
    int m_OperandValue;     // The value of the operand if it is numeric.
};


