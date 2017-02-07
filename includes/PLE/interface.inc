/************************************************************************************************************
PAWN Library Extension

Interface is a layer between the AMX instance and the plugin itself.
interface.inc
************************************************************************************************************/
#if defined _PLE_INTERFACE_INC
	#endinput
#else
	#define _PLE_INTERFACE_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif

#include <PLE\time>
/**********************************************************************************************************/
#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

#define INVALID_SCRIPT_ID -1
#define INVALID_INTERFACE_ID -1

#define SCRIPT_IDENTIFIER_SIZE 32
/***********************************************************************************************************/
#if !defined interface
	#define interface:: int_
#endif

enum
{
	INVALID,
	SCRIPT_UNSUPPORTED,
	SCRIPT_SUPPORTED
};

native interface::IsValidScript(scriptKey);
native interface::GetScriptType(scriptKey);
native interface::GetScriptPoolSize();
native interface::GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
native interface::GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));
native interface::GetScriptStartupTime(scriptKey, _time_t[time_t]);
