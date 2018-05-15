/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

"Custom" Time Library for PAWN (This is not a porting of C++ ctime library)
time.cpp

*************************************************************************************************************/
#include "main.h"
#include "chrono.h"

#include <chrono>
#include <ctime>

namespace PLE
{
	namespace chrono
	{
		std::chrono::time_point<std::chrono::system_clock> syc_start = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::steady_clock> stc_start = std::chrono::steady_clock::now();
	}
	namespace natives
	{
		cell AMX_NATIVE_CALL chrono_system_clock_now(AMX * amx, cell* params)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		cell AMX_NATIVE_CALL chrono_steady_clock_now(AMX * amx, cell* params)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		}
		cell AMX_NATIVE_CALL chrono_steady_clock_milliseconds(AMX * amx, cell* params)
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()
				% std::chrono::milliseconds::period::den;
		}
		cell AMX_NATIVE_CALL chrono_steady_clock_microseconds(AMX * amx, cell* params)
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()
				% std::chrono::microseconds::period::den;
		}
		cell AMX_NATIVE_CALL chrono_steady_clock_nanoseconds(AMX * amx, cell* params)
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()
				% std::chrono::nanoseconds::period::den;
		}

		//native gmtime(timestamp_t:ts, tm[tm_t]);
		cell AMX_NATIVE_CALL chrono_to_universal(AMX * amx, cell* params)
		{
			std::time_t rawtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::duration<std::chrono::system_clock>(std::chrono::seconds{ params[1] })));

			std::tm * time_dest;
			time_dest = gmtime(&rawtime);

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
		cell AMX_NATIVE_CALL chrono_to_local(AMX * amx, cell* params)
		{
			std::time_t rawtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::duration<std::chrono::system_clock>(std::chrono::seconds{ params[1] })));

			std::tm * time_dest;
			time_dest = localtime(&rawtime);

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
		//native mktime(tm[tm_t]);
		cell AMX_NATIVE_CALL chrono_to_timestamp(AMX * amx, cell* params)
		{
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

			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::from_time_t(std::mktime(&time_src)).time_since_epoch()).count();
		}
		//native difftime(_time_t1[], _time_t2[]);
		cell AMX_NATIVE_CALL time_difftime(AMX * amx, cell* params)
		{
			cell* time_src_addr1 = NULL, *time_src_addr2 = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr1);
			amx_GetAddr(amx, params[2], &time_src_addr2);

			std::tm time_src1, time_src2;
			time_src1.tm_sec = time_src_addr1[chrono::tm_offsets::second];
			time_src1.tm_min = time_src_addr1[chrono::tm_offsets::minute];
			time_src1.tm_hour = time_src_addr1[chrono::tm_offsets::hour];
			time_src1.tm_mday = time_src_addr1[chrono::tm_offsets::day];
			time_src1.tm_mon = time_src_addr1[chrono::tm_offsets::month];
			time_src1.tm_year = time_src_addr1[chrono::tm_offsets::year] - 1900;
			time_src1.tm_wday = time_src_addr1[chrono::tm_offsets::wday];
			time_src1.tm_yday = time_src_addr1[chrono::tm_offsets::yday];
			time_src1.tm_isdst = time_src_addr1[chrono::tm_offsets::isdst];

			time_src2.tm_sec = time_src_addr2[chrono::tm_offsets::second];
			time_src2.tm_min = time_src_addr2[chrono::tm_offsets::minute];
			time_src2.tm_hour = time_src_addr2[chrono::tm_offsets::hour];
			time_src2.tm_mday = time_src_addr2[chrono::tm_offsets::day];
			time_src2.tm_mon = time_src_addr2[chrono::tm_offsets::month];
			time_src2.tm_year = time_src_addr2[chrono::tm_offsets::year] - 1900;
			time_src2.tm_wday = time_src_addr2[chrono::tm_offsets::wday];
			time_src2.tm_yday = time_src_addr2[chrono::tm_offsets::yday];
			time_src2.tm_isdst = time_src_addr2[chrono::tm_offsets::isdst];

			return static_cast<cell>(difftime(mktime(&time_src1), mktime(&time_src2)));
		}
		//native asctime(_time_t[], result[], size_res = sizeof(result));
		cell AMX_NATIVE_CALL time_asctime(AMX * amx, cell* params)
		{
			cell* time_src_addr = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr);

			struct tm time_src;
			time_src.tm_sec = time_src_addr[second];
			time_src.tm_min = time_src_addr[minute];
			time_src.tm_hour = time_src_addr[hour];
			time_src.tm_mday = time_src_addr[day];
			time_src.tm_mon = time_src_addr[month];
			time_src.tm_year = time_src_addr[year] - 1900;
			time_src.tm_wday = time_src_addr[wday];
			time_src.tm_yday = time_src_addr[yday];
			time_src.tm_isdst = time_src_addr[isdst];

			const char * timestr = asctime(&time_src);

			cell* result_addr = NULL;
			amx_GetAddr(amx, params[2], &result_addr);
			amx_SetString(result_addr, timestr, 0, 0, params[3]);

			return true;
		}
		//native strftime(_time_t[], format[], result[], size_res = sizeof(result));
		cell AMX_NATIVE_CALL time_strftime(AMX * amx, cell* params)
		{
			cell* time_src_addr = NULL;
			amx_GetAddr(amx, params[1], &time_src_addr);

			struct tm time_src;
			time_src.tm_sec = time_src_addr[second];
			time_src.tm_min = time_src_addr[minute];
			time_src.tm_hour = time_src_addr[hour];
			time_src.tm_mday = time_src_addr[day];
			time_src.tm_mon = time_src_addr[month];
			time_src.tm_year = time_src_addr[year] - 1900;
			time_src.tm_wday = time_src_addr[wday];
			time_src.tm_yday = time_src_addr[yday];
			time_src.tm_isdst = time_src_addr[isdst];

			int len;
			cell* format_addr = NULL;
			amx_GetAddr(amx, params[2], &format_addr);
			amx_StrLen(format_addr, &len);

			cell* result_addr = NULL;
			amx_GetAddr(amx, params[3], &result_addr);

			if (len)
			{
				len++;

				char* format = new char[len];
				amx_GetString(format, format_addr, 0, len);

				char* timestr = new char[len + 80];
				strftime(timestr, len + 80, format, &time_src);

				amx_SetString(result_addr, timestr, 0, 0, params[4]);

				delete[] format;
				delete[] timestr;
				return true;
			}
			amx_SetString(result_addr, "", 0, 0, params[4]);
			return true;
		}
	}
}
