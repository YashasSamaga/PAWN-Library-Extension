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
#include <cstdint>
/************************************************************************************************************/
namespace Interface 
{
	#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
	#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

	#define INVALID_SCRIPT_ID -1
	#define INVALID_AMX_FUNCIDX -1

	#define SCRIPT_IDENTIFIER_SIZE MAX_SYMBOL_LEN
	/********************************************************************************************************/
	enum INTERFACE_TYPE
	{
		INVALID = 0x0,
		SUPPORTED = 0x01,
		UNSUPPORTED = 0x02
	};
	/********************************************************************************************************/
	struct PLE_HEADER
	{
		cell version;
		cell size;
		cell inc_version;
		cell reserved4;

		cell flags;
		cell debug_level;
		cell compiler_version;
		cell reserved8;

		cell dynmem_reserve_size;
		cell reserved10;
		cell reserved11;
		cell reserved12;
		cell reserved13;
		cell reserved14;
		cell reserved15;
		cell reserved16;
		cell custom1;
		cell custom2;
		cell custom3;
		cell custom4;
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
	/********************************************************************************************************/
	class Interface
	{
	public:
		AMX * amx;
		
		int ScriptKey; //every AMX instance is assigned a unique id
		std::string ScriptIdentifier; //SSO optimization in most cases

		Interface() {}
		~Interface() {}

		int Initilize(AMX * amx, int ScriptKey);
		INTERFACE_TYPE GetType() const { return type; }
		PLE_HEADER* GetHeader() const { return this->ple_header;  }
		void Trigger_OnScriptInit(int scriptKey, std::string& scriptIdentifier) const;
		void Trigger_OnScriptExit(int scriptKey, std::string& scriptIdentifier) const;

		bool empty() const { return (type == INTERFACE_TYPE::INVALID); }
		void Delete() { this->type = INTERFACE_TYPE::INVALID; }

	private:
		PLE_HEADER * ple_header;
		cell ple_compliant_pubvar_addr;
		INTERFACE_TYPE type;

		int cbidx_OnScriptInit;
		int cbidx_OnScriptExit;		
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
	cell AMX_NATIVE_CALL interface_GetScriptPLEHeader(AMX* amx, cell* params);
	
}