#include "App.h"

int main(void)
{
	Guide();

	/* To hold the number of query */
	QUERY query = QUERY::HELP;		// It's set to help as a default
	TopologyAPI *connection = new TopologyAPI("topology.json");
	TopologyAPI_Param parametrs;

	/* Super Loop */
	for (;;)
	{
		ReadQuery(query);
		std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;

		if (exit_request)
			break;
		
		connection->set_currentQuery(query);
		Query_preprocessing(query, parametrs);
		connection->ExecuteQuery(ADDRESS(parametrs));
	}

	delete connection;

	return 0;
}

//==============================================================================================================
//	Function: ReadQuery																							|
//	Return Type: void																							|
//	Parameters: None																							|
//	Blocking: No																								|
//==============================================================================================================
void Guide(void)
{
	std::cout << "\t\t\t\t" << "==========================================" << std::endl;
	std::cout << "\t\t\t\t" << "|| Welcome in Topology API application! ||" << std::endl;
	std::cout << "\t\t\t\t" << "==========================================" << std::endl;
	std::cout << "> Here are the menu of supported queries:" << std::endl;
	std::cout << "Enter 1 to Read a topology from a given JSON file and store it in the memory!" << std::endl;
	std::cout << "Enter 2 to Write a given topology from the memory to a JSON file!" << std::endl;
	std::cout << "Enter 3 to Query about which topologies are currently in the memory!" << std::endl;
	std::cout << "Enter 4 to Delete a given topology from memory!" << std::endl;
	std::cout << "Enter 5 to Query about which devices are in a given topology!" << std::endl;
	std::cout << "Enter 6 to Query about which devices are connected to a given netlist node in a given topology!" << std::endl;
	std::cout << "Enter u to show you the menu of test cases!" << std::endl;
	std::cout << "Enter q to exit!" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
}

//==============================================================================================================
//	Function: ReadQuery																							|
//	Return Type: void																							|
//	Parameters: None																							|
//	Blocking: No																								|
//==============================================================================================================
void ReadQuery(QUERY& query)
{
	char input;

	bool valid = false;

	while (!valid)
	{
		std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Enter h to help!" << std::endl;
		std::cout << "Query[" + std::to_string(queury_id) + "]: ";
		queury_id++;

		std::cin >> input;

		switch (input)
		{
		case '1':
			query = QUERY::READ;
			valid = true;
			break;
		case '2':
			query = QUERY::WRITE;
			valid = true;
			break;
		case '3':
			query = QUERY::WHICH_TOPOLOGIES;
			valid = true;
			break;
		case '4':
			query = QUERY::DELETE;
			valid = true;
			break;
		case '5':
			query = QUERY::WHICH_DEVICES;
			valid = true;
			break;
		case '6':
			query = QUERY::IS_CONNECTED;
			valid = true;
			break;
		case 'u':
			query = QUERY::UNIT_TESTS;
			valid = true;
			break;
		case 'q':
			valid = true;
			exit_request = true;
			break;
		case 'h':
			query = QUERY::HELP;
			valid = true;
			break;
		default:
			std::cout << "Undefined Query. It maybe under-development query. Please, Use only the supported queries." << std::endl;
		}
	}
}

void Query_preprocessing(QUERY query, TopologyAPI_Param& parameter)
{
	switch (query) {
	case QUERY::HELP:
		/* TODO */
		break;
	case QUERY::READ:
		std::cout << "Please, Enter the path of the json file of the topology you want to read it!" << std::endl;
		std::cout << "For example <topology.json> without brackets." << std::endl;
		std::cout << "PATH: ";
		std::cin >> parameter.filePath;
		break;
	case QUERY::WRITE:
		std::cout << "Please, Enter the path of the json file of the topology you want to write it!" << std::endl;
		std::cout << "For example <topology.json> without brackets." << std::endl;
		std::cout << "PATH: ";
		std::cin >> parameter.filePath;
		break;
	case QUERY::WHICH_TOPOLOGIES:
		/* TODO */
		break;
	case QUERY::DELETE:
		/* TODO */
		break;
	case QUERY::WHICH_DEVICES:
		/* TODO */
		break;
	case QUERY::IS_CONNECTED:
		/* TODO */
		break;
	case QUERY::UNIT_TESTS:
		/* TODO */
		break;
	default:
		throw ("Unsupported Query: " + std::to_string((int)query));
		break;
	}
}