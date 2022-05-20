#ifndef _DEFS_H
#define _DEFS_H

#include <fstream>

//#define	LOGGING					false

#if (LOGGING)
#include <fstream>
#define STREAM(X,Y)				(*(X) << Y << "\n")

// std::ofstream* log = new std::ofstream("log/TopologyAPI_log.txt");

#endif

#endif // !_DEFS_H