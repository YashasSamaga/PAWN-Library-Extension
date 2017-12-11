/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

"Custom" Time Library for PAWN (This is not a porting of C++ ctime library)
time.cpp

*************************************************************************************************************/
#include "main.h"
#include "time.h"

#include <ctime>

namespace PLE::natives
{
	//native now(_time_t[time_t]);
	cell AMX_NATIVE_CALL time_now(AMX * amx, cell* params)
	{
		cell* time_dest_addr = NULL;
		amx_GetAddr(amx, params[1], &time_dest_addr);
		
		time_t rawtime;
		time(&rawtime);

		struct tm * time_dest;		
		time_dest = gmtime(&rawtime);

		time_dest_addr[second] = time_dest->tm_sec;
		time_dest_addr[minute] = time_dest->tm_min;
		time_dest_addr[hour] = time_dest->tm_hour;
		time_dest_addr[day] = time_dest->tm_mday;
		time_dest_addr[month] = time_dest->tm_mon;
		time_dest_addr[year] = time_dest->tm_year + 1900;
		time_dest_addr[wday] = time_dest->tm_wday;
		time_dest_addr[yday] = time_dest->tm_yday;
		time_dest_addr[isdst] = time_dest->tm_isdst;

		return static_cast<cell>(rawtime);
	}
	//native createtime(ts, _time_t[]);
	cell AMX_NATIVE_CALL time_createtime(AMX * amx, cell* params)
	{
		time_t rawtime = static_cast<time_t>(params[1]);

		cell* time_dest_addr = NULL;
		amx_GetAddr(amx, params[2], &time_dest_addr);		

		struct tm * time_dest;
		time_dest = gmtime(&rawtime);

		time_dest_addr[second] = time_dest->tm_sec;
		time_dest_addr[minute] = time_dest->tm_min;
		time_dest_addr[hour] = time_dest->tm_hour;
		time_dest_addr[day] = time_dest->tm_mday;
		time_dest_addr[month] = time_dest->tm_mon;
		time_dest_addr[year] = time_dest->tm_year + 1900;
		time_dest_addr[wday] = time_dest->tm_wday;
		time_dest_addr[yday] = time_dest->tm_yday;
		time_dest_addr[isdst] = time_dest->tm_isdst;

		return params[1];
	}
	//native gettimestamp(_time_t[]);
	cell AMX_NATIVE_CALL time_gettimestamp(AMX * amx, cell* params)
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

		return static_cast<cell>(mktime(&time_src) - _timezone);
	}
	//native difftime(_time_t1[], _time_t2[]);
	cell AMX_NATIVE_CALL time_difftime(AMX * amx, cell* params)
	{
		cell* time_src_addr1 = NULL;
		amx_GetAddr(amx, params[1], &time_src_addr1);

		cell* time_src_addr2 = NULL;
		amx_GetAddr(amx, params[2], &time_src_addr2);

		struct tm time_src1;
		struct tm time_src2;

		time_src1.tm_sec = time_src_addr1[second];
		time_src1.tm_min = time_src_addr1[minute];
		time_src1.tm_hour = time_src_addr1[hour];
		time_src1.tm_mday = time_src_addr1[day];
		time_src1.tm_mon = time_src_addr1[month];
		time_src1.tm_year = time_src_addr1[year] - 1900;
		time_src1.tm_wday = time_src_addr1[wday];
		time_src1.tm_yday = time_src_addr1[yday];
		time_src1.tm_isdst = time_src_addr1[isdst];

		time_src2.tm_sec = time_src_addr2[second];
		time_src2.tm_min = time_src_addr2[minute];
		time_src2.tm_hour = time_src_addr2[hour];
		time_src2.tm_mday = time_src_addr2[day];
		time_src2.tm_mon = time_src_addr2[month];
		time_src2.tm_year = time_src_addr2[year] - 1900;
		time_src2.tm_wday = time_src_addr2[wday];
		time_src2.tm_yday = time_src_addr2[yday];
		time_src2.tm_isdst = time_src_addr2[isdst];

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
