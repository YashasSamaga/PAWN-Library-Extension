/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

errno macro
errno.cpp

*************************************************************************************************************/
#include "..\main.h"
#include "errno.h"

#include <cerrno>
/************************************************************************************************************/

//Work in progress to make an implementation independent errno system
namespace Natives
{
	//native errno();
	cell AMX_NATIVE_CALL errno_errno(AMX* amx, cell* params)
	{		
		return errno;
	}	
	//native clearerrno();
	cell AMX_NATIVE_CALL errno_clearerrno(AMX* amx, cell* params)
	{
		errno = 0;
		return true;
	}
}
