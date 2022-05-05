#include "TopologyAPI.h"
#include "Component.h"
#include "Resistor.h"
#include "Transistor.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

TopologyAPI::TopologyAPI(void):currentQuery(QUERY::HELP)
{
    this->connectionID = this->random_string();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
    std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;
}

TopologyAPI::TopologyAPI(QUERY currentQuery):currentQuery(currentQuery)
{
    this->connectionID = this->random_string();
    std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
    std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;
}

TopologyAPI::TopologyAPI(std::string filePath):currentQuery(QUERY::HELP)
{
	this->connectionID = this->random_string();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
	std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;
}

TopologyAPI::TopologyAPI(QUERY currentQuery, std::string filePath):currentQuery(currentQuery)
{
	this->connectionID = this->random_string();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
	std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;
}

void TopologyAPI::add_topology(std::string id, Topology* topology)
{
	this->topologies.insert({ id, topology });
}

std::string TopologyAPI::random_string(void)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

std::string TopologyAPI::get_connectionID(void)
{
	return this->connectionID;
}

QUERY TopologyAPI::get_currentQuery(void)
{
	return this->currentQuery;
}

void TopologyAPI::ExecuteQuery(TopologyAPI_Param* parameter)
{
	switch (this->currentQuery) {
	case QUERY::HELP:
		this->Query_Help();
		break;
	case QUERY::READ:
		this->Query_Read(parameter->filePath);
		break;
	case QUERY::WRITE:
		this->Query_Write(parameter->filePath);
		break;
	case QUERY::WHICH_TOPOLOGIES:
		this->Query_Which_Topologies();
		break;
	case QUERY::DELETE:
		this->Query_Delete();
		break;
	case QUERY::WHICH_DEVICES:
		this->Query_Which_Devices();
		break;
	case QUERY::IS_CONNECTED:
		this->Query_Is_Connected();
		break;
	case QUERY::UNIT_TESTS:
		this->Query_Unit_Tests();
		break;
	default:
		throw ("Unsupported Query: " + std::to_string((int)this->currentQuery));
		break;
	}
}

void TopologyAPI::set_currentQuery(QUERY currentQuery)
{
	this->currentQuery = currentQuery;
}

void TopologyAPI::chech_path(std::string filePath)
{
	size_t found = filePath.find(".json");
	if (found != std::string::npos)
		throw "<Error>: The entered path is not valid! Hint: Make sure it end by '.json'";
}

void TopologyAPI::Query_Help(void)
{
	std::cout << "Help query is executed successfully!" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "> Here are the menu of supported queries:" << std::endl;
	std::cout << "Enter 1 to Read a topology from a given JSON file and store it in the memory!" << std::endl;
	std::cout << "Enter 2 to Write a given topology from the memory to a JSON file!" << std::endl;
	std::cout << "Enter 3 to Query about which topologies are currently in the memory!" << std::endl;
	std::cout << "Enter 4 to Delete a given topology from memory!" << std::endl;
	std::cout << "Enter 5 to Query about which devices are in a given topology!" << std::endl;
	std::cout << "Enter 6 to Query about which devices are connected to a given netlist node in a given topology!" << std::endl;
	std::cout << "Enter u to show you the menu of test cases!" << std::endl;
	std::cout << "Enter q to exit!" << std::endl;
}

bool TopologyAPI::Query_Read(std::string filePath)
{
	try
	{
		this->chech_path(filePath);

		std::ifstream file(filePath);
		json document = json::parse(file);
		Topology *topology = new Topology(document["id"]);

		/* Parsing every component a side */
		for (int i = 0; i < document["components"].size(); i++)
		{
			/* Hold the component json sub document in subdocument */
			json subDocument = document["components"][i];

			/* Create a component instance */
			Component *component = new Component(subDocument["type"], subDocument["id"]);

			/* Parse the netlist information into unordered_map to pass it to the component object */
			std::unordered_map<std::string, std::string> netlist;
			
			/* If the component is resistor, then it has only 2 terminals because it is 2-terminal device. */
			if (subDocument["type"] == "resistor")
			{
				Resistor *resistor = new Resistor("resistance", subDocument["resistance"]["default"], subDocument["resistance"]["min"], subDocument["resistance"]["max"]);
				component->set_device(resistor);

				netlist.insert({ "t1", subDocument["netlist"]["t1"] });
				netlist.insert({ "t2", subDocument["netlist"]["t2"] });
			}
			/* If the component is resistor, then it has 3 terminals because it is 3-terminal device. */
			else if (subDocument["type"] == "nmos")
			{
				Transistor *transistor = new Transistor("m1", subDocument["m(l)"]["default"], subDocument["m(l)"]["min"], subDocument["m(l)"]["max"]);
				component->set_device(transistor);

				netlist.insert({ "drain", subDocument["netlist"]["drain"] });
				netlist.insert({ "gate", subDocument["netlist"]["gate"] });
				netlist.insert({ "source", subDocument["netlist"]["source"] });
			}

			/* Pass the netlist map to the component object */
			component->set_netlist(netlist);

			/* Add the component to the list of components of the topology */
			topology->add_component(component);
		}
		/* Add the topology to the list of topologies */
		this->add_topology(topology->get_id(), topology);

		std::cout << "<Notification>: Read query is executed successfully!" << std::endl;
		return true;
	}
	catch (const std::exception&)
	{
		std::cout << "<Notification>: Read query is faild! Hint: Make sure that the path of json file is valid!" << std::endl;
		return false;
	}
}

void TopologyAPI::Query_Write(std::string filePath)
{
	try
	{
		this->chech_path(filePath);
		json document;
		std::ofstream out(filePath);

		


		std::cout << "Write query is executed successfully!" << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << "Write query is failed!" << std::endl;
	}
}

void TopologyAPI::Query_Which_Topologies(void)
{
	std::cout << "Topologies query is executed successfully!" << std::endl;
}

void TopologyAPI::Query_Delete(void)
{
	std::cout << "Delete query is executed successfully!" << std::endl;
}

void TopologyAPI::Query_Which_Devices(void)
{
	std::cout << "Devices query is executed successfully!" << std::endl;
}

void TopologyAPI::Query_Is_Connected(void)
{
	std::cout << "Netlist query is executed successfully!" << std::endl;
}

void TopologyAPI::Query_Unit_Tests(void)
{
	std::cout << "Unit Tests query is executed successfully!" << std::endl;
}
int TopologyAPI::get_numberOfTopologies(void)
{
	return this->topologies.size();
}
/*
	TODO: Make sure that all changes are saved successfully!
*/

TopologyAPI::~TopologyAPI(void)
{
    std::cout << "<Notification>: Connection['" << this->connectionID << "'] to TopologyAPI has been destroyed successfully!" << std::endl;
	
	for (auto topology : this->topologies)
		delete topology.second;
}