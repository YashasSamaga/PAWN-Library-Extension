/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Math library
main.cpp

*************************************************************************************************************/
#include "..\main.h"
#include "math.h"

#include <math.h>
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL math_exp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);	
		num = static_cast<float>(expf(num));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_frexp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = frexpf(num, addr);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_ldexp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = ldexpf(num, params[2]);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_modf(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]), intpart;
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = modff(num, &intpart);

		*addr = amx_ftoc(intpart);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_log(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = logf(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_log10(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = log10f(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_exp2(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = exp2f(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_expm1(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = expm1f(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_log2(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = log2f(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_log1p(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = log1pf(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_cbrt(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = cbrtf(num);
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_hypot(AMX* amx, cell* params)
	{
		float num = hypotf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_fmod(AMX* amx, cell* params)
	{
		float num = fmodf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_remainder(AMX* amx, cell* params)
	{
		float num = remainderf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_copysign(AMX* amx, cell* params)
	{
		float num = copysignf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_fdim(AMX* amx, cell* params)
	{
		float num = fdimf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_fmin(AMX* amx, cell* params)
	{
		float num = fminf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_fmax(AMX* amx, cell* params)
	{
		float num = fmaxf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	cell AMX_NATIVE_CALL math_fma(AMX* amx, cell* params)
	{
		float num = fmaf(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
		return amx_ftoc(num);
	}
}
