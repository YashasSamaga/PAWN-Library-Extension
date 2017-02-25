/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

errno macro
errno.cpp

*************************************************************************************************************/
#include "main.h"
#include "errno.h"

#include <cerrno>
/************************************************************************************************************/
namespace Natives
{
	//native errno();
	cell AMX_NATIVE_CALL errno_errno(AMX* amx, cell* params)
	{		
		error_if(!check_params(0), "[PLE] errno>> errno: expected 0 parameters but found %d parameters.", get_params_count());
		return errno;
	}	
	//native clearerrno();
	cell AMX_NATIVE_CALL errno_clearerrno(AMX* amx, cell* params)
	{
		error_if(!check_params(0), "[PLE] errno>> errno: expected 0 parameters but found %d parameters.", get_params_count());
		errno = 0;
		return true;
	}
}
