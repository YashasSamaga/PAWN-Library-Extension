/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

bitset
bitset.h

*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL bitset_count(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_size(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_test(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_any(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_none(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_all(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_set(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_reset(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_flip(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_set_all(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_reset_all(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_flip_all(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_tostring(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_and(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_or(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_xor(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_equal(AMX *amx, cell params[]);

	cell AMX_NATIVE_CALL bitset_foreach_set(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_foreach_notset(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_find_set(AMX *amx, cell params[]);
	cell AMX_NATIVE_CALL bitset_find_notset(AMX *amx, cell params[]);
}