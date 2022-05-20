#ifndef _TOPOLOGY_API_H
#define _TOPOLOGY_API_H

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <unordered_map>

#include "Topology.h"
#include "Component.h"
#include "Resistor.h"
#include "NMOS.h"
#include "defs.h"

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
	CREATE = 7
};

struct TopologyAPI_Param {
	std::string filePath;
	std::string topologyID;
	std::string node;
};
/******************************************************************************************************************/

class TopologyAPI
{
private:
	std::string connectionID;
	QUERY currentQuery;

	std::vector<Topology*> topologies;

	bool chech_path(std::string filePath);

#if (LOGGING)
	std::ofstream* log;
#endif

public:
	TopologyAPI(void);
	TopologyAPI(QUERY currentQuery);
	TopologyAPI(std::string filePath);
	TopologyAPI(QUERY currentQuery, std::string filePath);

	std::string randomString(void);

	std::string getConnectionID(void);
	QUERY getCurrentQuery(void);
	int getNumberOfTopologies(void);
	std::vector<Topology*>* getTopologies(void);

	void addTopology(Topology* topology);
	void setCurrentQuery(QUERY currentQuery);
	void createTopology(void);

	void executeQuery(TopologyAPI_Param* parameter);

	void help(void);

	bool readJson(std::string filePath);
	bool writeJSON(std::string filePath, std::string topologyID);
	std::vector<Topology*>* queryTopologies(void);
	bool deleteTopology(std::string topologyID);
	std::vector<Device*>* queryDevices(std::string topologyID);
	std::vector<Device*>* queryDevicesWithNetlistNode(std::string topologyID, std::string node);

//#if (LOGGING)
//	void setLogger(std::ofstream* log);
//#endif

	~TopologyAPI(void);
};

#endif // !_TOPOLOGY_API_H