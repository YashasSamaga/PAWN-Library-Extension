/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

main.cpp
*************************************************************************************************************/
#include "main.h"
#include "interface.h"
/************************************************************************************************************/
extern void *pAMXFunctions;
logprintf_t logprintf;
/************************************************************************************************************/
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*********************************************************");
	logprintf("  PAWN Library Extension v%d.%d.%d loaded", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
	logprintf("  Version Key:%h Magic Key:%h", PLE_PLUGIN_VERSION_KEY, PLE_MAGIC_KEY);
	logprintf("*********************************************************");
	return true;
}
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("*** PAWN Library Extension v%d.%d.%d unloaded ***", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
}
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}
/************************************************************************************************************/
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{	
	return Interface::AddInterface(amx);
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{	
	Interface::DeleteInterface(amx);
	return AMX_ERR_NONE;
}
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	Interface::ProcessTick();
}