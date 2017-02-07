/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Collection of useful numeric algorithms (mostly from C++ standard/template library along with addititional functions)
numeric.h

*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL numeric_iota(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_accumulate(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_adjacent_difference(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_inner_product(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_partial_sum(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_gcd(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL numeric_lcm(AMX *amx, cell params[]);
}
