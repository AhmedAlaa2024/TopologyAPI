#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <iostream>
#include <unordered_map>

#include "Device.h"

class Component
{
private:
	std::string type;
	std::string id;
	Device* device;
	std::unordered_map<std::string, std::string> netlist;

#if (LOGGING)
	std::ofstream* log;
#endif

public:
	Component(std::string type, std::string id);
	Component(std::string id);
	Component(std::string type, std::string id, Device* device);
	Component(std::string type, std::string id, Device* device, std::unordered_map<std::string, std::string> &netlist);

	void set_type(std::string type);
	void set_id(std::string id);
	void set_device(Device* device);
	void set_netlist(std::unordered_map<std::string, std::string> &netlist);

	std::string get_type(void);
	std::string get_id(void);
	Device* get_device(void);
	std::unordered_map<std::string, std::string>* get_netlist(void);

#if (LOGGING)
	void setLogger(std::ofstream* log);
#endif

	void print(void);
	~Component(void);
};

#endif // !_COMPONENT_H