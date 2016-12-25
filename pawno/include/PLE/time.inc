/*****************************************************************************************************************
Standard Library Extension


string.inc
******************************************************************************************************************/
#if defined _PLE_TIME_INC
	#endinput
#else
	#define _PLE_TIME_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
//Custom Time Library

enum time_t
{
	second = 0,
	minute,
	hour,
	day,
	month,
	year,
	wday, //0-6
	yday, //0-365
	isdst //true if daylight saving time is in effect
}

native now(_time_t[time_t]); //Get current time in UTC - returns timestamp
native createtime(ts, _time_t[]); //Create time_T from timestamp
native gettimestamp(_time_t[]); //Convert time_t to timestamp
native difftime(_time_t1[], _time_t2[]); //Returns difference between two time_t structures as timestamp
native asctime(_time_t[], result[], size_res = sizeof(result)); //make a UTC time string from time_t
native strftime(_time_t[], format[], result[], size_res = sizeof(result)); //create time string with custom format
/*****************************************************************************************************************/
