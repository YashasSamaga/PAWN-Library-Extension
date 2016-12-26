/************************************************************************************************************
PAWN Library Extension

File functions
file.inc
*************************************************************************************************************/
#if defined _PLE_FILE_INC
	#endinput
#else
	#define _PLE_FILE_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif
/*****************************************************************************************************************/
#define EOF -1 //implementation independent
#define INVALID_PFILE_ID File:-1

//implementation dependent - automatically set
stock public const SEEK_SET = 0;
stock public const SEEK_CUR = 0;
stock public const SEEK_END = 0;

stock public const BUFSIZ = 0;
stock public const FILENAME_MAX = 0;
stock public const FOPEN_MAX = 0;
stock public const L_tmpnam = 0;
stock public const TMP_MAX = 0;

native file_fexists(const fname[]);
native file_GetFileLocation(File:file, dest[], size_dest = sizeof(dest));
native file_GetFileMode(File:file, dest[], size_dest = sizeof(dest));
native file_remove(const filename[]);
native file_rename(const oldname[], const newname[]);
native File:file_tmpfile();
native file_tmpname(const dest[], size_dest = sizeof(dest));
native file_fclose(File:fileid);
native file_fflush(File:fileid);
native File:file_fopen(const filename[], const mode[]);
native file_fgetc(File:fileid);
native file_fgets(File:fileid, dest[], size_dest = sizeof(dest));
native file_fputc(File:fileid, chr);
native file_fputs(File:fileid, const source[]);
native file_ungetc(File:fileid, chr);
native file_fread(File:fileid, dest[], dest_size = sizeof(dest));
native file_fwrite(File:fileid, const source[], dest_size = sizeof(source));
native file_fgetpos(File:fileid, &pos);
native file_fsetpos(File:fileid, pos);
native file_ftell(File:fileid);
native file_rewind(File:rewind);
native file_fseek(File:fileid, offset, origin);
native file_clearerr(File:fileid);
native file_feof(File:fileid);
native file_ferror(File:fileid);

#if !defined _file_included
native remove(const filename[]) = file_remove;
native rename(const oldname[], const newname[]) = file_rename;
native File:tmpfile() = file_tmpfile;
native tmpname(const dest[], size_dest = sizeof(dest)) = file_tmpname;
native fclose(File:fileid) = file_fclose;
native fflush(File:fileid) = file_fflush;
native File:fopen(const filename[], const mode[]) = file_fopen;
native fgetc(File:fileid) = file_fgetc;
native fgets(File:fileid, dest[], size_dest = sizeof(dest)) = file_fgets;
native fputc(File:fileid, chr) = file_fputc;
native fputs(File:fileid, const source[]) = file_fputs;
native ungetc(File:fileid, chr) = file_ungetc;
native fread(File:fileid, dest[], dest_size = sizeof(dest)) = file_fread;
native fwrite(File:fileid, const source[], dest_size = sizeof(source)) = file_fwrite;
native fgetpos(File:fileid, &pos) = file_fgetpos;
native fsetpos(File:fileid, pos) = file_fsetpos;
native ftell(File:fileid) = file_ftell;
native rewind(File:rewind) = file_rewind;
native fseek(File:fileid, offset, origin) = file_fseek;
native clearerr(File:fileid) = file_clearerr;
native feof(File:fileid) = file_feof;
native ferror(File:fileid) = file_ferror;
#endif
