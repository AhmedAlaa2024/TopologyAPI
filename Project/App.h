#ifndef _APP_H
#define _APP_H

#include <iostream>
#include <string>
#include "TopologyAPI.h"

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
void Query_preprocessing(QUERY query, TopologyAPI_Param& parameter);

/*********************************************** Global Data ******************************************************/
int queury_id = 0;
bool exit_request = false;
/******************************************************************************************************************/
#endif // !_APP_H

