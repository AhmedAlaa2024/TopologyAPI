#include "TopologyAPI.h"
#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

TopologyAPI::TopologyAPI(void):currentQuery(QUERY::HELP)
{
    this->connectionID = this->randomString();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
    std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;

	//STREAM(log, "<Notification>: Connection to TopologyAPI has been stablished successfully!\n");
	//STREAM(log, "<Notification>: Connection ID: " << this->connectionID << std::endl);
}

TopologyAPI::TopologyAPI(QUERY currentQuery):currentQuery(currentQuery)
{
    this->connectionID = this->randomString();
    std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
    std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;

	//STREAM(log, "<Notification>: Connection to TopologyAPI has been stablished successfully!\n");
	//STREAM(log, "<Notification>: Connection ID: " << this->connectionID << std::endl);
}

TopologyAPI::TopologyAPI(std::string filePath):currentQuery(QUERY::HELP)
{
	this->connectionID = this->randomString();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
	std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;

	//STREAM(log, "<Notification>: Connection to TopologyAPI has been stablished successfully!\n");
	//STREAM(log, "<Notification>: Connection ID: " << this->connectionID << std::endl);
}

TopologyAPI::TopologyAPI(QUERY currentQuery, std::string filePath):currentQuery(currentQuery)
{
	this->connectionID = this->randomString();
	std::cout << "<Notification>: Connection to TopologyAPI has been stablished successfully!" << std::endl;
	std::cout << "<Notification>: Connection ID: " << this->connectionID << std::endl;

	//STREAM(log, "<Notification>: Connection to TopologyAPI has been stablished successfully!\n");
	//STREAM(log, "<Notification>: Connection ID: " << this->connectionID << std::endl);
}

void TopologyAPI::addTopology(Topology* topology)
{
	this->topologies.push_back(topology);
}

std::string TopologyAPI::randomString(void)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

std::string TopologyAPI::getConnectionID(void)
{
	return this->connectionID;
}

QUERY TopologyAPI::getCurrentQuery(void)
{
	return this->currentQuery;
}

std::vector<Topology*>* TopologyAPI::getTopologies(void)
{
	return &(this->topologies);
}

void TopologyAPI::executeQuery(TopologyAPI_Param* parameter)
{
	switch (this->currentQuery) {
	case QUERY::HELP:
		this->help();
		break;
	case QUERY::READ:
		this->readJson(parameter->filePath);
		break;
	case QUERY::WRITE:
		this->writeJSON(parameter->filePath, parameter->topologyID);
		break;
	case QUERY::WHICH_TOPOLOGIES:
		this->queryTopologies();
		break;
	case QUERY::DELETE:
		this->deleteTopology(parameter->topologyID);
		break;
	case QUERY::WHICH_DEVICES:
		this->queryDevices(parameter->topologyID);
		break;
	case QUERY::IS_CONNECTED:
		this->queryDevicesWithNetlistNode(parameter->topologyID, parameter->node);
		break;
	case QUERY::CREATE:
		this->createTopology();
		break;
	default:
		throw ("Unsupported Query: " + std::to_string((int)this->currentQuery));
		break;
	}
}

void TopologyAPI::setCurrentQuery(QUERY currentQuery)
{
	this->currentQuery = currentQuery;
}

bool TopologyAPI::chech_path(std::string filePath)
{
	size_t found = filePath.find(".json");
	if (found == std::string::npos)
		return false;
	return true;
}

void TopologyAPI::help(void)
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
	std::cout << "Enter i to create new topology in the memory!" << std::endl;
	std::cout << "Enter u to show you the menu of test cases!" << std::endl;
	std::cout << "Enter q to exit!" << std::endl;

	//STREAM(log, "Help query is executed successfully!" << std::endl);
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------" << std::endl);
	//STREAM(log, "> Here are the menu of supported queries:" << std::endl);
	//STREAM(log, "Enter 1 to Read a topology from a given JSON file and store it in the memory!" << std::endl);
	//STREAM(log, "Enter 2 to Write a given topology from the memory to a JSON file!" << std::endl);
	//STREAM(log, "Enter 3 to Query about which topologies are currently in the memory!" << std::endl);
	//STREAM(log, "Enter 4 to Delete a given topology from memory!" << std::endl);
	//STREAM(log, "Enter 5 to Query about which devices are in a given topology!" << std::endl);
	//STREAM(log, "Enter 6 to Query about which devices are connected to a given netlist node in a given topology!" << std::endl);
	//STREAM(log, "Enter i to create new topology in the memory!" << std::endl);
	//STREAM(log, "Enter u to show you the menu of test cases!" << std::endl);
	//STREAM(log, "Enter q to exit!" << std::endl);
}

bool TopologyAPI::readJson(std::string filePath)
{
	try
	{
		if (!this->chech_path(filePath))
			return false;

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
				NMOS *transistor = new NMOS("m1", subDocument["m(l)"]["default"], subDocument["m(l)"]["min"], subDocument["m(l)"]["max"]);
				component->set_device(transistor);

				netlist.insert({ "drain", subDocument["netlist"]["drain"] });
				netlist.insert({ "gate", subDocument["netlist"]["gate"] });
				netlist.insert({ "source", subDocument["netlist"]["source"] });
			}

			/* Pass the netlist map to the component object */
			component->set_netlist(netlist);

			/* Add the component to the list of components of the topology */
			topology->addComponent(component);
		}
		/* Add the topology to the list of topologies */
		this->addTopology(topology);

		std::cout << "<Notification>: Read query is executed successfully!" << std::endl;
		//STREAM(log, "<Notification>: Read query is executed successfully!" << std::endl);
		return true;
	}
	catch (const std::exception&)
	{
		std::cout << "<Notification>: Read query is faild! Hint: Make sure that the path of json file is valid!" << std::endl;
		//STREAM(log, "<Notification>: Read query is faild! Hint: Make sure that the path of json file is valid!" << std::endl);
		return false;
	}
}

bool TopologyAPI::writeJSON(std::string filePath, std::string topologyID)
{
	try
	{
		if (!this->chech_path(filePath))
			return false;

		Topology* topology = nullptr;

		for (auto iterator : this->topologies)
		{
			if (iterator->getID() == topologyID)
			{
				topology = iterator;
				break;
			}
		}

		/* Not Found */
		if (!topology)
			return false;

		json document;
		std::ofstream out(filePath);

		out << "{" << std::endl;
		out << "  \"id\": \"" << topology->getID() << "\"," << std::endl;
		out << "  \"components\": [" << std::endl;

		for (auto component : *(topology->getComponents()))
		{
			out << "   {" << std::endl;
			out << "      \"type\": ";

			if (component->get_type() == "resistor")
				out << "\"resistor\"," << std::endl;
			else if (component->get_type() == "nmos")
				out << "\"nmos\"," << std::endl;

			out << "      \"id\": \"" << component->get_id() << "\"," << std::endl;

			out << "      \"" << component->get_device()->get_name() << "\": {" << std::endl;

			out << "        \"default\": " << component->get_device()->get_defaultValue() << "," << std::endl;
			out << "        \"min\": " << component->get_device()->get_minValue() << "," << std::endl;
			out << "        \"max\": " << component->get_device()->get_maxValue() << std::endl;
			out << "      }," << std::endl;

			out << "      \"netlist\": {" << std::endl;

			/* I put this scope to destruct the variables which i don't need any more outside the scope */
			{
				auto terminal = component->get_netlist()->begin();
				auto end = component->get_netlist()->end();
				end--;
				for (terminal = component->get_netlist()->begin(); terminal != end; terminal++)
					out << "        \"" << terminal->first << "\": \"" << terminal->second << "\"," << std::endl;

				out << "        \"" << terminal->first << "\": \"" << terminal->second << "\"" << std::endl;
			}

			out << "      }" << std::endl;
			if (component != topology->getComponents()->back())
				out << "   }," << std::endl;
			else
				out << "   }" << std::endl;
		}

		out << "  ]" << std::endl;

		out << "}" << std::endl;

		std::cout << "<Notification>: Write query is executed successfully!" << std::endl;
		//STREAM(log, "<Notification>: Write query is executed successfully!" << std::endl);
		return true;
	}
	catch (const std::exception&)
	{
		std::cout << "<Notification>: Write query is failed!" << std::endl;
		//STREAM(log, "<Notification>: Write query is failed!" << std::endl);
		return false;
	}
}

std::vector<Topology*>* TopologyAPI::queryTopologies(void)
{
	if (this->topologies.size() == 0)
	{
		std::cout << "<Notification>: There is no topologies in the memory." << std::endl;
		//STREAM(log, "<Notification>: There is no topologies in the memory." << std::endl);
		return nullptr;
	}

	std::cout << "Number of topologies in memory: " << this->topologies.size() << std::endl;
	//STREAM(log, "Number of topologies in memory: " << this->topologies.size() << std::endl);

	std::cout << "The following is ID list of the topologies in memory:" << std::endl;
	//STREAM(log, "The following is ID list of the topologies in memory:" << std::endl);
	int i = 0;
	for (auto topology : this->topologies)
	{
		std::cout << "[" << i++ << "] - " << topology->getID() << std::endl;
		topology->print();
		//STREAM(log, "[" << i++ << "] - " << topology->getID() << std::endl);
	}

	std::cout << "<Notification>: Topologies query is executed successfully!" << std::endl;
	//STREAM(log, "<Notification>: Topologies query is executed successfully!" << std::endl);

	return &(this->topologies);
}

bool TopologyAPI::deleteTopology(std::string topologyID)
{
	if (topologyID == "")
		return false;

	int i = 0;

	for (auto topology : this->topologies)
		if (topology->getID() == topologyID)
		{
			delete topology;
			this->topologies.erase(this->topologies.begin() + i);
			std::cout << "<Notification>: Delete query is executed successfully!" << std::endl;
			//STREAM(log, "<Notification>: Delete query is executed successfully!" << std::endl);
			return true;
		}
		else {
			i++;
		}

	std::cout << "<Notification>: Delete query is failed!" << std::endl;
	//STREAM(log, "<Notification>: Delete query is failed!" << std::endl);
	return false;
}

std::vector<Device*>* TopologyAPI::queryDevices(std::string topologyID)
{
	if (topologyID == "")
	{
		std::cout << "<Notification>: Devices query is failed! Error: Invalid arguments!" << std::endl;
		//STREAM(log, "<Notification>: Devices query is failed! Error: Invalid arguments!" << std::endl);
		return nullptr;
	}

	std::vector<Device*>* devices = new std::vector<Device*>();

	int i = 0;
	Topology* temp = nullptr;
	for (auto topology : this->topologies)
		if (topology->getID() == topologyID)
		{
			temp = topology;
			break;
		}
		else
			i++;

	if (!temp)
	{
		std::cout << "<Notification>: Devices query is failed! There is no topology in memory attached to ID<" << topologyID << ">" << std::endl;
		//STREAM(log, "<Notification>: Devices query is failed! There is no topology in memory attached to ID<" << topologyID << ">" << std::endl);
		return nullptr;
	}

	std::cout << "This is the list of devices in Topology[" << topologyID << "]:" << std::endl;
	//STREAM(log, "This is the list of devices in Topology[" << topologyID << "]:" << std::endl);
	i = 0;
	for (auto component : *(temp->getComponents()))
	{
		std::cout << "[" << i++ << "] - " << component->get_device()->get_name() << std::endl;
		component->get_device()->print();
		//STREAM(log, "[" << i++ << "] - " << component->get_device()->get_name() << std::endl);

		devices->push_back(component->get_device());
	}

	std::cout << "<Notification>: Devices query is executed successfully!" << std::endl;
	//STREAM(log, "<Notification>: Devices query is executed successfully!" << std::endl);
	return devices;
}

std::vector<Device*>* TopologyAPI::queryDevicesWithNetlistNode(std::string topologyID, std::string node)
{

	if ((topologyID == "") || (node == ""))
	{
		std::cout << "<Notification>: Netlist query is failed! Error: Invalid arguments!" << std::endl;
		//STREAM(log, "<Notification>: Netlist query is failed! Error: Invalid arguments!" << std::endl);
		return nullptr;
	}

	int i = 0;
	Topology* temp = nullptr;
	for (auto topology : this->topologies)
		if (topology->getID() == topologyID)
		{
			temp = topology;
			break;
		}
		else
			i++;

	if (!temp)
	{
		std::cout << "<Notification>: Netlist query is failed! There is no topology in memory attached to ID<" << topologyID << ">" << std::endl;
		//STREAM(log, "<Notification>: Netlist query is failed! There is no topology in memory attached to ID<" << topologyID << ">" << std::endl);
		return nullptr;
	}


	std::vector<Device*>* devices = nullptr;
	i = 0;
	for (auto component : *(temp->getComponents()))
	{
		for (auto terminal : *(component->get_netlist()))
		{
			if (terminal.second == node)
			{
				if (i == 0) {
					std::cout << "This is the list of connected devices in Topology[" << topologyID << "]:" << std::endl;
					//STREAM(log, "This is the list of connected devices in Topology[" << topologyID << "]:" << std::endl);
					devices = new std::vector<Device*>();
				}
				devices->push_back(component->get_device());
				std::cout << "[" << i++ << "] - " << component->get_device()->get_name() << std::endl;
			}
		}
	}

	if (!devices)
	{
		std::cout << "<Notification>: Netlist query is failed, There is no connected devices by node<" << node << ">" << std::endl;
		//STREAM(log, "<Notification>: Netlist query is failed, There is no connected devices by node<" << node << ">" << std::endl);
		return nullptr;
	}

	std::cout << "<Notification>: Netlist query is executed successfully!" << std::endl;
	//STREAM(log, "<Notification>: Netlist query is executed successfully!" << std::endl);
	return devices;
}

int TopologyAPI::getNumberOfTopologies(void)
{
	return (int)(this->topologies.size());
}

void TopologyAPI::createTopology(void)
{
	Topology* topology = nullptr;
	Component* component = nullptr;
	Device* device = nullptr;

	std::string input;

	std::cout << "Enter the ID of the new topology: ";
	//STREAM(log, "Enter the ID of the new topology: ");
	std::cin >> input;
	//STREAM(log, input << std::endl);
	topology = new Topology(input);

	int numberOfComponents = 0;

	for (;;)
	{
		std::cout << "Do you want to add new component? (Y/N) ";
		//STREAM(log, "Do you want to add new component? (Y/N) ");
		std::cin >> input;
		//STREAM(log, input << std::endl);

		if ((input != "y") && (input != "Y"))
			break;

		numberOfComponents++;

		std::cout << "Enter the ID of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the ID of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);

		component = new Component(input);

		std::cout << "Enter the type of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the type of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);
		component->set_type(input);

		std::cout << "Enter the Device's name of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the Device's name of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);

		if (component->get_type() == "resistor")
			device = new Resistor(input);
		else if (component->get_type() == "nmos")
			device = new NMOS(input);
		else
			device = new Device(input);

		std::cout << "Enter the Device's default value of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the Device's default value of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);
		device->set_defaultValue(std::stof(input));

		std::cout << "Enter the Device's min value of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the Device's min value of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);
		device->set_minValue(std::stof(input));

		std::cout << "Enter the Device's max value of component No. " << numberOfComponents << ": ";
		//STREAM(log, "Enter the Device's max value of component No. " << numberOfComponents << ": ");
		std::cin >> input;
		//STREAM(log, input << std::endl);
		device->set_maxValue(std::stof(input));

		component->set_device(device);

		std::unordered_map<std::string, std::string> netlist;

		// If it's resistor, then it's 2-terminal device.
		if (component->get_type() == "resistor")
		{

			std::cout << "Enter the node of the first terminal: ";
			//STREAM(log, "Enter the node of the first terminal: ");
			std::cin >> input;
			//STREAM(log, input << std::endl);

			netlist.insert({ "t1", input });
			
			std::cout << "Enter the node of the second terminal: ";
			//STREAM(log, "Enter the node of the second terminal: ");
			std::cin >> input;
			//STREAM(log, input << std::endl);

			netlist.insert({ "t2", input });
		}
		else if (component->get_type() == "nmos")
		{

			std::cout << "Enter the node of the drain: ";
			//STREAM(log, "Enter the node of the drain: ");
			std::cin >> input;
			//STREAM(log, input << std::endl);

			netlist.insert({ "drain", input });

			std::cout << "Enter the node of the gate: ";
			//STREAM(log, "Enter the node of the gate: ");
			std::cin >> input;
			//STREAM(log, input << std::endl);

			netlist.insert({ "gate", input });

			std::cout << "Enter the node of the source: ";
			//STREAM(log, "Enter the node of the source: ");
			std::cin >> input;
			//STREAM(log, input << std::endl);

			netlist.insert({ "source", input });
		}

		component->set_netlist(netlist);
		
		topology->addComponent(component);
	}

	this->addTopology(topology);
}

#if (LOGGING)
void Topology::setLogger(std::ofstream* log)
{
	this->log = log;
}
#endif

/*
	TODO: Make sure that all changes are saved successfully!
*/

TopologyAPI::~TopologyAPI(void)
{
    std::cout << "<Notification>: Connection['" << this->connectionID << "'] to TopologyAPI has been destroyed successfully!" << std::endl;
	//STREAM(log, "<Notification>: Connection['" << this->connectionID << "'] to TopologyAPI has been destroyed successfully!" << std::endl);
	
	for (auto topology : this->topologies)
		delete topology;
}