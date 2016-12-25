#define FILTERSCRIPT

#define SCRIPT_IDENTIFIER "filterscript-2"

#include <a_samp>
#include <PLE\isc>
#include <PLE\interface>
/*****************************************************************************************************************/
public OnScriptInit(scriptKey, scriptIdentifier[])
{
	printf("[FILTERSCRIPT-SECONDARY] OnScriptInit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);
}
public OnScriptExit(scriptKey, scriptIdentifier[])
{
    printf("[FILTERSCRIPT-SECONDARY] OnScriptExit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);
}
