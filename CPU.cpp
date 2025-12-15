#include "cpu.hpp"

CPU::CPU()
{
}

void CPU::setBus(Bus *bus_pointer)
{
    this->addr_bus = bus_pointer;

}

uint8_t CPU::CPU::read(uint16_t addr)
{
	return bus->read(addr);
}

void CPU::CPU::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}