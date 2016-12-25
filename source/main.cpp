/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

main.cpp

*************************************************************************************************************/
#include "main.h"

#include "interface.h"
#include "natives\string.h"
#include "natives\ctype.h"
#include "natives\math.h"
#include "natives\time.h"
#include "natives\algorithm.h"
#include "natives\isc.h"

#include <algorithm>
#include <vector>

#pragma warning(disable : 4996)
/************************************************************************************************************/
extern void *pAMXFunctions;

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;
/************************************************************************************************************/
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*** PAWN Library Extension v%d.%d.%d loaded ***", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
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
cell AMX_NATIVE_CALL PLE_ScriptInit(AMX* amx, cell* params)
{
	cell *addr = NULL;
	char scriptIdentifier[SCRIPT_IDENTIFIER_SIZE];
	unsigned int scriptKey, duplicate_count = 0;

	amx_GetAddr(amx, params[2], &addr);
	amx_GetString(scriptIdentifier, addr, 0, params[3]);

	auto amx_interface = InterfaceList.begin(), interface_list_end = InterfaceList.end();
	while (amx_interface != interface_list_end)
	{
		if (!IsValidInterface(amx_interface)) continue;

		if ((*amx_interface)->amx == amx)
		{
			strcpy((*amx_interface)->ScriptIdentifier, scriptIdentifier);
			scriptKey = (*amx_interface)->ScriptKey;

			(*amx_interface)->SetInterfaceState(INTERFACE_STATES::PLE_INITILIZED_S1);
			(*amx_interface)->SetScriptType(SCRIPT_TYPES::SCRIPT_SUPPORTED);
		}
		else if (!strcmp((*amx_interface)->ScriptIdentifier, scriptIdentifier))
			duplicate_count++;	

		amx_interface++;
	}

	if (!strcmp(scriptIdentifier, UNDEFINED_SCRIPT_IDENTIFIER))
	{
		logprintf("[NOTICE] PAWN Library Extension: A loaded script does not have script a identifier.");
		logprintf("[NOTICE] Total number of scripts without identifer: %d", duplicate_count);
	}
	else if (duplicate_count)
		logprintf("[WARNING] PAWN Library Extension: Duplicate Script Identifier '%s'.", scriptIdentifier);

	if (PLUGIN_INCLUDE_KEY > params[1])
		logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s'.\nThe script is using older version of PLE includes with a newer version of the plugin.", scriptIdentifier);
	else if(PLUGIN_INCLUDE_KEY > params[1])
		logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s'.\nThe script is using a newer version of PLE includes with an older version of the plugin.", scriptIdentifier);

	return scriptKey;
}

AMX_NATIVE_INFO NativeFunctionsTable[] =
{
	{"PLE_ScriptInit", PLE_ScriptInit },

	{ "IsValidScript", Natives::IsValidScript },
	{ "GetScriptType", Natives::GetScriptType },
	{ "GetScriptPoolSize", Natives::GetScriptPoolSize },
	{ "GetScriptIdentifierFromKey", Natives::GetScriptIdentifierFromKey },
	{ "GetScriptKeyFromIdentifier", Natives::GetScriptKeyFromIdentifier },

	{ "memmove", Natives::string_memmove },
	{ "strcpy", Natives::string_strcpy },
	{ "strncpy", Natives::string_strncpy },
	{ "strncat", Natives::string_strncat },
	{ "strncmp", Natives::string_strncmp },
	{ "memchr", Natives::string_memchr },
	{ "strchr", Natives::string_strchr },
	{ "strrchr", Natives::string_strrchr },
	{ "strcspn", Natives::string_strcspn },
	{ "strpbrk", Natives::string_strpbrk },
	{ "strspn", Natives::string_strspn },
	{ "strtok", Natives::string_strtok },
	{ "memset", Natives::string_memset },
	{ "strreplace", Natives::string_strreplace },
	{ "strtrim", Natives::string_strtrim},
	{ "strtolower", Natives::string_strtolower },
	{ "strtoupper", Natives::string_strtoupper },

	{ "isalnum", Natives::ctype_isalnum },
	{ "isalpha", Natives::ctype_isalpha },
	{ "isblank", Natives::ctype_isblank },
	{ "iscntrl", Natives::ctype_iscntrl },
	{ "isdigit", Natives::ctype_isdigit },
	{ "isgraph", Natives::ctype_isgraph },
	{ "islower", Natives::ctype_islower },
	{ "isprint", Natives::ctype_isprint },
	{ "ispunct", Natives::ctype_ispunct },
	{ "isspace", Natives::ctype_isspace },
	{ "isupper", Natives::ctype_isupper },
	{ "isxdigit", Natives::ctype_isxdigit },

	{ "exp", Natives::math_exp },
	{ "frexp", Natives::math_frexp },
	{ "ldexp", Natives::math_ldexp },
	{ "modf", Natives::math_modf },
	{ "log", Natives::math_log },
	{ "log10", Natives::math_log10 },
	{ "exp2", Natives::math_exp2 },
	{ "expm1", Natives::math_expm1 },
	{ "log2", Natives::math_log2 },
	{ "log1p", Natives::math_log1p },
	{ "cbrt", Natives::math_cbrt },
	{ "hypot", Natives::math_hypot },
	{ "fmod", Natives::math_fmod },
	{ "remainder", Natives::math_remainder },
	{ "copysign", Natives::math_copysign },
	{ "fdim", Natives::math_fdim },
	{ "fmin", Natives::math_fmin },
	{ "fmax", Natives::math_fmax },
	{ "fma", Natives::math_fma },
	{ "cbrt", Natives::math_cbrt },

	{ "now", Natives::time_now },
	{ "createtime", Natives::time_createtime },
	{ "gettimestamp", Natives::time_gettimestamp },
	{ "difftime", Natives::time_difftime },
	{ "asctime", Natives::time_asctime },
	{ "strftime", Natives::time_strftime },

	{ "ibsearch", Natives::algo_ibsearch },
	{ "fbsearch", Natives::algo_fbsearch },
	{ "sbsearch", Natives::algo_sbsearch },

	{ "GetExternalFunctionID", Natives::isc_GetExternalFunctionID },
	{ "CallExternalFunction", Natives::isc_CallExternalFunction },
	{ "GetExternalFunctionInfo", Natives::isc_GetExternalFunctionInfo },
	{ "GetExternalVariableID", Natives::isc_GetExternalVariableID },
	{ "GetExternalVariableInfo", Natives::isc_GetExternalVariableInfo },
	{ "GetExternalVariable", Natives::isc_GetExternalVariable },
	{ "SetExternalVariable", Natives::isc_SetExternalVariable },
	{ 0, 0 }
};
/************************************************************************************************************/
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	//Interfaces are added/removed on server startup/shutdown
	//Interfaces added/removed at runtime needn't be thought about as nobody loads too many AMX excutables at once (unless he is...)
	//Therefore, we will avoid reusing of objects for the sake of readablity. (performance gain is negligible) 

	auto amx_interface = std::find(InterfaceList.begin(), InterfaceList.end(), nullptr); //find an unused scriptKey

	if (amx_interface == InterfaceList.end())
		InterfaceList.push_back(new Interface(amx, InterfaceList.size())); //no unused script key, we will proceed to create a new key
	else
		*amx_interface = new Interface(amx, std::distance(InterfaceList.begin(), amx_interface)); //unused script key found, we will assign that key to this AMX instance

	return amx_Register(amx, NativeFunctionsTable, -1);
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{	
	auto unloading_interface = InterfaceList.begin(), interface_list_end = InterfaceList.end();

	//find the interface which interacts with the AMX instance being unloaded
	while (unloading_interface != interface_list_end)
	{
		if (IsValidInterface(unloading_interface))
			if ((*unloading_interface)->amx == amx) break; //found the interface

		unloading_interface++;
	}

	//unloading_interface points to the interface of the AMX instance being unloaded
	unsigned int scriptKey = (*unloading_interface)->ScriptKey;
	char * scriptIdentifier = (*unloading_interface)->ScriptIdentifier;

	//trigger OnScriptExit in every script except the one being unloaded
	if ((*unloading_interface)->GetInterfaceState() == INTERFACE_STATES::PLE_INITILIZED_S2)
	{
		for (auto itr = InterfaceList.begin(); itr != interface_list_end; itr++)
			if (IsValidInterface(itr) && itr != unloading_interface)
				(*itr)->Trigger_OnScriptExit(scriptKey, scriptIdentifier);
	}	
	else { /* shouldn't happen */ }

	//ScriptKeys indicate the position of the interface in the InterfaceList.
	//Therefore, the interface pointers won't be removed from the InterfaceList. They will instead be invalidated.
	InvalidateInterface(unloading_interface);
	return AMX_ERR_NONE;
}
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	for (auto amx_interface = InterfaceList.begin(), interface_list_end = InterfaceList.end(); amx_interface != interface_list_end; amx_interface++)
	{
		if (!IsValidInterface(amx_interface)) continue;

		switch ((*amx_interface)->GetInterfaceState())
		{			
			case INTERFACE_STATES::LOADED:
			{
				//Inform other AMX instances that an unsupported script has been loaded
				unsigned int scriptKey = (*amx_interface)->ScriptKey;
				char * scriptIdentifier = (*amx_interface)->ScriptIdentifier;

				for (auto itr = InterfaceList.begin(); itr != interface_list_end; itr++)
					if (amx_interface != itr)
						(*itr)->Trigger_OnScriptInit(scriptKey, scriptIdentifier);

				(*amx_interface)->SetInterfaceState(INTERFACE_STATES::PLE_INITILIZED_S2);

				logprintf("[NOTICE] PAWN Library Extension: A script was loaded which wasn't compiled for PLE.");
				break;
			}
			case INTERFACE_STATES::PLE_INITILIZED_S1:
			{
				//Inform other AMX instances that a script has been loaded
				unsigned int scriptKey = (*amx_interface)->ScriptKey;
				char * scriptIdentifier = (*amx_interface)->ScriptIdentifier;

				for (auto itr = InterfaceList.begin(); itr != interface_list_end; itr++)
					if(amx_interface != itr)
						(*itr)->Trigger_OnScriptInit(scriptKey, scriptIdentifier);

				(*amx_interface)->SetInterfaceState(INTERFACE_STATES::PLE_INITILIZED_S2);
				break;
			}
		}
	}
}