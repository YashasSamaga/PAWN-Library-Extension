/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Math library
math.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL math_exp(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_frexp(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_ldexp(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_modf(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_log(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_log10(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_exp2(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_expm1(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_log2(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_log1p(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_cbrt(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_hypot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_fmod(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_remainder(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_copysign(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_fdim(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_fmin(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_fmax(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL math_fma(AMX* amx, cell* params);
}
