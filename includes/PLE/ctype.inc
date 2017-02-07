/*****************************************************************************************************************
PAWN Library Extension

Character types
ctype.inc
******************************************************************************************************************/
#if defined _PLE_CTYPE_INC
	#endinput
#else
	#define _PLE_CTYPE_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#if !defined ctype
	#define ctype:: ctype_
#endif

native ctype::isalnum(c);
native ctype::isalpha(c);
native ctype::isblank(c);
native ctype::iscntrl(c);
native ctype::isdigit(c);
native ctype::isgraph(c);
native ctype::islower(c);
native ctype::isprint(c);
native ctype::ispunct(c);
native ctype::isspace(c);
native ctype::isupper(c);
native ctype::isxdigit(c);
