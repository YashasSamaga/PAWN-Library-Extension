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

#ifndef PLE_STRING_H_INCLUDED
#define PLE_STRING_H_INCLUDED

#include "main.h"

namespace PLE::string::natives
{
	cell AMX_NATIVE_CALL memmove(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strcpy(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strncpy(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL strncat(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL strncmp(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL memchr(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strchr(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strrchr(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strcspn(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strpbrk(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strspn(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strtok(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL memset(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL strreplace(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strtrim(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strtolower(AMX * amx, cell* params);
	cell AMX_NATIVE_CALL strtoupper(AMX * amx, cell* params);

	cell AMX_NATIVE_CALL strerror(AMX * amx, cell* params);
}

#endif