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

#ifndef PLE_MATH_H_INCLUDED
#define PLE_MATH_H_INCLUDED

#include "main.h"
/************************************************************************************************************/
namespace PLE::math::natives
{
	extern cell AMX_NATIVE_CALL exp(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL frexp(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL ldexp(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL modf(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL log(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL log10(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL exp2(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL expm1(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL log2(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL log1p(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL cbrt(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL hypot(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fmod(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL remainder(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL copysign(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fdim(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fmin(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fmax(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fma(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fclamp(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL ov_math_errhandling(AMX * amx, cell* params);
}

#endif /* PLE_MATH_H_INCLUDED */