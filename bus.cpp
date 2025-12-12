#include <bus.hpp>

Bus::Bus()
{
}

void Bus::write (uint16_t address, uint8_t data)
{
	ram[address] = data;
}

uint8_t Bus::read(uint16_t address)
{
	
}