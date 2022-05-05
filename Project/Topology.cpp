#include "Topology.h"

Topology::Topology(std::string id):id(id)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being constructed." << std::endl;
}

Topology::Topology(std::string id, std::unordered_map<std::string, Component*> components):id(id)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being constructed." << std::endl;
	this->set_components(components);
}

void Topology::set_ID(std::string id)
{
	this->id = id;
}

void Topology::set_components(std::unordered_map<std::string, Component*> components)
{
	for (auto component : components)
	{
		(this->components).insert({ component.first, component.second });
	}
}

std::string Topology::get_id(void)
{
	return this->id;
}

std::unordered_map<std::string, Component*>* Topology::get_components(void)
{
	return &(this->components);
}

void Topology::add_component(Component* component)
{
	(this->components).insert({ component->get_id(), component});
}

void Topology::print(void)
{
	std::cout << "Topology[" + this->id + "]: {" << std::endl;
	for (auto component : this->components)
		(component.second)->print();
	
	std::cout << "}" << std::endl;
}

Topology::~Topology(void)
{
	std::cout << "<Notification>: Topology[" + this->id + "] is being destructed." << std::endl;

	for (auto component : this->components)
		delete component.second;
}
