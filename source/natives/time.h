/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

"Custom" Time Library for PAWN (This is not a porting of C++ ctime library)
time.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL time_now(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL time_createtime(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL time_gettimestamp(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL time_difftime(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL time_asctime(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL time_strftime(AMX* amx, cell* params);
}
