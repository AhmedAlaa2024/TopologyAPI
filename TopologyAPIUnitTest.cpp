#include "TopologyAPIUnitTest.h"

TopologyAPIUnitTest::TopologyAPIUnitTest(void)
{
	this->connection = new TopologyAPI();
	//this->log = new std::ofstream("log//TopologyAPITest_log.txt");

	//STREAM(log, "\t\t\t\t==========================================");
	//STREAM(log, "\t\t\t\t||   Welcome in Topology API Testing    ||");
	//STREAM(log, "\t\t\t\t==========================================");
}

void TopologyAPIUnitTest::TestQuery1(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [1]>: Read a topology from a given JSON file and store it in the memory." << std::endl;
	//STREAM(log, "<TEST [1]>: Read a topology from a given JSON file and store it in the memory.");

	bool test = this->connection->readJson("test1_1.json");

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	test = this->connection->readJson("test1_2.json");

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	test = this->connection->readJson("test1_3.json");

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	test = this->connection->readJson("test1_4.json");

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	/* This test case to test that it will not read a wrong passed file */
	test = this->connection->readJson("test1_5.mp3");

	try
	{
		if (!test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}
}

void TopologyAPIUnitTest::TestQuery2(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [2]>: Write a given topology from the memory to a JSON file." << std::endl;
	//STREAM(log, "<TEST [2]>: Write a given topology from the memory to a JSON file.");

	std::unordered_map<std::string, std::string> netlist;

	Topology* topology1 = new Topology("test1");
	Resistor* res1 = new Resistor("resistance", 100, 10, 1000);
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "vss" });
	Component* component1 = new Component("resistor", "res1", res1, netlist);
	topology1->addComponent(component1);


	Topology* topology2 = new Topology("test2");
	NMOS* m1 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component2 = new Component("nmos", "m1", m1, netlist);
	topology2->addComponent(component2);


	Topology* topology3 = new Topology("test3");
	Resistor* res2 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n1" });
	Component* component3 = new Component("resistor", "res2", res2, netlist);
	NMOS* m2 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n1" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component4 = new Component("nmos", "m2", m2, netlist);
	topology3->addComponent(component3);
	topology3->addComponent(component4);


	Topology* topology4 = new Topology("test4");
	NMOS* m3 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n2" });
	Component* component5 = new Component("nmos", "m3", m3, netlist);
	Resistor* res3 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n2" });
	netlist.insert({ "t2", "vss" });
	Component* component6 = new Component("resistor", "res3", res3, netlist);
	topology4->addComponent(component5);
	topology4->addComponent(component6);


	Topology* topology5 = new Topology("test5");
	Resistor* res4 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n3" });
	Component* component7 = new Component("resistor", "res4", res4, netlist);
	NMOS* m4 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n3" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n4" });
	Component* component8 = new Component("nmos", "m4", m4, netlist);
	Resistor* res5 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n4" });
	netlist.insert({ "t2", "vss" });
	Component* component9 = new Component("resistor", "res5", res5, netlist);
	topology5->addComponent(component7);
	topology5->addComponent(component8);
	topology5->addComponent(component9);


	this->connection->addTopology(topology1);
	this->connection->addTopology(topology2);
	this->connection->addTopology(topology3);
	this->connection->addTopology(topology4);
	this->connection->addTopology(topology5);

	bool test = false;

	test = this->connection->writeJSON("test2_1.json", topology1->getID());

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	test = this->connection->writeJSON("test2_2.json", topology2->getID());

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	test = this->connection->writeJSON("test2_3.json", topology3->getID());

	try
	{
		if (test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	/* This test case to test that it will not write because of a wrong passed filepath */
	test = this->connection->writeJSON("test2_4.mp3", topology4->getID());

	try
	{
		if (!test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	/* This test case to test that it will not write because of a wrong passed topologyID */
	test = this->connection->writeJSON("test2_5.json", topology5->getID() + "salt");

	try
	{
		if (!test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}
}

void TopologyAPIUnitTest::TestQuery3(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [3]>: Query about which topologies are currently in the memory." << std::endl;
	//STREAM(log, "<TEST [3]>: Query about which topologies are currently in the memory.");

	std::vector<Topology*>* topologies = this->connection->getTopologies();
	size_t size = topologies->size();

	/* To make sure there is no any topologies in memory before this unit test */
	for (int i = 0; i < size; i++)
		this->connection->deleteTopology(topologies->at(0)->getID());
		
	std::unordered_map<std::string, std::string> netlist;

	Topology* topology1 = new Topology("test1");
	Resistor* res1 = new Resistor("resistance", 100, 10, 1000);
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "vss" });
	Component* component1 = new Component("resistor", "res1", res1, netlist);
	topology1->addComponent(component1);


	Topology* topology2 = new Topology("test3");
	Resistor* res2 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n1" });
	Component* component2 = new Component("resistor", "res2", res2, netlist);
	NMOS* m1 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n1" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component3 = new Component("nmos", "m1", m1, netlist);
	topology2->addComponent(component2);
	topology2->addComponent(component3);


	Topology* topology3 = new Topology("test5");
	Resistor* res3 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n2" });
	Component* component4 = new Component("resistor", "res3", res3, netlist);
	NMOS* m2 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n2" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n3" });
	Component* component5 = new Component("nmos", "m2", m2, netlist);
	Resistor* res4 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n3" });
	netlist.insert({ "t2", "vss" });
	Component* component6 = new Component("resistor", "res4", res4, netlist);
	topology3->addComponent(component4);
	topology3->addComponent(component5);
	topology3->addComponent(component6);

	// std::vector<Topology*>* topologies = nullptr;

	/* This test case to test that it will return nullptr when there is no any topology in memory */
	try {
		topologies = this->connection->queryTopologies();

		if (!topologies)
		{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Doesn't return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Doesn't return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	try {
		this->connection->addTopology(topology1);
		topologies = this->connection->queryTopologies();

		if (topologies != nullptr)
		{
			if (topologies->size() == 1)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	try {
		this->connection->addTopology(topology2);
		topologies = this->connection->queryTopologies();

		if (topologies != nullptr)
		{
			if (topologies->size() == 2)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	try {
		this->connection->addTopology(topology3);
		topologies = this->connection->queryTopologies();

		if (topologies != nullptr)
		{
			if (topologies->size() == 3)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	try {
		this->connection->readJson("topology.json");
		topologies = this->connection->queryTopologies();

		if (topologies != nullptr)
		{
			if (topologies->size() == 4)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}
}

void TopologyAPIUnitTest::TestQuery4(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [4]>: Delete a given topology from memory." << std::endl;
	//STREAM(log, "<TEST [4]>: Delete a given topology from memory.");

	std::vector<Topology*>* topologies = this->connection->getTopologies();
	size_t size = topologies->size();
	/* To make sure there is no any topologies in memory before this unit test */
	for (int i = 0; i < size; i++)
		this->connection->deleteTopology(topologies->at(0)->getID());

	std::unordered_map<std::string, std::string> netlist;

	Topology* topology1 = new Topology("test1");
	Resistor* res1 = new Resistor("resistance", 100, 10, 1000);
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "vss" });
	Component* component1 = new Component("resistor", "res1", res1, netlist);
	topology1->addComponent(component1);


	Topology* topology2 = new Topology("test2");
	NMOS* m1 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component2 = new Component("nmos", "m1", m1, netlist);
	topology2->addComponent(component2);


	Topology* topology3 = new Topology("test3");
	Resistor* res2 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n1" });
	Component* component3 = new Component("resistor", "res2", res2, netlist);
	NMOS* m2 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n1" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component4 = new Component("nmos", "m2", m2, netlist);
	topology3->addComponent(component3);
	topology3->addComponent(component4);


	this->connection->addTopology(topology1);
	this->connection->addTopology(topology2);
	this->connection->addTopology(topology3);

	bool test = false;
	std::string topologyID_test = topology3->getID();

	// Test Case [1]
	try {
		test = this->connection->deleteTopology(topology3->getID());
		topologies = this->connection->queryTopologies();

		if (test && (topologies != nullptr))
		{
			if (topologies->size() == 2)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	// Test Case [2]
	try {
		this->connection->deleteTopology(topology2->getID());
		topologies = this->connection->queryTopologies();

		if (test && (topologies != nullptr))
		{
			if (topologies->size() == 1)
			{
				std::cout << "<RESULT>: PASSED!" << std::endl;
				//STREAM(log, "<RESULT>: PASSED!");
			}
			else
			{
				std::cout << "<RESULT>: FAILED!" << std::endl;
				//STREAM(log, "<RESULT>: FAILED!");
				std::cout << "<REASON>: Number of topologies mismatch!" << std::endl;
				//STREAM(log, "<REASON>: Number of topologies mismatch!");
			}
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	// Test Case [3]
	/* This test case to test that it will return nullptr when try to delete a topology, and the passed topologyID is wrong!  */
	try {
		test = this->connection->deleteTopology(topology1->getID() + "salt");

		if (!test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Doesn't Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Doesn't Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	// Test Case [4]
	try {
		test = this->connection->deleteTopology(topology1->getID());
		topologies = this->connection->queryTopologies();

		if (test && !topologies)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}

	// Test Case [5]
	/* This test case to test that it will return nullptr when try to delete non-existing topology  */
	test = this->connection->deleteTopology(topologyID_test);
	try {

		if (!test)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: FAILED!");
			std::cout << "<REASON>: Return nullptr!" << std::endl;
			//STREAM(log, "<REASON>: Return nullptr!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: FAILED!");
		std::cout << "<REASON>: Runtime Error!" << std::endl;
		//STREAM(log, "<REASON>: Runtime Error!");
	}
}

void TopologyAPIUnitTest::TestQuery5(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [5]>: Query about which devices are in a given topology." << std::endl;
	//STREAM(log, "<TEST [5]>: Query about which devices are in a given topology.");

	std::vector<Topology*>* topologies = this->connection->getTopologies();
	size_t size = topologies->size();
	/* To make sure there is no any topologies in memory before this unit test */
	for (int i = 0; i < size; i++)
		this->connection->deleteTopology(topologies->at(0)->getID());

	std::unordered_map<std::string, std::string> netlist;

	Topology* topology1 = new Topology("test1");
	Resistor* res1 = new Resistor("resistance", 100, 10, 1000);
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "vss" });
	Component* component1 = new Component("resistor", "res1", res1, netlist);
	topology1->addComponent(component1);


	Topology* topology2 = new Topology("test2");
	NMOS* m1 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component2 = new Component("nmos", "m1", m1, netlist);
	topology2->addComponent(component2);


	Topology* topology3 = new Topology("test3");
	Resistor* res2 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n1" });
	Component* component3 = new Component("resistor", "res2", res2, netlist);
	NMOS* m2 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n1" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component4 = new Component("nmos", "m2", m2, netlist);
	topology3->addComponent(component3);
	topology3->addComponent(component4);


	Topology* topology4 = new Topology("test4");
	NMOS* m3 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n2" });
	Component* component5 = new Component("nmos", "m3", m3, netlist);
	Resistor* res3 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n2" });
	netlist.insert({ "t2", "vss" });
	Component* component6 = new Component("resistor", "res3", res3, netlist);
	topology4->addComponent(component5);
	topology4->addComponent(component6);


	Topology* topology5 = new Topology("test5");
	Resistor* res4 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n3" });
	Component* component7 = new Component("resistor", "res4", res4, netlist);
	NMOS* m4 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n3" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n4" });
	Component* component8 = new Component("nmos", "m4", m4, netlist);
	Resistor* res5 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n4" });
	netlist.insert({ "t2", "vss" });
	Component* component9 = new Component("resistor", "res5", res5, netlist);
	topology5->addComponent(component7);
	topology5->addComponent(component8);
	topology5->addComponent(component9);


	this->connection->addTopology(topology1);
	this->connection->addTopology(topology2);
	this->connection->addTopology(topology3);
	this->connection->addTopology(topology4);
	this->connection->addTopology(topology5);


	try
	{
		std::vector<Device*>* result = this->connection->queryDevices(topology1->getID());

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevices(topology2->getID());

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevices(topology3->getID());

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevices(topology4->getID());

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevices(topology5->getID());

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}
}

void TopologyAPIUnitTest::TestQuery6(void)
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	//STREAM(log, "-----------------------------------------------------------------------------------------------------------------");
	std::cout << "<TEST [6]>: Query about which devices are connected to a given netlist node in a given topology." << std::endl;
	//STREAM(log, "<TEST [6]>: Query about which devices are connected to a given netlist node in a given topology.");

	std::vector<Topology*>* topologies = this->connection->getTopologies();
	size_t size = topologies->size();
	/* To make sure there is no any topologies in memory before this unit test */
	for (int i = 0; i < size; i++)
		this->connection->deleteTopology(topologies->at(0)->getID());

	std::unordered_map<std::string, std::string> netlist;

	Topology* topology1 = new Topology("test1");
	Resistor* res1 = new Resistor("resistance", 100, 10, 1000);
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "vss" });
	Component* component1 = new Component("resistor", "res1", res1, netlist);
	topology1->addComponent(component1);


	Topology* topology2 = new Topology("test2");
	NMOS* m1 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component2 = new Component("nmos", "m1", m1, netlist);
	topology2->addComponent(component2);


	Topology* topology3 = new Topology("test3");
	Resistor* res2 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n1" });
	Component* component3 = new Component("resistor", "res2", res2, netlist);
	NMOS* m2 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n1" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "vss" });
	Component* component4 = new Component("nmos", "m2", m2, netlist);
	topology3->addComponent(component3);
	topology3->addComponent(component4);


	Topology* topology4 = new Topology("test4");
	NMOS* m3 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "vdd" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n2" });
	Component* component5 = new Component("nmos", "m3", m3, netlist);
	Resistor* res3 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n2" });
	netlist.insert({ "t2", "vss" });
	Component* component6 = new Component("resistor", "res3", res3, netlist);
	topology4->addComponent(component5);
	topology4->addComponent(component6);


	Topology* topology5 = new Topology("test5");
	Resistor* res4 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "vdd" });
	netlist.insert({ "t2", "n3" });
	Component* component7 = new Component("resistor", "res4", res4, netlist);
	NMOS* m4 = new NMOS("m(l)", 1.5, 1, 2);
	netlist.clear();
	netlist.insert({ "drain", "n3" });
	netlist.insert({ "gate", "vin" });
	netlist.insert({ "source", "n4" });
	Component* component8 = new Component("nmos", "m4", m4, netlist);
	Resistor* res5 = new Resistor("resistance", 100, 10, 1000);
	netlist.clear();
	netlist.insert({ "t1", "n4" });
	netlist.insert({ "t2", "vss" });
	Component* component9 = new Component("resistor", "res5", res5, netlist);
	topology5->addComponent(component7);
	topology5->addComponent(component8);
	topology5->addComponent(component9);


	this->connection->addTopology(topology1);
	this->connection->addTopology(topology2);
	this->connection->addTopology(topology3);
	this->connection->addTopology(topology4);
	this->connection->addTopology(topology5);


	try
	{
		std::vector<Device*>* result = this->connection->queryDevicesWithNetlistNode(topology1->getID(), "vdd");

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevicesWithNetlistNode(topology2->getID(), "n1");

		if (result == nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevicesWithNetlistNode(topology3->getID(), "n1");

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevicesWithNetlistNode(topology4->getID(), "n2");

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}

	try
	{
		std::vector<Device*>* result = this->connection->queryDevicesWithNetlistNode(topology5->getID(), "n4");

		if (result != nullptr)
		{
			std::cout << "<RESULT>: PASSED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
		else
		{
			std::cout << "<RESULT>: FAILED!" << std::endl;
			//STREAM(log, "<RESULT>: PASSED!");
		}
	}
	catch (const std::exception&)
	{
		std::cout << "<RESULT>: FAILED!" << std::endl;
		//STREAM(log, "<RESULT>: PASSED!");
	}
}

TopologyAPIUnitTest::~TopologyAPIUnitTest(void)
{
	delete this->connection;
}
