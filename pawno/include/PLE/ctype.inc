/*****************************************************************************************************************
Standard Library Extension


string.inc
******************************************************************************************************************/
#if defined _PLE_CTYPES_INC
	#endinput
#else
	#define _PLE_CTYPES_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
native isalnum(c);
native isalpha(c);
native isblank(c);
native iscntrl(c);
native isdigit(c);
native isgraph(c);
native islower(c);
native isprint(c);
native ispunct(c);
native isspace(c);
native isupper(c);
native isxdigit(c);
/*****************************************************************************************************************/
