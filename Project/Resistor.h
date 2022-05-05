#ifndef _RESISTOR_H
#define _RESISTOR_H

#include <iostream>
#include "Device.h"

class Resistor: public Device
{
public:
	Resistor(std::string name);
	Resistor(std::string name, float defaultValue, float minValue, float maxValue);
	virtual void print(void);
	~Resistor(void);
};

#endif // !_RESISTOR_H