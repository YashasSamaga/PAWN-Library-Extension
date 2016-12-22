/************************************************************************************************************
Standard Library Extension

SLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, SLE is not an arbitary
collection of C++ libaries for PAWN.

main.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"
#include "algorithm.h"
#include "list.h"

#include <algorithm>
#include <vector>

#pragma warning(disable : 4996)
/************************************************************************************************************/
extern void *pAMXFunctions;

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;

unsigned int tick_count = 0;
unsigned int ticks_per_cycle = 20;
/************************************************************************************************************/
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	return true;
}
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	for (std::vector<Interface *>::iterator itr = InterfaceList.begin(); itr != InterfaceList.end();itr++)
		if (*itr != nullptr) delete *itr;

	//TO:DO
	//Delete all active objects apart from the ones related to interfaces
}
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	tick_count++;
	if (tick_count%ticks_per_cycle == 0)
		for (std::vector<Interface *>::iterator itr = InterfaceList.begin(), itrend = InterfaceList.end(); itr != itrend; itr++)
			if (*itr != nullptr)
				(*itr)->RequestScriptUpdate();
}
/************************************************************************************************************/
cell AMX_NATIVE_CALL SLE_ScriptInit(AMX* amx, cell* params)
{
	cell *addr = NULL;
	char SIdentifier[32];
	unsigned int ScriptID;
	unsigned int duplicate_count = 0;

	amx_GetAddr(amx, params[2], &addr);
	amx_GetString(SIdentifier, addr, 0, static_cast<size_t>(params[3]));
	
	std::vector<Interface *>::iterator itr = InterfaceList.begin(), itrend = InterfaceList.end();
	while (itr != itrend)
	{
		if ((*itr)->amx == amx)
		{
			ScriptID = std::distance(InterfaceList.begin(), itr);
			strcpy((*itr)->ScriptIdentifier, SIdentifier);
		}
		else
		{
			if (!strcmp((*itr)->ScriptIdentifier, SIdentifier))
				duplicate_count++;  
		}
		itr++;
	}	
	if (duplicate_count)
		logprintf("[WARNING] Standard Library Extension: Duplicate Script Identifier '%s'.", SIdentifier);

	if (PLUGIN_INCLUDE_KEY != static_cast<unsigned int>(params[1]))
		logprintf("[WARNING] Standard Library Extension: The plugin version does not match the include version in script '%s'.", SIdentifier);
	return ScriptID;
}
cell AMX_NATIVE_CALL SLE_ScriptUpdate(AMX* amx, cell* params)
{
	InterfaceList[static_cast<unsigned int>(params[1])]->ScriptUpdate();
	return 0;
}
cell AMX_NATIVE_CALL SLE_SetTicksPerCycle(AMX* amx, cell* params)
{
	ticks_per_cycle = static_cast<unsigned int>(params[1]);
	return 0;
}

AMX_NATIVE_INFO NativeFunctionsTable[] =
{
	{ "SLE_ScriptInit", SLE_ScriptInit },
	{ "SLE_ScriptUpdate", SLE_ScriptUpdate },
	{ "SLE_SetTicksPerCycle", SLE_SetTicksPerCycle },

	//List
	{ "SLE_list_Destroy", SLE_list_Destroy },
	{ "SLE_list_Create", SLE_list_Create },
	{ "SLE_list_empty", SLE_list_empty },
	{ "SLE_list_size", SLE_list_size },
	{ "SLE_list_max_size", SLE_list_max_size },
	{ "SLE_list_front", SLE_list_front },
	{ "SLE_list_back", SLE_list_back },
	{ "SLE_list_assign2", SLE_list_assign2 },
	{ "SLE_list_push_front", SLE_list_push_front },
	{ "SLE_list_pop_front", SLE_list_pop_front },
	{ "SLE_list_push_back", SLE_list_push_back },
	{ "SLE_list_pop_back", SLE_list_pop_back },
	{ "SLE_list_insert", SLE_list_insert },
	{ "SLE_list_erase", SLE_list_erase },
	{ "SLE_list_resize", SLE_list_resize },
	{ "SLE_list_swap", SLE_list_swap },
	
	{ "SLE_algo_foreach_list_get", SLE_algo_foreach_list_get },

	{ "SLE_list_iter_copy", SLE_list_iter_copy },
	{ "SLE_list_begin", SLE_list_begin },
	{ "SLE_list_end", SLE_list_end },
	{ "SLE_list_iterator_advance", SLE_list_iterator_advance },
	{ "SLE_list_iterator_distance", SLE_list_iterator_distance },
	{ "SLE_list_iterator_equal", SLE_list_iterator_equal },
	{ "SLE_list_itr_dereference", SLE_list_itr_dereference },

	{ "SLE_list_remove", SLE_list_remove },
	{ "SLE_list_unqiue", SLE_list_unqiue },
	{ "SLE_list_sort", SLE_list_sort },
	{ "SLE_list_reverse", SLE_list_reverse },
	{ "SLE_list_merge", SLE_list_merge },
	{ "SLE_list_splice", SLE_list_splice },

	{ "SLE_list_equal", SLE_list_equal },
	{ "SLE_list_greater_than", SLE_list_greater_than },
	{ "SLE_list_lesser_than", SLE_list_less_than },

	{ "test", test },
	{ 0, 0 }
};
/************************************************************************************************************/
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	std::vector<Interface *>::iterator itr = std::find(InterfaceList.begin(), InterfaceList.end(), nullptr);
	if (itr == InterfaceList.end())
		InterfaceList.push_back(new Interface(amx));
	else
		*itr = new Interface(amx);
	
	return amx_Register(amx, NativeFunctionsTable, -1);
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	std::vector<Interface *>::iterator itr = InterfaceList.begin();
	while ((*itr)->amx != amx) itr++;

	delete *itr;
	*itr = nullptr;

	return AMX_ERR_NONE;
}