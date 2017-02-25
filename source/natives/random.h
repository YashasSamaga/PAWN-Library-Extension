/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Random number generator
random.h

*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL errno_errno(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL errno_clearerrno(AMX* amx, cell* params);
}
