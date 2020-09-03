# Assembler-

#The Quack3200 Computer

The Quack3200 is a decimal computer with 100,000 words of memory. Each word consists of 8 decimal digits. There is an additional 10 words of memory called registers. These are on chip memory. The machine language instructions for the Quack3200 is of the following form:

                         |2 digits             | 1 digit                 |5 digits             |
                         |operation code | register number |address portion|
A machine language program is a sequence of machine language instructions stored in memory. The computer runs a machine language program by executing a sequence of instructions stored in successive memory locations. The first instruction of a program is assumed to be at location 100. The following are the machine language instructions for the Quack3200.

NAME OP. CODE MEANING

ADD 01 Reg <-- c(Reg) + c(ADDR) (The contents of the register specified in the instruction and of the memory location specified by the address portion of the instruction are added together. The result is placed in the register.):

SUBTRACT 02 Reg <-- c(Reg) - c(ADDR)

MULTIPLY 03 Reg <-- c(Reg) * c(ADDR)

DIVIDE 04 Reg <-- c(Reg) / c(ADDR)

LOAD 05 Reg <-- c(ADDR)

STORE 06 ADDR <-- c(Reg)

READ 07 A line is read and record the number found there in the specified address. The register value is ignored.

WRITE 08 c(ADDR) is displayed The register value is ignored.

BRANCH 09 go to ADDR for next instruction. The register value is ignored.

BRANCH MINUS 10 go to ADDR if c(Reg) < 0

BRANCH ZERO 11 go to ADDR if c(Reg) = 0

BRANCH POSITIVE 12 go to ADDR if c(Reg) > 0

HALT 13 terminate execution. The register value is ignored.
