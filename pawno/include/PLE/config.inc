/******************************************************************************************************************
Standard Library Extension

config.inc
******************************************************************************************************************/
#if defined _PLE_CONFIG_INC
	#endinput
#else
	#define _PLE_CONFIG_INC
#endif
/*****************************************************************************************************************/
#include <PLE/interface>

#if !defined SCRIPT_IDENTIFIER
	#define SCRIPT_IDENTIFIER UNDEFINED_SCRIPT_IDENTIFIER
#endif

#define PLE_PLUGIN_INCLUDE_KEY 0x3A7B8C
/*****************************************************************************************************************/
native PLE_ScriptInit(key, const scriptIdentifier[], size = sizeof(scriptIdentifier));
/*****************************************************************************************************************/
static const ScriptIdentifier[] = SCRIPT_IDENTIFIER;
static ScriptKey;

#pragma unused ScriptKey
/*****************************************************************************************************************/
forward OnScriptInit(scriptKey, scriptIdentifier[]);
forward OnScriptExit(scriptKey, scriptIdentifier[]);
/*****************************************************************************************************************/
#if defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
 		ScriptKey = PLE_ScriptInit(PLE_PLUGIN_INCLUDE_KEY, ScriptIdentifier);
		#if defined PLE_OnFilterScriptInit
			PLE_OnFilterScriptInit();
		#endif
		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit PLE_OnFilterScriptInit
	#if defined PLE_OnFilterScriptInit
		forward PLE_OnFilterScriptInit();
	#endif
#else
    public OnGameModeInit()
	{
	   	ScriptKey = PLE_ScriptInit(PLE_PLUGIN_INCLUDE_KEY, ScriptIdentifier);
		#if defined PLE_OnGameModeInit
			PLE_OnGameModeInit();
		#endif
		return 1;
	}

   	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit PLE_OnGameModeInit
	#if defined PLE_OnGameModeInit
		forward PLE_OnGameModeInit();
	#endif
#endif

stock GetScriptKey()
{
	return ScriptKey;
}
