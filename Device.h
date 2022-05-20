#ifndef _DEVICE_H
#define _DEVICE_H

#include <iostream>

class Device
{
private:
	std::string name;
	float defaultValue;
	float minValue;
	float maxValue;

#if (LOGGING)
	std::ofstream* log;
#endif

public:
	Device(std::string name);
	Device(std::string name, float defaultValue);
	Device(std::string name, float defaultValue, float minValue);
	Device(std::string name, float defaultValue, float minValue, float maxValue);

	void set_name(std::string name);
	void set_defaultValue(float defaultValue);
	void set_minValue(float minValue);
	void set_maxValue(float maxValue);

	std::string get_name(void);
	float get_defaultValue(void);
	float get_minValue(void);
	float get_maxValue(void);

	virtual void print(void);

#if (LOGGING)
	void setLogger(std::ofstream* log);
#endif

	~Device(void);
};

#endif // !_DEVICE_H