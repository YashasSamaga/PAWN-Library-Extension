/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Interscript communication (ISC)
isc.h

*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
#define INVALID_EXT_FID ~VALIDITY_EFID_RESBITS
#define INVALID_EXT_VID ~VALIDITY_EVID_RESBITS

#define VALIDITY_EFID_RESBITS 172
#define VALIDITY_EVID_RESBITS 171

typedef struct externalFunctionID
{
	unsigned short scriptKey : 8;
	unsigned short funcidx : 16;
	unsigned short reserved : 8;

	externalFunctionID(uint8_t scriptKey, uint16_t funcidx) : scriptKey(scriptKey), funcidx(funcidx), reserved(VALIDITY_EFID_RESBITS) { }
	externalFunctionID(uint32_t efid)
	{
		scriptKey = (0xFF000000 & efid) >> 24;
		funcidx = (0xFFFF00 & efid) >> 8;
		reserved = (0xFF & efid);
	}
	operator uint32_t()
	{
		return (scriptKey << 24) + (funcidx << 8) + reserved;
	}
	int operator=(uint32_t efid)
	{
		scriptKey = (0xFF000000 & efid) >> 24;
		funcidx = (0xFFFF00 & efid) >> 8;
		reserved = (0xFF & efid);
		return *this;
	}
}externalFunctionID;
typedef struct externalVariableID
{
	unsigned short scriptKey : 8;
	unsigned short varidx : 16;
	unsigned short reserved : 8;

	externalVariableID(uint8_t scriptKey, uint16_t varidx) : scriptKey(scriptKey), varidx(varidx), reserved(VALIDITY_EVID_RESBITS) { }
	externalVariableID(uint32_t evid)
	{
		scriptKey = (0xFF000000 & evid) >> 24;
		varidx = (0xFFFF00 & evid) >> 8;
		reserved = (0xFF & evid);
	}
	operator uint32_t()
	{
		return (scriptKey << 24) + (varidx << 8) + reserved;
	}
	int operator=(uint32_t evid)
	{
		scriptKey = (0xFF000000 & evid) >> 24;
		varidx = (0xFFFF00 & evid) >> 8;
		reserved = (0xFF & evid);
		return *this;
	}
}externalVariableID;

namespace Natives
{
	//native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
	cell AMX_NATIVE_CALL isc_GetAMXHeader(AMX * amx, cell *params);
	//native ReadAMXMemory(scriptKey, address, &val);
	cell AMX_NATIVE_CALL isc_ReadAMXMemory(AMX * amx, cell *params);
	//native WriteAMXMemory(scriptKey, address, val);
	cell AMX_NATIVE_CALL isc_WriteAMXMemory(AMX * amx, cell *params);
	//native ReadAMXMemoryArray(scriptKey, address, dest[], numcells);
	cell AMX_NATIVE_CALL isc_ReadAMXMemoryArray(AMX * amx, cell *params);
	//native WriteAMXMemoryArray(scriptKey, address, src[], numcells);
	cell AMX_NATIVE_CALL isc_WriteAMXMemoryArray(AMX * amx, cell *params);
	//native GetExternalFunctionID(scriptKey, const name[]);
	cell AMX_NATIVE_CALL isc_GetExternalFunctionID(AMX* amx, cell* params);
	//native CallExternalFunction(extFuncID, &ret, const format[], ...);
	cell AMX_NATIVE_CALL isc_CallExternalFunction(AMX* amx, cell* params);
	//native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);
	cell AMX_NATIVE_CALL isc_GetExternalFunctionInfo(AMX* amx, cell* params);
	//native GetExternalVariableID(scriptKey, const name[]);
	cell AMX_NATIVE_CALL isc_GetExternalVariableID(AMX* amx, cell* params);
	//native GetExternalVariable(extVarID, &result);
	cell AMX_NATIVE_CALL isc_GetExternalVariableInfo(AMX* amx, cell* params);
	//native SetExternalVariable(extVarID, value);
	cell AMX_NATIVE_CALL isc_GetExternalVariable(AMX* amx, cell* params);
	//native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
	cell AMX_NATIVE_CALL isc_SetExternalVariable(AMX* amx, cell* params);
}
