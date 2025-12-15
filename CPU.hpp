#pragma once

class Bus;

class CPU
{
public:
    CPU();
	
	enum FLAGS
	{
		C = (1 << 0),	
		Z = (1 << 1),	
		I = (1 << 2),	
		D = (1 << 3),	
		B = (1 << 4),   
		U = (1 << 5),	
		V = (1 << 6),	
		N = (1 << 7),	
	};
    
	uint8_t accumulator = 0x00;
	uint8_t x_reg = 0x00;
	uint8_t y_reg = 0x00;
    uint8_t stackp = 0x00;
    uint16_t	pc = 0x0000;
    uint8_t status = 0x00;	
	
	void setBus(Bus *bus_pointer);
	
private:
	// Addressing modes functions (they dont in fact do the reading, they just set the register to the right values)
	uint8_t IMP(); uint8_t IMM();
	uint8_t ZP0(); uint8_t ZPX();
	uint8_t ZPY(); uint8_t REL();
	uint8_t ABS(); uint8_t APX();
	uint8_t ABY(); uint8_t IND();
	uint8_t IZX(); uint8_t IZY();
	
	//OPCODES
    uint8_t LDA(); uint8_t LDX(); uint8_t LDY(); uint8_t STA(); uint8_t STX(); uint8_t STY(); //Access
    uint8_t ADC(); uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t SBC(); //Arithmetic 
    uint8_t AND(); uint8_t BIT(); uint8_t EOR(); uint8_t ORA(); //Bitwise
    uint8_t BCC(); uint8_t BCS(); uint8_t BEQ(); uint8_t BNE(); uint8_t BMI(); uint8_t BPL(); uint8_t BVC(); uint8_t BVS(); //Branch
    uint8_t CMP(); uint8_t CPX(); uint8_t CPY(); //Compare
    uint8_t CLC(); uint8_t CLD(); uint8_t CLI(); uint8_t CLV(); uint8_t SEC(); uint8_t SED(); uint8_t SEI(); //Flags
    uint8_t BRK(); uint8_t JMP(); uint8_t JSR(); uint8_t RTI(); uint8_t RTS(); //Jump
    uint8_t PHA(); uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t TSX(); uint8_t TXS(); //Stack
    uint8_t TAX(); uint8_t TAY(); uint8_t TXA(); uint8_t TXY(); uint8_t TYA(); //Transfer
    uint8_t ASL(); uint8_t LSR(); uint8_t ROL(); uint8_t ROR(); //Shift
    uint8_t NOP(); //Other
	
	void clock();
	void reset();
	void irq(); //interrupt request
	void nmi(); //non maskable interrupt request
	
	uint8_t fetch();
	uint8_t fetched = 0x00;
	
	
	uint16_t addr_abs = 0x0000;
	uint16_t addr_rel = 0x00;
	uint8_t opcode = 0x00; //current operation being solved
	uint8_t cycles = 0; //number of cycles left for current operation
	
private:
    Bus *addr_bus;
    
	uint8_t read(uint16_t addr);
    void write (uint16_t addr, uint8_t data);
	
	uint8_t GetFlag(FLAGs f);
	void SetFlag(FLAGS f, bool value);
};