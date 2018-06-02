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

#include "main.h"
#include "system.h"

#include <cstdlib>
/************************************************************************************************************/
namespace PLE::system::natives
{
	//native system(const cmd[]);
	cell AMX_NATIVE_CALL system(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] system>> system: expected 1 parameters but found %d parameters.", get_params_count());
		cell *addr, len;
		amx_GetAddr(amx, params[1], &addr);	
		amx_StrLen(addr, &len);
		len++;
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		int retval = std::system(text);

		delete[] text;
		return retval;
	}
	//native getenv(const env_var[], dest[], dest_size = sizeof(dest));
	cell AMX_NATIVE_CALL getenv(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] system>> getenv: expected 3 parameters but found %d parameters.", get_params_count());

		cell *var_addr, len;
		amx_GetAddr(amx, params[1], &var_addr);		
		amx_StrLen(var_addr, &len);
		len++;
		char* env_var = new char[len];

		char *str = std::getenv(env_var);

		cell *dest_addr;
		amx_GetAddr(amx, params[2], &dest_addr);
		amx_SetString(dest_addr, str, 0, 0, params[3]);
		delete[] env_var;
		return 0;
	}
}
