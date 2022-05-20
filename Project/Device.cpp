#include "Device.h"


Device::Device(std::string name):name(name), defaultValue(0.0f), minValue(0.0f), maxValue(0.0f)
{
	std::cout << "<Notification>: Device['" + this->name << "'] is being constructed!" << std::endl;
}

Device::Device(std::string name, float defaultValue):name(name),defaultValue(defaultValue), minValue(0.0f), maxValue(0.0f)
{
	std::cout << "<Notification>: Device['" + this->name << "'] is being constructed!" << std::endl;
}

Device::Device(std::string name, float defaultValue, float minValue):name(name), defaultValue(defaultValue), minValue(minValue), maxValue(0.0f)
{
	std::cout << "<Notification>: Device['" + this->name << "'] is being constructed!" << std::endl;
}

Device::Device(std::string name, float defaultValue, float minValue, float maxValue) : name(name), defaultValue(defaultValue), minValue(minValue), maxValue(maxValue)
{
	std::cout << "<Notification>: Device['" + this->name << "'] is being constructed!" << std::endl;
}

void Device::set_name(std::string name)
{
	this->name = name;
}

void Device::set_defaultValue(float defaultValue)
{
	this->defaultValue = defaultValue;
}

void Device::set_minValue(float minValue)
{
	this->minValue = minValue;
}

void Device::set_maxValue(float maxValue)
{
	this->maxValue = maxValue;
}

std::string Device::get_name(void)
{
	return this->name;
}

float Device::get_defaultValue(void)
{
	return this->defaultValue;
}

float Device::get_minValue(void)
{
	return this->minValue;
}

float Device::get_maxValue(void)
{
	return this->maxValue;
}

void Device::print(void)
{
	std::cout << "'" << this->name << "': {" << std::endl;
	std::cout << "'default': " << this->defaultValue << "," << std::endl;
	std::cout << "'min': " << this->minValue << "," << std::endl;
	std::cout << "'max': " << this->maxValue << "," << std::endl;
	std::cout << "}," << std::endl;
}

#if (LOGGING)
void Topology::setLogger(std::ofstream* log)
{
	this->log = log;
}
#endif

Device::~Device(void)
{
	std::cout << "<Notification>: Device['" + this->name << "'] is being destructed!" << std::endl;
}
