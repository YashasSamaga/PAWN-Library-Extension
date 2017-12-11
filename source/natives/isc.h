/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Interscript communication (ISC)
isc.h

*************************************************************************************************************/
#ifndef PLE_ISC_H_INCLUDED
#define PLE_ISC_H_INCLUDED

#include "main.h"

namespace PLE
{
	namespace isc
	{
		class function
		{
		public:
			function(uint8_t scriptKey, uint16_t funcidx) { info.scriptKey = scriptKey;	info.funcidx = funcidx; }
			function(uint32_t fid) { decode(fid); }

			void decode(uint32_t fid)
			{
				info.scriptKey = (fid & 0xFF000000) >> 24;
				info.funcidx = (fid & 0x00FFFF00) >> 8;
			}
			void encode(uint32_t& fid) const 
			{
				fid = (info.scriptKey << 24) | (info.funcidx << 8);
			}
			IScript::ScriptKey_t GetScriptKey() const { return info.scriptKey; }
			IScript::FunctionIndex_t GetFunctionIndex() const { return info.funcidx; }
		private:
			struct {
				uint32_t scriptKey : 8;
				uint32_t funcidx : 16;
				uint32_t reserved : 8;
			} info;
			static_assert(sizeof(cell) == 4);
			static_assert(sizeof(IScript::ScriptKey_t) == 1);
			static_assert(sizeof(IScript::FunctionIndex_t) == 2);
		};

		class variable
		{
		public:
			variable(uint8_t scriptKey, uint16_t varidx) { info.scriptKey = scriptKey;	info.varidx = varidx; }
			variable(uint32_t vid) { decode(vid); }

			void decode(uint32_t vid)
			{
				info.scriptKey = (vid & 0xFF000000) >> 24;
				info.varidx = (vid & 0x00FFFF00) >> 8;
			}
			void encode(uint32_t& vid)
			{
				vid = (info.scriptKey << 24) | (info.varidx << 8);
			}
			IScript::ScriptKey_t GetScriptKey() const { return info.scriptKey; }
			IScript::VariableIndex_t GetVariableIndex() const { return info.varidx; }
		private:
			struct {
				uint32_t scriptKey : 8;
				uint32_t varidx : 16;
				uint32_t reserved : 8;
			} info;
			static_assert(sizeof(cell) == 4);
			static_assert(sizeof(IScript::ScriptKey_t) == 1);
			static_assert(sizeof(IScript::VariableIndex_t) == 2);
		};
	}

	namespace natives
	{
		//native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
		extern cell AMX_NATIVE_CALL isc_GetAMXHeader(AMX * amx, cell *params);
		//native ReadAMXMemory(scriptKey, address, &val);
		extern cell AMX_NATIVE_CALL isc_ReadAMXMemory(AMX * amx, cell *params);
		//native WriteAMXMemory(scriptKey, address, val);
		extern cell AMX_NATIVE_CALL isc_WriteAMXMemory(AMX * amx, cell *params);
		//native ReadAMXMemoryArray(scriptKey, address, dest[], numcells);
		extern cell AMX_NATIVE_CALL isc_ReadAMXMemoryArray(AMX * amx, cell *params);
		//native WriteAMXMemoryArray(scriptKey, address, src[], numcells);
		extern cell AMX_NATIVE_CALL isc_WriteAMXMemoryArray(AMX * amx, cell *params);
		//native GetExternalFunctionID(scriptKey, const name[]);
		extern cell AMX_NATIVE_CALL isc_GetExternalFunctionID(AMX * amx, cell* params);
		//native CallExternalFunction(extFuncID, &ret, const format[], ...);
		extern cell AMX_NATIVE_CALL isc_CallExternalFunction(AMX * amx, cell* params);
		//native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);
		extern cell AMX_NATIVE_CALL isc_GetExternalFunctionInfo(AMX * amx, cell* params);
		//native GetExternalVariableID(scriptKey, const name[]);
		extern cell AMX_NATIVE_CALL isc_GetExternalVariableID(AMX * amx, cell* params);
		//native GetExternalVariable(extVarID, &result);
		extern cell AMX_NATIVE_CALL isc_GetExternalVariableInfo(AMX * amx, cell* params);
		//native SetExternalVariable(extVarID, value);
		extern cell AMX_NATIVE_CALL isc_GetExternalVariable(AMX * amx, cell* params);
		//native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
		extern cell AMX_NATIVE_CALL isc_SetExternalVariable(AMX * amx, cell* params);
	}
}

#endif /* PLE_ISC_H_INCLUDED */