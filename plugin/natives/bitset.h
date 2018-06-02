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

#ifndef PLE_H_INCLUDED
#define PLE_H_INCLUDED

#include "main.h"

namespace PLE::bitset::natives
{
	extern cell AMX_NATIVE_CALL test(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL any(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL none(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL all(AMX *amx, cell params[]);

    extern cell AMX_NATIVE_CALL count(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL size(AMX *amx, cell params[]);

	extern cell AMX_NATIVE_CALL set(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL reset(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL flip(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL set_all(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL reset_all(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL flip_all(AMX *amx, cell params[]);

    extern cell AMX_NATIVE_CALL ov_and(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL ov_or(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL ov_xor(AMX *amx, cell params[]);

	extern cell AMX_NATIVE_CALL tostring(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL equal(AMX *amx, cell params[]);

	extern cell AMX_NATIVE_CALL foreach_set(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL foreach_notset(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL find_set(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL find_notset(AMX *amx, cell params[]);
}

#endif /* PLE_H_INCLUDED */