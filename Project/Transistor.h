#ifndef _TRANSISTOR_H
#define _TRANSISTOR_H

#include "Device.h"

class Transistor: public Device
{
public:
	Transistor(std::string name);
	Transistor(std::string name, float defaultValue, float minValue, float maxValue);
	virtual void print(void);
	~Transistor(void);
};

#endif // !_TRANSISTOR_H