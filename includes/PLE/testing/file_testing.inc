/************************************************************************************************************
PAWN Library Extension

File functions testing
file.inc
*************************************************************************************************************/
#if defined _PLE_FILET_INC
	#endinput
#else
	#define _PLE_FILET_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/file>
/*****************************************************************************************************************/
File()
{
	//TO:DO
	new result[256];
	file::tmpname(result);

	new File:pfile = file::fopen("new2.txt", "w");
	file::fclose(pfile);

	file_rename("new2.txt", "new3.txt");

	pfile = file::tmpfile();
	file::fclose(pfile);

	pfile =	file::fopen("new4.txt", "w");
	file::fclose(pfile);
}
