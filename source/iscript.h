/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Interface is a layer between the AMX instance and the plugin itself.
iscript.h

*************************************************************************************************************/
#ifndef PLE_ISCRIPT_H_INCLUDED
#define PLE_ISCRIPT_H_INCLUDED

#include "main.h"
#include <cstdint>
#include <string>

namespace PLE
{
	namespace IScript
	{
		/* these limits are not imposed by PAWN; they are imposed by this plugin */
		typedef std::int8_t ScriptKey_t;
		typedef std::int16_t NativeIndex_t;
		typedef std::int16_t FunctionIndex_t;
		typedef std::int16_t VariableIndex_t;

		constexpr ScriptKey_t INVALID_SCRIPT_KEY = -1;

		namespace ScriptIdentifier
		{
			/* we use std::string so that we can use the '==' operator overload on C-strings */
			const std::string undefined = "Undefined";
			const std::string unsupported = "Unsupported";

			constexpr std::size_t max_length = MAX_SYMBOL_LEN;
		}

		enum interface_type
		{
			invalid = 0,
			supported = 1,
			unsupported = 2
		};

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

			cell scriptidentifier[ScriptIdentifier::max_length];

			cell scriptkey;
			cell reserved58;
			cell reserved59;
			cell reserved60;

			cell reserved61;
			cell reserved62;
			cell reserved63;
			cell signature_end;
		};

		/*
		**	PAWN structures needn't be aligned to the alignment requirements of the structure in the plugin. 
		**	However, they will be aligned according to alignment requirements of 'cell'. If our structure's
		**	alignment requirements is equal to that of 'cell' we don't have to worry about alignment while
		**	casting pointers (cell* to PLE_HEADER*).
		*/
		static_assert(alignof(PLE_HEADER) == alignof(cell));

		/*
		** The following class identifier ("IScript") uses the prefix 'I' but it isn't an interface as
		** dictated in common conventions. It is supposed to stand for "I[nterface]Script".
		*/
		class IScript
		{
		public:
			AMX *amx;

			IScript() { type = interface_type::invalid; }
			~IScript() {}

			void load(AMX *p_amx, ScriptKey_t p_scriptKey); //Initilizes the interface, registers natives, sets public constants
			void unload(); //Unloads the AMX and frees the interface for another script
			bool empty() const { return (type == interface_type::invalid); }

			ScriptKey_t GetScriptKey() const { return scriptKey; }
			const std::string& GetScriptIdentifier() const { return scriptIdentifier; }
			interface_type GetType() const { return type; }
			PLE_HEADER* GetHeader() const { return ple_header; }

		private:
			ScriptKey_t scriptKey; //every AMX instance is assigned a unique id
			std::string scriptIdentifier; //SSO optimization in most cases		

			interface_type type;
			PLE_HEADER *ple_header;
			cell startof_header_marker;
			cell endof_header_marker;

			//OnScriptLoad is called in every script (except the newly initilized) when a script is loaded
			void Trigger_OnScriptLoad(ScriptKey_t p_scriptKey, const std::string& p_scriptIdentifier) const;
			//OnScriptUnload is called in every script (except the unloaded script) when a script is unloaded
			void Trigger_OnScriptUnload(ScriptKey_t p_scriptKey, const std::string& p_scriptIdentifier) const;
		};

		extern void AddInterface(AMX *amx); //Creates and initilizes an interface for amx
		extern void RemoveInterface(AMX *amx); //Deinitilizes and deletes the interface for amx
		extern ScriptKey_t FindInterface(AMX *amx);	//Returns the scriptKey of the amx's interface
		extern bool IsValidScript(cell scriptKey); //Check if a scriptKey is valid
		extern AMX* GetInterfaceAMX(ScriptKey_t scriptKey); //Returns the AMX structure of the interface (validity of scriptKey is not checked)
	}
	namespace natives
	{
		extern cell AMX_NATIVE_CALL iscript_IsValidScript(AMX* amx, cell* params);
		extern cell AMX_NATIVE_CALL iscript_GetScriptType(AMX* amx, cell* params);
		extern cell AMX_NATIVE_CALL iscript_GetScriptPoolSize(AMX* amx, cell* params);
		extern cell AMX_NATIVE_CALL iscript_GetScriptIdentifierFromKey(AMX* amx, cell* params);
		extern cell AMX_NATIVE_CALL iscript_GetScriptKeyFromIdentifier(AMX* amx, cell* params);
		extern cell AMX_NATIVE_CALL iscript_GetScriptPLEHeader(AMX* amx, cell* params);
	}
}
#endif /* PLE_ISCRIPT_H_INCLUDED */