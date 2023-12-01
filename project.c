#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned* ALUresult, char* Zero)
{
	    // should i initizlized char* Zero to "0"

	if (ALUControl == 0) {// addition or don't care
		*ALUresult = A + B;
	}
	else if (ALUControl == 1) {// subtraction
		*ALUresult = A - B;
		if(ALUresult == 0) *Zero = 1;
	}
	else if (ALUControl == 2) {// set on less than
		if (A < B) *ALUresult = 1;	
		else {
			*ALUresult = 0;
			*Zero = 1;
		}
	}
	else if (ALUControl == 3) {// set on less than unsigned
	
	}
	else if (ALUControl == 4) {// AND operation
		if (A == B)
			*ALUresult = 1;
		else {
			*ALUresult = 0;
			*Zero = 1;
		}
	}
	else if (ALUControl == 5) {	//XOR
		if (A != B)
			*ALUresult = 1;
		else {
			*ALUresult = 0;
			*Zero = 1;
		}
	}
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
void instruction_partition(unsigned instruction, unsigned* op, unsigned* r1, unsigned* r2, unsigned* r3, unsigned* funct, unsigned* offset, unsigned* jsec)
{
   *op = (instruction & 0xFC000000) >> 26;
    
    if(!(*op ^ 0)) { //r-type
        *r1 = (instruction & 0x03E00000) >> 21;
        *r2 = (instruction & 0x001F0000) >> 16;
        *r3 = (instruction & 0x00003800) >> 11;
        *offset = (instruction & 0x000007B0) >> 6;
        *funct = (instruction & 0x0000003F); 
    }
    else if(*op == 2) { //j-type
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
int instruction_decode(unsigned op, struct_controls* controls)
{
	switch(op) {
        case 0: //r-type: add, subtract, and, xor, slt, and sltu
        	controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 7; //depends on funct
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 1;
          	break;
        case 2: //j-type
          	controls->RegDst = 0;
		controls->Jump = 1;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
      	    	break;
        case 4: //beq
          	controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 1;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->ALUOp = 1; //subtract
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;  
          	break;
        case 8: //addi
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0; //add
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
          	break;
        case 10: //slti
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 2;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
      		break;
        case 11: //sltiu
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 3;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
          	break;
        case 15: //lui
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 1;
		controls->ALUOp = 6;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
          	break;
        case 35: //lw
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 1;
		controls->MemtoReg = 1;
		controls->ALUOp = 0; //add
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
          	break;
        case 43: //sw
          	controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0; //add
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
          	break;
        default:
          return 1;
    }
    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2]; 
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    unsigned signbit = offset >> 15;
    if (signbit == 0) {
        *extended_value = 0b00000000000000000000000000000000 + offset;
    }
    
    else {
        *extended_value = 0b11111111111111110000000000000000 + offset;
    }
    
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value, unsigned funct, char ALUOp, char ALUSrc, unsigned* ALUresult, char* Zero)
{
  	if(ALUOp == 7) {
		switch(funct) {
			case 32: //add
				ALUOp = 0;
				break;
			case 34: //subtract
				ALUOp = 1;
				break;
			case 36: //and
				ALUOp = 4;
				break;
			case 38: //xor
				ALUOp = 5;
				break;
			case 42: //slt
				ALUOp = 2;
				break;
			case 43: //sltu
				ALUOp = 3;
				break;
			default:
				return 1;
		}
}

if (ALUSrc == 1) // i type uses extended value
ALU(data1, extended_value, ALUOp, ALUresult, Zero);
else //r-type uses registers
ALU(data1,data2,ALUOp,ALUresult,Zero);

//If overflows, then it halts and return 1


return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned* memdata, unsigned* Mem)
{

}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst, char MemtoReg, unsigned* Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned* PC)
{

}
