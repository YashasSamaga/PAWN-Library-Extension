/************************************************************************************************************
PAWN Library Extension

main.cpp

//TODO
debug library
matrix.cpp library
invoke using address function
managed & unmanaged pointers
setjmp longjmp
bitset operator[]
biset shifts
hash
invoke functional
functional target, target_type
functional address func calls
basic_string
array
forward_list
set
multiset
map
multimap
chrono
unordered_set/multiset
unordered_map/multimap
stack
deque
queue
priority_queue
iterator
valarray
random
threads
regex
streams
pair
tuple
HP Timers
*************************************************************************************************************/
#include "main.h"
#include "iscript.h"

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>
#include <samplog/PluginLogger.h>

extern void *pAMXFunctions;
logprintf_t logprintf;

samplog::CPluginLogger logger("PAWN-Library-Extension");

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{	
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	samplog::Init();
	
	logprintf("*********************************************************");
	logprintf("  PAWN Library Extension v%d.%d.%d loaded", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
	logprintf("  Version Key:%h", PLE_PLUGIN_VERSION_KEY);
	logprintf("*********************************************************");
	return true;
}
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	samplog::Exit();
	logprintf("*** PAWN Library Extension v%d.%d.%d unloaded ***", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
}
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{	
	PLE::IScript::AddInterface(amx);
	return AMX_ERR_NONE;
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{	
	PLE::IScript::RemoveInterface(amx);
	return AMX_ERR_NONE;
}