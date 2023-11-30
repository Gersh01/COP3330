#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{   
    //(sizeof(Mem) < (65536 >> 2)
    if(PC % 4 == 0) {
        *instruction = Mem[PC >> 2];
        return 0;
    }
    else {
        return 1;
    }
    
}

/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
   *op = (instruction & 0xFC000000) >> 26;
    
    if(!(*op ^ 0)) { //r-type
        *r1 = (instruction & 0x03E00000) >> 21;
        *r2 = (instruction & 0x001F0000) >> 16;
        *r3 = (instruction & 0x00003800) >> 11;
        *offset = (instruction & 0x000007B0) >> 6;
        *funct = (instruction & 0x0000003F); 
    }
    else if(*op < 8) { //j-type
        *jsec = (instruction & 0x03FFFFFF);
    }
    else { //i-type
        *r1 = (instruction & 0x03E00000) >> 21;
        *r2 = (instruction & 0x00180000) >> 16;
        *offset = (instruction & 0x0000FFFF);
    }
    
}

/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    extended_value = offset << 16;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
