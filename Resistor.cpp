#include "Resistor.h"

Resistor::Resistor(std::string name):Device(name)
{
	std::cout << "<Notification>: Resistor['" + name << "'] is being constructed!" << std::endl;
}

Resistor::Resistor(std::string name, float defaultValue, float minValue, float maxValue):Device(name, defaultValue, minValue, maxValue)
{
	std::cout << "<Notification>: Resistor['" + name << "'] is being constructed!" << std::endl;
}

void Resistor::print(void)
{
	Device::print();
}

Resistor::~Resistor(void)
{
}
