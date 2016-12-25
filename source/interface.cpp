/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interface is a layer between the AMX instance and the plugin itself.
interface.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"

#include <algorithm>
#include <vector>
/************************************************************************************************************/
std::vector <Interface *> InterfaceList;

Interface::Interface(AMX * amx, unsigned int ScriptKey) : amx(amx), ScriptKey(ScriptKey)
{
	strcpy(this->ScriptIdentifier, UNSUPPORTED_SCRIPT_IDENTIFIER);
	this->state = INTERFACE_STATES::LOADED;	
	this->type = SCRIPT_TYPES::SCRIPT_UNSUPPORTED;

	//public OnScriptInit(scriptKey, scriptIdentifier[])
	int amx_error = amx_FindPublic(amx, "OnScriptInit", &this->cbidx_OnScriptInit);
	if (amx_error != AMX_ERR_NONE)
		this->cbidx_OnScriptInit = CALLBACK_ERROR::CALLBACK_INVALID;

	//public OnScriptExit(scriptKey, scriptIdentifier[])
	amx_error = amx_FindPublic(amx, "OnScriptExit", &this->cbidx_OnScriptExit);
	if (amx_error != AMX_ERR_NONE)
		this->cbidx_OnScriptExit = CALLBACK_ERROR::CALLBACK_INVALID;

	time(&(this->time_loaded));
}

//OnScriptInit is called in every script (except the newly initilized) when a script is loaded
void Interface::Trigger_OnScriptInit(unsigned int scriptKey, char * scriptIdentifier)
{
	if (this->cbidx_OnScriptInit == CALLBACK_ERROR::CALLBACK_INVALID) return;

	cell addr;
	amx_PushString(amx, &addr, NULL, scriptIdentifier, NULL, NULL);
	amx_Push(amx, scriptKey);

	amx_Exec(this->amx, NULL, this->cbidx_OnScriptInit);
	amx_Release(amx, addr);
}
//OnScriptExit is called in every script (except the unloaded script) when a script is unloaded
void Interface::Trigger_OnScriptExit(unsigned int scriptKey, char * scriptIdentifier)
{
	if (this->cbidx_OnScriptExit == CALLBACK_ERROR::CALLBACK_INVALID) return;

	cell addr;
	amx_PushString(amx, &addr, NULL, scriptIdentifier, NULL, NULL);
	amx_Push(amx, scriptKey);

	amx_Exec(this->amx, NULL, this->cbidx_OnScriptExit);
	amx_Release(amx, addr);	
}

bool IsValidInterface(std::vector <Interface *>::iterator iter)
{
	return !(*iter == nullptr);
}
void InvalidateInterface(std::vector <Interface *>::iterator iter)
{
	if (IsValidInterface(iter))
	{
		delete (*iter);
		*iter = nullptr;
	}
}

namespace Natives
{
	//native IsValidScript(scriptKey);
	cell AMX_NATIVE_CALL IsValidScript(AMX* amx, cell* params)
	{
		unsigned int scriptKey = static_cast<unsigned int>(params[1]);

		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return static_cast<cell>(false);
		return static_cast<cell>(InterfaceList[scriptKey] != nullptr);
	}
	//native GetScriptType(scriptKey);
	cell AMX_NATIVE_CALL GetScriptType(AMX* amx, cell* params)
	{
		unsigned int scriptKey = static_cast<unsigned int>(params[1]);

		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return static_cast<cell>(SCRIPT_TYPES::INVALID);
		if (InterfaceList[scriptKey] == nullptr) return static_cast<cell>(SCRIPT_TYPES::INVALID);

		return static_cast<cell>(InterfaceList[scriptKey]->GetScriptType());
	}
	//native GetScriptPoolSize();
	cell AMX_NATIVE_CALL GetScriptPoolSize(AMX* amx, cell* params)
	{
		return static_cast<cell>(InterfaceList.size());
	}
	//native GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
	cell AMX_NATIVE_CALL GetScriptIdentifierFromKey(AMX* amx, cell* params)
	{
		unsigned int scriptKey = static_cast<unsigned int>(params[1]);

		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return static_cast<cell>(false);
		if (InterfaceList[scriptKey] == nullptr) return static_cast<cell>(false);

		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, InterfaceList[scriptKey]->ScriptIdentifier, 0, 0, params[3]);
		return static_cast<cell>(true);
	}
	//native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));
	cell AMX_NATIVE_CALL GetScriptKeyFromIdentifier(AMX* amx, cell* params)
	{
		int len = 0, count = 0;
		cell *addr = NULL;

		amx_GetAddr(amx, params[1], &addr);
		amx_StrLen(addr, &len);

		char scriptIdentifier[SCRIPT_IDENTIFIER_SIZE];
		amx_GetString(scriptIdentifier, addr, 0, SCRIPT_IDENTIFIER_SIZE);

		cell * scriptID;
		amx_GetAddr(amx, params[2], &scriptID);

		for (auto amx_interface = InterfaceList.begin(), interface_list_end = InterfaceList.end(); amx_interface != interface_list_end; amx_interface++)
		{
			if (!strcmp(scriptIdentifier, (*amx_interface)->ScriptIdentifier))
			{
				if (count < static_cast<int>(params[3]))
				{
					*scriptID++ = static_cast<cell>((*amx_interface)->ScriptKey);
					count++;
				}
			}
		}
		return static_cast<cell>(count);
	}
}