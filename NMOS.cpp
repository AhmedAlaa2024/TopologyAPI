#include "NMOS.h"

NMOS::NMOS(std::string name) :Device(name)
{
	std::cout << "<Notification>: NMOS['" + name << "'] is being constructed!" << std::endl;
}

NMOS::NMOS(std::string name, float defaultValue, float minValue, float maxValue):Device(name, defaultValue, minValue, maxValue)
{
	std::cout << "<Notification>: NMOS['" + name << "'] is being constructed!" << std::endl;
}

void NMOS::print(void)
{
	Device::print();
}

NMOS::~NMOS(void)
{
}
