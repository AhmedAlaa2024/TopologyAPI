#ifndef _NMOS_H
#define _NMOS_H

#include "Device.h"

class NMOS: public Device
{
public:
	NMOS(std::string name);
	NMOS(std::string name, float defaultValue, float minValue, float maxValue);
	virtual void print(void);
	~NMOS(void);
};

#endif // !_TRANSISTOR_H