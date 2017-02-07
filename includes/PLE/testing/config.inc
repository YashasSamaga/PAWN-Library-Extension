/******************************************************************************************************************
PAWN Library Extension

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

#define PLE_MAGIC_KEY 0x3A7B8C
#define PLE_INCLUDE_VERSION_KEY 0xAB000001
/*****************************************************************************************************************/
static const ScriptIdentifier[] = SCRIPT_IDENTIFIER;
new ScriptKey = -1;

#pragma unused ScriptKey
/*****************************************************************************************************************/
forward OnScriptInit(scriptKey, scriptIdentifier[]);
forward OnScriptExit(scriptKey, scriptIdentifier[]);
/*****************************************************************************************************************/
stock GetScriptKey()
{
	return ScriptKey;
}
/*****************************************************************************************************************/
native __InitAcknowledge(magic_key, version_key, const scriptIdentifier[], size = sizeof(scriptIdentifier));
forward __PLEInitilize(skey);
public __PLEInitilize(skey)
{
    ScriptKey = skey;
    return __InitAcknowledge(PLE_MAGIC_KEY, PLE_INCLUDE_VERSION_KEY, ScriptIdentifier);
}

