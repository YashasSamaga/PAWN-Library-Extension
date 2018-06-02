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
#include <chrono>
#include <ctime>

#ifndef PLE_CHRONO_H_INCLUDED
#define PLE_CHRONO_H_INCLUDED

namespace PLE::chrono
{
	extern std::chrono::time_point<std::chrono::system_clock> syc_start;
	extern std::chrono::time_point<std::chrono::steady_clock> stc_start;

    namespace timespec_offsets
    {
        constexpr int seconds = 0;
        constexpr int nanoseconds = 1;
    }

	namespace tm_offsets
	{
		constexpr int second = 0;
		constexpr int minute = 1;
		constexpr int hour = 2;
		constexpr int day = 3;
		constexpr int month = 4;
	    constexpr int year = 5;
		constexpr int wday = 6;
		constexpr int yday = 7;
		constexpr int isdst = 8;
	}

    namespace natives 
    {
        extern cell AMX_NATIVE_CALL system_clock_now(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL steady_clock_now(AMX * amx, cell* params);

        extern cell AMX_NATIVE_CALL timespec_get(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_add(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_diff(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_diff_as_seconds(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_diff_as_milliseconds(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_diff_as_microseconds(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL timespec_diff_as_nanoseconds(AMX * amx, cell* params);

        extern cell AMX_NATIVE_CALL to_universal(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL to_local(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL to_timestamp(AMX * amx, cell* params);

        extern cell AMX_NATIVE_CALL difftime(AMX * amx, cell* params);

        extern cell AMX_NATIVE_CALL asctime(AMX * amx, cell* params);
        extern cell AMX_NATIVE_CALL strftime(AMX * amx, cell* params);
    }
}

#endif /* PLE_CHRONO_H_INCLUDED */