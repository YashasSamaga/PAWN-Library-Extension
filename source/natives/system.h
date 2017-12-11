/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

access to the host
system.h

*************************************************************************************************************/
#ifndef PLE_SYSTEM_H_INCLUDED
#define PLE_SYSTEM_H_INCLUDED

#include "main.h"
/************************************************************************************************************/
namespace PLE::natives
{
	cell AMX_NATIVE_CALL system_system(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL system_getenv(AMX * amx, cell* params);
}

#endif