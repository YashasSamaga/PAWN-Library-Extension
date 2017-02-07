/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

File Functions
Files can be shared across different scripts.

file.cpp

*************************************************************************************************************/
#include "main.h"
#include "file.h"

#include <cstring>
#include <cstdio>
#include <vector>
#include <memory>
/************************************************************************************************************/
class PLE_File
{
public:
	FILE * pFile;	
	int fileid;

	char *location;
	char *mode;
	
	PLE_File(FILE * pFile, unsigned int fileid, char *_location, char *_mode) : pFile(pFile), fileid(fileid)
	{
		size_t len = strlen(_location) + 1;
		location = new char[len];
		strcpy(location, _location);

		len = strlen(_mode) + 1;
		mode = new char[len];
		strcpy(mode, _mode);
	}
	~PLE_File()
	{
		delete[] location;
		delete[] mode;
	}	
};

std::vector <std::unique_ptr<PLE_File>> FileList;

namespace Natives
{
	//native file_fexists(const fname[]);
	cell AMX_NATIVE_CALL file_fexists(AMX* amx, cell* params)
	{
		char fname[FILENAME_MAX];
		cell *addr_fname = NULL;
		amx_GetAddr(amx, params[1], &addr_fname);
		amx_GetString(fname, addr_fname, 0, sizeof(fname));

		if (FILE *file = fopen(fname, "r")) 
		{
			fclose(file);
			return true;
		}
		else return false;
	}
	//native file_GetFileLocation(File:file, dest[], size_dest = sizeof(dest));
	cell AMX_NATIVE_CALL file_GetFileLocation(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if (!(bool)FileList[fileid]) return false;

		cell* addr = NULL;
		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, FileList[fileid]->location, 0, 0, params[3]);
		return true;
	}
	//native file_GetFileMode(File:file, dest[], size_dest = sizeof(dest));
	cell AMX_NATIVE_CALL file_GetFileMode(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if (!(bool)FileList[fileid]) return false;

		cell* addr = NULL;
		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, FileList[fileid]->mode, 0, 0, params[3]);
		return true;
	}
	//native file_remove(const filename[]);
	cell AMX_NATIVE_CALL file_remove(AMX* amx, cell* params)
	{
		char fname[FILENAME_MAX];
		cell *addr_fname = NULL;
		amx_GetAddr(amx, params[1], &addr_fname);		
		amx_GetString(fname, addr_fname, 0, sizeof(fname));
		return remove(fname);
	}
	//native file_rename(const oldname[], const newname[]);
	cell AMX_NATIVE_CALL file_rename(AMX* amx, cell* params)
	{
		char fname_old[FILENAME_MAX], fname_new[FILENAME_MAX];
		cell *addr_fname = NULL;		
		amx_GetAddr(amx, params[1], &addr_fname);		
		amx_GetString(fname_old, addr_fname, 0, sizeof(fname_old));
		amx_GetAddr(amx, params[2], &addr_fname);
		amx_GetString(fname_new, addr_fname, 0, sizeof(fname_new));
		return rename(fname_old, fname_new);
	}
	//native File:file_tmpfile();
	cell AMX_NATIVE_CALL file_tmpfile(AMX* amx, cell* params)
	{ 
		FILE * pFile = tmpfile();
		if (pFile == NULL) return INVALID_PFILE_ID;

		int fileid;	
		auto fileitr = std::find(FileList.begin(), FileList.end(), nullptr);
		if (fileitr == FileList.end())
		{
			fileid = static_cast<int>(static_cast<int>(FileList.size()));
			FileList.push_back(std::unique_ptr<PLE_File>(new PLE_File(pFile, fileid, "", "")));
		}
		else
		{
			fileid = static_cast<int>(std::distance(FileList.begin(), fileitr));
			*fileitr = std::unique_ptr<PLE_File>(new PLE_File(pFile, fileid, "", ""));
		}		
		return fileid;
	}
	//native file_tmpname(const dest[], size_dest = sizeof(dest));
	cell AMX_NATIVE_CALL file_tmpname(AMX* amx, cell* params)
	{
		char buffer[L_tmpnam];	
		tmpnam(buffer);

		cell* addr = NULL;
		amx_GetAddr(amx, params[1], &addr);
		amx_SetString(addr, buffer, 0, 0, params[2]);
		return true;
	}
	//native file_fclose(File:fileid);
	cell AMX_NATIVE_CALL file_fclose(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		if (!fclose(FileList[fileid]->pFile))
		{
			FileList[fileid].reset();
			return 0;
		}
		return EOF;
	}
	//native file_fflush(File:fileid);
	cell AMX_NATIVE_CALL file_fflush(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		if (fflush(FileList[fileid]->pFile) == 0) return 0;
		return EOF;
	}
	//native File:file_fopen(const filename[], const mode[]);
	cell AMX_NATIVE_CALL file_fopen(AMX* amx, cell* params)
	{		
		char fname[FILENAME_MAX], fmode[32];
		cell *addr = NULL;

		amx_GetAddr(amx, params[1], &addr);		
		amx_GetString(fname, addr, 0, sizeof(fmode));

		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(fmode, addr, 0, sizeof(fmode));

		FILE * pFile = fopen(fname, fmode);
		if (pFile == NULL) return INVALID_PFILE_ID;		

		int fileid;
		auto fileitr = std::find(FileList.begin(), FileList.end(), nullptr);
		if (fileitr == FileList.end())
		{
			fileid = static_cast<int>(static_cast<int>(FileList.size()));
			FileList.push_back(std::unique_ptr<PLE_File>(new PLE_File(pFile, fileid, fname, fmode)));
		}
		else
		{
			fileid = static_cast<int>(std::distance(FileList.begin(), fileitr));
			*fileitr = std::unique_ptr<PLE_File>(new PLE_File(pFile, fileid, fname, fmode));
		}
		return fileid;		
	}
	//native file_fgetc(File:fileid);
	cell AMX_NATIVE_CALL file_fgetc(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;

		return fgetc(FileList[fileid]->pFile);
	}
	//native file_fgets(File:fileid, dest[], size_dest = sizeof(dest));
	cell AMX_NATIVE_CALL file_fgets(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;		

		cell* dest_addr = NULL;
		amx_GetAddr(amx, params[2], &dest_addr);

		char *buffer = new char[params[3]];
		fgets(buffer, params[3], FileList[fileid]->pFile);

		amx_SetString(dest_addr, buffer, 0, 0, params[3]);

		delete[] buffer;
		return true;
	}
	//native file_fputc(File:fileid, chr);
	cell AMX_NATIVE_CALL file_fputc(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		if (fputc(params[2], FileList[fileid]->pFile) == EOF) return EOF;
		return params[2];
	}
	//native file_fputs(File:fileid, const source[]);
	cell AMX_NATIVE_CALL file_fputs(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		int len;
		cell *addr_fname = NULL;
		amx_GetAddr(amx, params[2], &addr_fname);
		amx_StrLen(addr_fname, &len);
		len++;
		char* buffer = new char[len];
		amx_GetString(buffer, addr_fname, 0, len);
		delete[] buffer;
	
		return fputs(buffer, FileList[fileid]->pFile);
	}
	//native file_ungetc(File:fileid, chr);
	cell AMX_NATIVE_CALL file_ungetc(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		if (ungetc(params[2], FileList[fileid]->pFile) == EOF) return EOF;
		return params[2];
	}
	//native file_fread(File:fileid, dest[], dest_size = sizeof(dest));
	cell AMX_NATIVE_CALL file_fread(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;

		cell* addr_buf = NULL;
		amx_GetAddr(amx, params[2], &addr_buf);

		return fread(addr_buf, 4, params[3], FileList[fileid]->pFile);
	}
	//native file_fwrite(File:fileid, const source[], dest_size = sizeof(source));
	cell AMX_NATIVE_CALL file_fwrite(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;

		cell* addr_buf = NULL;
		amx_GetAddr(amx, params[2], &addr_buf);

		return fwrite(addr_buf, 4, params[3], FileList[fileid]->pFile);
	}
	//native file_fgetpos(File:fileid, &pos);
	cell AMX_NATIVE_CALL file_fgetpos(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		cell* pos_addr;
		amx_GetAddr(amx, params[2], &pos_addr);

		fpos_t pos;
		cell retval = fgetpos(FileList[fileid]->pFile, &pos);

		*pos_addr = static_cast<cell>(pos);
		return retval;
	}
	//native file_fsetpos(File:fileid, pos);
	cell AMX_NATIVE_CALL file_fsetpos(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;

		fpos_t pos = static_cast<long long>(params[2]);
		cell retval = fsetpos(FileList[fileid]->pFile, &pos);
		return retval;
	}
	//native file_ftell(File:fileid);
	cell AMX_NATIVE_CALL file_ftell(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return -1;
		if(!(bool)FileList[fileid]) return -1;

		return ftell(FileList[fileid]->pFile);		
	}
	//native file_rewind(File:rewind);
	cell AMX_NATIVE_CALL file_rewind(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;

		rewind(FileList[fileid]->pFile);
		return true;
	}
	//native file_fseek(File:fileid, offset, origin);
	cell AMX_NATIVE_CALL file_fseek(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return EOF;
		if(!(bool)FileList[fileid]) return EOF;
 
		cell retval = fseek(FileList[fileid]->pFile, static_cast<long>(params[2]), static_cast<long>(params[3]));
		return retval;
	}
	////native file_clearerr(File:fileid);
	cell AMX_NATIVE_CALL file_clearerr(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;

		clearerr(FileList[fileid]->pFile);
		return true;
	}
	////native file_feof(File:fileid);
	cell AMX_NATIVE_CALL file_feof(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;
		
		return feof(FileList[fileid]->pFile);;
	}	
	////native file_ferror(File:fileid);
	cell AMX_NATIVE_CALL file_ferror(AMX* amx, cell* params)
	{
		const int fileid = params[1];
		if (fileid < 0 || fileid >= static_cast<int>(FileList.size())) return false;
		if(!(bool)FileList[fileid]) return false;
		
		return ferror(FileList[fileid]->pFile);
	}
}
