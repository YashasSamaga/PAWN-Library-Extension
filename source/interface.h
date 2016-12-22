/************************************************************************************************************
Standard Library Extension

interface.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#define INTERFACE_CALLBACK_INVALID -1

class Interface
{
public:
	Interface(AMX * amx);
	~Interface();

	void ScriptUpdate();
	void RequestScriptUpdate();

	AMX * amx;
	char ScriptIdentifier[32];

private:
	int ScriptUpdateCallbackIndex;
	bool SLEEnabled;
};
