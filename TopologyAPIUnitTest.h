#ifndef _TOPOLOGYAPIUNITTEST_H
#define _TOPOLOGYAPIUNITTEST_H

#include <iostream>

#include "TopologyAPI.h"

class TopologyAPIUnitTest
{
private:
	TopologyAPI *connection;

#if (LOGGING)
	std::ofstream* log;
#endif

public:
	TopologyAPIUnitTest(void);

	void TestQuery1(void);
	void TestQuery2(void);
	void TestQuery3(void);
	void TestQuery4(void);
	void TestQuery5(void);
	void TestQuery6(void);

#if (LOGGING)
	void setLogger(std::ofstream* log);
#endif

	~TopologyAPIUnitTest(void);
};

#endif // !_TOPOLOGYAPIUNITTEST_H