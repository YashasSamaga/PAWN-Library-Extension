/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

complex numbers
complex.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#include <complex>
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL complex_cabs(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_carg(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cnorm(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cconj(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cpolar(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_ccos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_csin(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_ctan(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cacos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_casin(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_catan(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cexp(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_clog(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_clog10(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cpow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_csqrt(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cnegate(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cadd(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_csub(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cmul(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cdiv(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL complex_cequal(AMX* amx, cell* params);
}