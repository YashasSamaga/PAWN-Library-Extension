/*
** PAWN Library Extension (PLE)
**
** Complex
** Library to manipulate complex numbers
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

#if defined PLE_COMPLEX_INCLUDED
	#endinput
#endif
#define PLE_COMPLEX_INCLUDED

/* dependencies */
#include <PLE/config>

#if !defined complex::
	#define complex:: c
#endif

enum complex_t
{
	Float:real,
	Float:imag
}

/*
** all natives allow memory overlapping of arguments
** i.e: native_func(complex1, complex1) will work as expected even though both
** the arguments point to the same memory
*/
native Float:complex::abs(num[complex_t]);
native Float:complex::arg(num[complex_t]);
native Float:complex::norm(num[complex_t]);
native noret:complex::conj(num[complex_t]);
native noret:complex::polar(Float:modulus, Float:arg, result[complex_t]);

native noret:complex::cos(num[complex_t], result[complex_t]);
native noret:complex::sin(num[complex_t], result[complex_t]);
native noret:complex::tan(num[complex_t], result[complex_t]);
native noret:complex::cosh(num[complex_t], result[complex_t]);
native noret:complex::sinh(num[complex_t], result[complex_t]);
native noret:complex::tanh(num[complex_t], result[complex_t]);

native noret:complex::acos(num[complex_t], result[complex_t]);
native noret:complex::asin(num[complex_t], result[complex_t]);
native noret:complex::atan(num[complex_t], result[complex_t]);
native noret:complex::acosh(num[complex_t], result[complex_t]);
native noret:complex::asinh(num[complex_t], result[complex_t]);
native noret:complex::atanh(num[complex_t], result[complex_t]);

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
