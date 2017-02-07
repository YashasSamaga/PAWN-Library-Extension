/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

File Functions
file.h

*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
#define INVALID_PFILE_ID -1

namespace Natives
{
	cell AMX_NATIVE_CALL file_fexists(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_GetFileLocation(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_GetFileMode(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL file_remove(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_rename(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_tmpfile(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_tmpname(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fclose(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fflush(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fopen(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fgetc(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fgets(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fputc(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fputs(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_ungetc(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fread(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fwrite(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fgetpos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fsetpos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_ftell(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_rewind(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_fseek(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_clearerr(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_feof(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL file_ferror(AMX* amx, cell* params);
}
