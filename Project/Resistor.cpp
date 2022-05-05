#include "Resistor.h"

Resistor::Resistor(std::string name):Device(name)
{
}

Resistor::Resistor(std::string name, float defaultValue, float minValue, float maxValue):Device(name, defaultValue, minValue, maxValue)
{
}

void Resistor::print(void)
{
	Device::print();
}

Resistor::~Resistor(void)
{
}
