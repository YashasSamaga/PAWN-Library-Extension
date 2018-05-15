/*
** PAWN Library Extension (PLE)
**
** Chrono
** Time library
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

#if defined PLE_CHRONO_INCLUDED
	#endinput
#endif
#define PLE_CHRONO_INCLUDED

/* dependencies */
#include <PLE/config>

/*
** Timepoint:
** -----------
** timestamp_t
**  - stores a time point in real life time (as seconds)
**  - the epoch is implementation-defined (defined by the C++ standard library)
**  - can move forward/backward by adding/subtracting seconds
*/
/*
** Durations:
** -----------
** seconds_t
**  - primarily the difference between two timestamps
**  - stores number of seconds since a given epoch
**
** nanoseconds_t, microseconds_t, milliseconds_t
** - same as 'seconds_t' but with different time period
** - nanoseconds_t can measure time for at most 4.29 seconds
** - microseconds_t can measure time for at most 16.67 minutes
** - milliseconds_t can measure time for at most 24 days
*/

forward operator=(timestamp_t:x);
forward bool:operator!(timestamp_t:x);

forward timestamp_t:operator-(timestamp_t:x);
stock timestamp_t:operator++(timestamp_t:x)
	return timestamp_t:(_:x + 1);
stock timestamp_t:operator--(timestamp_t:x)
	return timestamp_t:(_:x - 1);

forward timestamp_t:operator+(timestamp_t:x, timestamp_t:y);
stock timestamp_t:operator+(timestamp_t:x, seconds_t:y)
	return timestamp_t:(_:x + y);
stock timestamp_t:operator+(timestamp_t:x, y)
	return timestamp_t:(_:x + y);

forward timestamp_t:operator-(timestamp_t:x, timestamp_t:y);
forward timestamp_t:operator-(seconds_t:x, timestamp_t:y);
forward timestamp_t:operator-(x, timestamp_t:y);
stock timestamp_t:operator-(timestamp_t:x, seconds_t:y);
	return timestamp_t:(_:x - y);
stock timestamp_t:operator-(timestamp_t:x, y);
	return timestamp_t:(_:x - y);

forward timestamp_t:operator*(timestamp_t:x, timestamp_t:y);
forward timestamp_t:operator*(timestamp_t:x, seconds_t:y);
forward timestamp_t:operator*(timestamp_t:x, y);

forward timestamp_t:operator/(timestamp_t:x, timestamp_t:y);
forward timestamp_t:operator/(seconds_t:x, timestamp_t:y);
forward timestamp_t:operator/(x, timestamp_t:y);
forward timestamp_t:operator/(timestamp_t:x, seconds_t:y);
forward timestamp_t:operator/(timestamp_t:x, y);

forward timestamp_t:operator%(timestamp_t:x, timestamp_t:y);
forward timestamp_t:operator%(seconds_t:x, timestamp_t:y);
forward timestamp_t:operator%(x, timestamp_t:y);
forward timestamp_t:operator%(timestamp_t:x, seconds_t:y);
forward timestamp_t:operator%(timestamp_t:x, y);

// unit conversion overloads not implemented
	
/*
** system_clock
** This clock directly maps to the operating system's clock.
**
** system_clock_now() returns a timestamp. The timestamp is the number of
** seconds from an implementation defined epoch. From C++20, system_clock
** measures Unix Time.
*/
native timestamp_t:system_clock_now();

/*
** steady_clock
** This represents a monotonic clock indepdent of the system clock. The time
** points of this clock is gaurnteed to never decrease unless there is an
** overflow.
**
** The epoch for this clock is the time of start of the "server process".
** returns the number of seconds since the epoch */
native seconds_t:steady_clock_now();

/*
** timespec_t structure
** stores point in time (or interval) broken down into seconds and nanoseconds
**
** ts_seconds - stores seconds (as interval or time point from epoch)
** ts_nanoseconds - stores nanosecond offset [0, 1'000'000'000)
*/
enum timespec_t
{
	seconds_t:ts_seconds,
	nanoseconds_t:ts_nanoseconds
}

native noret:timespec_get(ts[timespec_t]);
native noret:timespec_add(ts[timespec_t], seconds_t:seconds = 0, milliseconds_t:ms = 0, microseconds_t:us = 0, nanoseconds_t:ns = 0);
native noret:timespec_diff(const ts_start[timespec_t], const ts_end[timespec_t], ts_dest[timespec_t]);
native seconds_t:timespec_diff_as_seconds(const ts_start[timespec_t], const ts_end[timespec_t]);
native milliseconds_t:timespec_diff_as_milliseconds(const ts_start[timespec_t], const ts_end[timespec_t]);
native microseconds_t:timespec_diff_as_microseconds(const ts_start[timespec_t], const ts_end[timespec_t]);
native nanoseconds_t:timespec_diff_as_nanoseconds(const ts_start[timespec_t], const ts_end[timespec_t]);

/*
** datetime structure (tm_t)
** timestamps can be broken down into human readable structure
*/
/* broken down structure for time points */
enum tm_t
{
	tm_second = 0,
	tm_minute = 1,
	tm_hour = 2,
	tm_day = 3,
	tm_month = 4,
	tm_year = 5,
	tm_wday = 6, //0-6
	tm_yday = 7, //0-365
	tm_isdst = 8 //true if daylight saving time is in effect
}

/* builds the datetime structure representing UTC from the timestamp */
native noret:to_universal(timestamp_t:ts, tm[tm_t]);

/* builds the datetime structure representing local time from the timestamp */
native noret:to_local(timestamp_t:ts, tm[tm_t]);

/* reduces a local datetime structure to timestamp */
native timestamp_t:to_timestamp(const tm[tm_t]);


/*
** time difference between two tm_t structures
*/
native seconds_t:difftime(const tm1[tm_t], const tm2[tm_t]);

/*
** datetime strings
** tm_t structures can be convereted into strings
*/
/* format: Www Mmm dd hh:mm:ss yyyy\n */
native noret:asctime(const tm[tm_t], result[], size_res = sizeof(result));

/* TBA */
native strftime(const tm[tm_t], const format[], result[], size_res = sizeof(result));
