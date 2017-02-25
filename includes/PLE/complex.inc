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
	Float:real,
	Float:imag
}

native Float:complex::abs(num[complex_t]);
native Float:complex::arg(num[complex_t]);
native Float:complex::norm(num[complex_t]);
native noret:complex::conj(num[complex_t]);
native noret:complex::polar(Float:modulus, Float:arg, result[complex_t]);

native noret:complex::cos(num[complex_t], result[complex_t]);
native noret:complex::sin(num[complex_t], result[complex_t]);
native noret:complex::tan(num[complex_t], result[complex_t]);
//ccosh not implemented
//csinh not implemented
//ctahh not implemented

native noret:complex::acos(num[complex_t], result[complex_t]);
native noret:complex::asin(num[complex_t], result[complex_t]);
native noret:complex::atan(num[complex_t], result[complex_t]);
//cacosh not implemented
//casinh not implemented
//catanh not implemented

native noret:complex::exp(num[complex_t], result[complex_t]);
native noret:complex::log(num[complex_t], result[complex_t]);
native noret:complex::log10(num[complex_t], result[complex_t]);
native noret:complex::pow(num[complex_t], power[complex_t], result[complex_t]);
native noret:complex::sqrt(num[complex_t], result[complex_t]);

native noret:complex::negate(num[complex_t]);
native noret:complex::add(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:complex::sub(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:complex::mul(num1[complex_t], num2[complex_t], result[complex_t]);
native noret:complex::div(num1[complex_t], num2[complex_t], result[complex_t]);

native bool:complex::equal(num1[complex_t], num2[complex_t]);
