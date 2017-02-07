/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interface is a layer between the AMX instance and the plugin itself.
interface.cpp

*************************************************************************************************************/
#include "main.h"
#include "natives/time.h"
#include "interface.h"

#include <algorithm>
#include <vector>
/************************************************************************************************************/
std::vector <Interface *> InterfaceList;

Interface::Interface(AMX * amx, int ScriptKey) : amx(amx), ScriptKey(ScriptKey)
{
	strcpy(this->ScriptIdentifier, UNSUPPORTED_SCRIPT_IDENTIFIER);
	this->state = INTERFACE_STATES::LOADED;	
	this->type = SCRIPT_TYPES::SCRIPT_UNSUPPORTED;

	//public OnScriptInit(scriptKey, scriptIdentifier[])
	if (amx_FindPublic(amx, "OnScriptInit", &this->cbidx_OnScriptInit) != AMX_ERR_NONE)
		this->cbidx_OnScriptInit = CALLBACK_ERROR::CALLBACK_INVALID;

	//public OnScriptExit(scriptKey, scriptIdentifier[])
	if (amx_FindPublic(amx, "OnScriptExit", &this->cbidx_OnScriptExit) != AMX_ERR_NONE)
		this->cbidx_OnScriptExit = CALLBACK_ERROR::CALLBACK_INVALID;

	time(&(this->time_loaded));
}

//OnScriptInit is called in every script (except the newly initilized) when a script is loaded
void Interface::Trigger_OnScriptInit(int scriptKey, char * scriptIdentifier)
{
	if (this->cbidx_OnScriptInit == CALLBACK_ERROR::CALLBACK_INVALID) return;

	cell addr;
	amx_PushString(amx, &addr, NULL, scriptIdentifier, NULL, NULL);
	amx_Push(amx, static_cast<unsigned int>(scriptKey));

	amx_Exec(this->amx, NULL, this->cbidx_OnScriptInit);
	amx_Release(amx, addr);
}
//OnScriptExit is called in every script (except the unloaded script) when a script is unloaded
void Interface::Trigger_OnScriptExit(int scriptKey, char * scriptIdentifier)
{
	if (this->cbidx_OnScriptExit == CALLBACK_ERROR::CALLBACK_INVALID) return;

	cell addr;
	amx_PushString(amx, &addr, NULL, scriptIdentifier, NULL, NULL);
	amx_Push(amx, static_cast<unsigned int>(scriptKey));

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
		const int scriptKey = params[1];

		if (scriptKey < 0 || static_cast<size_t>(scriptKey) >= InterfaceList.size()) return false;
		return (InterfaceList[scriptKey] != nullptr);
	}
	//native GetScriptType(scriptKey);
	cell AMX_NATIVE_CALL GetScriptType(AMX* amx, cell* params)
	{
		const int scriptKey = params[1];

		if (scriptKey < 0 || static_cast<size_t>(scriptKey) >= InterfaceList.size()) return SCRIPT_TYPES::INVALID;
		if (InterfaceList[scriptKey] == nullptr) return SCRIPT_TYPES::INVALID;

		return InterfaceList[scriptKey]->GetScriptType();
	}
	//native GetScriptPoolSize();
	cell AMX_NATIVE_CALL GetScriptPoolSize(AMX* amx, cell* params)
	{
		return static_cast<cell>(InterfaceList.size());
	}
	//native GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
	cell AMX_NATIVE_CALL GetScriptIdentifierFromKey(AMX* amx, cell* params)
	{
		const int scriptKey = params[1];

		if (scriptKey < 0 || static_cast<size_t>(scriptKey) >= InterfaceList.size()) return false;
		if (InterfaceList[scriptKey] == nullptr) return false;

		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, InterfaceList[scriptKey]->ScriptIdentifier, 0, 0, static_cast<size_t>(params[3]));
		return true;
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
	//native GetScriptStartupTime(scriptKey, _time_t[time_t]);
	cell AMX_NATIVE_CALL GetScriptStartupTime(AMX* amx, cell* params)
	{
		const int scriptKey = params[1];

		if (scriptKey < 0 || static_cast<size_t>(scriptKey) >= InterfaceList.size()) return 0;
		if (InterfaceList[scriptKey] == nullptr) return 0;

		cell* time_dest_addr = NULL;
		amx_GetAddr(amx, params[1], &time_dest_addr);

		struct tm * time_dest;
		time_dest = gmtime(&InterfaceList[scriptKey]->time_loaded);

		time_dest_addr[second] = time_dest->tm_sec;
		time_dest_addr[minute] = time_dest->tm_min;
		time_dest_addr[hour] = time_dest->tm_hour;
		time_dest_addr[day] = time_dest->tm_mday;
		time_dest_addr[month] = time_dest->tm_mon;
		time_dest_addr[year] = time_dest->tm_year + 1900;
		time_dest_addr[wday] = time_dest->tm_wday;
		time_dest_addr[yday] = time_dest->tm_yday;
		time_dest_addr[isdst] = time_dest->tm_isdst;

		return static_cast<cell>(InterfaceList[scriptKey]->time_loaded);
	}
}