/*****************************************************************************************************************
PAWN Library Extension

Math library
math.inc
******************************************************************************************************************/
#if defined _PLE_MATH_INC
	#endinput
#else
	#define _PLE_MATH_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#define NAN         0x7FB00000
#define INFINITY    0x7F800000
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

native Float:sin(Float:value) = floatsin;
native Float:cos(Float:value) = floatcos;
native Float:tan(Float:value) = floattan;
//asin already implemented
//acos already implemented
//atan already implemented
//atan2 already implemented
//sinh not implemented
//cosh not implemented
//tanh not implemented
//asinh not implemented
//acosh not implemented
//atanh not implemented
native Float:exp(Float:value);
native Float:frexp(Float:value, &exp);
native Float:ldexp(Float:value, exp);
//hyperbolic functions have not been implemented
native Float:log(Float:value);
native Float:log10(Float:value);
native Float:modf(Float:value, &intpart);
native Float:exp2(Float:value);
native Float:expm1(Float:value);
//ilogb not implemented
native Float:log1p(Float:value);
native Float:log2(Float:value);
//logb not implemented
//scalbn not implemented
//scalbln not implemented
native Float:pow(Float:value, Float:exp) = floatpower;
native Float:sqrt(Float:value) = floatsqroot;
native Float:cbrt(Float:value);
native Float:hypot(Float:s1, Float:s2);
//erf not implemented
//erfc not implemented
//tgamma not implemented
//lgamma not implemented
#define ceil(%0) 	(Float:floatround(%0,floatround_ceil))
#define floor(%0)	(Float:floatround(%0,floatround_floor))
#define trunc(%0)	(Float:floatround(%0,floatround_tozero))
#define round(%0)	(Float:floatround(%0,floatround_round))
native Float:fmod(Float:value, Float:denom);
//lround not implemented
//llround not implemented
//rint not implemented
//lrint not implemented
//llrint not implemented
//nearbyint not implemented
native Float:remainder(Float:value, Float:denom);
//remquo not implemented
native Float:copysign(Float:value, Float:sign);
//nan not implemented
//nextafter not implemented
//nexttoward not implemented
native Float:fdim(Float:x, Float:y);
native Float:fmax(Float:x, Float:y);
native Float:fmin(Float:x, Float:y);
native Float:fabs(Float:value) = floatabs;
//abs not implemented
native Float:fma(Float:mul1, Float:mul2, Float:add);
//abs not implemented
//fpclassify not implemented
#define isfinite(%0) (!isinf(%0))
#define isinf(%0)	(Float:%0 == Float:%0);
#define isnan(%0) 	(%0 != %0);
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
/*****************************************************************************************************************/
