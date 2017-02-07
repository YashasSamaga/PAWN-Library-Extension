/*****************************************************************************************************************
PAWN Library Extension

complex numbers
complex.inc
******************************************************************************************************************/
#if defined _PLE_COMPLEX_INC
	#endinput
#else
	#define _PLE_COMPLEX_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#define complex:: c

enum complex_t
{
	real,
	imag
}

native Float:abs(num[complex_t]);
native Float:arg(num[complex_t]);
native Float:norm(num[complex_t]);
native noret:conj(num[complex_t]);
native noret:polar(Float:modulus, Float:arg, result[complex_t]);

native noret:ccos(num[complex_t], result[complex_t]);
native noret:csin(num[complex_t], result[complex_t]);
native noret:ctan(num[complex_t], result[complex_t]);
//ccosh not implemented
//csinh not implemented
//ctahh not implemented

native noret:cacos(num[complex_t], result[complex_t]);
native noret:casin(num[complex_t], result[complex_t]);
native noret:catan(num[complex_t], result[complex_t]);
//cacosh not implemented
//casinh not implemented
//catanh not implemented

native noret:cexp(num[complex_t], result[complex_t]);
native noret:clog(num[complex_t], result[complex_t]);
native noret:clog10(num[complex_t], result[complex_t]);
native noret:cpow(num[complex_t], power[complex_t], result[complex_t]);
native noret:csqrt(num[complex_t], result[complex_t]);

native noret:cnegate(num[complex_t]);
native noret:cadd(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:csub(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:cmul(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:cdiv(num1[complex_t], num2[complex_t], result[complex_t]);

native bool:cequal(num1[complex_t], num2[complex_t]);
