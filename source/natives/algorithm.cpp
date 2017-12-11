/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Collection of useful algorithms (mostly from C++ standard/template library along with some new ones)
algorithm.cpp

TODO:
 - sort strings
 - multi dimensional lexicographical sort
 - string insertion from an array of strings
 - string deletion from an array of strings
 - lower_bound and upper_bound for multi dimensional arrays

*************************************************************************************************************/
#include "main.h"
#include "iscript.h"
#include "utility.h"

#include "algorithm.h"
#include "functional.h"

#include <algorithm>
#include <functional>
#include <vector>
#include <random>
/************************************************************************************************************/
namespace PLE
{
	std::random_device algo_random_device;
	std::mt19937 algo_mt19937(algo_random_device());

	namespace natives
	{
		//native bool:ibsearch(key, array[], &idx, size = sizeof(array));
		cell AMX_NATIVE_CALL algo_ibsearch(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> ibsearch: expected 4 parameters but found %d parameters.", get_params_count());

			cell key = params[1];

			cell* arr = NULL;
			amx_GetAddr(amx, params[2], &arr);

			cell* idx_addr = NULL;
			amx_GetAddr(amx, params[3], &idx_addr);

			size_t size = params[4];
			error_if(size < 0, "[PLE] algorithm>> ibsearch: 'size' parameter (%d) below zero", size);

			int low = 0, high = size - 1, mid = 0;
			while (low <= high)
			{
				mid = low + (high - low) / 2;

				if (arr[mid] > key)
					high = mid - 1;
				else if (arr[mid] < key)
					low = mid + 1;
				else
				{
					*idx_addr = mid;
					return true;
				}
			}
			return false;
		}
		//native bool:fbsearch(Float:key, Float:array[], &idx, Float:error = 0.01, size = sizeof(array));
		cell AMX_NATIVE_CALL algo_fbsearch(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> fbsearch: expected 5 parameters but found %d parameters.", get_params_count());

			float key = amx_ctof(params[1]);

			cell* arr = NULL;
			amx_GetAddr(amx, params[2], &arr);

			cell* idx_addr = NULL;
			amx_GetAddr(amx, params[3], &idx_addr);

			float error = amx_ctof(params[4]);
			error_if(error < 0.0, "[PLE] algorithm>> fbsearch: 'error' parameter (%f) below zero", error);

			float key_lower = key - error;
			float key_upper = key + error;

			size_t size = params[5];
			error_if(size < 0, "[PLE] algorithm>> fbsearch: 'size' parameter (%d) below zero", size);

			int low = 0, high = size - 1, mid = 0;
			while (low <= high)
			{
				mid = low + (high - low) / 2;

				if (key_lower < amx_ctof(arr[mid]) && key_upper > amx_ctof(arr[mid]))
				{
					*idx_addr = mid;
					return true;
				}
				else if (amx_ctof(arr[mid]) > key)
					high = mid - 1;
				else
					low = mid + 1;
			}
			return false;
		}
		//native bool:sbsearch(search[], source[][], &idx, size_major = sizeof(source), size_minor = sizeof(source[]));
		cell AMX_NATIVE_CALL algo_sbsearch(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> sbsearch: expected 5 parameters but found %d parameters.", get_params_count());

			cell* search_str = NULL;
			amx_GetAddr(amx, params[1], &search_str);

			cell* source_arr = NULL;
			amx_GetAddr(amx, params[2], &source_arr);

			cell* idx = NULL;
			amx_GetAddr(amx, params[3], &idx);

			size_t size_major = static_cast<size_t>(params[4]);
			error_if(size_major < 0, "[PLE] algorithm>> sbsearch: 'size_major' parameter (%d) below zero", size_major);

			size_t size_minor = static_cast<size_t>(params[5]);
			error_if(size_minor < 0, "[PLE] algorithm>> sbsearch: 'size_minor' parameter (%d) below zero", size_minor);

			source_arr += size_major - size_minor;

			int first = 0, last = size_major - 1, mid, result;
			while (first <= last)
			{
				mid = (first + last) / 2;

				cell *str = source_arr + mid*size_minor;

				result = Utility::strcmp4b(str, search_str);

				if (result > 0)
					last = mid - 1;
				else if (result < 0)
					first = mid + 1;
				else
				{
					*idx = mid - 1;
					return true;
				}
			}
			return false;
		}

		//native bool:all_of(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_all_of(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> all_of: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> all_of: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);

			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> all_of: function object 'func' is not valid");

			while (start != end)
			{
				if (!ExecuteFunctionC1(amx, fid, *start)) return false;
				start++;
			}
			return true;
		}
		//native bool:any_of(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_any_of(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> any_of: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> any_of: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> any_of: function object 'func' is not valid");

			while (start != end)
			{
				if (ExecuteFunctionC1(amx, fid, *start)) return true;
				start++;
			}
			return false;
		}
		//native bool:none_of(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_none_of(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> none_of: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> none_of: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> none_of: function object 'func' is not valid");

			while (start != end)
			{
				if (ExecuteFunctionC1(amx, fid, *start)) return false;
				start++;
			}
			return true;
		}
		//native noret:for_each(range[], numcells, func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_for_each(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> for_each: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> for_each: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> for_each: function object 'func' is not valid");

			while (start != end)
			{
				ExecuteFunctionC1(amx, fid, *start);
				start++;
			}
			return true;
		}
		//native find(range[], numcells, search_value);
		cell AMX_NATIVE_CALL algo_find(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> find: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> find: 'numcells' parameter (%d) below zero", params[2]);

			cell value = params[3];

			cell* pos = start;
			while (pos != end)
			{
				if (*pos == value) return pos - start;
				pos++;
			}
			return params[2];
		}
		//native find_if(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_find_if(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> find_if: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> find_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> find_if: function object 'func' is not valid");

			cell *pos = start;
			while (pos != end)
			{
				if (ExecuteFunctionC1(amx, fid, *pos)) return pos - start;
				pos++;
			}
			return params[2];
		}
		//native find_if_not(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_find_if_not(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> find_if_not: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);

			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> find_if_not: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> find_if_not: function object 'func' is not valid");

			cell *pos = start;
			while (pos != end)
			{
				if (!ExecuteFunctionC1(amx, fid, *pos)) return pos - start;
				pos++;
			}
			return false;
		}
		//native find_end(range1[], numcells1, range2[], numcells2, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_find_end(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> find_end: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> find_end: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> find_end: 'numcells2' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> find_end: function object 'func' is not valid");

			if (start2 == end2) return params[2];

			cell *ret = end1, *pos1 = start1;
			while (pos1 != end1)
			{
				cell *it1 = pos1, *it2 = start2;
				while (ExecuteFunctionC2(amx, fid, *it1, *it2))
				{
					it1++;
					it2++;
					if (it2 == end2)
					{
						ret = pos1;
						break;
					}
					if (it1 == end1) return ret - start1;
				}
				pos1++;
			}
			return ret - start1;
		}
		//native find_first_of(range1[], numcells1, range2[], numcells2, {func_bool2, func_cell2, _}:func[FTSIZE]) = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_find_first_of(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> find_first_of: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> find_first_of: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> find_first_of: 'numcells2' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> find_first_of: function object 'func' is not valid");

			if (start2 == end2) return params[2];

			cell *pos = start1;
			while (pos != end1)
			{
				for (cell* it = start2; it != end2; ++it)
				{
					if (ExecuteFunctionC2(amx, fid, *it, *pos))
						return pos - start1;
				}
				pos++;
			}
			return params[2];
		}
		//native adjacent_find(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_adjacent_find(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> adjacent_find: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> adjacent_find: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> adjacent_find: function object 'func' is not valid");

			cell* pos = start;
			if (pos != end)
			{
				cell *next = pos + 1;
				while (next != end)
				{
					if (ExecuteFunctionC2(amx, fid, *pos, *next))
						return pos - start;
					++pos;
					++next;
				}
			}
			return params[2];
		}
		//native count(range[], numcells, value);
		cell AMX_NATIVE_CALL algo_count(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> count: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> count: 'numcells' parameter (%d) below zero", params[2]);

			cell value = params[3];

			int count = 0;
			while (start != end)
				if (*start++ == value) count++;

			return count;
		}
		//native count_if(range[], numcells, { func_bool1, func_cell1, _ }:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_count_if(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> count_if: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> count_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> count_if: function object 'func' is not valid");

			int count = 0;
			while (start != end)
			{
				if (ExecuteFunctionC1(amx, fid, *start)) count++;
				start++;
			}
			return count;
		}
		//native mismatch(range1[], numcells1, range2[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_mismatch(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> mismatch: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> mismatch: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> mismatch: function object 'func' is not valid");

			cell *pos1 = start1, *pos2 = start2;
			while ((pos1 != end1) && ExecuteFunctionC2(amx, fid, *pos1, *pos2))
			{
				++pos1;
				++pos2;
			}
			return pos1 - start1;
		}
		//native bool:equal(range1[], numcells1, range2[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_equal(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> equal: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> equal: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> equal: function object 'func' is not valid");

			cell *pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				if (!ExecuteFunctionC2(amx, fid, *pos1, *pos2)) return false;
				++pos1;
				++pos2;
			}
			return true;
		}
		//native bool:is_permutation(range1[], numcells1, range2[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_is_permutation(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> is_permutation: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> is_permutation: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> is_permutation: function object 'func' is not valid");

			return std::is_permutation(start1, end1, start2, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
		//native search(range1[], numcells1, range2[], numcells2, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_search(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> search: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> search: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> search: 'numcells2' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> search: function object 'func' is not valid");

			return std::search(start1, end1, start2, end2, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - start1;
		}
		//native search_n(range[], numcells, n, value, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_search_n(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> search_n: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> search_n: 'numcells' parameter (%d) below zero", params[2]);

			cell n = params[3];
			error_if(n < 0, "[PLE] algorithm>> search_n: 'n' parameter (%d) below zero", n);

			cell val = params[4];

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> search_n: function object 'func' is not valid");

			return std::search_n(start, end, n, val, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - start;
		}

		//native noret:copy(source[], numcells, dest[]);
		cell AMX_NATIVE_CALL algo_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> copy: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			std::copy(start1, end1, start2);
			return true;
		}
		//native noret:copy_if(source[], numcells, dest[], {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_copy_if(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> copy_if: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> copy_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> copy_if: function object 'func' is not valid");

			std::copy_if(start1, end1, start2, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x);  });
			return true;
		}
		//native noret:copy_backward(source[], numcells, dest_end[]);
		cell AMX_NATIVE_CALL algo_copy_backward(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> copy_backward: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> copy_backward: 'numcells' parameter (%d) below zero", params[2]);

			cell* end2 = NULL;
			amx_GetAddr(amx, params[3], &end2);

			std::copy_backward(start1, end1, end2 + 1);
			return true;
		}

		//native noret:swap(&val1, &val2);
		cell AMX_NATIVE_CALL algo_swap(AMX* amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] algorithm>> swap: expected 2 parameters but found %d parameters.", get_params_count());

			cell* val1 = NULL;
			amx_GetAddr(amx, params[1], &val1);

			cell* val2 = NULL;
			amx_GetAddr(amx, params[2], &val2);

			cell tmp = *val1;
			*val1 = *val2;
			*val2 = tmp;
			return true;
		}
		//native noret:swap_ranges(range1[], numcells1, range2[]);
		cell AMX_NATIVE_CALL algo_swap_ranges(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> swap_ranges: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> swap_ranges: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			std::swap_ranges(start1, end1, start2);
			return true;
		}
		//native noret:transform(range[], numcells, dest[], {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_transform(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> transform: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> transform: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> transform: function object 'func' is not valid");

			cell* pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				*pos2 = ExecuteFunctionC1(amx, fid, *pos1);
				++pos2;
				++pos1;
			}
			return true;
		}
		//native noret:transform2(range1[], numcells1, range2[], dest[], {func_bool2, func_cell2, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_transform2(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> transform2: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> transform2: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* start3 = NULL;
			amx_GetAddr(amx, params[4], &start3);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> transform2: function object 'func' is not valid");

			cell* pos1 = start1, *pos2 = start2, *pos3 = start3;
			while (pos1 != end1)
			{
				*pos3 = ExecuteFunctionC2(amx, fid, *pos1, *pos2);
				++pos3;
				++pos2;
				++pos1;
			}
			return true;
		}
		//native replace(range[], numcells, search_value, replace_value);
		cell AMX_NATIVE_CALL algo_replace(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> replace: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> replace: 'numcells' parameter (%d) below zero", params[2]);

			cell search_value = params[3];
			cell replace_value = params[4];

			int count = 0;
			while (start != end)
			{
				if (*start == search_value)
				{
					*start = replace_value;
					count++;
				}
				start++;
			}
			return count;
		}
		//native replace_if(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE], replace_value);
		cell AMX_NATIVE_CALL algo_replace_if(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> replace_if: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> replace_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> replace_if: function object 'func' is not valid");

			cell replace_value = params[4];

			int count = 0;
			while (start != end)
			{
				if (ExecuteFunctionC1(amx, fid, *start))
				{
					*start = replace_value;
					count++;
				}
				start++;
			}
			return count;
		}
		//native replace_copy(range[], numcells, dest[], search_value, replace_value);
		cell AMX_NATIVE_CALL algo_replace_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> replace_copy: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> replace_copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell search_value = params[4];
			cell replace_value = params[5];

			int count = 0;
			cell* pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				if (*pos1 == search_value)
				{
					*pos2 = replace_value;
					count++;
				}
				else *pos2 = *pos1;

				pos1++;
				pos2++;
			}
			return count;
		}
		//native replace_copy_if(range[], numcells, dest[], {func_bool1, func_cell1, _}:func[FTSIZE], replace_value);
		cell AMX_NATIVE_CALL algo_replace_copy_if(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> replace_copy_if: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> replace_copy_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> copy_if: function object 'func' is not valid");

			cell replace_value = params[5];

			int count = 0;
			cell* pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				if (ExecuteFunctionC1(amx, fid, *pos1))
				{
					*pos2 = replace_value;
					count++;
				}
				else *pos2 = *pos1;

				pos1++;
				pos2++;
			}
			return count;
		}
		//native notret:fill(range[], numcells, value);
		cell AMX_NATIVE_CALL algo_fill(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> fill: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> fill: 'numcells' parameter (%d) below zero", params[2]);

			cell fill_value = params[3];

			while (start != end)
			{
				*start = fill_value;
				start++;
			}
			return true;
		}
		//fill_n = fill
		//native noret:generate(range[], numcells, {func_bool0, func_cell0, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_generate(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> generate: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> generate: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(0), "[PLE] algorithm>> generate: function object 'func' is not valid");

			while (start != end)
			{
				*start = ExecuteFunctionC0(amx, fid);
				start++;
			}
			return true;
		}
		//generate_n = generate
		//native remove(range[], numcells, value);
		cell AMX_NATIVE_CALL algo_remove(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> remove: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> remove: 'numcells' parameter (%d) below zero", params[2]);

			cell value = params[3];

			return std::remove(start, end, value) - start;
		}
		//native remove_if(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_remove_if(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> remove_if: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> remove_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> remove_if: function object 'func' is not valid");

			return std::remove_if(start, end, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); }) - start;
		}
		//native remove_copy(range[], numcells, dest[], value);
		cell AMX_NATIVE_CALL algo_remove_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> remove_copy: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> remove_copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell value = params[4];

			cell* pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				if (*pos1 != value)
				{
					*pos2 = *pos1;
					pos2++;
				}
				pos1++;
			}
			return pos2 - start2;
		}
		//native remove_copy_if(range[], numcells, dest[], {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_remove_copy_if(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> remove_copy_if: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> remove_copy_if: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> copy_if: function object 'func' is not valid");

			cell* pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				if (!ExecuteFunctionC1(amx, fid, *pos1))
				{
					*pos2 = *pos1;
					pos2++;
				}
				pos1++;
			}
			return pos2 - start2;
		}
		//native unique(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_unique(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> unique: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> unique: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> unique: function object 'func' is not valid");

			return std::unique(start, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y);  }) - start;
		}
		//native unique_copy(range[], numcells, dest[], {func_bool1, func_cell1, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_unique_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> unique_copy: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> unique_copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> unique_copy: function object 'func' is not valid");

			if (start1 == end1) return 0;

			cell *pos1 = start1, *pos2 = start2;
			*pos2 = *start1;
			while (++pos1 != end1)
			{
				if (!ExecuteFunctionC2(amx, fid, *pos2, *pos1))
				{
					pos2++;
					*pos2 = *pos1;
				}
			}
			return pos2 - start2 + 1;
		}
		//native noret:reverse(range[], numcells);
		cell AMX_NATIVE_CALL algo_reverse(AMX* amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] algorithm>> reverse: expected 2 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> reverse: 'numcells' parameter (%d) below zero", params[2]);

			while ((start != end) && (start != --end))
			{
				cell val = *start;
				*start = *end;
				*end = val;
				++start;
			}
			return true;
		}
		//native noret:reverse_copy(range[], numcells, dest[]);
		cell AMX_NATIVE_CALL algo_reverse_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> reverse_copy: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> reverse_copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell *pos1 = start1, *pos2 = start2;
			while (pos1 != end1)
			{
				--end1;
				*pos2 = *end1;
				++pos2;
			}
			return true;
		}
		//native noret:rotate(range[], middle, end);
		cell AMX_NATIVE_CALL algo_rotate(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> rotate: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* middle = start + params[2];
			error_if(middle < start, "[PLE] algorithm>> rotate: 'middle' parameter (%d) below zero", params[2]);
			cell* end = start + params[3];
			error_if(end < start, "[PLE] algorithm>> rotate: 'end' parameter (%d) below zero", params[3]);

			error_if(end < middle, "[PLE] algorithm>> rotate: 'middle' parameter (%d) is more than 'end' parameter (%d)", params[2], params[3]);

			std::rotate(start, middle, end);
			return true;
		}
		//native noret:rotate_copy(range[], middle, end, dest[]);
		cell AMX_NATIVE_CALL algo_rotate_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> rotate_copy: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* middle1 = start1 + params[2];
			error_if(middle1 < start1, "[PLE] algorithm>> rotate_copy: 'middle' parameter (%d) below zero", params[2]);
			cell* end1 = start1 + params[3];
			error_if(end1 < start1, "[PLE] algorithm>> rotate_copy: 'end' parameter (%d) below zero", params[3]);

			error_if(end1 < middle1, "[PLE] algorithm>> rotate_copy: 'middle' parameter (%d) is more than 'end' parameter (%d)", params[2], params[3]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[4], &start2);

			std::rotate_copy(start1, middle1, end1, start2);
			return true;
		}
		//native noret:shuffle(range[], end);
		cell AMX_NATIVE_CALL algo_shuffle(AMX* amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] algorithm>> shuffle: expected 2 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> shuffle: 'end' parameter (%d) below zero", params[2]);

			std::shuffle(start, end, algo_mt19937);
			return true;
		}
		//sample not implemented

		//native bool:is_partitioned(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_is_partitioned(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> is_partitioned: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> is_partitioned: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> is_partitioned: function object 'func' is not valid");

			return std::is_partitioned(start, end, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); });
		}
		//native partition(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_partition(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> partition: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> partition: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> partition: function object 'func' is not valid");

			return std::partition(start, end, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); }) - start;
		}
		//native stable_partition(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_stable_partition(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> stable_partition: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> stable_partition: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> stable_partition: function object 'func' is not valid");

			return std::stable_partition(start, end, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); }) - start;
		}
		//native noret:partition_copy(range[], numcells, dest1[], dest2[], {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_partition_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> partition_copy: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> partition_copy: 'numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);

			cell* start3 = NULL;
			amx_GetAddr(amx, params[4], &start3);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> partition_copy: function object 'func' is not valid");

			std::partition_copy(start1, end1, start2, start3, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); });
			return true;
		}
		//native partition_point(range[], numcells, {func_bool1, func_cell1, _}:func[FTSIZE]);
		cell AMX_NATIVE_CALL algo_partition_point(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> partition_point: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> partition_point: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(1), "[PLE] algorithm>> partition_point: function object 'func' is not valid");

			return std::partition_point(start, end, [&amx, &fid, &func](cell x) { return ExecuteFunctionC1(amx, fid, x); }) - start;
		}

		//native noret:sort(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_sort(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> sort: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> sort: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> sort: function object 'func' is not valid");

			std::sort(start, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
			return true;
		}
		//native noret:sort(range[], middle, end, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_partial_sort(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> partial_sort: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* middle = start + params[2];
			error_if(middle < start, "[PLE] algorithm>> partial_sort:'middle' parameter (%d) below zero", params[2]);
			cell* end = start + params[3];
			error_if(end < start, "[PLE] algorithm>> partial_sort: 'end' parameter (%d) below zero", params[3]);

			error_if(end < middle, "[PLE] algorithm>> partial_sort: 'middle' parameter (%d) is more than end parameter (%d)", params[2], params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> partial_sort: function object 'func' is not valid");

			std::partial_sort(start, middle, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
			return true;
		}
		//native partial_sort_copy(range[], range_numcells, dest[], dest_numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_partial_sort_copy(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> partial_sort_copy: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> partial_sort_copy: 'range_numcells' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> partial_sort_copy: 'dest_numcells' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> partial_sort_copy: function object 'func' is not valid");

			return std::partial_sort_copy(start1, end1, start2, end2, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - start2;
		}
		//native bool:is_sorted(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_is_sorted(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> is_sorted: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> is_sorted: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> is_sorted: function object 'func' is not valid");

			return std::is_sorted(start, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
		//native noret:nth_element(range[], nth, end, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_nth_element(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> nth_element: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* nth = start + params[2];
			error_if(nth < start, "[PLE] algorithm>> nth_element: 'nth' parameter (%d) below zero", params[2]);
			cell* end = start + params[3];
			error_if(end < start, "[PLE] algorithm>> nth_element: 'end' parameter (%d) below zero", params[3]);

			error_if((end < nth), "[PLE] algorithm>> nth_element: 'nth' parameter (%d) is more than or equal to 'end' parameter (%d)", params[2], params[3]);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> nth_element: function object 'func' is not valid");

			std::nth_element(start, nth, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
			return true;
		}

		//native lower_bound(range[], numcells, value, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_lower_bound(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> lower_bound: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> lower_bound: 'numcells' parameter (%d) below zero", params[2]);

			cell val = params[3];

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> lower_bound: function object 'func' is not valid");

			return std::lower_bound(start, end, val, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - start;
		}
		//native upper_bound(range[], numcells, value, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_upper_bound(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> upper_bound: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> upper_bound: 'numcells' parameter (%d) below zero", params[2]);

			cell val = params[3];

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> upper_bound: function object 'func' is not valid");

			return std::upper_bound(start, end, val, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - start;
		}
		//native noret:equal_range(range[], numcells, value, &smallest, &largest, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_equal_range(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> equal_range: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> equal_range: 'numcells' parameter (%d) below zero", params[2]);

			cell value = params[3];

			cell* smallest_addr = NULL;
			amx_GetAddr(amx, params[4], &smallest_addr);

			cell* largest_addr = NULL;
			amx_GetAddr(amx, params[5], &largest_addr);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> equal_range: function object 'func' is not valid");

			auto pr = std::equal_range(start, end, value, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });

			*smallest_addr = pr.first - start;
			*largest_addr = pr.second - start;
			return true;
		}
		//native bool:binary_search(range[], numcells, value, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_binary_search(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> binary_search: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> binary_search: 'numcells' parameter (%d) below zero", params[2]);

			cell val = params[3];

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> binary_search: function object 'func' is not valid");

			return std::binary_search(start, end, val, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}

		//native merge(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_merge(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> merge: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> merge: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> merge: 'numcells2' parameter (%d) below zero", params[4]);

			cell* result = NULL;
			amx_GetAddr(amx, params[5], &result);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> merge: function object 'func' is not valid");

			return std::merge(start1, end1, start2, end2, result, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - result;
		}
		//native noret:inplace_merge(range[], middle, end, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_inplace_merge(AMX* amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] algorithm>> inplace_merge: expected 4 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* middle = start + params[2];
			error_if(middle < start, "[PLE] algorithm>> inplace_merge: 'middle' parameter (%d) below zero", params[2]);
			cell* end = start + params[3];
			error_if(end < start, "[PLE] algorithm>> inplace_merge: 'end' parameter (%d) below zero", params[4]);

			error_if((end < middle), "[PLE] algorithm>> inplace_merge: 'middle' parameter (%d) is more than or equal to 'end' parameter (%d)", params[2], params[3]);

			cell* func = NULL;
			amx_GetAddr(amx, params[4], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> inplace_merge: function object 'func' is not valid");

			std::inplace_merge(start, middle, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
			return true;
		}
		//native bool:includes(range1[], numcells1, range2[], numcells2, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::equal_to);
		cell AMX_NATIVE_CALL algo_includes(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> includes: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> includes: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> includes: 'numcells2' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> includes: function object 'func' is not valid");

			return std::includes(start1, end1, start2, end2, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
		//native set_union(range1[], numcells1, range2[], numcells2, dest[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_set_union(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> set_union: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> set_union: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> set_union: 'numcells2' parameter (%d) below zero", params[4]);

			cell* result = NULL;
			amx_GetAddr(amx, params[5], &result);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> set_union: function object 'func' is not valid");

			return std::set_union(start1, end1, start2, end2, result, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - result;
		}
		//native set_intersection(range1[], numcells1, range2[], numcells2, dest[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_set_intersection(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> set_intersection: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> set_intersection: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> set_intersection: 'numcells2' parameter (%d) below zero", params[4]);

			cell* result = NULL;
			amx_GetAddr(amx, params[5], &result);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> set_intersection: function object 'func' is not valid");

			return std::set_intersection(start1, end1, start2, end2, result, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - result;
		}
		//native set_difference(range1[], numcells1, range2[], numcells2, dest[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_set_difference(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> set_difference: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> set_difference: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> set_difference: 'numcells2' parameter (%d) below zero", params[4]);

			cell* result = NULL;
			amx_GetAddr(amx, params[5], &result);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> set_difference: function object 'func' is not valid");

			return std::set_difference(start1, end1, start2, end2, result, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - result;
		}
		//native set_symmetric_difference(range1[], numcells1, range2[], numcells2, dest[], {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_set_symmetric_difference(AMX* amx, cell* params)
		{
			error_if(!check_params(6), "[PLE] algorithm>> set_symmetric_difference: expected 6 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> set_symmetric_difference: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> set_symmetric_difference: 'numcells2' parameter (%d) below zero", params[4]);

			cell* result = NULL;
			amx_GetAddr(amx, params[5], &result);

			cell* func = NULL;
			amx_GetAddr(amx, params[6], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> set_symmetric_difference: function object 'func' is not valid");

			return std::set_symmetric_difference(start1, end1, start2, end2, result, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); }) - result;
		}

		//push_heap, pop_heap, make_heap, sort_heap, is_heap, is_heap_until not implemented

		//min, max already implemented
		//minmax not implemented
		//clamp already implemented
		//native noret:minmax_element(range[], numcells, &smallest, &largest, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_minmax_element(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> minmax_element: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> minmax_element: 'numcells' parameter (%d) below zero", params[2]);

			cell* smallest_addr = NULL;
			amx_GetAddr(amx, params[3], &smallest_addr);

			cell* largest_addr = NULL;
			amx_GetAddr(amx, params[4], &largest_addr);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> minxmax_element: function object 'func' is not valid");

			cell *smallest = start, *largest = start, *pos = start;
			while (pos != end)
			{
				if (ExecuteFunctionC2(amx, fid, *pos, *smallest))	smallest = pos;
				if (ExecuteFunctionC2(amx, fid, *largest, *pos))	largest = pos;
				pos++;
			}
			*smallest_addr = smallest - start;
			*largest_addr = largest - start;
			return true;
		}
		//native min_element(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_min_element(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> min_element: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> min_element: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> min_element: function object 'func' is not valid");

			cell *pos = start, *smallest = start;
			while (pos != end)
			{
				if (ExecuteFunctionC2(amx, fid, *pos, *smallest))	smallest = pos;
				pos++;
			}
			return smallest - start;
		}
		//native max_element(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_max_element(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> max_element: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> max_element: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> max_element: function object 'func' is not valid");

			cell *pos = start, *largest = start;
			while (pos != end)
			{
				if (ExecuteFunctionC2(amx, fid, *largest, *pos))	largest = pos;
				pos++;
			}
			return largest - start;
		}

		//native bool:lexicographical_compare(range1[], numcells1, range2[], numcells2, {func_bool2, func_cell2, _}:func[FTSIZE]) = fixed_functions::less;
		cell AMX_NATIVE_CALL algo_lexicographical_compare(AMX* amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] algorithm>> lexicographical_compare: expected 5 parameters but found %d parameters.", get_params_count());

			cell* start1 = NULL;
			amx_GetAddr(amx, params[1], &start1);
			cell* end1 = start1 + params[2];
			error_if(end1 < start1, "[PLE] algorithm>> lexicographical_compare: 'numcells1' parameter (%d) below zero", params[2]);

			cell* start2 = NULL;
			amx_GetAddr(amx, params[3], &start2);
			cell* end2 = start2 + params[4];
			error_if(end2 < start2, "[PLE] algorithm>> lexicographical_compare: 'numcells2' parameter (%d) below zero", params[4]);

			cell* func = NULL;
			amx_GetAddr(amx, params[5], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> lexicographical_compare: function object 'func' is not valid");

			return std::lexicographical_compare(start1, end1, start2, end2, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
		//native bool:prev_permutation(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_next_permutation(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> next_permutation: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> prev_permutation: 'numcells' parameter (%d) below zero", params[2]);

			cell* func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> next_permutation: function object 'func' is not valid");

			return std::next_permutation(start, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
		//native bool:next_permutation(range[], numcells, {func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
		cell AMX_NATIVE_CALL algo_prev_permutation(AMX* amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] algorithm>> prev_permutation: expected 3 parameters but found %d parameters.", get_params_count());

			cell* start = NULL;
			amx_GetAddr(amx, params[1], &start);
			cell* end = start + params[2];
			error_if(end < start, "[PLE] algorithm>> prev_permutation: 'numcells' parameter (%d) below zero", params[2]);

			cell *func = NULL;
			amx_GetAddr(amx, params[3], &func);
			PLE::functional::function fid(func);
			error_if(!fid.IsValidFunctionID(2), "[PLE] algorithm>> prev_permutation: function object 'func' is not valid");

			return std::prev_permutation(start, end, [&amx, &fid](cell x, cell y) { return ExecuteFunctionC2(amx, fid, x, y); });
		}
	}
}