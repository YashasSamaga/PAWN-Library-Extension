/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Interscript communication (ISC)
isc.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
#define INVALID_EXT_FID ~VALIDITY_EFID_RESBITS
#define INVALID_EXT_VID ~VALIDITY_EVID_RESBITS

#define VALIDITY_EFID_RESBITS 172
#define VALIDITY_EVID_RESBITS 171

namespace Natives
{
	cell AMX_NATIVE_CALL isc_GetExternalFunctionID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL isc_CallExternalFunction(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL isc_GetExternalFunctionInfo(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL isc_GetExternalVariableID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL isc_GetExternalVariableInfo(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL isc_GetExternalVariable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL isc_SetExternalVariable(AMX* amx, cell* params);
}
