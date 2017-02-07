/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

complex numbers
complex.cpp

*************************************************************************************************************/
#include "main.h"
#include "complex.h"

#include <complex>
/************************************************************************************************************/
namespace Natives
{
	//native Float:cabs(num[complext_t]);
	cell AMX_NATIVE_CALL complex_cabs(AMX* amx, cell* params)
	{	
		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
		float result = sqrt(amx_ctof(complex_addr[0])*amx_ctof(complex_addr[0]) + amx_ctof(complex_addr[1])*amx_ctof(complex_addr[1]));
		return amx_ftoc(result);
	}	
	//native Float:carg(num[complext_t]);
	cell AMX_NATIVE_CALL complex_carg(AMX* amx, cell* params)
	{
		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
		float arg = amx_ctof(complex_addr[1]) / amx_ctof(complex_addr[0]);
		return amx_ftoc(arg);
	}
	//native Float:cnorm(num[complext_t]);
	cell AMX_NATIVE_CALL complex_cnorm(AMX* amx, cell* params)
	{
		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);
		float result = (amx_ctof(complex_addr[0])*amx_ctof(complex_addr[0]) + amx_ctof(complex_addr[1])*amx_ctof(complex_addr[1]));
		return amx_ftoc(result);
	}
	//native conj(num[complex_t]);
	cell AMX_NATIVE_CALL complex_cconj(AMX* amx, cell* params)
	{
		cell *complex_addr = NULL;
		amx_GetAddr(amx, params[1], &complex_addr);

		float neg_i = -amx_ctof(complex_addr[1]);
		complex_addr[1] = amx_ftoc(neg_i);
		return true;
	}
	//native polar(Float:modulus, Float:arg, result[complex_t]);
	cell AMX_NATIVE_CALL complex_cpolar(AMX* amx, cell* params)
	{
		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(params[1])*cos(amx_ctof(params[2]));
		float img = amx_ctof(params[1])*sin(amx_ctof(params[2]));
		complex_addr_dest[0] = amx_ftoc(real);
		complex_addr_dest[1] = amx_ftoc(img);
		return true;
	}

	//native ccos(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_ccos(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::cos(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native csin(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_csin(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::sin(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native ctan(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_ctan(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::tan(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native cacos(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cacos(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::acos(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native casin(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_casin(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::asin(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native catan(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_catan(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::atan(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//cosh, sinh, tanh, acosh, asinh, atanh not implemented

	//native cexp(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cexp(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::exp(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native clog(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_clog(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::log(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native clog10(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_clog10(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::log10(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native cpow(num[complex_t], pow[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cpow(AMX* amx, cell* params)
	{
		cell *complex_addr_num = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num);

		cell *complex_addr_power = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_power);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_num[0]), amx_ctof(complex_addr_num[1]));
		std::complex<float> power(amx_ctof(complex_addr_power[0]), amx_ctof(complex_addr_power[1]));
		std::complex<float> result = std::pow(num, power);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}
	//native csqrt(num[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_csqrt(AMX* amx, cell* params)
	{
		cell *complex_addr_src = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_src);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_dest);

		std::complex<float> num(amx_ctof(complex_addr_src[0]), amx_ctof(complex_addr_src[1]));
		std::complex<float> result = std::sqrt(num);

		float val = result.real();
		complex_addr_dest[0] = amx_ftoc(val);
		val = result.imag();
		complex_addr_dest[1] = amx_ftoc(val);
		return true;
	}

	//native cnegate(num[complex_t]);
	cell AMX_NATIVE_CALL complex_cnegate(AMX* amx, cell* params)
	{
		cell *complex_addr_num = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num);

		float real = -amx_ctof(complex_addr_num[0]);
		float imag = -amx_ctof(complex_addr_num[1]);

		complex_addr_num[0] = amx_ftoc(real);
		complex_addr_num[1] = amx_ftoc(imag);
		return true;
	}
	//native cadd(num1[complex_t], num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cadd(AMX* amx, cell* params)
	{
		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0]) + amx_ctof(complex_addr_num2[0]);
		float imag = amx_ctof(complex_addr_num1[1]) + amx_ctof(complex_addr_num2[1]);

		complex_addr_dest[0] = amx_ftoc(real);
		complex_addr_dest[1] = amx_ftoc(imag);
		return true;
	}
	//native csub(num1[complex_t], num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_csub(AMX* amx, cell* params)
	{
		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0]) - amx_ctof(complex_addr_num2[0]);
		float imag = amx_ctof(complex_addr_num1[1]) - amx_ctof(complex_addr_num2[1]);

		complex_addr_dest[0] = amx_ftoc(real);
		complex_addr_dest[1] = amx_ftoc(imag);
		return true;
	}
	//native cmul(num1[complex_t], num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cmul(AMX* amx, cell* params)
	{
		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		cell *complex_addr_dest = NULL;
		amx_GetAddr(amx, params[3], &complex_addr_dest);

		float real = amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[0]) - amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[1]);
		float imag = amx_ctof(complex_addr_num1[0])*amx_ctof(complex_addr_num2[1]) - amx_ctof(complex_addr_num1[1])*amx_ctof(complex_addr_num2[0]);

		complex_addr_dest[0] = amx_ftoc(real);
		complex_addr_dest[1] = amx_ftoc(imag);
		return true;
	}
	//native cdiv(num1[complex_t], num2[complex_t], result[complex_t]);
	cell AMX_NATIVE_CALL complex_cdiv(AMX* amx, cell* params)
	{
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
		
		complex_addr_dest[0] = amx_ftoc(real);
		complex_addr_dest[1] = amx_ftoc(imag);
		return true;
	}	
	
	//native bool:cequal(num1[complex_t], num2[complex_t]);
	cell AMX_NATIVE_CALL complex_cequal(AMX* amx, cell* params)
	{
		cell *complex_addr_num1 = NULL;
		amx_GetAddr(amx, params[1], &complex_addr_num1);

		cell *complex_addr_num2 = NULL;
		amx_GetAddr(amx, params[2], &complex_addr_num2);

		return ((complex_addr_num1[0] == complex_addr_num2[0]) && (complex_addr_num1[1] == complex_addr_num1[1]));
	}
}
