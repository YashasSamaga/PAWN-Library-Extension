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
#include "chrono.h"

#include <chrono>
#include <ctime>
#include <string>

namespace PLE::chrono
{
	std::chrono::time_point<std::chrono::system_clock> syc_start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> stc_start = std::chrono::steady_clock::now();

	namespace natives
	{
        //native timestamp_t:system_clock_now();
		cell AMX_NATIVE_CALL system_clock_now(AMX* amx, cell* params) 
		{
            error_if(!check_params(0), "[PLE] chrono>> system_clock_now: expected 0 parameters but found %d parameters.", get_params_count());
			return static_cast<cell>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
        //native seconds_t:steady_clock_now();
		cell AMX_NATIVE_CALL steady_clock_now(AMX* amx, cell* params)
		{
            error_if(!check_params(0), "[PLE] chrono>> steady_clock_now: expected 0 parameters but found %d parameters.", get_params_count());
			return static_cast<cell>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - stc_start).count());
		}

        //native noret:timespec_get(ts[timespec_t]);
        cell AMX_NATIVE_CALL timespec_get(AMX * amx, cell* params)
        {
            error_if(!check_params(0), "[PLE] chrono>> timespec_get: expected 1 parameters but found %d parameters.", get_params_count());

            auto duration = std::chrono::steady_clock::now() - stc_start;
            cell* ts_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_addr);
			ts_addr[timespec_offsets::seconds] = static_cast<cell>(std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			ts_addr[timespec_offsets::nanoseconds] = static_cast<cell>(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()%std::chrono::nanoseconds::duration::period::den);
            return false;
        }
        //native noret:timespec_add(ts[timespec_t], seconds_t:seconds = 0, milliseconds_t:ms = 0, microseconds_t:us = 0, nanoseconds_t:ns = 0);
        cell AMX_NATIVE_CALL timespec_add(AMX * amx, cell* params)
        {
            error_if(!check_params(5), "[PLE] chrono>> timespec_add: expected 5 parameters but found %d parameters.", get_params_count());

            using ns_duration = typename std::chrono::nanoseconds;
            ns_duration::rep nanoseconds = params[5],
                                          microseconds = params[4],
                                          milliseconds = params[3],
                                          seconds = params[2];

            cell* ts_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_addr);
            ns_duration::rep delta_ns = ts_addr[timespec_offsets::nanoseconds] + nanoseconds + (microseconds + (milliseconds + seconds * 1000) * 1000) * 1000;

            ts_addr[timespec_offsets::seconds] += static_cast<cell>(delta_ns/ns_duration::period::den) - (delta_ns < 0);
			ts_addr[timespec_offsets::nanoseconds] = delta_ns%ns_duration::period::den;
            return false;
        }
        //native noret:timespec_diff(const ts_start[timespec_t], const ts_end[timespec_t], ts_dest[timespec_t]);
        cell AMX_NATIVE_CALL timespec_diff(AMX * amx, cell* params)
        {
            error_if(!check_params(3), "[PLE] chrono>> timespec_diff: expected 3 parameters but found %d parameters.", get_params_count());

            using ns_duration = typename std::chrono::nanoseconds;
            
            cell* ts_start_addr = NULL, *ts_end_addr = NULL, *ts_dest_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_start_addr);
            amx_GetAddr(amx, params[2], &ts_end_addr);
            amx_GetAddr(amx, params[3], &ts_dest_addr);
            
            ns_duration::rep final_ns = (ts_end_addr[timespec_offsets::seconds] - ts_start_addr[timespec_offsets::seconds])*ns_duration::period::den;
            final_ns += (ts_end_addr[timespec_offsets::nanoseconds] - ts_start_addr[timespec_offsets::nanoseconds]);

            ts_dest_addr[timespec_offsets::seconds] = static_cast<cell>(final_ns/ns_duration::period::den);
			ts_dest_addr[timespec_offsets::nanoseconds] = final_ns%ns_duration::period::den;
            return false;
        }
        //native seconds_t:timespec_diff_as_seconds(const ts_start[timespec_t], const ts_end[timespec_t]);
        cell AMX_NATIVE_CALL timespec_diff_as_seconds(AMX * amx, cell* params)
        {
            error_if(!check_params(2), "[PLE] chrono>> timespec_diff_as_seconds: expected 2 parameters but found %d parameters.", get_params_count());

            using ns_duration = typename std::chrono::nanoseconds;
            
            cell* ts_start_addr = NULL, *ts_end_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_start_addr);
            amx_GetAddr(amx, params[2], &ts_end_addr);
            
            ns_duration::rep final_ns = (ts_end_addr[timespec_offsets::seconds] - ts_start_addr[timespec_offsets::seconds])*ns_duration::period::den;
            final_ns += (ts_end_addr[timespec_offsets::nanoseconds] - ts_start_addr[timespec_offsets::nanoseconds]);

            return static_cast<cell>(final_ns/ns_duration::period::den);
        }
        //native milliseconds_t:timespec_diff_as_milliseconds(const ts_start[timespec_t], const ts_end[timespec_t]);
        cell AMX_NATIVE_CALL timespec_diff_as_milliseconds(AMX * amx, cell* params)
        {
            error_if(!check_params(2), "[PLE] chrono>> timespec_diff_as_milliseconds: expected 2 parameters but found %d parameters.", get_params_count());
            using ns_duration = typename std::chrono::nanoseconds;
            
            cell* ts_start_addr = NULL, *ts_end_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_start_addr);
            amx_GetAddr(amx, params[2], &ts_end_addr);
            
            ns_duration::rep final_ns = (ts_end_addr[timespec_offsets::seconds] - ts_start_addr[timespec_offsets::seconds])*ns_duration::period::den;
            final_ns += (ts_end_addr[timespec_offsets::nanoseconds] - ts_start_addr[timespec_offsets::nanoseconds]);

            return static_cast<cell>(final_ns/(ns_duration::period::den/std::chrono::milliseconds::period::den));
        }
        //native microseconds_t:timespec_diff_as_microseconds(const ts_start[timespec_t], const ts_end[timespec_t]);
        cell AMX_NATIVE_CALL timespec_diff_as_microseconds(AMX * amx, cell* params)
        {
            error_if(!check_params(2), "[PLE] chrono>> timespec_diff_as_microseconds: expected 2 parameters but found %d parameters.", get_params_count());

            using ns_duration = typename std::chrono::nanoseconds;
            
            cell* ts_start_addr = NULL, *ts_end_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_start_addr);
            amx_GetAddr(amx, params[2], &ts_end_addr);
            
            ns_duration::rep final_ns = (ts_end_addr[timespec_offsets::seconds] - ts_start_addr[timespec_offsets::seconds])*ns_duration::period::den;
            final_ns += (ts_end_addr[timespec_offsets::nanoseconds] - ts_start_addr[timespec_offsets::nanoseconds]);

            return static_cast<cell>(final_ns/(ns_duration::period::den/std::chrono::microseconds::period::den));
        }
        //native nanoseconds_t:timespec_diff_as_nanoseconds(const ts_start[timespec_t], const ts_end[timespec_t]);
        cell AMX_NATIVE_CALL timespec_diff_as_nanoseconds(AMX * amx, cell* params)
        {   
            error_if(!check_params(2), "[PLE] chrono>> timespec_diff_as_nanoseconds: expected 2 parameters but found %d parameters.", get_params_count());

            using ns_duration = typename std::chrono::nanoseconds;
            cell* ts_start_addr = NULL, *ts_end_addr = NULL;
			amx_GetAddr(amx, params[1], &ts_start_addr);
            amx_GetAddr(amx, params[2], &ts_end_addr);
            
            ns_duration::rep final_ns = (ts_end_addr[timespec_offsets::seconds] - ts_start_addr[timespec_offsets::seconds])*ns_duration::period::den;
            final_ns += (ts_end_addr[timespec_offsets::nanoseconds] - ts_start_addr[timespec_offsets::nanoseconds]);
            return static_cast<cell>(final_ns);
        }

		//native gmtime(timestamp_t:ts, tm[tm_t]);
		cell AMX_NATIVE_CALL to_universal(AMX * amx, cell* params)
		{
            error_if(!check_params(2), "[PLE] chrono>> to_universal: expected 2 parameters but found %d parameters.", get_params_count());

            std::time_t rawtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::seconds{ params[1] }));

			std::tm *time_dest = std::gmtime(&rawtime);

			cell* time_dest_addr = NULL;
			amx_GetAddr(amx, params[2], &time_dest_addr);
			time_dest_addr[chrono::tm_offsets::second] = time_dest->tm_sec;
			time_dest_addr[chrono::tm_offsets::minute] = time_dest->tm_min;
			time_dest_addr[chrono::tm_offsets::hour] = time_dest->tm_hour;
			time_dest_addr[chrono::tm_offsets::day] = time_dest->tm_mday;
			time_dest_addr[chrono::tm_offsets::month] = time_dest->tm_mon;
			time_dest_addr[chrono::tm_offsets::year] = time_dest->tm_year + 1900;
			time_dest_addr[chrono::tm_offsets::wday] = time_dest->tm_wday;
			time_dest_addr[chrono::tm_offsets::yday] = time_dest->tm_yday;
			time_dest_addr[chrono::tm_offsets::isdst] = time_dest->tm_isdst;
			return true;
		}
		//native localtime(timestamp_t:ts, tm[tm_t]);
		cell AMX_NATIVE_CALL to_local(AMX * amx, cell* params)
		{
            error_if(!check_params(2), "[PLE] chrono>> to_local: expected 2 parameters but found %d parameters.", get_params_count());
			
            std::time_t rawtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::seconds{ params[1] }));

			std::tm * time_dest = localtime(&rawtime);

			cell* time_dest_addr = NULL;
			amx_GetAddr(amx, params[2], &time_dest_addr);
			time_dest_addr[chrono::tm_offsets::second] = time_dest->tm_sec;
			time_dest_addr[chrono::tm_offsets::minute] = time_dest->tm_min;
			time_dest_addr[chrono::tm_offsets::hour] = time_dest->tm_hour;
			time_dest_addr[chrono::tm_offsets::day] = time_dest->tm_mday;
			time_dest_addr[chrono::tm_offsets::month] = time_dest->tm_mon;
			time_dest_addr[chrono::tm_offsets::year] = time_dest->tm_year + 1900;
			time_dest_addr[chrono::tm_offsets::wday] = time_dest->tm_wday;
			time_dest_addr[chrono::tm_offsets::yday] = time_dest->tm_yday;
			time_dest_addr[chrono::tm_offsets::isdst] = time_dest->tm_isdst;
			return true;
		}
		//native timestamp_t:to_timestamp(tm[tm_t]);
		cell AMX_NATIVE_CALL to_timestamp(AMX * amx, cell* params)
		{
            error_if(!check_params(1), "[PLE] to_timestamp>> to_local: expected 1 parameters but found %d parameters.", get_params_count());

			cell* time_src_addr = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr);

			std::tm time_src;
			time_src.tm_sec = time_src_addr[chrono::tm_offsets::second];
			time_src.tm_min = time_src_addr[chrono::tm_offsets::minute];
			time_src.tm_hour = time_src_addr[chrono::tm_offsets::hour];
			time_src.tm_mday = time_src_addr[chrono::tm_offsets::day];
			time_src.tm_mon = time_src_addr[chrono::tm_offsets::month];
			time_src.tm_year = time_src_addr[chrono::tm_offsets::year] - 1900;
			time_src.tm_wday = time_src_addr[chrono::tm_offsets::wday];
			time_src.tm_yday = time_src_addr[chrono::tm_offsets::yday];
			time_src.tm_isdst = time_src_addr[chrono::tm_offsets::isdst];

			return static_cast<cell>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::from_time_t(std::mktime(&time_src)).time_since_epoch()).count());
		}
        
        //native seconds_t:difftime(const tm1[tm_t], const tm2[tm_t]);
        cell AMX_NATIVE_CALL difftime(AMX * amx, cell* params)
        {
            error_if(!check_params(2), "[PLE] difftime>> to_local: expected 2 parameters but found %d parameters.", get_params_count());

            cell* time_src_addr1 = NULL;
            amx_GetAddr(amx, params[1], &time_src_addr1);

            cell* time_src_addr2 = NULL;
            amx_GetAddr(amx, params[2], &time_src_addr2);

            struct tm time_src1, time_src2;

            time_src1.tm_sec = time_src_addr1[tm_offsets::second];
            time_src1.tm_min = time_src_addr1[tm_offsets::minute];
            time_src1.tm_hour = time_src_addr1[tm_offsets::hour];
            time_src1.tm_mday = time_src_addr1[tm_offsets::day];
            time_src1.tm_mon = time_src_addr1[tm_offsets::month];
            time_src1.tm_year = time_src_addr1[tm_offsets::year] - 1900;
            time_src1.tm_wday = time_src_addr1[tm_offsets::wday];
            time_src1.tm_yday = time_src_addr1[tm_offsets::yday];
            time_src1.tm_isdst = time_src_addr1[tm_offsets::isdst];

            time_src2.tm_sec = time_src_addr2[tm_offsets::second];
            time_src2.tm_min = time_src_addr2[tm_offsets::minute];
            time_src2.tm_hour = time_src_addr2[tm_offsets::hour];
            time_src2.tm_mday = time_src_addr2[tm_offsets::day];
            time_src2.tm_mon = time_src_addr2[tm_offsets::month];
            time_src2.tm_year = time_src_addr2[tm_offsets::year] - 1900;
            time_src2.tm_wday = time_src_addr2[tm_offsets::wday];
            time_src2.tm_yday = time_src_addr2[tm_offsets::yday];
            time_src2.tm_isdst = time_src_addr2[tm_offsets::isdst];

            return static_cast<cell>(std::difftime(std::mktime(&time_src1), std::mktime(&time_src2)));
        }
		
        //native asctime(const tm[tm_t], result[], size_res = sizeof(result));
		cell AMX_NATIVE_CALL asctime(AMX * amx, cell* params)
		{
            error_if(!check_params(3), "[PLE] chrono>> asctime: expected 3 parameters but found %d parameters.", get_params_count());

			cell* time_src_addr = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr);

			struct tm time_src;
			time_src.tm_sec = time_src_addr[tm_offsets::second];
			time_src.tm_min = time_src_addr[tm_offsets::minute];
			time_src.tm_hour = time_src_addr[tm_offsets::hour];
			time_src.tm_mday = time_src_addr[tm_offsets::day];
			time_src.tm_mon = time_src_addr[tm_offsets::month];
			time_src.tm_year = time_src_addr[tm_offsets::year] - 1900;
			time_src.tm_wday = time_src_addr[tm_offsets::wday];
			time_src.tm_yday = time_src_addr[tm_offsets::yday];
			time_src.tm_isdst = time_src_addr[tm_offsets::isdst];

			const char * timestr = asctime(&time_src);

			cell* result_addr = NULL;
			amx_GetAddr(amx, params[2], &result_addr);
			amx_SetString(result_addr, timestr, 0, 0, params[3]);

			return true;
		}
		//native strftime(const tm[tm_t], const format[], result[], size_res = sizeof(result));
		cell AMX_NATIVE_CALL strftime(AMX * amx, cell* params)
		{
            error_if(!check_params(4), "[PLE] chrono>> strftime: expected 4 parameters but found %d parameters.", get_params_count());

			cell* time_src_addr = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr);

			struct tm time_src;
			time_src.tm_sec = time_src_addr[tm_offsets::second];
			time_src.tm_min = time_src_addr[tm_offsets::minute];
			time_src.tm_hour = time_src_addr[tm_offsets::hour];
			time_src.tm_mday = time_src_addr[tm_offsets::day];
			time_src.tm_mon = time_src_addr[tm_offsets::month];
			time_src.tm_year = time_src_addr[tm_offsets::year] - 1900;
			time_src.tm_wday = time_src_addr[tm_offsets::wday];
			time_src.tm_yday = time_src_addr[tm_offsets::yday];
			time_src.tm_isdst = time_src_addr[tm_offsets::isdst];

			int len;
			cell* format_addr = NULL;
			amx_GetAddr(amx, params[2], &format_addr);
			amx_StrLen(format_addr, &len);

			cell* result_addr = NULL;
			amx_GetAddr(amx, params[3], &result_addr);

			if (len)
			{
				len++;

                std::string format;
                format.resize(len);
				amx_GetString(format.data(), format_addr, 0, len);

                std::string timestr;
                timestr.resize(len + 80);
				size_t ret = std::strftime(timestr.data(), len + 80, format.c_str(), &time_src);

				amx_SetString(result_addr, timestr.c_str(), 0, 0, params[4]);
				return ret;
			}
			return 0;
		}
	}
}
