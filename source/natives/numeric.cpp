/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Collection of useful numeric algorithms (mostly from C++ standard/template library along with addititional functions)
numeric.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"

#include "algorithm.h"
#include "functional.h"

#include <numeric>
#include <functional>
#include <vector>
/************************************************************************************************************/
namespace Natives
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
		functionID fid(func);
		func += 2;

		while (start != end)
		{
			*start = init;
			init = ExecuteFunctionCC1O2(amx, &fid, init);
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
		functionID fid(func);

		cell *pos = start;
		while (pos != end) 
		{
			init = ExecuteFunctionCC1C2(amx, &fid, init, *pos);
			pos++;
		}
		return init;
	}
	//reduce not implemented
	//transform_reduce not implemented
	//inclusive_scan not implemented
	//exclusive_scan not implemented
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
		functionID fid1(func1);

		cell* func2 = NULL;
		amx_GetAddr(amx, params[6], &func2);
		functionID fid2(func2);

		cell *pos1 = start1, *pos2 = start2;
		while (pos1 != end1)
		{
			init = ExecuteFunctionCC1C2(amx, &fid1, init, ExecuteFunctionCC1C2(amx, &fid2, *pos1, *pos2));
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
		functionID fid(func);

		return std::adjacent_difference(start1, end1, start2, [&amx, &fid](cell a, cell b) { return ExecuteFunctionCC1C2(amx, &fid, a, b); }) - start2;
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
		functionID fid(func);

		if (start1 == end1) return 0;

		cell sum = *start1;
		*start2 = sum;

		cell *pos1 = start1, *pos2 = start2;
		while (++pos1 != end1)
		{
			sum = ExecuteFunctionCC1C2(amx, &fid, sum, *pos1);
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
}
