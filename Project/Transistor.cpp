#include "Transistor.h"

Transistor::Transistor(std::string name) :Device(name)
{
}

Transistor::Transistor(std::string name, float defaultValue, float minValue, float maxValue):Device(name, defaultValue, minValue, maxValue)
{
}

void Transistor::print(void)
{
	Device::print();
}

Transistor::~Transistor(void)
{
}
