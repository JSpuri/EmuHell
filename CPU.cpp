#include "cpu.hpp"
#include "bus.hpp"


CPU::CPU()
{
	//TODO move this array to file so we don't need to initialize it everytime the program runs
	instructionTable =
	{
	{&CPU::BRK, &CPU::IMM, 7 },{&CPU::ORA, &CPU::IZX, 6 },{&CPU::invalidOP, &CPU::IMP, 2 },{&CPU::invalidOP, &CPU::IMP, 8 },{&CPU::NOP, &CPU::IMP, 3 },{&CPU::ORA, &CPU::ZP0, 3 },{&CPU::ASL, &CPU::ZP0, 5 },{&CPU::invalidOP, &CPU::IMP, 5 },{&CPU::PHP, &CPU::IMP, 3 },{&CPU::ORA, &CPU::IMM, 2 },{&CPU::ASL, &CPU::IMP, 2 },{&CPU::invalidOP, &CPU::IMP, 2 },{&CPU::NOP, &CPU::IMP, 4 },{&CPU::ORA, &CPU::ABS, 4 },{&CPU::ASL, &CPU::ABS, 6 },{&CPU::invalidOP, &CPU::IMP, 6 },
	{&CPU::BPL, &CPU::REL, 2 },{&CPU::ORA, &CPU::IZY, 5 },{&CPU::invalidOP, &CPU::IMP, 2 },{&CPU::invalidOP, &CPU::IMP, 8 },{&CPU::NOP, &CPU::IMP, 4 },{&CPU::ORA, &CPU::ZPX, 4 },{&CPU::ASL, &CPU::ZPX, 6 },{&CPU::invalidOP, &CPU::IMP, 6 },{&CPU::CLC, &CPU::IMP, 2 },{&CPU::ORA, &CPU::ABY, 4 },{&CPU::NOP, &CPU::IMP, 2 },{&CPU::invalidOP, &CPU::IMP, 7 },{&CPU::NOP, &CPU::IMP, 4 }, { &CPU::ORA, &CPU::ABX, 4 }, { &CPU::ASL, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
	{ &CPU::JSR, &CPU::ABS, 6 }, { &CPU::AND, &CPU::IZX, 6 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::BIT, &CPU::ZP0, 3 }, { &CPU::AND, &CPU::ZP0, 3 }, { &CPU::ROL, &CPU::ZP0, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::PLP, &CPU::IMP, 4 }, { &CPU::AND, &CPU::IMM, 2 }, { &CPU::ROL, &CPU::IMP, 2 }, { CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::BIT, &CPU::ABS, 4 }, { &CPU::AND, &CPU::ABS, 4 }, { &CPU::ROL, &CPU::ABS, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 },
	{ &CPU::BMI, &CPU::REL, 2 }, { &CPU::AND, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::AND, &CPU::ZPX, 4 }, { &CPU::ROL, &CPU::ZPX, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::SEC, &CPU::IMP, 2 }, { &CPU::AND, &CPU::ABY, 4 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 7 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::AND, &CPU::ABX, 4 }, { &CPU::ROL, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
	{ &CPU::RTI, &CPU::IMP, 6 }, { &CPU::EOR, &CPU::IZX, 6 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 3 }, { &CPU::EOR, &CPU::ZP0, 3 }, { &CPU::LSR, &CPU::ZP0, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::PHA, &CPU::IMP, 3 }, { &CPU::EOR, &CPU::IMM, 2 }, { &CPU::LSR, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::JMP, &CPU::ABS, 3 }, { &CPU::EOR, &CPU::ABS, 4 }, { &CPU::LSR, &CPU::ABS, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 },
	{ &CPU::BVC, &CPU::REL, 2 }, { &CPU::EOR, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::EOR, &CPU::ZPX, 4 }, { &CPU::LSR, &CPU::ZPX, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::CLI, &CPU::IMP, 2 }, { &CPU::EOR, &CPU::ABY, 4 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 7 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::EOR, &CPU::ABX, 4 }, { &CPU::LSR, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
	{ &CPU::RTS, &CPU::IMP, 6 }, { &CPU::ADC, &CPU::IZX, 6 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 3 }, { &CPU::ADC, &CPU::ZP0, 3 }, { &CPU::ROR, &CPU::ZP0, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::PLA, &CPU::IMP, 4 }, { &CPU::ADC, &CPU::IMM, 2 }, { &CPU::ROR, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::JMP, &CPU::IND, 5 }, { &CPU::ADC, &CPU::ABS, 4 }, { &CPU::ROR, &CPU::ABS, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 },
	{ &CPU::BVS, &CPU::REL, 2 }, { &CPU::ADC, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::ADC, &CPU::ZPX, 4 }, { &CPU::ROR, &CPU::ZPX, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::SEI, &CPU::IMP, 2 }, { &CPU::ADC, &CPU::ABY, 4 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 7 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::ADC, &CPU::ABX, 4 }, { &CPU::ROR, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
	{ &CPU::NOP, &CPU::IMP, 2 }, { &CPU::STA, &CPU::IZX, 6 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::STY, &CPU::ZP0, 3 }, { &CPU::STA, &CPU::ZP0, 3 }, { &CPU::STX, &CPU::ZP0, 3 }, { &CPU::invalidOP, &CPU::IMP, 3 }, { &CPU::DEY, &CPU::IMP, 2 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::TXA, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::STY, &CPU::ABS, 4 }, { &CPU::STA, &CPU::ABS, 4 }, { &CPU::STX, &CPU::ABS, 4 }, { &CPU::invalidOP, &CPU::IMP, 4 },
	{ &CPU::BCC, &CPU::REL, 2 }, { &CPU::STA, &CPU::IZY, 6 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::STY, &CPU::ZPX, 4 }, { &CPU::STA, &CPU::ZPX, 4 }, { &CPU::STX, &CPU::ZPY, 4 }, { &CPU::invalidOP, &CPU::IMP, 4 }, { &CPU::TYA, &CPU::IMP, 2 }, { &CPU::STA, &CPU::ABY, 5 }, { &CPU::TXS, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::NOP, &CPU::IMP, 5 }, { &CPU::STA, &CPU::ABX, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 },
	{ &CPU::LDY, &CPU::IMM, 2 }, { &CPU::LDA, &CPU::IZX, 6 }, { &CPU::LDX, &CPU::IMM, 2 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::LDY, &CPU::ZP0, 3 }, { &CPU::LDA, &CPU::ZP0, 3 }, { &CPU::LDX, &CPU::ZP0, 3 }, { &CPU::invalidOP, &CPU::IMP, 3 }, { &CPU::TAY, &CPU::IMP, 2 }, { &CPU::LDA, &CPU::IMM, 2 }, { &CPU::TAX, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::LDY, &CPU::ABS, 4 }, { &CPU::LDA, &CPU::ABS, 4 }, { &CPU::LDX, &CPU::ABS, 4 }, { &CPU::invalidOP, &CPU::IMP, 4 },
	{ &CPU::BCS, &CPU::REL, 2 }, { &CPU::LDA, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::LDY, &CPU::ZPX, 4 }, { &CPU::LDA, &CPU::ZPX, 4 }, { &CPU::LDX, &CPU::ZPY, 4 }, { &CPU::invalidOP, &CPU::IMP, 4 }, { &CPU::CLV, &CPU::IMP, 2 }, { &CPU::LDA, &CPU::ABY, 4 }, { &CPU::TSX, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 4 }, { &CPU::LDY, &CPU::ABX, 4 }, { &CPU::LDA, &CPU::ABX, 4 }, { &CPU::LDX, &CPU::ABY, 4 }, { &CPU::invalidOP, &CPU::IMP, 4 },
	{ &CPU::CPY, &CPU::IMM, 2 }, { &CPU::CMP, &CPU::IZX, 6 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::CPY, &CPU::ZP0, 3 }, { &CPU::CMP, &CPU::ZP0, 3 }, { &CPU::DEC, &CPU::ZP0, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::INY, &CPU::IMP, 2 }, { &CPU::CMP, &CPU::IMM, 2 }, { &CPU::DEX, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::CPY, &CPU::ABS, 4 }, { &CPU::CMP, &CPU::ABS, 4 }, { &CPU::DEC, &CPU::ABS, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 },
	{ &CPU::BNE, &CPU::REL, 2 }, { &CPU::CMP, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::CMP, &CPU::ZPX, 4 }, { &CPU::DEC, &CPU::ZPX, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::CLD, &CPU::IMP, 2 }, { &CPU::CMP, &CPU::ABY, 4 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 7 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::CMP, &CPU::ABX, 4 }, { &CPU::DEC, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
	{ &CPU::CPX, &CPU::IMM, 2 }, { &CPU::SBC, &CPU::IZX, 6 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::CPX, &CPU::ZP0, 3 }, { &CPU::SBC, &CPU::ZP0, 3 }, { &CPU::INC, &CPU::ZP0, 5 }, { &CPU::invalidOP, &CPU::IMP, 5 }, { &CPU::INX, &CPU::IMP, 2 }, { &CPU::SBC, &CPU::IMM, 2 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::SBC, &CPU::IMP, 2 }, { &CPU::CPX, &CPU::ABS, 4 }, { &CPU::SBC, &CPU::ABS, 4 }, { &CPU::INC, &CPU::ABS, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 },
	{ &CPU::BEQ, &CPU::REL, 2 }, { &CPU::SBC, &CPU::IZY, 5 }, { &CPU::invalidOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 8 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::SBC, &CPU::ZPX, 4 }, { &CPU::INC, &CPU::ZPX, 6 }, { &CPU::invalidOP, &CPU::IMP, 6 }, { &CPU::SED, &CPU::IMP, 2 }, { &CPU::SBC, &CPU::ABY, 4 }, { &CPU::NOP, &CPU::IMP, 2 }, { &CPU::invalidOP, &CPU::IMP, 7 }, { &CPU::NOP, &CPU::IMP, 4 }, { &CPU::SBC, &CPU::ABX, 4 }, { &CPU::INC, &CPU::ABX, 7 }, { &CPU::invalidOP, &CPU::IMP, 7 },
};
	
}

void CPU::setBus(Bus *bus_pointer)
{
    this->addr_bus = bus_pointer;

}

void CPU::clock(){
	if (cyclesleft == 0)
	{
		opcode = read(pc);
		pc++;

		cyclesleft = instructionTable[opcode].ncycles;

		(this->*instructionTable[opcode].addressmode)();
		(this->*instructionTable[opcode].operation)();


		//instructions may need an extra cycle, so we`re checking for that here and adding it if necessary
		//our funtions return 1 if an extra cycle is needed, 0 otherwise
		uint8_t extra_cycle1 = 0;
		uint8_t extra_cycle2 = 0;

		cyclesleft += (extra_cycle1 & extra_cycle2);
	}

	cyclesleft--;
	
}

uint8_t CPU::CPU::read(uint16_t addr)
{
	return addr_bus->read(addr);
}

void CPU::CPU::write(uint16_t addr, uint8_t data)
{
	addr_bus->write(addr, data);
}

//Addressing Modes

uint8_t CPU::IMP()
{
	fetched = accumulator;
	return 0;
}

uint8_t CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

//zero page reading only needs the first 8 bits of the address, so we mask the higher bits
uint8_t CPU::ZP0()
{
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPX()
{
	addr_abs = read(pc) + x_reg;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPY()
{
	addr_abs = read(pc) + y_reg;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::REL()
{
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80) //if the offset is negative we need to set all the higher bits to 1s, since we're working with two`s complement
	{
		addr_rel |= 0xFF00;
	}
	return 0;
}

//absolute addressing reads two bytes to form the full 16 bit address
uint8_t CPU::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	return 0;
}

//both ABX and ABY may need an extra cycle if a page boundary is crossed
uint8_t CPU::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	addr_abs += x_reg;
	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t CPU::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	addr_abs += y_reg;
	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t CPU::IND()
{
	uint16_t pointer_lo = read(pc);
	pc++;
	uint16_t pointer_hi = read(pc);
	pc++;
	uint16_t pointer = (pointer_hi << 8) | pointer_lo;
	//this adressing mode is exclusive to the JMP instruction, which has a bug in the original 6502 that prevents page crossing when reading from the pointer location
	if (pointer_lo == 0x00FF) //if the adress ends in 0xFF page crossing occurs, and thus the bug happens 
	{
		addr_abs = (read(pointer & 0xFF00) << 8) | read(pointer);
	}
	else
	{
		addr_abs = (read(pointer + 1) << 8) | read(pointer);
	}
	return 0;
}

//x_reg is added to the zero page address, and then the final address is read from there
uint8_t CPU::IZX()
{
	uint16_t zerop_addr = read(pc);
	pc++;
	uint16_t lo = read((uint16_t)(zerop_addr + (uint16_t)x_reg) & 0x00FF);
	uint16_t hi = read((uint16_t)(zerop_addr + (uint16_t)x_reg + 1) & 0x00FF);
	addr_abs = (hi << 8) | lo;
	return 0;
}

//y_reg is added to the final address after reading it from the zero page address, aditional cycle may be needed if page boundary is crossed
uint8_t CPU::IZY()
{
	uint16_t zerop_addr = read(pc);
	pc++;
	uint16_t lo = read(zerop_addr & 0x00FF);
	uint16_t hi = read((zerop_addr + 1) & 0x00FF);
	addr_abs = (hi << 8) | lo;
	addr_abs += y_reg;
	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Opcodes implementations

//Access
uint8_t CPU::LDA()
{
	fetched = read(addr_abs);
	accumulator = fetched;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 1;
}

uint8_t CPU::LDX()
{
	fetched = read(addr_abs);
	x_reg = fetched;
	SetFlag(Z, x_reg == 0x00);
	SetFlag(N, x_reg & 0x80);
	return 1;
}

uint8_t CPU::LDY()
{
	fetched = read(addr_abs);
	y_reg = fetched;
	SetFlag(Z, y_reg == 0x00);
	SetFlag(N, y_reg & 0x80);
	return 1;
}

uint8_t CPU::STA()
{
	write(addr_abs, accumulator);
	return 0;
}

uint8_t CPU::STX()
{
	write(addr_abs, x_reg);
	return 0;
}

uint8_t CPU::STY()
{
	write(addr_abs, y_reg);
	return 0;
}

//arithmetic
uint8_t CPU::ADC()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)accumulator + (uint16_t)fetched + (uint16_t)GetFlag(C);
	SetFlag(C, temp > 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	SetFlag(V, (~((uint16_t)accumulator ^ (uint16_t)fetched) & ((uint16_t)accumulator ^ (uint16_t)temp)) & 0x0080); //overflow happens when both the acumulator and the value added to it have the same sign and the result has a different sign
	accumulator = temp & 0x00FF;
	return 1;
}

uint8_t CPU::DEC()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)fetched - 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	return 0;
}

uint8_t CPU::DEX()
{
	x_reg--;
	SetFlag(Z, x_reg == 0x00);
	SetFlag(N, x_reg & 0x80);
	return 0;
}

uint8_t CPU::DEY()
{
	y_reg--;
	SetFlag(Z, y_reg == 0x00);
	SetFlag(N, y_reg & 0x80);
	return 0;
}

uint8_t CPU::INC()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)fetched + 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	return 0;
}

uint8_t CPU::INX()
{
	x_reg++;
	SetFlag(Z, x_reg == 0x00);
	SetFlag(N, x_reg & 0x80);
	return 0;
}

uint8_t CPU::INY()
{
	y_reg++;
	SetFlag(Z, y_reg == 0x00);
	SetFlag(N, y_reg & 0x80);
	return 0;
}

uint8_t CPU::SBC()
{
	fetched = read(addr_abs);
	uint16_t value = (uint16_t)fetched ^ 0x00FF; //we can use the same logic as ADC by inverting all the bits of the value to be subtracted
	uint16_t temp = (uint16_t)accumulator + value + (uint16_t)GetFlag(C);
	SetFlag(C, temp > 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	SetFlag(V, (((uint16_t)accumulator ^ temp) & (value ^ temp)) & 0x0080); //overflow happens when both the acumulator and the value added to it have different signs and the result has the same sign as the value
	accumulator = temp & 0x00FF;
	return 1;
}

//bitwise
uint8_t CPU::AND()
{
	fetched = read(addr_abs);
	accumulator = accumulator & fetched;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 1;
}

uint8_t CPU::BIT()
{
	fetched = read(addr_abs);
	uint8_t temp = accumulator & fetched;
	SetFlag(Z, (temp == 0x00));
	SetFlag(N, fetched & 0x80);
	SetFlag(V, fetched & 0x40);
	return 0;
}

uint8_t CPU::EOR()
{
	fetched = read(addr_abs);
	accumulator = accumulator ^ fetched;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 1;
}

uint8_t CPU::ORA()
{
	fetched = read(addr_abs);
	accumulator = accumulator | fetched;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 1;
}

//branching
uint8_t CPU::BCC()
{
	if (GetFlag(C) == 0)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BCS()
{
	if (GetFlag(C) == 1)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BMI()
{
	if (GetFlag(N) == 1)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BPL()
{
	if (GetFlag(N) == 0)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}	

uint8_t CPU::BVC()
{
	if (GetFlag(V) == 0)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

uint8_t CPU::BVS()
{
	if (GetFlag(V) == 1)
	{
		cyclesleft++;
		uint16_t temp_addr = pc + addr_rel;
		if ((temp_addr & 0xFF00) != (pc & 0xFF00))
		{
			cyclesleft++;
		}
		pc = temp_addr;
	}
	return 0;
}

//compare
uint8_t CPU::CMP()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)accumulator - (uint16_t)fetched;
	SetFlag(C, accumulator >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	return 1;
}

uint8_t CPU::CPX()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)x_reg - (uint16_t)fetched;
	SetFlag(C, x_reg >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	return 1;
}

uint8_t CPU::CPY()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)y_reg - (uint16_t)fetched;
	SetFlag(C, y_reg >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	return 1;
}

//flags
uint8_t CPU::CLC()
{
	SetFlag(C, false);
	return 0;
}


uint8_t CPU::CLD() //nes actually has the decimal mode permanently disabled, but we can still use it to store a state
{
	SetFlag(D, false);
	return 0;
}

uint8_t CPU::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t CPU::CLV() //there is no set overflow equivalent instruction, which is done on the 6502 by external hardware
{
	SetFlag(V, false);
	return 0;
}

uint8_t CPU::SEC()
{
	SetFlag(C, true);
	return 0;
}

uint8_t CPU::SED()
{
	SetFlag(D, true);
	return 0;
}

uint8_t CPU::SEI()
{
	SetFlag(I, true);
	return 0;
}

//Jump
uint8_t CPU::BRK()
{
	pc++;
	SetFlag(I, true);
	write(0x0100 + stackp, (pc >> 8) & 0x00FF);
	stackp--;
	write(0x0100 + stackp, pc & 0x00FF);
	stackp--;
	SetFlag(B, true);
	write(0x0100 + stackp, status);
	stackp--;
	SetFlag(B, false);
	uint16_t lo = read(0xFFFE);
	uint16_t hi = read(0xFFFF);
	pc = (hi << 8) | lo;
	return 0;
}

uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t CPU::JSR()
{
	pc--;
	write(0x0100 + stackp, (pc >> 8) & 0x00FF);
	stackp--;
	write(0x0100 + stackp, pc & 0x00FF);
	stackp--;
	pc = addr_abs;
	return 0;
}

uint8_t CPU::RTI()
{
	stackp++;
	status = read(0x0100 + stackp);
	SetFlag(B, false);
	SetFlag(U, true);
	stackp++;
	uint16_t lo = read(0x0100 + stackp);
	stackp++;
	uint16_t hi = read(0x0100 + stackp);
	pc = (hi << 8) | lo;
	return 0;
}

uint8_t CPU::RTS()
{
	stackp++;
	uint16_t lo = read(0x0100 + stackp);
	stackp++;
	uint16_t hi = read(0x0100 + stackp);
	pc = ((hi << 8) | lo);
	pc++;
	return 0;
}

//stack manipulation
uint8_t CPU::PHA()
{
	write(0x0100 + stackp, accumulator);
	stackp--;
	return 0;
}

uint8_t CPU::PHP()
{
	write(0x0100 + stackp, status | B | U); //both break and unused flags are set when pushing to stack
	SetFlag(B, false);
	SetFlag(U, true);
	stackp--;
	return 0;
}

uint8_t CPU::PLA()
{
	stackp++;
	accumulator = read(0x0100 + stackp);
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 0;
}

uint8_t CPU::PLP()
{
	stackp++;
	status = read(0x0100 + stackp);
	SetFlag(U, true);
	return 0;
}

uint8_t CPU::TSX()
{
	x_reg = stackp;
	SetFlag(Z, x_reg == 0x00);
	SetFlag(N, x_reg & 0x80);
	return 0;
}

uint8_t CPU::TXS()
{
	stackp = x_reg;
	return 0;
}

//transfer
uint8_t CPU::TAX()
{
	x_reg = accumulator;
	SetFlag(Z, x_reg == 0x00);
	SetFlag(N, x_reg & 0x80);
	return 0;
}

uint8_t CPU::TAY()
{
	y_reg = accumulator;
	SetFlag(Z, y_reg == 0x00);
	SetFlag(N, y_reg & 0x80);
	return 0;
}

uint8_t CPU::TXA()
{
	accumulator = x_reg;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 0;
}

uint8_t CPU::TYA()
{
	accumulator = y_reg;
	SetFlag(Z, accumulator == 0x00);
	SetFlag(N, accumulator & 0x80);
	return 0;
}

//shift
uint8_t CPU::ASL()
{
	fetched = read(addr_abs);
	uint16_t temp = (uint16_t)fetched << 1;
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (instructionTable[opcode].addressmode == &CPU::IMP)
	{
		accumulator = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}
	return 0;
}

uint8_t CPU::LSR()
{
	fetched = read(addr_abs);
	SetFlag(C, fetched & 0x01);
	uint16_t temp = (uint16_t)fetched >> 1;
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (instructionTable[opcode].addressmode == &CPU::IMP)
	{
		accumulator = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}
	return 0;
}

uint8_t CPU::ROL()
{
	fetched = read(addr_abs);
	uint16_t temp = ((uint16_t)fetched << 1) | (uint16_t)GetFlag(C);
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (instructionTable[opcode].addressmode == &CPU::IMP)
	{
		accumulator = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}
	return 0;
}

uint8_t	CPU::ROR()
{
	fetched = read(addr_abs);
	uint16_t temp = ((uint16_t)GetFlag(C) << 7) | ((uint16_t)fetched >> 1);
	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (instructionTable[opcode].addressmode == &CPU::IMP)
	{
		accumulator = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}
	return 0;
}

uint8_t CPU::NOP()
{
	//here i'm using the opcodes of the unofficial instrucions that one lone coder provided in his code, maybe after everything else is working i'll implement all of them
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

//illegal opcode
uint8_t CPU::invalidOP()
{
	return 0;
}
