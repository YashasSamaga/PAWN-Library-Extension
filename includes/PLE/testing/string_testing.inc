/*****************************************************************************************************************
PAWN Library Extension

String library
string.inc
******************************************************************************************************************/
#if defined _PLE_STRING_INC
	#endinput
#else
	#define _PLE_STRING_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#if !defined NULL
	#define NULL 0
#endif

//memcpy already implemented
native memmove(destination[], const source[], numbytes);
native strcpy(destination[], const source[], size_dest = sizeof(destination));
native strncpy(destination[], const source[], num, size_dest = sizeof(destination),  size_src = sizeof(source));
//strcat - already implemented by PAWN Standard Library
native strncat(destination[], const source[], num, size_dest = sizeof(destination));
native memcmp(const src1[], const src2[], num) = strncmp; //mem natives use cells instead of bytes, therefore, memcmp is as good as strncmp; unit of memory = cell
//strcmp already implemented
//strcoll not implemented
native strncmp(const str1[], const str2[], num);
//strxfrm not implemented
native memchr(const source[], value, num);
native strchr(const source[], value, idx = 0);
native strcspn(const str1[], const str2[]); //returns the index - same as C++ implementation
native strpbrk(const str1[], const str2[]); //returns the character instead of a pointer (C++ implementation returns a pointer)
native strrchr(const source[], value, size_src = sizeof(source));
native strspn(const str1[], const str2[]);
native strstr(const source[], const search[], bool:ignorecase=false, pos=0) = strfind;
native strtok(const source[], destination[], &idx, delimiter[], size_dest = sizeof(destination)); //better than C++ implementation
native memset(destination[], value, num);
native strerror(errorid, errormsg[], size_errormsg = sizeof(errormsg));
//strlen - already implemented by PAWN Standard Library

//Bonus Natives
native bool:strreplace(source[], const search[], const replace[], size_src = sizeof(source)); //returns true if something was replaced
native strtrim(source[]); //returns the length of the new string
native strtolower(source[]); //returns length of the string
native strtoupper(source[]); //returns length of the string
/*****************************************************************************************************************/
