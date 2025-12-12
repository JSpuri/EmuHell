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