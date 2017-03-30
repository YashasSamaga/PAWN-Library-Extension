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

#include <string>
#include <chrono>
#include <ctime>
#include <cstdint>
/************************************************************************************************************/
namespace Interface 
{
	#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
	#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

	#define INVALID_SCRIPT_ID -1
	#define INVALID_AMX_FUNCIDX -1

	#define SCRIPT_IDENTIFIER_SIZE 32
	/********************************************************************************************************/
	enum INTERFACE_TYPE
	{
		INVALID = 0x0,
		SUPPORTED = 0x02,
		UNSUPPORTED = 0x04,
	};
	/********************************************************************************************************/
	struct PLE_HEADER
	{
		cell signature1;
		cell signature2;
		cell signature3;
		cell signature4;

		cell version;
		cell size;
		cell inc_version;
		cell reserved8;

		cell flags;
		cell debug_level;
		cell compiler_version;
		cell reserved12;

		cell dynmem_reserve_size;
		cell reserved14;
		cell reserved15;
		cell reserved16;
		cell reserved17;
		cell reserved18;
		cell reserved19;
		cell reserved20;
		cell reserved21;
		cell reserved22;
		cell reserved23;
		cell reserved24;

		cell scriptidentifier[SCRIPT_IDENTIFIER_SIZE];

		cell scriptkey;
		cell reserved58;
		cell reserved59;
		cell reserved60;

		cell reserved61;
		cell reserved62;
		cell reserved63;
		cell signature_end;
	};
	class Interface
	{
	public:
		AMX * amx;
		PLE_HEADER * ple_header;

		cell ple_compliant_pubvar_addr;

		int ScriptKey; //every AMX instance is assigned a unique id	
		std::string ScriptIdentifier; //SSO optimization in most cases
		std::chrono::system_clock::time_point time_loaded;

		Interface() {}
		~Interface() {}
		int Initilize(AMX * amx, int ScriptKey);
		INTERFACE_TYPE GetType() const { return type; }
		void Trigger_OnScriptInit(int scriptKey, std::string& scriptIdentifier) const;
		void Trigger_OnScriptExit(int scriptKey, std::string& scriptIdentifier) const;

		bool empty() const { return (type == INTERFACE_TYPE::INVALID); }
		void Delete() { this->type = INTERFACE_TYPE::INVALID; }

	private:
		int cbidx_OnScriptInit;
		int cbidx_OnScriptExit;
		INTERFACE_TYPE type;
	};
	/********************************************************************************************************/
	extern int AddInterface(AMX * amx);
	extern int FindInterface(AMX * amx);
	extern int DeleteInterface(AMX * amx);
	extern bool IsValidScript(const int scriptKey);
	extern AMX * GetInterfaceAMX(const int scriptKey);
}
namespace Natives
{
	cell AMX_NATIVE_CALL interface_IsValidScript(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptType(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptPoolSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptIdentifierFromKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptKeyFromIdentifier(AMX* amx, cell* params);
}