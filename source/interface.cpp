/************************************************************************************************************
Standard Library Extension

interface.cpp

*************************************************************************************************************/
#include "interface.h"
#include "list.h"
#include "algorithm.h"

#include <vector>
#include <algorithm>
/************************************************************************************************************/
std::vector<Interface *> InterfaceList;
Interface::Interface(AMX * amx) : amx(amx)
{
	//TO:DO Set data members
	int amx_error = amx_FindPublic(amx, "ScriptExecutionStateCheck", &this->ScriptUpdateCallbackIndex);
	this->SLEEnabled = (amx_error != AMX_ERR_NONE);
}
Interface::~Interface()
{
	//Destroy active lists
	for (auto itr = active_lists.begin(), itre = active_lists.end(); itr != itre; itr++)
	{
		if (this->amx == (*itr)->amx)
		{
			delete *itr;
			*itr = nullptr;
			unused_list_ids.push_back(std::distance(active_lists.begin(), itr));			
		}
	}
	//Destroy active foreach loops
	internal_algo_foreach_reset(amx);
}

void Interface::ScriptUpdate()
{
	//Destroy active foreach loops	
	internal_algo_foreach_reset(this->amx);
}
void Interface::RequestScriptUpdate()
{
	if (this->SLEEnabled)
		amx_Exec(this->amx, NULL, this->ScriptUpdateCallbackIndex);
}

