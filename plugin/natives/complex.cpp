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
#include "complex.h"
#include <complex>

namespace PLE::complex::natives
{
	//native Float:cabs(const num[complex_t]);
	cell AMX_NATIVE_CALL cabs(AMX* amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] complex>> cabs: expected 1 parameters but found %d parameters.", get_params_count());

		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
		float result = std::abs(std::complex<float>(amx_ctof(complex_addr[complex_offsets::real]), amx_ctof(complex_addr[complex_offsets::real])));
		return amx_ftoc(result);
	}
	//native Float:carg(const num[complex_t]);
	cell AMX_NATIVE_CALL carg(AMX* amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] complex>> carg: expected 1 parameters but found %d parameters.", get_params_count());

		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
        float result = std::arg(std::complex<float>(amx_ctof(complex_addr[complex_offsets::real]), amx_ctof(complex_addr[complex_offsets::imag])));
		return amx_ftoc(result);
	}
	//native Float:cnorm(const num[complex_t]);
	cell AMX_NATIVE_CALL cnorm(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] complex>> cnorm: expected 1 parameters but found %d parameters.", get_params_count());

		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
		float result = std::norm(std::complex<float>(amx_ctof(complex_addr[complex_offsets::real]), amx_ctof(complex_addr[complex_offsets::imag])));
		return amx_ftoc(result);
	}
	//native noret:conj(num[complex_t]);
	cell AMX_NATIVE_CALL cconj(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] complex>> cconj: expected 1 parameters but found %d parameters.", get_params_count());

		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);

		float neg_i = -amx_ctof(complex_addr[complex_offsets::imag]);
		complex_addr[complex_offsets::imag] = amx_ftoc(neg_i);
		return true;
	}
	//native noret:polar(Float:modulus, Float:arg, result[complex_t]);
	cell AMX_NATIVE_CALL cpolar(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> cpolar: expected 3 parameters but found %d parameters.", get_params_count());

		error_if(amx_ctof(params[1]) < 0, "[PLE] complex>> cpolar: 'modulus' parameter below zero");
		error_if(std::isnan(amx_ctof(params[1])), "[PLE] complex>> cpolar: 'modulus' parameter is NaN");
		error_if(std::isinf(amx_ctof(params[2])), "[PLE] complex>> cpolar: 'arg' parameter tends to infinity.");

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

        std::complex<float> result = std::polar(amx_ctof(params[complex_offsets::real]), amx_ctof(params[complex_offsets::imag]));
        float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}

	//native noret:ccos(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL ccos(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> ccos: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::cos(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:csin(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL csin(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> csin: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::sin(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:ctan(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL ctan(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> ctan: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::tan(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:cacos(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cacos(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> cacos: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::acos(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:casin(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL casin(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> casin: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::asin(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:catan(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL catan(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> catan: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::atan(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}	

	//native noret:ccosh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL ccosh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> ccosh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::cosh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:csinh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL csinh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> csinh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::sinh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:ctanh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL ctanh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> ctanh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::tanh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:cacosh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cacosh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> cacosh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::acosh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:casinh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL casinh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> casinh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::asinh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:catanh(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL catanh(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> catanh: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::atanh(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}

	//native noret:cexp(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cexp(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> cexp: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::exp(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:clog(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL clog(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> clog: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::log(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:clog10(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL clog10(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> clog10: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::log10(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:cpow(const num[complex_t], power[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cpow(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> cpow: expected 3 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num);

		cell *complex_addr_power = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_power);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		const std::complex<float> num(amx_ctof(complex_addr_num[0]), amx_ctof(complex_addr_num[1])),
		                          power(amx_ctof(complex_addr_power[0]), amx_ctof(complex_addr_power[1]));

		std::complex<float> result = std::pow(num, power);
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:csqrt(const num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL csqrt(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> csqrt: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> result = std::sqrt(std::complex<float>(amx_ctof(complex_addr_src[complex_offsets::real]), amx_ctof(complex_addr_src[complex_offsets::imag])));
		float real = result.real(), imag = result.imag();
		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}

	//native cnegate(num[complex_t]);
	cell AMX_NATIVE_CALL cnegate(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] complex>> cnegate: expected 1 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num);

		float real = -amx_ctof(complex_addr_num[0]);
		float imag = -amx_ctof(complex_addr_num[1]);

		complex_addr_num[0] = amx_ftoc(real);
		complex_addr_num[1] = amx_ftoc(imag);
		return true;
	}
	//native noret:cadd(const num1[complex_t], const num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cadd(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> cadd: expected 3 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0]) + amx_ctof(complex_addr_num2[0]);
		float imag = amx_ctof(complex_addr_num1[1]) + amx_ctof(complex_addr_num2[1]);

		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:csub(const num1[complex_t], const num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL csub(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> csub: expected 3 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0]) - amx_ctof(complex_addr_num2[0]);
		float imag = amx_ctof(complex_addr_num1[1]) - amx_ctof(complex_addr_num2[1]);

		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:cmul(const num1[complex_t], const num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cmul(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> cmul: expected 3 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[0]) - amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[1]);
		float imag = amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[1]) - amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[0]);

		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}
	//native noret:cdiv(const num1[complex_t], const num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL cdiv(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] complex>> cdiv: expected 3 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[0]) + amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[1]);
		float imag = amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[0]) - amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[1]);

		float magsq = (amx_ctof(complex_addr_num2[0])*amx_ctof(complex_addr_num2[0]) + amx_ctof(complex_addr_num2[1])*amx_ctof(complex_addr_num2[1]));

		real /= magsq;
		imag /= magsq;

		complex_addr_dest[complex_offsets::real] = amx_ftoc(real);
		complex_addr_dest[complex_offsets::imag] = amx_ftoc(imag);
		return true;
	}

	//native bool:cequal(const num1[complex_t], const num2[complex_t]);
	cell AMX_NATIVE_CALL cequal(AMX * amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] complex>> cequal: expected 2 parameters but found %d parameters.", get_params_count());

		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		return ((amx_ctof(complex_addr_num1[0]) == amx_ctof(complex_addr_num2[0])) 
			 && (amx_ctof(complex_addr_num1[1]) == amx_ctof(complex_addr_num2[1])));
	}
}