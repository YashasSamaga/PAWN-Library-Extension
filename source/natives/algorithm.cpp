/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Collection of useful algorithms (mostly from C++ standard/template library along with addititional functions)
algorithm.cpp

*************************************************************************************************************/
#include "..\main.h"
#include "algorithm.h"
/************************************************************************************************************/
cell strcmp4b(const cell* s1, const cell* s2) //strcmp for PAWN strings
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

namespace Natives
{
	cell AMX_NATIVE_CALL algo_ibsearch(AMX* amx, cell* params)
	{ 
		cell key = params[1];

		cell* arr = NULL;
		amx_GetAddr(amx, params[2], &arr);		

		cell* idx_addr = NULL;
		amx_GetAddr(amx, params[3], &idx_addr);

		size_t size = params[4];

		int low = 0, high = size - 1, mid = 0;
		while (low <= high)
		{
			mid = low + (high - low) / 2;
	
			if (arr[mid] > key)
				high = mid - 1;
			else if(arr[mid] < key)
				low = mid + 1;
			else
			{
				*idx_addr = mid;
				return true;
			}
		}
		return false;
	}
	cell AMX_NATIVE_CALL algo_fbsearch(AMX* amx, cell* params)
	{
		float key = amx_ctof(params[1]);

		cell* arr = NULL;
		amx_GetAddr(amx, params[2], &arr);

		cell* idx_addr = NULL;
		amx_GetAddr(amx, params[3], &idx_addr);

		size_t size = params[4];

		int low = 0, high = size - 1, mid = 0;
		while (low <= high)
		{
			mid = low + (high - low) / 2;

			if (amx_ctof(arr[mid]) > key)
				high = mid - 1;
			else if (amx_ctof(arr[mid]) < key)
				low = mid + 1;
			else
			{
				*idx_addr = mid;
				return true;
			}
		}
		return false;
	}
	cell AMX_NATIVE_CALL algo_sbsearch(AMX* amx, cell* params)
	{
		cell* search_str = NULL;
		amx_GetAddr(amx, params[1], &search_str);
		
		cell* source_arr = NULL;
		amx_GetAddr(amx, params[2], &source_arr);

		cell* idx = NULL;
		amx_GetAddr(amx, params[3], &idx);

		size_t size_major = static_cast<size_t>(params[4]);
		size_t size_minor = static_cast<size_t>(params[5]);

		source_arr += size_major - size_minor;

		int first = 0, last = size_major - 1, mid, result;

		while (first <= last) 
		{
			mid = (first + last)/2;	

			cell *str = source_arr + mid*size_minor;

			result = strcmp4b(str, search_str);

			if (result > 0) 
				last = mid - 1;
			else if (result < 0) 
				first = mid + 1;
			else 
			{
				*idx = mid;
				return true;
			}
		}		
		return false;
	}
}
