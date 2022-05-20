#include "App.h"
#include "defs.h"
#include <csignal>

static TopologyAPI* connection;
static void signalHandler(int signum);

int main(void)
{
	// register signal SIGINT and signal handler
	signal(SIGINT, signalHandler);

	std::ofstream* log = new std::ofstream("log/TopologyAPI_log.txt");

	Guide();

	/* To hold the number of query */
	QUERY query = QUERY::HELP;		// It's set to help as a default
	connection = new TopologyAPI("topology.json");
	//connection->setLogger(log);
	TopologyAPI_Param parametrs;

	/* Super Loop */
	for (;;)
	{
		ReadQuery(query);
		std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;

		if (exit_request)
			break;

		if (test_request)
		{
			unitTesting();
			test_request = false;
		}
		
		connection->setCurrentQuery(query);
		queryPreprocessing(query, parametrs);
		connection->executeQuery(ADDRESS(parametrs));
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
	std::cout << "Enter i to create new topology in the memory!" << std::endl;
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
		case 'i':
			query = QUERY::CREATE;
			valid = true;
			break;
		case 'u':
			valid = true;
			test_request = true;
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

void queryPreprocessing(QUERY query, TopologyAPI_Param& parameter)
{
	/* To clean the old parameters */
	parameter.filePath = "";
	parameter.node = "";
	parameter.topologyID = "";

	std::vector<Topology*>* topologies = nullptr;
	int i = 0;

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
		std::cout << "Please, Enter the ID of the topology which you want to be writte in json file! Make sure it's in memory!" << std::endl;
		std::cout << "Topology ID: ";
		std::cin >> parameter.topologyID;
		break;
	case QUERY::WHICH_TOPOLOGIES:
		/* Nothing */
		break;
	case QUERY::DELETE:
		topologies = connection->getTopologies();

		if (topologies->size() == 0)
		{
			std::cout << "<Notification>: There is no topologies in the memory." << std::endl;
		}
		else
		{
			std::cout << "The following is ID list of the topologies in memory:" << std::endl;

			for (auto topology : *topologies)
				std::cout << "[" << i++ << "] - " << topology->getID() << std::endl;

			std::cout << "Please, Enter the index of the query you want to delete: ";
			int index;
			std::cin >> index;

			parameter.topologyID = topologies->at(index)->getID();
		}

		break;
	case QUERY::WHICH_DEVICES:
		topologies = connection->getTopologies();

		if (topologies->size() == 0)
		{
			std::cout << "<Notification>: There is no topologies in the memory." << std::endl;
		}
		else
		{
			std::cout << "The following is ID list of the topologies in memory:" << std::endl;

			for (auto topology : *topologies)
				std::cout << "[" << i++ << "] - " << topology->getID() << std::endl;

			std::cout << "Please, Enter the index of the query you want to query about its devices: ";
			int index;
			std::cin >> index;

			parameter.topologyID = topologies->at(index)->getID();
		}

		break;
	case QUERY::IS_CONNECTED:
		topologies = connection->getTopologies();

		if (topologies->size() == 0)
		{
			std::cout << "<Notification>: There is no topologies in the memory." << std::endl;
		}
		else
		{
			std::cout << "The following is ID list of the topologies in memory:" << std::endl;

			for (auto topology : *topologies)
				std::cout << "[" << i++ << "] - " << topology->getID() << std::endl;

			std::cout << "Please, Enter the index of the query you want to query about its devices: ";
			int index;
			std::cin >> index;

			parameter.topologyID = topologies->at(index)->getID();

			std::cout << "Please, Enter the node's name: ";
			std::cin >> parameter.node;
		}

		break;
	case QUERY::CREATE:
		/* Nothing TODO */
		break;
	default:
		throw ("Unsupported Query: " + std::to_string((int)query));
		break;
	}
}

void signalHandler(int signum)
{
	std::cout << std::endl << "Interrupt signal (" << signum << ") received." << std::endl;

	delete connection;

	exit(EXIT_SUCCESS);
}

void unitTesting(void)
{
	std::ofstream* logForTesting = new std::ofstream("log/TopologyAPITest_log.txt");

	TopologyAPIUnitTest topologyAPIUnitTest;
	// topologyAPIUnitTest.setLogger(logForTesting);
	topologyAPIUnitTest.TestQuery1();
	topologyAPIUnitTest.TestQuery2();
	topologyAPIUnitTest.TestQuery3();
	topologyAPIUnitTest.TestQuery4();
	topologyAPIUnitTest.TestQuery5();
	topologyAPIUnitTest.TestQuery6();
}