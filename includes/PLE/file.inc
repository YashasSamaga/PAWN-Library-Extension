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
/************************************************************************************************************/
#define INVALID_FILE_ID File:-1
/************************************************************************************************************/
#if !defined file
	#define file:: file_
#endif

stock public const file::EOF = 0;
stock public const file::SEEK_SET = 0;
stock public const file::SEEK_CUR = 0;
stock public const file::SEEK_END = 0;

stock public const file::BUFSIZ = 0;
stock public const file::FILENAME_MAX = 0;
stock public const file::FOPEN_MAX = 0;
stock public const file::L_tmpnam = 0;
stock public const file::TMP_MAX = 0;

native file::GetFileLocation(File:file, dest[], size_dest = sizeof(dest));
native file::GetFileMode(File:file, dest[], size_dest = sizeof(dest));
native file::fexists(const fname[]);
native file::fremove(const filename[]);
native file::frename(const oldname[], const newname[]);
native File:file::tmpfile();
native file::tmpname(const dest[], size_dest = sizeof(dest));
native file::fclose(File:fileid);
native file::fflush(File:fileid);
native File:file::fopen(const filename[], const mode[]);
native file::fgetc(File:fileid);
native file::fgets(File:fileid, dest[], size_dest = sizeof(dest));
native file::fputc(File:fileid, chr);
native file::fputs(File:fileid, const source[]);
native file::ungetc(File:fileid, chr);
native file::fread(File:fileid, dest[], dest_size = sizeof(dest));
native file::fwrite(File:fileid, const source[], dest_size = sizeof(source));
native file::fgetpos(File:fileid, &pos);
native file::fsetpos(File:fileid, pos);
native file::ftell(File:fileid);
native file::rewind(File:rewind);
native file::fseek(File:fileid, offset, origin);
native file::clearerr(File:fileid);
native file::feof(File:fileid);
native file::ferror(File:fileid);
