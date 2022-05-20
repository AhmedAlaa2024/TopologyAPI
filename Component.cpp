#include "Component.h"

Component::Component(std::string type, std::string id):type(type), id(id), device(nullptr), netlist(NULL)
{
	std::cout << "<Notification>: component[" + this->id + "] is being constructed!" << std::endl;
}

Component::Component(std::string id) : type(""), id(id), device(nullptr), netlist(NULL)
{
	std::cout << "<Notification>: component[" + this->id + "] is being constructed!" << std::endl;
}

Component::Component(std::string type, std::string id, Device* device) : type(type), id(id), device(device), netlist(NULL)
{
	std::cout << "<Notification>: component[" + this->id + "] is being constructed!" << std::endl;
}

Component::Component(std::string type, std::string id, Device* device, std::unordered_map<std::string, std::string> &netlist) : type(type), id(id), device(device)
{
	std::cout << "<Notification>: component[" + this->id + "] is being constructed!" << std::endl;
	this->set_netlist(netlist);
}

void Component::set_type(std::string type)
{
	this->type = type;
}

void Component::set_id(std::string id)
{
	this->id = id;
}

void Component::set_device (Device* device)
{
	this->device = device;
}

void Component::set_netlist(std::unordered_map<std::string, std::string> &netlist)
{
	for (auto node : netlist)
	{
		this->netlist.insert({ node.first, node.second });
	}
}

std::string Component::get_type(void)
{
	return this->type;
}

std::string Component::get_id(void)
{
	return this->id;
}

Device* Component::get_device(void)
{
	return this->device;
}

std::unordered_map<std::string, std::string>* Component::get_netlist(void)
{
	return &(this->netlist);
}

#if (LOGGING)
void Topology::setLogger(std::ofstream* log)
{
	this->log = log;
}
#endif

void Component::print(void)
{
	std::cout << "{" << std::endl;
	std::cout << "'type': " << this->type << "," << std::endl;
	std::cout << "'id': " << this->id << "," << std::endl;
	this->device->print();
	std::cout << "," << std::endl;
	std::cout << "'netlist': {" << std::endl;
	int i = 1;
	for (auto terminal : this->netlist)
	{
		if (i != this->netlist.size())
			std::cout << "'" << terminal.first << "': " << terminal.second << "," << std::endl;
		else
			std::cout << "'" << terminal.first << "': " << terminal.second << std::endl;
	}
	std::cout << "}" << std::endl;
	std::cout << "}" << std::endl;
}

Component::~Component(void)
{
	std::cout << "<Notification>: component[" + this->id + "] is being destructed!" << std::endl;

	delete this->device;
}
