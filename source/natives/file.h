/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

File Functions
file.h

*************************************************************************************************************/
#ifndef PLE_FILE_H_INCLUDED
#define PLE_FILE_H_INCLUDED

#include "main.h"

#include <cstdio>
#include <string>
/************************************************************************************************************/
#define INVALID_PFILE_ID -1

class PLE_File
{
public:
	FILE *pFile;
	int fileid;

	std::string location;
	std::string mode;

	PLE_File(FILE *pFile, unsigned int fileid, char *_location, char *_mode) : pFile(pFile), fileid(fileid)
	{
		this->location = _location;
		this->mode = mode;
	}
	~PLE_File()
	{
	}
};

namespace PLE::natives
{
	cell AMX_NATIVE_CALL file_fexists(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_GetFileLocation(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_GetFileMode(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL file_remove(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_rename(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_tmpfile(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_tmpname(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fclose(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fflush(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fopen(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fgetc(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fgets(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fputc(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fputs(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_ungetc(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fread(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fwrite(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fgetpos(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fsetpos(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_ftell(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_rewind(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_fseek(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_clearerr(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_feof(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL file_ferror(AMX * amx, cell* params);
}

#endif /* PLE_FILE_H_INCLUDED */