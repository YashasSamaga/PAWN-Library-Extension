/*****************************************************************************************************************
PAWN Library Extension

complex numbers testing
complex.inc
******************************************************************************************************************/
#if defined _PLE_COMPLEXT_INC
	#endinput
#else
	#define _PLE_COMPLEXT_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/complex>
/*****************************************************************************************************************/
stock complex_testing()
{
	new c1[complex_t], c2[complex_t], c3[complex_t];
	c1[real] = 8;
	c1[imag] = 6;

	if(complex::abs(c1) != 10.0) print("[TEST] complex::abs failed");
	if(complex::arg(c1) != 0.75) print("[TEST] complex::arg failed");
	if(complex::norm(c1) != 100.0) print("[TEST] complex::norm failed");

	complex::conj(c1);
	if(c1[real] != 8.0 || c1[imag] != -6.0) print("[TEST] complex::conj failed");

	complex::polar(10.0, 0.643501109, c1);
	if(c1[real] != 8.0 || c1[imag] != 6.0) print("[TEST] complex::polar failed");

	complex::exp({1.0, 0.0}, c2);
	if(!(2.70 < c2[real] < 2.72) || c2[imag] != 0.0) print("[TEST] complex::exp failed");

	complex::sqrt({-1.0, 0.0}, c2);
	if(c2[real] != 0.0 || c2[imag] != 1.0) print("[TEST] complex::sqrt failed");

	complex::pow({0.0, 1.0}, {2.0, 0.0}, c2);
	if(!_floatcmp(c2[real], -1.0) || !_floatcmp(c2[imag], 0.0)) print("[TEST] complex::pow failed");

	c2[real] = 1.0;
	c2[imag] = 2.0;
	complex::negate(c2);
	if(c2[real] != -1.0 || c2[imag] != -2.0) print("[TEST] complex::negate failed");

	complex::add({1.0, 1.0}, {2.0, 4.0}, c2);
	if(c2[real] != 3.0 || c2[imag] != 5.0) print("[TEST] complex::add failed");

	complex::sub({3.0, 4.0}, {2.0, 1.0}, c2);
	if(c2[real] != 1 || c2[imag] != 3) print("[TEST] complex::sub failed");

	complex::mul({3.0, 4.0}, {0.0, 1.0}, c2);
	if(c2[real] != -4.0 || c2[imag] != 3.0) print("[TEST] complex::mul failed");

	complex::div({3.0, 4.0}, {0.0, 1.0}, c2);
	if(c2[real] != 4.0 || c2[imag] != -3.0) print("[TEST] complex::div failed");

	if(complex::equal({1.0, 2.0}, {1.0, 3.0})) print("[TEST] complex::equal failed");
	if(!complex::equal({1.0, 2.0}, {1.0, 2.0})) print("[TEST] complex::equal failed");

	complex::cos({5.0, 5.0}, c3);
	complex::acos(c3, c2);
	if(!_floatcmp(c2[real], 1.28) || !_floatcmp(c2[imag], -5.0)) print("[TEST] complex::cos/complex::acos failed");

	complex::sin({5.0, 5.0}, c3);
	complex::asin(c3, c2);
	if(!_floatcmp(c2[real], -1.28) || !_floatcmp(c2[imag], 5.0)) print("[TEST] complex::sin/complex::asin failed");

	complex::tan({5.0, 5.0}, c3);
	complex::atan(c3, c2);
	if(!_floatcmp(c2[real], -1.28) || !_floatcmp(c2[imag], 5.0)) print("[TEST] complex::tan/complex::atan failed");

	complex::log({1.0, 0.0}, c2);
	if(c2[real] != 0.0 || c2[imag] != 0.0) print("[TEST] complex::log failed");

	complex::log10({100.0, 0.0}, c2);
	if(c2[real] != 2.0 || c2[imag] != 0.0) print("[TEST] complex::log10 failed");
}
