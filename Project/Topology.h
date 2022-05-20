#ifndef _TOPOLOGY_H
#define _TOPOLOGY_H

#include <iostream>
#include <vector>

#include "Component.h"
#include "defs.h"

class Topology
{
private:
	std::string id;
	std::vector<Component*>* components;

#if (LOGGING)
	std::ofstream* log;
#endif

public:
	Topology(std::string id);
	Topology(std::string id, std::vector<Component*> components);
	
	void setID(std::string id);
	void setComponents(std::vector<Component*> components);

	std::string getID(void);
	std::vector<Component*>* getComponents(void);

	void addComponent(Component* component);
	void print(void);

#if (LOGGING)
	void setLogger(std::ofstream* log);
#endif

	~Topology(void);
};

#endif // !_TOPOLOGY_H