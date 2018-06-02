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
#include "errno.h"

#include <cerrno>

namespace PLE::ov_errno::natives
{
	//native errno();
	cell AMX_NATIVE_CALL ov_errno(AMX * amx, cell* params)
	{		
		error_if(!check_params(0), "[PLE] errno>> errno: expected 0 parameters but found %d parameters.", get_params_count());
		return errno;
	}	
	//native clearerrno();
	cell AMX_NATIVE_CALL clearerrno(AMX * amx, cell* params)
	{
		error_if(!check_params(0), "[PLE] errno>> errno: expected 0 parameters but found %d parameters.", get_params_count());
		errno = 0;
		return true;
	}
}
