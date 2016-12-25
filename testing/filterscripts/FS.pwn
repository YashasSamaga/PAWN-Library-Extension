#define FILTERSCRIPT

#define SCRIPT_IDENTIFIER "filterscript"

#include <a_samp>
#include <PLE\isc>
#include <PLE\interface>
/*****************************************************************************************************************/
public AV = 1;
public AB = 2;
public AC = 3;

stock test(...) { }
public OnScriptInit(scriptKey, scriptIdentifier[])
{
	printf("[FILTERSCRIPT-MAIN] OnScriptInit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);

	new efid = GetExternalFunctionID(0, "RandomPublic");
	if(efid == INVALID_EXT_FID) print("[TEST] GetExternalFunction failed.");
	
	new sk, id;
	GetExternalFunctionInfo(efid, sk, id);
	if(sk != 0) print("[TEST] GetExternalFunctionInfo failed.");
	if(id != 3) print("[TEST] GetExternalFunctionInfo failed.");
	
	new ret;
	new a = GetTickCount();
	for(new i = 0; i < 100000; i++)
	{
		CallExternalFunction(efid, ret, "iss", 1337, "abcdefg", "ABCD");
	}
	new b = GetTickCount();
	for(new i = 0; i < 100000; i++)
	{
		//test(1337, "abcdefg", "ABCD");
		CallRemoteFunction("RandomPublic", "iss", 1337, "abcdefg", "ABCD");
	}
	new c = GetTickCount();
	printf("%d %d" , b-a, c-b);
		
	new evid = GetExternalVariableID(0, "PublicVar");
	if(evid == INVALID_EXT_VID) print("[TEST] GetExternalVariableID failed.");

	GetExternalVariableInfo(evid, sk, id);
	if(sk != 0) print("[TEST] GetExternalVariableInfo failed.");
	if(id != 0) print("[TEST] GetExternalVariableInfo failed.");

	new result = 123;
	GetExternalVariable(evid, result);
	if(result != 1027) print("[TEST] GetExternalVariable failed.");

	SetExternalVariable(evid, 1021);
	GetExternalVariable(evid, result);
	if(result != 1021) print("[TEST] GetExternalVariable failed.");

}
public OnScriptExit(scriptKey, scriptIdentifier[])
{
	printf("[FILTERSCRIPT-MAIN] OnScriptExit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);
}
