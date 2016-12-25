/************************************************************************************************************
Standard Library Extension


algorithm.inc
*************************************************************************************************************/
#if defined _PLE_INTERFACE_INC
	#endinput
#else
	#define _PLE_INTERFACE_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif
/*****************************************************************************************************************/
#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

#define INVALID_SCRIPT_ID -1
#define INVALID_INTERFACE_ID -1

#define SCRIPT_IDENTIFIER_SIZE 32

enum
{
	INVALID,
	SCRIPT_UNSUPPORTED,
	SCRIPT_SUPPORTED
};

native IsValidScript(scriptKey);
native GetScriptType(scriptKey);
native GetScriptPoolSize();
native GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));