/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

bitset
bitset.cpp

TODO:
 - bitset_shift_left(bitset:bs[], shift)
 - bitset_shift_right(bitset:bs[], shift)

*************************************************************************************************************/
#include "main.h"
#include "bitset.h"
#include "functional.h"
#include <algorithm>
#include <cstdint>

namespace PLE::natives
{
	//native bitset_count(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_count(AMX *amx, cell params[])
	{
		static const uint8_t bcount_tlb256[256] =
		{
			#define B2(n) n,     n+1,     n+1,     n+2
			#define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
			#define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
			B6(0), B6(1), B6(1), B6(2)
		};

		error_if(!check_params(1), "[PLE] bitset>> bitset::count: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::count: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		size_t count = 0;
		while (bitset != end)
		{
			unsigned char *p = reinterpret_cast<unsigned char*>(bitset);
			#if BYTES_PER_CELL == 4
			count += bcount_tlb256[p[0]] +
				bcount_tlb256[p[1]] +
				bcount_tlb256[p[2]] +
				bcount_tlb256[p[3]];
			#endif
			#if BYTES_PER_CELL == 8
			count += bcount_tlb256[p[0]] +
				bcount_tlb256[p[1]] +
				bcount_tlb256[p[2]] +
				bcount_tlb256[p[3]];
				bcount_tlb256[p[4]] +
				bcount_tlb256[p[5]] +
				bcount_tlb256[p[6]] +
				bcount_tlb256[p[7]];
			#endif
			bitset++;
		}
		if (bits_last_cell)
			for (int i = 0; i < bits_last_cell; i++)
			{
				if (*bitset & (1 << i))
					count++;
			}
		return count;
	}
	//native bitset_size(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_size(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::size: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset;
		error_if(size < 0, "[PLE] bitset>> bitset::size: bitset size is less than zero.");

		return size;
	}
	//native bool:bitset_test(bitset:bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_test(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::test: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::test: bitset size is less than zero.");

		cell bitpos = params[2];
		if (bitpos >= size || bitpos < 0) return false;

		return !!(bitset[bitpos / BITS_PER_CELL] & (1 << (bitpos % BITS_PER_CELL)));
	}
	//native bool:bitset_any(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_any(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::any: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::any: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			if (*bitset++) return true;

		if (bits_last_cell)
			if (*bitset & ((1 << bits_last_cell) - 1))
				return true;

		return false;
	}
	//native bool:bitset_none(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_none(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::none: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::none: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			if (*bitset++) return false;

		if (bits_last_cell)
			if (*bitset & ((1 << bits_last_cell) - 1))
				return false;

		return true;
	}
	//native bool:bitset_all(bitset : bs[]);
	cell AMX_NATIVE_CALL bitset_all(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::all: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::all: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			if (*bitset++ != 0xFFFFFFFF) return false;

		if (bits_last_cell)
			if ((*bitset & ((1 << bits_last_cell) - 1)) != ((1 << bits_last_cell) - 1))
				return false;

		return true;
	}

	//native bool:bitset_set(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_set(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::set: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::set: bitset size is less than zero.");

		cell bitpos = params[2];
		if (bitpos >= size || bitpos < 0) return false;

		bitset[bitpos / BITS_PER_CELL] |= 1 << (bitpos % BITS_PER_CELL);
		return true;
	}
	//native bool:bitset_reset(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_reset(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::reset: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::reset: bitset size is less than zero.");

		cell bitpos = params[2];
		if (bitpos >= size || bitpos < 0) return false;

		bitset[bitpos / BITS_PER_CELL] &= ~(1 << (bitpos % BITS_PER_CELL));
		return true;
	}
	//native bool:bitset_flip(bitset : bs[], bitpos);
	cell AMX_NATIVE_CALL bitset_flip(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::flip: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::flip: bitset size is less than zero.");

		cell bitpos = params[2];
		if (bitpos >= size || bitpos < 0) return false;

		bitset[bitpos / BITS_PER_CELL] ^= 1 << (bitpos % BITS_PER_CELL);
		return true;
	}

	//native bool:bitset_set_all(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_set_all(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::set_all: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::set_all: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			*bitset++ = 0xFFFFFFFF;

		if (bits_last_cell)
			*bitset |= ((1 << bits_last_cell) - 1);
		return true;
	}
	//native bool:bitset_reset_all(bitset:bs[]);
	cell AMX_NATIVE_CALL bitset_reset_all(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::reset_all: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::reset_all: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			*bitset++ = 0;

		if (bits_last_cell)
			*bitset &= ~((1 << bits_last_cell) - 1);
		return true;
	}
	//native bool:bitset_flip_all(bitset:bs[]);	
	cell AMX_NATIVE_CALL bitset_flip_all(AMX *amx, cell params[])
	{
		error_if(!check_params(1), "[PLE] bitset>> bitset::flip_all: expected 1 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::flip_all: bitset size is less than zero.");

		cell *end = bitset + (size / BITS_PER_CELL);
		cell bits_last_cell = size % BITS_PER_CELL;

		while (bitset != end)
			*bitset = ~*bitset++;

		if (bits_last_cell)
			*bitset = (*bitset & ~((1 << bits_last_cell) - 1)) | (~*bitset & ((1 << bits_last_cell) - 1));
		return true;
	}

	//native noret:bitset_tostring(bitset:bs[], dest[], dest_size = sizeof(dest));
	cell AMX_NATIVE_CALL bitset_tostring(AMX *amx, cell params[])
	{
		error_if(!check_params(3), "[PLE] bitset>> bitset::tostring: expected 3 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::tostring: bitset size is less than zero.");

		cell *dest = NULL;
		amx_GetAddr(amx, params[2], &dest);

		cell *dest_end = dest + params[3];

		for (int i = 0; i < size; i++)
		{
			if (dest == dest_end)
			{
				*dest = 0;
				return false;
			}
			if (bitset[i / BITS_PER_CELL] & (1 << i))
				*dest++ = '1';
			else *dest++ = '0';
		}
		*dest = 0;
		return true;
	}

	//native noret:bitset_and(bitset:bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_and(AMX *amx, cell params[])
	{
		error_if(!check_params(3), "[PLE] bitset>> bitset::and: expected 3 parameters but found %d parameters.", get_params_count());

		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		error_if(size < 0, "[PLE] bitset>> bitset::and: bitset size is less than zero.");

		cell *end = bitset_dest + (size / BITS_PER_CELL);
		cell bits_last_cell = size % 32;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ & *bitset2++;

		if (bits_last_cell)
			*bitset_dest = (*bitset_dest & ~((1 << bits_last_cell) - 1)) | ((*bitset1 & *bitset2) & ((1 << bits_last_cell) - 1));
		return true;
	}
	//native noret:bitset_or(bitset : bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_or(AMX *amx, cell params[])
	{
		error_if(!check_params(3), "[PLE] bitset>> bitset::or: expected 3 parameters but found %d parameters.", get_params_count());

		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		error_if(size < 0, "[PLE] bitset>> bitset::or: bitset size is less than zero.");

		cell *end = bitset_dest + (size / BITS_PER_CELL);
		cell bits_last_cell = size % 32;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ | *bitset2++;

		if (bits_last_cell)
			*bitset_dest = (*bitset_dest & ~((1 << bits_last_cell) - 1)) | ((*bitset1 | *bitset2) & ((1 << bits_last_cell) - 1));
		return true;
	}
	//native noret:bitset_xor(bitset:bs1[], bitset : bs2[], bitset : dest[]);
	cell AMX_NATIVE_CALL bitset_xor(AMX *amx, cell params[])
	{
		error_if(!check_params(3), "[PLE] bitset>> bitset::xor: expected 3 parameters but found %d parameters.", get_params_count());

		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell *bitset_dest = NULL;
		amx_GetAddr(amx, params[3], &bitset_dest);

		cell size = std::min(*bitset_dest++, std::min(*bitset1++, *bitset2++));
		error_if(size < 0, "[PLE] bitset>> bitset::xor: bitset size is less than zero.");

		cell *end = bitset_dest + (size / BITS_PER_CELL);
		cell bits_last_cell = size % 32;

		while (bitset_dest != end)
			*bitset_dest++ = *bitset1++ ^ *bitset2++;

		if (bits_last_cell)
			*bitset_dest = (*bitset_dest & ~((1 << bits_last_cell) - 1)) | ((*bitset1 ^ *bitset2) & ((1 << bits_last_cell) - 1));
		return true;
	}
	//native bool:bitset_flip_all(bitset:bs[], shift);	

	//native bool:bitset_equal(bitset:bs1[], bitset : bs2[]);
	cell AMX_NATIVE_CALL bitset_equal(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::equal: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset1 = NULL;
		amx_GetAddr(amx, params[1], &bitset1);

		cell *bitset2 = NULL;
		amx_GetAddr(amx, params[2], &bitset2);

		cell size = std::min(*bitset1++, *bitset2++);
		error_if(size < 0, "[PLE] bitset>> bitset::equal: bitset size is less than zero.");

		cell *end1 = bitset1 + (size / BITS_PER_CELL);
		cell bits_last_cell = size % 32;

		while (bitset1 != end1)
			if (*bitset1++ != *bitset2++) return false;

		if (bits_last_cell)
			if ((*bitset1 & ((1 << bits_last_cell) - 1)) != (*bitset2 & ((1 << bits_last_cell) - 1)))
				return false;
		return true;
	}

	//native noret:bitset_foreach_set(bitset:bs[], { _, func_bool1, func_cell1 } : func[FTSIZE]);
	cell AMX_NATIVE_CALL bitset_foreach_set(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::foreach_set: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::foreach_set: bitset size is less than zero.");

		cell* func = NULL;
		amx_GetAddr(amx, params[2], &func);
		PLE::functional::function fid(func);
		error_if(!fid.IsValidFunctionID(1), "[PLE] bitset>> bitset::foreach_set: function object 'func' is not valid");

		for (int i = 0; i < size; i++)
		{
			if (bitset[i / BITS_PER_CELL] & (1 << (i%BITS_PER_CELL)))
				ExecuteFunctionC1(amx, fid, i);
		}
		return true;
	}
	//native noret:bitset_foreach_notset(bitset:bs[], { _, func_bool1, func_cell1 } : func[FTSIZE]);
	cell AMX_NATIVE_CALL bitset_foreach_notset(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::foreach_notset: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::foreach_notset: bitset size is less than zero.");

		cell* func = NULL;
		amx_GetAddr(amx, params[2], &func);
		PLE::functional::function fid(func);
		error_if(!fid.IsValidFunctionID(1), "[PLE] bitset>> bitset::foreach_set: function object 'func' is not valid");

		for (int i = 0; i < size; i++)
		{
			if (!(bitset[i / BITS_PER_CELL] & (1 << (i % BITS_PER_CELL))))
				ExecuteFunctionC1(amx, fid, i);
		}
		return true;
	}
	//native bool:bitset_find_set(bitset:bs[], &start_bitpos);	
	cell AMX_NATIVE_CALL bitset_find_set(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::find_set: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::find_set: bitset size is less than zero.");

		cell *idx = NULL;
		amx_GetAddr(amx, params[2], &idx);
		error_if(*idx < 0, "[PLE] bitset>> bitset::find_set: start_bitpos is less then zero.");
		error_if(*idx >= size, "[PLE] bitset>> bitset::find_set: start_bitpos is greater than the bitset size.");

		for (int i = *idx; i < size; i++)
		{
			if (bitset[i / BITS_PER_CELL] & (1 << (i % BITS_PER_CELL)))
			{
				*idx = i;
				return true;
			}
		}
		return false;
	}
	//native bool:bitset_find_notset(bitset:bs[], &start_bitpos);
	cell AMX_NATIVE_CALL bitset_find_notset(AMX *amx, cell params[])
	{
		error_if(!check_params(2), "[PLE] bitset>> bitset::find_notset: expected 2 parameters but found %d parameters.", get_params_count());

		cell *bitset = NULL;
		amx_GetAddr(amx, params[1], &bitset);

		cell size = *bitset++;
		error_if(size < 0, "[PLE] bitset>> bitset::find_notset: bitset size is less than zero.");

		cell *idx = NULL;
		amx_GetAddr(amx, params[2], &idx);
		error_if(*idx < 0, "[PLE] bitset>> bitset::find_notset: start_bitpos is less then zero.");
		error_if(*idx >= size, "[PLE] bitset>> bitset::find_notset: start_bitpos is greater than the bitset size.");

		for (int i = *idx; i < size; i++)
		{
			if (!(bitset[i / BITS_PER_CELL] & (1 << (i % BITS_PER_CELL))))
			{
				*idx = i;
				return true;
			}
		}
		return false;
	}
}