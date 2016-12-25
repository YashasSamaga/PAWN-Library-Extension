/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

String library
string.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL string_memmove(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strcpy(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strncpy(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL string_strncat(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL string_strncmp(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL string_memchr(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strchr(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strrchr(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strcspn(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strpbrk(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strspn(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strtok(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_memset(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL string_strreplace(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strtrim(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strtolower(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL string_strtoupper(AMX* amx, cell* params);
}