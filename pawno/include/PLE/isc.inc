/************************************************************************************************************
Standard Library Extension


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

native GetExternalFunctionID(scriptKey, const name[]);
native CallExternalFunction(extFuncID, &ret, const format[], ...);
native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);

native GetExternalVariableID(scriptKey, const name[]);
native GetExternalVariable(extVarID, &result);
native SetExternalVariable(extVarID, value);
native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
