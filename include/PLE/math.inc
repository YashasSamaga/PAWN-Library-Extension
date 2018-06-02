/*
** PAWN Library Extension (PLE)
**
** Math
** Math library
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

#if defined PLE_MATH_INCLUDED
	#endinput
#endif
#define PLE_MATH_INCLUDED

/* dependencies */
#include <PLE/config>

#define FLOAT_NAN         Float:0x7FB00000
#define FLOAT_INFINITY    Float:0x7F800000
#define EULER 		2.718281
#define PI    		3.141592

stock public const MATH_ERRNO = 1;
stock public const MATH_ERREXCEPT = 2;

stock public const FE_DIVBYZERO = 0;
stock public const FE_INEXACT = 0;
stock public const FE_INVALID = 0;
stock public const FE_OVERFLOW = 0;
stock public const FE_UNDERFLOW = 0;
stock public const FE_ALL_EXCEPT = 0;

/* Basic functions */
native abs(value); //TODO
native Float:fabs(Float:value) = floatabs;
native Float:fmod(Float:value, Float:denom);
native Float:remainder(Float:value, Float:denom);
native Float:remquo(Float:x, Float:y, &quad); //TODO
native Float:fma(Float:mul1, Float:mul2, Float:add);
native Float:fmax(Float:x, Float:y);
native Float:fmin(Float:x, Float:y);
native Float:fdim(Float:x, Float:y);

/* Exponential functions */
native Float:exp(Float:value);
native Float:exp2(Float:value);
native Float:expm1(Float:value);
native Float:log(Float:value);
native Float:log10(Float:value);
native Float:log2(Float:value);
native Float:log1p(Float:value);

/* Power functions */
native Float:pow(Float:value, Float:exp) = floatpower;
native Float:sqrt(Float:value) = floatsqroot;
native Float:cbrt(Float:value);
native Float:hypot(Float:s1, Float:s2);

/* Trignometric functions */
native Float:sin(Float:value) = floatsin;
native Float:cos(Float:value) = floatcos;
native Float:tan(Float:value) = floattan;
//asin already implemented
//acos already implemented
//atan already implemented
//atan2 already implemented]

/* Hyperbolic functions */
//sinh not implemented
//cosh not implemented
//tanh not implemented
//asinh not implemented
//acosh not implemented
//atanh not implemented

/* Nearest integer floating point operations */
native Float:ceil(Float:value);
native Float:floor(Float:value);
native Float:trunc(Float:value);
native Float:round(Float:value);
//rint not implemented
//nearbyint not implemented

/* Floating point manipulation functions */
native Float:frexp(Float:value, &exp);
native Float:ldexp(Float:value, exp);
native Float:modf(Float:value, &intpart);
//scalbn not implemented
//scalbln not implemented
//ilogb not implemented
//logb not implemented
//nextafter not implemented
//nexttoward not implemented
native Float:copysign(Float:value, Float:sign);



/* Error and gamma functions */
//erf not implemented
//erfc not implemented
//tgamma not implemented
//lgamma not implemented

//nan not implemented

//fpclassify not implemented
#define isfinite(%0) (!isinf(%0))
#define isinf(%0)	(Float:%0 == Float:%0)
#define isnan(%0) 	(%0 != %0)
//isnormal not implemented
#define signbit(%0) (%0 < 0)
//isgreater not implemented
//isgreater not implemented
//isgreaterequal not implemented
//isless not implemented
//islessequal not implemented
//islessgreater not implemented
//isunordered not implemented
native math_errhandling();
