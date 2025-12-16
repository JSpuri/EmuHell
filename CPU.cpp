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
	}
	
}

uint8_t CPU::CPU::read(uint16_t addr)
{
	return addr_bus->read(addr);
}

void CPU::CPU::write(uint16_t addr, uint8_t data)
{
	addr_bus->write(addr, data);
}