#ifndef _TOPOLOGY_API_H
#define _TOPOLOGY_API_H

#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include "Topology.h"

#define NUM_SUPPORTED_QUERIES	9

/******************************************** Structs and Enums ***************************************************/
enum class QUERY {
	HELP = 0,
	READ = 1,
	WRITE = 2,
	WHICH_TOPOLOGIES = 3,
	DELETE = 4,
	WHICH_DEVICES = 5,
	IS_CONNECTED = 6,
	UNIT_TESTS = 7,
};

struct TopologyAPI_Param {
	std::string filePath;
};
/******************************************************************************************************************/

class TopologyAPI
{
private:
	std::string connectionID;
	QUERY currentQuery;

	std::unordered_map<std::string, Topology*> topologies;

	void add_topology(std::string id, Topology* topology);
	void chech_path(std::string filePath);

public:
	TopologyAPI(void);
	TopologyAPI(QUERY currentQuery);
	TopologyAPI(std::string filePath);
	TopologyAPI(QUERY currentQuery, std::string filePath);

	std::string random_string(void);

	std::string get_connectionID(void);
	QUERY get_currentQuery(void);
	int get_numberOfTopologies(void);

	void set_currentQuery(QUERY currentQuery);

	void ExecuteQuery(TopologyAPI_Param* parameter);

	void Query_Help(void);
	bool Query_Read(std::string filePath);
	void Query_Write(std::string filePath);
	void Query_Which_Topologies(void);
	void Query_Delete(void);
	void Query_Which_Devices(void);
	void Query_Is_Connected(void);
	void Query_Unit_Tests(void);

	~TopologyAPI(void);
};

#endif // !_TOPOLOGY_API_H