/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Math library
main.cpp

*************************************************************************************************************/
#include "main.h"
#include "math.h"

#include <cmath>
/************************************************************************************************************/
//math_errhandling implementation pending

namespace Natives
{	
 	//native Float:exp(Float:value);
	cell AMX_NATIVE_CALL math_exp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);	
		num = static_cast<float>(std::expf(num));
		return amx_ftoc(num);
	}
	//native Float:frexp(Float:value, &exp);
	cell AMX_NATIVE_CALL math_frexp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = std::frexpf(num, addr);
		return amx_ftoc(num);
	}
	//native Float:ldexp(Float:value, exp);
	cell AMX_NATIVE_CALL math_ldexp(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::ldexpf(num, params[2]);
		return amx_ftoc(num);
	}
	//native Float:modf(Float:value, &intpart);
	cell AMX_NATIVE_CALL math_modf(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]), intpart;
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = std::modff(num, &intpart);

		*addr = amx_ftoc(intpart);
		return amx_ftoc(num);
	}
	//native Float:log(Float:value);
	cell AMX_NATIVE_CALL math_log(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::logf(num);
		return amx_ftoc(num);
	}
	//native Float:log10(Float:value);
	cell AMX_NATIVE_CALL math_log10(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log10f(num);
		return amx_ftoc(num);
	}
	//native Float:exp2(Float:value);
	cell AMX_NATIVE_CALL math_exp2(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::exp2f(num);
		return amx_ftoc(num);
	}
	//native Float:expm1(Float:value);
	cell AMX_NATIVE_CALL math_expm1(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::expm1f(num);
		return amx_ftoc(num);
	}
	//native Float:log2(Float:value);
	cell AMX_NATIVE_CALL math_log2(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log2f(num);
		return amx_ftoc(num);
	}
	//native Float:log1p(Float:value);
	cell AMX_NATIVE_CALL math_log1p(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log1pf(num);
		return amx_ftoc(num);
	}
	//native Float:cbrt(Float:value);
	cell AMX_NATIVE_CALL math_cbrt(AMX* amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::cbrtf(num);
		return amx_ftoc(num);
	}
	//native Float:hypot(Float:s1, Float:s2);
	cell AMX_NATIVE_CALL math_hypot(AMX* amx, cell* params)
	{
		float num = std::hypotf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmod(Float:value, Float:denom);
	cell AMX_NATIVE_CALL math_fmod(AMX* amx, cell* params)
	{
		float num = std::fmodf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:remainder(Float:value, Float:denom);
	cell AMX_NATIVE_CALL math_remainder(AMX* amx, cell* params)
	{
		float num = remainderf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:copysign(Float:value, Float:sign);
	cell AMX_NATIVE_CALL math_copysign(AMX* amx, cell* params)
	{
		float num = std::copysignf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fdim(Float:x, Float:y);
	cell AMX_NATIVE_CALL math_fdim(AMX* amx, cell* params)
	{
		float num = std::fdimf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmax(Float:x, Float:y);
	cell AMX_NATIVE_CALL math_fmin(AMX* amx, cell* params)
	{
		float num = std::fminf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmin(Float:x, Float:y);
	cell AMX_NATIVE_CALL math_fmax(AMX* amx, cell* params)
	{
		float num = std::fmaxf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fma(Float:mul1, Float:mul2, Float:add);
	cell AMX_NATIVE_CALL math_fma(AMX* amx, cell* params)
	{
		float num = std::fmaf(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
		return amx_ftoc(num);
	}
	//native math_errhandling();
	cell AMX_NATIVE_CALL math_math_errhandling(AMX* amx, cell* params)
	{
		return math_errhandling;
	}	
}	
	
	
	

	
	
