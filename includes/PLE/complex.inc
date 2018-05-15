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

#if defined PLE_COMPLEX_INCLUDED
	#endinput
#endif
#define PLE_COMPLEX_INCLUDED

/* dependencies */
#include <PLE/config>

enum complex_t
{
	Float:real_part,
	Float:imag_part
}

/*
** all natives allow memory overlapping of arguments
** i.e: native_func(complex1, complex1) will work as expected even though both
** the arguments point to the same memory
*/
native Float:cabs(const num[complex_t]);
native Float:carg(const num[complex_t]);
native Float:cnorm(const num[complex_t]);
native noret:cconj(num[complex_t]);
native noret:cpolar(Float:modulus, Float:arg, result[complex_t]);

native noret:ccos(const num[complex_t], result[complex_t]);
native noret:csin(const num[complex_t], result[complex_t]);
native noret:ctan(const num[complex_t], result[complex_t]);
native noret:ccosh(const num[complex_t], result[complex_t]);
native noret:csinh(const num[complex_t], result[complex_t]);
native noret:ctanh(const num[complex_t], result[complex_t]);

native noret:cacos(const num[complex_t], result[complex_t]);
native noret:casin(const num[complex_t], result[complex_t]);
native noret:catan(const num[complex_t], result[complex_t]);
native noret:cacosh(const num[complex_t], result[complex_t]);
native noret:casinh(const num[complex_t], result[complex_t]);
native noret:catanh(const num[complex_t], result[complex_t]);

native noret:cexp(const num[complex_t], result[complex_t]);
native noret:clog(const num[complex_t], result[complex_t]);
native noret:clog10(const num[complex_t], result[complex_t]);
native noret:cpow(const num[complex_t], power[complex_t], result[complex_t]);
native noret:csqrt(const num[complex_t], result[complex_t]);

native noret:cnegate(num[complex_t]);
native noret:cadd(const num1[complex_t], const num2[complex_t], result[complex_t]);
native noret:csub(const num1[complex_t], const num2[complex_t], result[complex_t]);
native noret:cmul(const num1[complex_t], const num2[complex_t], result[complex_t]);
native noret:cdiv(const num1[complex_t], const num2[complex_t], result[complex_t]);

native bool:cequal(const num1[complex_t], const num2[complex_t]);
