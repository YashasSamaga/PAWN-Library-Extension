/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Character types
ctype.cpp

*************************************************************************************************************/
#include "..\main.h"
#include "ctype.h"

#include <ctype.h>
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL ctype_isalnum(AMX* amx, cell* params)
	{
		return isalnum(params[1]);
	}
	cell AMX_NATIVE_CALL ctype_isalpha(AMX* amx, cell* params)
	{
		return isalpha(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isblank(AMX* amx, cell* params)
	{
		return isblank(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_iscntrl(AMX* amx, cell* params)
	{
		return iscntrl(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isdigit(AMX* amx, cell* params)
	{
		return isdigit(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isgraph(AMX* amx, cell* params)
	{
		return isgraph(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_islower(AMX* amx, cell* params)
	{
		return islower(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isprint(AMX* amx, cell* params)
	{
		return isprint(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_ispunct(AMX* amx, cell* params)
	{
		return ispunct(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isspace(AMX* amx, cell* params)
	{
		return isspace(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isupper(AMX* amx, cell* params)
	{
		return isupper(params[2]);
	}
	cell AMX_NATIVE_CALL ctype_isxdigit(AMX* amx, cell* params)
	{
		return isxdigit(params[2]);
	}

	//tolower & toupper implemented in PAWN 'core' library
}
