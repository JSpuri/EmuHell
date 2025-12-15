#include "bus.hpp"

Bus::Bus()
{
	cpu.SetBus(this);
	
}

void Bus::write (uint16_t addr, uint8_t data)
{
	ram[address] = data;
}

uint8_t Bus::read(uint16_t addr)
{
	return ram[address];
}