/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

"Custom" Time Library for PAWN (This is not a porting of C++ ctime library)
time.h

*************************************************************************************************************/
#include "main.h"
#include <chrono>
#include <ctime>

#ifndef PLE_CHRONO_H_INCLUDED
#define PLE_CHRONO_H_INCLUDED

namespace PLE
{
	namespace chrono
	{
		extern std::chrono::time_point<std::chrono::system_clock> syc_start;
		extern std::chrono::time_point<std::chrono::steady_clock> stc_start;

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
	}
	namespace natives
	{

	}
}



#endif /* PLE_CHRONO_H_INCLUDED */