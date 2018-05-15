/*
** PAWN Library Extension (PLE)
**
** This file is part of PAWN Library Extension.
**
**   This library is free software: you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation, either version 3 of the License, or
**   (at your option) any later version.
**
**   This library is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
** Copyright (C) 2016-2018  Yashas Samaga
*/

#include "main.h"
#include "math.h"

#include <cmath>

namespace PLE::math::natives
{	
 	//native Float:exp(Float:value);
	cell AMX_NATIVE_CALL exp(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);	
		num = static_cast<float>(std::expf(num));
		return amx_ftoc(num);
	}
	//native Float:frexp(Float:value, &exp);
	cell AMX_NATIVE_CALL frexp(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = std::frexpf(num, addr);
		return amx_ftoc(num);
	}
	//native Float:ldexp(Float:value, exp);
	cell AMX_NATIVE_CALL ldexp(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::ldexpf(num, params[2]);
		return amx_ftoc(num);
	}
	//native Float:modf(Float:value, &intpart);
	cell AMX_NATIVE_CALL modf(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]), intpart;
		cell* addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		num = std::modff(num, &intpart);

		*addr = amx_ftoc(intpart);
		return amx_ftoc(num);
	}
	//native Float:log(Float:value);
	cell AMX_NATIVE_CALL log(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::logf(num);
		return amx_ftoc(num);
	}
	//native Float:log10(Float:value);
	cell AMX_NATIVE_CALL log10(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log10f(num);
		return amx_ftoc(num);
	}
	//native Float:exp2(Float:value);
	cell AMX_NATIVE_CALL exp2(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::exp2f(num);
		return amx_ftoc(num);
	}
	//native Float:expm1(Float:value);
	cell AMX_NATIVE_CALL expm1(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::expm1f(num);
		return amx_ftoc(num);
	}
	//native Float:log2(Float:value);
	cell AMX_NATIVE_CALL log2(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log2f(num);
		return amx_ftoc(num);
	}
	//native Float:log1p(Float:value);
	cell AMX_NATIVE_CALL log1p(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::log1pf(num);
		return amx_ftoc(num);
	}
	//native Float:cbrt(Float:value);
	cell AMX_NATIVE_CALL cbrt(AMX * amx, cell* params)
	{
		float num = amx_ctof(params[1]);
		num = std::cbrtf(num);
		return amx_ftoc(num);
	}
	//native Float:hypot(Float:s1, Float:s2);
	cell AMX_NATIVE_CALL hypot(AMX * amx, cell* params)
	{
		float num = std::hypotf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmod(Float:value, Float:denom);
	cell AMX_NATIVE_CALL fmod(AMX * amx, cell* params)
	{
		float num = std::fmodf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:remainder(Float:value, Float:denom);
	cell AMX_NATIVE_CALL remainder(AMX * amx, cell* params)
	{
		float num = remainderf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:copysign(Float:value, Float:sign);
	cell AMX_NATIVE_CALL copysign(AMX * amx, cell* params)
	{
		float num = std::copysignf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fdim(Float:x, Float:y);
	cell AMX_NATIVE_CALL fdim(AMX * amx, cell* params)
	{
		float num = std::fdimf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmax(Float:x, Float:y);
	cell AMX_NATIVE_CALL fmin(AMX * amx, cell* params)
	{
		float num = std::fminf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fmin(Float:x, Float:y);
	cell AMX_NATIVE_CALL fmax(AMX * amx, cell* params)
	{
		float num = std::fmaxf(amx_ctof(params[1]), amx_ctof(params[2]));
		return amx_ftoc(num);
	}
	//native Float:fma(Float:mul1, Float:mul2, Float:add);
	cell AMX_NATIVE_CALL fma(AMX * amx, cell* params)
	{
		float num = std::fmaf(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
		return amx_ftoc(num);
	}
	//native Float:fclamp(Float:value, Float:min, Float:max);
	cell AMX_NATIVE_CALL fclamp(AMX * amx, cell* params)
	{
		float value = amx_ctof(params[1]),
			  min = amx_ctof(params[2]),
			  max = amx_ctof(params[3]);
		if (value > max) return amx_ftoc(max);
		if (value < min) return amx_ftoc(min);
		return amx_ftoc(value);
	}
	//native math_errhandling();
	cell AMX_NATIVE_CALL ov_math_errhandling(AMX * amx, cell* params)
	{
		return math_errhandling;
	}	
}	
	
	
	

	
	
