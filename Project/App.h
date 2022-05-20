#ifndef _APP_H
#define _APP_H

#include <iostream>
#include <string>
#include <math.h>
#include <unordered_map>

#include "TopologyAPI.h"
#include "TopologyAPIUnitTest.h"

#define ACCESS(X)	(*(X))
#define ADDRESS(X)	(&(X))


/******************************************** Functions Prototypes ************************************************/
//==============================================================================================================
//	Function: ReadQuery																							|
//	Return Type: void																							|
//	Parameters: None																							|
//	Blocking: No																								|
//==============================================================================================================
void Guide(void);
//==============================================================================================================
//	Function: ReadQuery																							|
//	Return Type: void																							|
//	Parameters: None																							|
//	Blocking: No																								|
//==============================================================================================================
void ReadQuery(QUERY& query);
void queryPreprocessing(QUERY query, TopologyAPI_Param& parameter);
void unitTesting(void);

/*********************************************** Global Data ******************************************************/
int queury_id = 0;
bool exit_request = false;
bool test_request = false;
/******************************************************************************************************************/
#endif // !_APP_H

