/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Interface is a layer between the AMX instance and the plugin itself.
interface.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#include <vector>
#include <ctime>
/***********************************************************************************************/
#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

#define INVALID_SCRIPT_ID -1
#define INVALID_INTERFACE_ID -1

#define SCRIPT_IDENTIFIER_SIZE 32

enum SCRIPT_TYPES
{
	INVALID,
	SCRIPT_UNSUPPORTED,
	SCRIPT_SUPPORTED
};
enum CALLBACK_ERROR
{
	CALLBACK_INVALID = -10
};
enum INTERFACE_STATES
{
	LOADED,
	PLE_INITILIZED_S1, //other scripts haven't been informed about the initilization
	PLE_INITILIZED_S2 //other scripts have been informed about the initilization
};
class Interface
{
public:
	AMX * amx; //pointer to AMX instance

	int ScriptKey; //every AMX instance is assigned a unique id	
	char ScriptIdentifier[SCRIPT_IDENTIFIER_SIZE]; //identifier given in the script

	time_t time_loaded; //time when the instance was created

	Interface(AMX * amx, unsigned int ScriptKey);
	void Trigger_OnScriptInit(unsigned int scriptKey, char * scriptIdentifier);
	void Trigger_OnScriptExit(unsigned int scriptKey, char * scriptIdentifier);

	unsigned int GetInterfaceState() { return this->state; }
	void SetInterfaceState(unsigned int state) { this->state = state; }

	unsigned int GetScriptType() { return this->type; }
	void SetScriptType(unsigned int type) { this->type = type; }
private:
	unsigned int state;
	unsigned int type;
	int cbidx_OnScriptInit;
	int cbidx_OnScriptExit;
};
/***********************************************************************************************/
extern std::vector <Interface *> InterfaceList;
extern bool IsValidInterface(std::vector <Interface *>::iterator iter);
extern void InvalidateInterface(std::vector <Interface *>::iterator iter);

namespace Natives
{
	cell AMX_NATIVE_CALL IsValidScript(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetScriptType(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetScriptPoolSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetScriptIdentifierFromKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetScriptKeyFromIdentifier(AMX* amx, cell* params);
}
