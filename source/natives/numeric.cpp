/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Collection of useful numeric algorithms (mostly from C++ standard/template library along with addititional functions)
numeric.cpp

NOTES:
 - reduce not implemented
 - transform_reduce not implemented
 - inclusive_scan not implemented
 - exclusive_scan not implemented

*************************************************************************************************************/
#include "main.h"
#include "iscript.h"

#include "algorithm.h"
#include "functional.h"

#include <numeric>
#include <functional>
#include <vector>

namespace PLE::natives
{
	//native iota(range[], numcells, init, {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::increment);
	cell AMX_NATIVE_CALL numeric_iota(AMX *amx, cell params[])
	{
		cell* start = NULL;
		amx_GetAddr(amx, params[1], &start);

		cell* end = start + params[2];

		cell init = params[3];

		cell* func = NULL;
		amx_GetAddr(amx, params[4], &func);
		PLE::functional::function fid(func);
		func += 2;

		while (start != end)
		{
			*start = init;
			init = ExecuteFunctionC1(amx, fid, init);
			start++;
		}
		return true;
	}
	//native accumulate(range[], numcells, init, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
	cell AMX_NATIVE_CALL numeric_accumulate(AMX *amx, cell params[])
	{
		cell* start = NULL;
		amx_GetAddr(amx, params[1], &start);

		cell* end = start + params[2];

		cell init = params[3];

		cell* func = NULL;
		amx_GetAddr(amx, params[4], &func);
		PLE::functional::function fid(func);

		cell *pos = start;
		while (pos != end) 
		{
			init = ExecuteFunctionC2(amx, fid, init, *pos);
			pos++;
		}
		return init;
	}
	//native inner_product(range[], numcells, dest[], init, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::multiplies);
	cell AMX_NATIVE_CALL numeric_inner_product(AMX *amx, cell params[])
	{
		cell* start1 = NULL;
		amx_GetAddr(amx, params[1], &start1);

		cell* end1 = start1 + params[2];

		cell* start2 = NULL;
		amx_GetAddr(amx, params[3], &start2);

		cell init = params[4];

		cell* func1 = NULL;
		amx_GetAddr(amx, params[5], &func1);
		PLE::functional::function fid1(func1);

		cell* func2 = NULL;
		amx_GetAddr(amx, params[6], &func2);
		PLE::functional::function fid2(func2);

		cell *pos1 = start1, *pos2 = start2;
		while (pos1 != end1)
		{
			init = ExecuteFunctionC2(amx, fid1, init, ExecuteFunctionC2(amx, fid2, *pos1, *pos2));
			++pos1;
			++pos2;
		}
		return init;
	}
	//native adjacent_difference(range[], numcells, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::minus);
	cell AMX_NATIVE_CALL numeric_adjacent_difference(AMX *amx, cell params[])
	{
		cell* start1 = NULL;
		amx_GetAddr(amx, params[1], &start1);

		cell* end1 = start1 + params[2];

		cell* start2 = NULL;
		amx_GetAddr(amx, params[3], &start2);

		cell* func = NULL;
		amx_GetAddr(amx, params[4], &func);
		PLE::functional::function fid(func);

		return std::adjacent_difference(start1, end1, start2, [&amx, &fid](cell a, cell b) { return ExecuteFunctionC2(amx, fid, a, b); }) - start2;
	}
	//native partial_sum(range[], numcells, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
	cell AMX_NATIVE_CALL numeric_partial_sum(AMX *amx, cell params[])
	{
		cell* start1 = NULL;
		amx_GetAddr(amx, params[1], &start1);

		cell* end1 = start1 + params[2];

		cell* start2 = NULL;
		amx_GetAddr(amx, params[3], &start2);

		cell* func = NULL;
		amx_GetAddr(amx, params[4], &func);
		PLE::functional::function fid(func);

		if (start1 == end1) return 0;

		cell sum = *start1;
		*start2 = sum;

		cell *pos1 = start1, *pos2 = start2;
		while (++pos1 != end1)
		{
			sum = ExecuteFunctionC2(amx, fid, sum, *pos1);
			*++pos2 = sum;
		}
		return ++pos2 - start2;
	}
	//native gcd(x, y);
	cell AMX_NATIVE_CALL numeric_gcd(AMX *amx, cell params[])
	{		
		std::function<cell(cell, cell)> gcd = [&](cell x, cell y)
		{
			if (x < y) return gcd(y, x);
			int remainder = x % y;
			if (remainder == 0) return y;
			return gcd(y, remainder);
		};
		return gcd(params[1], params[2]);
	}
	//native lcm(x, y);
	cell AMX_NATIVE_CALL numeric_lcm(AMX *amx, cell params[])
	{
		std::function<cell(cell, cell)> gcd = [&](cell x, cell y)
		{
			if (x < y) return gcd(y, x);
			int remainder = x % y;
			if (remainder == 0) return y;
			return gcd(y, remainder);
		};
		return (params[1] * (params[2] / gcd(params[1], params[2])));
	}

	//reduce, exclusive_scan, inclusive_scan, transform_reduce, transform_exclusive_scan, transform_inclusive_form not implemented
}
