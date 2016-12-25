/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Character types
ctype.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL ctype_isalnum(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isalpha(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isblank(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_iscntrl(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isdigit(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isgraph(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_islower(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isprint(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_ispunct(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isspace(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isupper(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ctype_isxdigit(AMX* amx, cell* params);
}
