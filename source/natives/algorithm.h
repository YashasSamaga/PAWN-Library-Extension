/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Collection of useful algorithms (mostly from C++ standard/template library along with addititional functions)
algorithm.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL algo_sbsearch(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL algo_fbsearch(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL algo_ibsearch(AMX* amx, cell* params);
}
