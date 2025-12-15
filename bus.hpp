#pragma once

#include<cstlib>

#include "CPU.hpp"

class Bus
{
public:
    Bus();
	
public:
    void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);
};

private:
    CPU cpu;
	
	//placeholder ram while we dont have the address range for each device (nes addressable range is 64KB)
	std::array<uint8_tm 64 * 1024> ram;