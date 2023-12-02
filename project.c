// Alexander Gershfeld, Gabriel Perez, Ishan Patel
// Final Project - OurSpim
// CDA3103
// Jongouk Choi
// December 2, 2023

#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{ 
    if (ALUControl == 0) { // addition or don't care
        *ALUresult = A + B;
    }
    else if (ALUControl == 1) { // subtraction
        *ALUresult = A - B;
        if (ALUresult == 0) *Zero = 1;
    }
    else if (ALUControl == 2) { // set on less than
        if ((short)A < B) *ALUresult = 1; //cast A as a signed integer
        else{
            *ALUresult = 0;
            *Zero = 1;
        }
    }
    else if (ALUControl == 3) { // set on less than unsigned
        if (A < B) *ALUresult = 1;
        else {
            *ALUresult = 0;
            *Zero = 1;
        }
    }
    else if (ALUControl == 4) { // AND operation
        if (A == B) *ALUresult = 1;
        else {
            *ALUresult = 0;
            *Zero = 1;
        }
    }
    else if (ALUControl == 5) { // XOR
        *ALUresult = A ^ B;

        if (*ALUresult == 0) {
            *ALUresult = 0;
            *Zero = 1;
       }
    }
    else if (ALUControl == 6) { // shift - used for lui
        *ALUresult = (B << 16); 
    }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC, unsigned *Mem, unsigned *instruction)
{                       
    if (PC % 4 == 0 && PC < 65536) { //if the counter is word aligned as well as within the bounds of memory
        *instruction = Mem[PC >> 2]; //assigning the instruction to the spot in memory corresponding to the PC

        // illegal instructions
        if ((*instruction & 0xdeadbeaf == 1) || (*instruction & 0xbadabeaf == 1) || (*instruction & 0 == 1))
            return 1;
        else return 0;
    }
    else return 1;
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1, unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    *op = (instruction & 0xFC000000) >> 26;

    if (!(*op ^ 0)) { // r-type
        *r1 = (instruction & 0x03E00000) >> 21;
        *r2 = (instruction & 0x001F0000) >> 16;
        *r3 = (instruction & 0x0000F800) >> 11;
        *offset = (instruction & 0x000007B0) >> 6;
        *funct = (instruction & 0x0000003F);
    }
    else if (*op == 2) { // j-type
        *jsec = (instruction & 0x03FFFFFF);
    }
    else { // i-type
        *r1 = (instruction & 0x03E00000) >> 21;
        *r2 = (instruction & 0x001F0000) >> 16;
        *offset = (instruction & 0x0000FFFF);
    }
}

/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op, struct_controls *controls)
{
    switch (op) {
        case 0: // r-type: add, subtract, and, xor, slt, and sltu
            controls->RegDst = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 7; // depends on funct
            controls->MemWrite = 0;
            controls->ALUSrc = 0;
            controls->RegWrite = 1; //write data to register
            break;
        case 2: // j-type - jump
            controls->RegDst = 2;
            controls->Jump = 1;
            controls->Branch = 0;
            controls->MemRead = 2;
            controls->MemtoReg = 2;
            controls->ALUOp = 0; // dont care
            controls->MemWrite = 0;
            controls->ALUSrc = 2;
            controls->RegWrite = 0;
            break;
        case 4: // beq
            controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 1; // subtract
            controls->MemWrite = 0;
            controls->ALUSrc = 0;
            controls->RegWrite = 0;
            break;
        case 8: // addi
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 0; // add
            controls->MemWrite = 0;
            controls->ALUSrc = 1; //data is from sign extended
            controls->RegWrite = 1; //write data to register
            break;
        case 10: // slti
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 2; // slt
            controls->MemWrite = 0;
            controls->ALUSrc = 1; //data is from sign extended
            controls->RegWrite = 1; //write data to register
            break;
        case 11: // sltiu
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 3; // sltu
            controls->MemWrite = 0;
            controls->ALUSrc = 1; //data is from sign extended
            controls->RegWrite = 1; //write data to register
            break;
        case 15: // lui
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 2;
            controls->MemtoReg = 0;
            controls->ALUOp = 6; // shift left 16
            controls->MemWrite = 0;
            controls->ALUSrc = 1; //data is from sign extended
            controls->RegWrite = 1; //write data to register
            break;
        case 35: // lw
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 1; //read data from memory
            controls->MemtoReg = 1; //write data from memory to register
            controls->ALUOp = 0; // add
            controls->MemWrite = 0;
            controls->ALUSrc = 1; //offset is used and added to register
            controls->RegWrite = 1; //write data read from memory to register calculated with alu
            break;
        case 43: // sw
            controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 2;
            controls->MemtoReg = 2;
            controls->ALUOp = 0; // add
            controls->MemWrite = 1; //write data to memory 
            controls->ALUSrc = 1;
            controls->RegWrite = 0;
            break;
        default: //any instructions not listed in Appendix A
            return 1;
        }

    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1, unsigned r2, unsigned *Reg, unsigned *data1, unsigned *data2)
{
    //initialize variables to data inside the index r1 and r2 of Reg
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset, unsigned *extended_value)
{
    unsigned signbit = offset >> 15; //figure out the sign bit
    if (signbit == 0) //if positive
        *extended_value = 0b00000000000000000000000000000000 + offset;
    else //if negative
        *extended_value = 0b11111111111111110000000000000000 + offset;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value, unsigned funct, char ALUOp, char ALUSrc, unsigned *ALUresult, char *Zero)
{   
    if (ALUOp == 7) { //when ALUOp = 111
        switch (funct) {
            case 32: // add
                ALUOp = 0;
                break;
            case 34: // subtract
                ALUOp = 1;
                break;
            case 36: // and
                ALUOp = 4;
                break;
            case 38: // xor
                ALUOp = 5;
                break;
            case 42: // slt
                ALUOp = 2;
                break;
            case 43: // sltu
                ALUOp = 3;
                break;
            default: //any illegal ALU operation
                return 1;
        }
    }
    if (ALUSrc == 1) // i type uses extended value
        ALU(data1, extended_value, ALUOp, ALUresult, Zero);
    else // r-type uses registers
        ALU(data1, data2, ALUOp, ALUresult, Zero);

    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem)
{
    if (MemWrite == 1) { // write to memory
        if ((ALUresult % 4) != 0) //check for word alignment
            return 1;
        else
        {
            Mem[ALUresult >> 2] = data2;
            return 0;
        }
    }
    else if (MemRead == 1) { // read from memory
        if ((ALUresult % 4) != 0)
            return 1;
        else {
            *memdata = Mem[ALUresult >> 2];
            return 0;
        }
    }
    else return 0;
}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst, char MemtoReg, unsigned *Reg)
{
    if (RegWrite == 1 && MemtoReg == 1 && RegDst == 0) // bring data from memory - lw 
        Reg[r2] = memdata;
    else if (RegWrite == 1 && MemtoReg == 0 && RegDst == 0) // bring data from aluresult into r2
        Reg[r2] = ALUresult;
    else if (RegWrite == 1 && MemtoReg == 0 && RegDst == 1) // bring data from aluresult into r3
        Reg[r3] = ALUresult;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC)
{
    *PC = *PC + 4; //update PC regardless of jump or branch
    
    if (Jump == 1)
        *PC = (*PC >> 27) + (jsec << 2);
    else if (Branch == 1 && Zero == 1)
        *PC += (extended_value << 2);
}
