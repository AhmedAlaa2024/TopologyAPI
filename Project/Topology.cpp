#include "Topology.h"

Topology::Topology(std::string id):id(id), components(nullptr)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being constructed." << std::endl;
	// STREAM(log, "<Notification>: Topology[" + this->id + "] is being constructed." << std::endl);
}

Topology::Topology(std::string id, std::vector<Component*> components):id(id)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being constructed." << std::endl;
	this->setComponents(components);
}

void Topology::setID(std::string id)
{
	this->id = id;
}

void Topology::setComponents(std::vector<Component*> components)
{
	for (auto component : components)
		this->components->push_back(component);
}

std::string Topology::getID(void)
{
	return this->id;
}

std::vector<Component*>* Topology::getComponents(void)
{
	return this->components;
}

void Topology::addComponent(Component* component)
{
	if (this->components == nullptr)
		this->components = new std::vector<Component*>();
	(this->components)->push_back(component);
}

void Topology::print(void)
{
	std::cout << "Topology[" + this->id + "]: {" << std::endl;
	for (auto component : *(this->components))
		component->print();
	
	std::cout << "}" << std::endl;
}

//#if (LOGGING)
//void Topology::setLogger(std::ofstream* log)
//{
//	this->log = log;
//}
//#endif

Topology::~Topology(void)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being destructed." << std::endl;

	for (auto component : *(this->components))
		delete component;
}
