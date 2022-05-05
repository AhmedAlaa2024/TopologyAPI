#ifndef _TOPOLOGY_H
#define _TOPOLOGY_H

#include <iostream>
#include <unordered_map>

#include "Component.h"

class Topology
{
private:
	std::string id;
	std::unordered_map<std::string, Component*> components;

public:
	Topology(std::string id);
	Topology(std::string id, std::unordered_map<std::string, Component*> components);
	
	void set_ID(std::string id);
	void set_components(std::unordered_map<std::string, Component*> components);

	std::string get_id(void);
	std::unordered_map<std::string, Component*>* get_components(void);

	void add_component(Component* component);
	void print(void);

	~Topology(void);
};

#endif // !_TOPOLOGY_H