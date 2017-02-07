/************************************************************************************************************
PAWN Library Extension

Interscript-Communication
isc.inc
*************************************************************************************************************/
#if defined _PLE_ISC_INC
	#endinput
#else
	#define _PLE_ISC_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif
/*****************************************************************************************************************/
#define INVALID_EXT_FID ~172
#define INVALID_EXT_VID ~171
/*****************************************************************************************************************/
enum AMX_HEADER
{
	AMX_HEADER_SIZE,
	AMX_HEADER_MAGIC,
	AMX_HEADER_FILE_VERSION,
	AMX_HEADER_AMX_VERSION,
	AMX_HEADER_FLAGS,
	AMX_HEADER_DEFSIZE,
	AMX_HEADER_COD,
	AMX_HEADER_DAT,
	AMX_HEADER_HEA,
	AMX_HEADER_STP,
	AMX_HEADER_CIP,
	AMX_HEADER_PUBLICS,
	AMX_HEADER_NATIVES,
	AMX_HEADER_LIBRARIES,
	AMX_HEADER_PUBVARS,
	AMX_HEADER_TAGS,
	AMX_HEADER_NAMETABLE
}
enum AMX_FUNCSTUBNT
{
	AMX_FUNCSTUBNT_ADDRESS,
	AMX_FUNCSTUBNT_NAMEOFS
}

stock const AMX_HEADER_OFFSETS[] =
{
	0, 	//AMX_HEADER_SIZE
	4, 	//AMX_HEADER_MAGIC
	6, 	//AMX_HEADER_FILE_VERSION
	7, 	//AMX_HEADER_AMX_VERSION
	8, 	//AMX_HEADER_FLAGS
	10, //AMX_HEADER_DEFSIZE
	12, //AMX_HEADER_COD
	16, //AMX_HEADER_DAT
	20, //AMX_HEADER_HEA
	24, //AMX_HEADER_STP
	28, //AMX_HEADER_CIP
	32, //AMX_HEADER_PUBLICS
	36, //AMX_HEADER_NATIVES
	40, //AMX_HEADER_LIBRARIES
	44, //AMX_HEADER_PUBVARS
	48, //AMX_HEADER_TAGS
	52 	//AMX_HEADER_NAMETABLE
};

stock GetArrayAddress(arr[])
{
	#emit LOAD.S.pri arr
	#emit RETN

	return 0; //make the compiler happy
}
stock GetVarAddress(&var)
{
	#emit LOAD.S.pri var
	#emit RETN

	return 0; //make the compiler happy
}
/*****************************************************************************************************************/
native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
native ReadAMXMemory(scriptKey, address, &val); //address relative to the script's DAT segment
native WriteAMXMemory(scriptKey, address, val); //address relative to the script's DAT segment

native ReadAMXMemoryArray(scriptKey, address, dest[], numcells); //address relative to the script's DAT segment
native WriteAMXMemoryArray(scriptKey, address, src[], numcells); //address relative to the script's DAT segment

native GetExternalFunctionID(scriptKey, const name[]);
native CallExternalFunction(extFuncID, &ret, const format[], ...);
native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);

native GetExternalVariableID(scriptKey, const name[]);
native GetExternalVariable(extVarID, &result);
native SetExternalVariable(extVarID, value);
native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
