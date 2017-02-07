/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

bitset
bitset.cpp

*************************************************************************************************************/
#include "main.h"
#include "bitset.h"
#include "functional.h"

#include <algorithm>
/************************************************************************************************************/
namespace Natives
{	
	//native std::bitset_count(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_count(AMX *amx, cell params[])
	{
		static const uint8_t bcount_tlb256[256] =
		{
			#define B2(n) n,     n+1,     n+1,     n+2
			#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
			#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
			B6(0), B6(1), B6(1), B6(2)
		};

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;

		cell *end = bitset + (size / 32 + 1);
		size_t count = 0;
		while(bitset != end)
		{
			uint8_t *p = (uint8_t*)bitset++;
			count += bcount_tlb256[p[0]] +
					 bcount_tlb256[p[1]] +
					 bcount_tlb256[p[2]] +
					 bcount_tlb256[p[3]];
		}
		return count;
	}
	//native std::bitset_size(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_size(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		return *bitset;
	}
	//native bool:std::bitset_test(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_test(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell bitpos = params[2];
		if (bitpos >= *bitset) return false;

		return !!(bitset[bitpos / 32 + 1] & 1 << (bitpos % 32));
	}
	//native bool:std::bitset_any(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_any(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		size_t cells = *bitset++ / 32 + 1;
		while (cells--)
		{
			if (*bitset++) return true;
		}
		return false;
	}
	//native bool:std::bitset_none(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_none(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		size_t cells = *bitset++ / 32 + 1;
		while (cells--)
			if (*bitset++) return false;

		return true;
	}
	//native bool:std::bitset_all(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_all(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		size_t cells = *bitset++ / 32 + 1;
		while (cells--)
			if (*bitset++ != 0xFFFFFFFF) return false;

		return true;
	}

	//native bool:std::bitset_set(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_set(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell bitpos = params[2];
		if (bitpos >= *bitset++) return false;

		bitset[bitpos / 32] |= 1 << (bitpos % 32);
		return true;
	}
	//native bool:std::bitset_reset(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_reset(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell bitpos = params[2];
		if (bitpos >= *bitset++) return false;

		bitset[bitpos / 32] &= ~(1<<(bitpos % 32));
		return true;
	}
	//native bool:std::bitset_flip(bitset : bs[], bitpos);	
	cell AMX_NATIVE_CALL bitset_flip(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell bitpos = params[2];
		if (bitpos >= *bitset++) return false;

		bitset[bitpos / 32] ^= 1 << (bitpos % 32);
		return true;
	}

	//native noret:std::bitset_tostring(bitset:bs[], dest[], dest_size = sizeof(dest));
	cell AMX_NATIVE_CALL bitset_tostring(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell *dest = NULL;
		amx_GetAddr(amx, params[2], &dest);	

		cell *dest_end = dest + params[3];

		cell size = *bitset++;
		for (int i = 0; i < size; i++)
		{
			if (dest == dest_end)
			{
				*dest = 0;
				return false;
			}				
			if (bitset[i / 32] & (1 << i))
				*dest++ = '1';
			else *dest++ = '0';
		}
		*dest = 0;
		return true;
	}

	//native noret:std::bitset_and(bitset:bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_and(AMX *amx, cell params[])
	{
		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		cell *end = bitset_dest + (size/32) + 1;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ & *bitset2++;
		return true;
	}
	//native noret:std::bitset_or(bitset : bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_or(AMX *amx, cell params[])
	{
		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		cell *end = bitset_dest + (size / 32) + 1;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ | *bitset2++;
		return true;
	}
	//native noret:std::bitset_xor(bitset:bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_xor(AMX *amx, cell params[])
	{
		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		cell *end = bitset_dest + (size / 32) + 1;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ ^ *bitset2++;
		return true;
	}

	//native bool:std::bitset_equal(bitset:bs1[], bitset : bs2[]);
	cell AMX_NATIVE_CALL bitset_equal(AMX *amx, cell params[])
	{
		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell size = std::min(*bitset1++, *bitset2++);
		cell *end1 = bitset1 + (size / 32) + 1;

		while (bitset1 != end1)
			if (*bitset1++ != *bitset2++) return false;
		return true;
	}

	//native noret:std::bitset_foreach_set(bitset:bs[], { _, func_bool1, func_cell1 } : func[FTSIZE]);
	cell AMX_NATIVE_CALL bitset_foreach_set(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;

		cell* func = NULL;
		amx_GetAddr(amx, params[2], &func);
		functionID fid(func);

		for (int i = 0; i < size; i++)
		{
			if (bitset[i/32] & (1 << (i%32)))
				ExecuteFunctionCC1O2(amx, &fid, i);
		}
		return true;
	}
	//native noret:std::bitset_foreach_notset(bitset:bs[], { _, func_bool1, func_cell1 } : func[FTSIZE]);
	cell AMX_NATIVE_CALL bitset_foreach_notset(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;

		cell* func = NULL;
		amx_GetAddr(amx, params[2], &func);
		functionID fid(func);

		for (int i = 0; i < size; i++)
		{
			if (!(bitset[i / 32] & (1 << (i % 32))))
				ExecuteFunctionCC1O2(amx, &fid, i);
		}
		return true;
	}
	//native bool:std::bitset_find_set(bitset:bs[], &start_bitpos);	
	cell AMX_NATIVE_CALL bitset_find_set(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell *idx = NULL;
		amx_GetAddr(amx, params[2], &idx);

		cell size = *bitset++;
		for (int i = *idx; i < size; i++)
		{
			if (bitset[i / 32] & (1 << (i % 32)))
			{
				*idx = i;
				return true;
			}
		}
		return false;
	}
	//native bool:std::bitset_find_notset(bitset:bs[], &start_bitpos);
	cell AMX_NATIVE_CALL bitset_find_notset(AMX *amx, cell params[])
	{
		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell *idx = NULL;
		amx_GetAddr(amx, params[2], &idx);

		cell size = *bitset++;
		for (int i = *idx; i < size; i++)
		{
			if (!(bitset[i / 32] & (1 << (i % 32))))
			{
				*idx = i;
				return true;
			}
		}
		return false;
	}
}