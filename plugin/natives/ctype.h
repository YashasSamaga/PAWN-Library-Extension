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

#ifndef PLE_CTYPE_H_INCLUDED
#define PLE_CTYPE_H_INCLUDED

#include "main.h"

namespace PLE::ctype::natives
{
	extern cell AMX_NATIVE_CALL isalnum(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isalpha(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isblank(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL iscntrl(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isdigit(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isgraph(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL islower(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isprint(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL ispunct(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isspace(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isupper(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL isxdigit(AMX * amx, cell* params);
}

#endif /* PLE_CTYPE_H_INCLUDED */
