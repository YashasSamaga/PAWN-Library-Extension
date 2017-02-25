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
	enum INTERFACE_FLAGS
	{
		INVALID = 0x0,
		LOADED = 0x01,
		SCRIPT_SUPPORTED = 0x02,
		SCRIPT_UNSUPPORTED = 0x04,
		INTERFACE_INITILIZED = 0x08
	};
	/********************************************************************************************************/
	class Interface
	{
	public:
		AMX * amx; //pointer to AMX instance

		int ScriptKey; //every AMX instance is assigned a unique id	
		std::string ScriptIdentifier; //SSO optimization in most cases
		std::chrono::system_clock::time_point time_loaded;

		Interface() {}
		~Interface() {}
		int Initilize(AMX * amx, int ScriptKey);
		void Trigger_OnScriptInit(int scriptKey, std::string& scriptIdentifier) const;
		void Trigger_OnScriptExit(int scriptKey, std::string& scriptIdentifier) const;

		bool empty() const { return (flags == INTERFACE_FLAGS::INVALID); }

		bool IsFlagSet(uint32_t flag) const { return ((this->flags & flag) == flag); }
		uint32_t GetFlags() const { return this->flags; }
		void SetFlag(uint32_t flag) { this->flags |= flag; }
		void UnsetFlag(uint32_t flag) { this->flags &= ~flag; }
		void Reset() { this->flags = INTERFACE_FLAGS::INVALID; }

	private:
		int cbidx_OnScriptInit;
		int cbidx_OnScriptExit;
		uint32_t flags;
	};
	/********************************************************************************************************/
	extern int AddInterface(AMX * amx);
	extern int FindInterface(AMX * amx);
	extern int DeleteInterface(AMX * amx);
	extern bool IsValidScript(const int scriptKey);
	extern AMX * GetInterfaceAMX(const int scriptKey);

	extern void ProcessTick();
}
namespace Natives
{
	cell AMX_NATIVE_CALL interface_ScriptInitAcknowledge(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_IsValidScript(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptFlags(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptPoolSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptIdentifierFromKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL interface_GetScriptKeyFromIdentifier(AMX* amx, cell* params);
}