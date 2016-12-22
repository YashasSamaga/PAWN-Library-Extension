/************************************************************************************************************
Standard Library Extension


algorithm.cpp

*************************************************************************************************************/
#include "list.h"

#include <vector>
/************************************************************************************************************/
extern std::vector <ForeachList *> active_foreach_list_loops;
extern std::vector <unsigned int> unused_foreach_list_ids;
extern unsigned int foreach_list_loop_maxid;

void internal_algo_foreach_reset(AMX* amx)
{
	// Update unused foreach loops for a particular script
	for (unsigned int idx = 0; idx <= foreach_list_loop_maxid; idx++)
		if (active_foreach_list_loops[idx]->amx == amx)
		{
			unused_foreach_list_ids.push_back(idx);
			delete active_foreach_list_loops[idx];
		}
}