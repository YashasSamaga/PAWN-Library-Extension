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
#include "ctype.h"

#include <cctype>

namespace PLE::ctype::natives
{
	//native isalnum(c);
	cell AMX_NATIVE_CALL isalnum(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isalnum: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isalnum(params[1]);
	}
	//native isalpha(c);
	cell AMX_NATIVE_CALL isalpha(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isalpha: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isalpha(params[2]);
	}
	//native isblank(c);
	cell AMX_NATIVE_CALL isblank(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isblank: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isblank(params[2]);
	}
	//native iscntrl(c);
	cell AMX_NATIVE_CALL iscntrl(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> iscntrl: expected 1 parameters but found %d parameters.", get_params_count());
		return std::iscntrl(params[2]);
	}
	//native isdigit(c);
	cell AMX_NATIVE_CALL isdigit(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isdigit: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isdigit(params[2]);
	}
	//native isgraph(c);
	cell AMX_NATIVE_CALL isgraph(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isgraph: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isgraph(params[2]);
	}
	//native islower(c);
	cell AMX_NATIVE_CALL islower(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> islower: expected 1 parameters but found %d parameters.", get_params_count());
		return std::islower(params[2]);
	}
	//native isprint(c);
	cell AMX_NATIVE_CALL isprint(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isprint: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isprint(params[2]);
	}
	//native ispunct(c);
	cell AMX_NATIVE_CALL ispunct(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> ispunct: expected 1 parameters but found %d parameters.", get_params_count());
		return std::ispunct(params[2]);
	}
	//native isspace(c);
	cell AMX_NATIVE_CALL isspace(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isspace: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isspace(params[2]);
	}
	//native isupper(c);
	cell AMX_NATIVE_CALL isupper(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isupper: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isupper(params[2]);
	}
	//native isxdigit(c);
	cell AMX_NATIVE_CALL isxdigit(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isxdigit: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isxdigit(params[2]);
	}
}
