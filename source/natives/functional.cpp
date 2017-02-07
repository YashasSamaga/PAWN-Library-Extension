/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

functional
functional.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"
#include "functional.h"

#include <functional>
#include <vector>
/************************************************************************************************************/
__forceinline cell ExecuteFunctionCO1O2(AMX *amx, functionID *fid)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		switch (fid->argc)
		{
		case 1:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				amx_Push(amx, fid->params[0]);
				amx_Exec(amx, &retval, fid->address);
			}
			break;
		case 2:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1) && fid->IsFlagSet(FUNCTION_FLAG_BIND2))
			{
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, fid->params[0]);
				amx_Exec(amx, &retval, fid->address);
			}
			break;
		}
		break;
	}
	case FUNCTION_ID_TYPE_DEFAULT:
	{
		switch (fid->argc)
		{
		case 1:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
				retval = unary_functions[fid->address](fid->params[0]);
			break;
		case 2:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1) && fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				retval = binary_functions[fid->address](fid->params[0], fid->params[1]);
			break;
		}
		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}
__forceinline cell ExecuteFunctionCC1O2(AMX *amx, functionID *fid, cell cparam)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		switch (fid->argc)
		{
		case 1:
			amx_Push(amx, cparam);
			break;
		case 2:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				amx_Push(amx, cparam);
				amx_Push(amx, fid->params[0]);
			}
			else if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
			{
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, cparam);
			}
			break;
		}
		amx_Exec(amx, &retval, fid->address);
		break;
	}
	case FUNCTION_ID_TYPE_DEFAULT:
	{
		switch (fid->argc)
		{
		case 1:
			retval = unary_functions[fid->address](cparam);
			break;
		case 2:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
				retval = binary_functions[fid->address](fid->params[0], cparam);
			else if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				retval = binary_functions[fid->address](cparam, fid->params[1]);
			break;
		}
		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}
__forceinline cell ExecuteFunctionCC1C2(AMX *amx, functionID *fid, cell cparam1, cell cparam2)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		if (fid->argc == 2)
		{
			amx_Push(amx, cparam2);
			amx_Push(amx, cparam1);
			amx_Exec(amx, &retval, fid->address);
		}
		break;
	}
	case FUNCTION_ID_TYPE_DEFAULT:
	{
		if (fid->argc == 2)
			retval = binary_functions[fid->address](cparam1, cparam2);

		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}

std::vector <std::function<cell(cell)>> unary_functions =
{
	[](cell x) {return -x; },	//negate
	[](cell x) {return !x; },	//logical_not
	[](cell x) {return ~x; },	//bit_not
	[](cell x) {return x + 1; }, //increment
	[](cell x) {return x - 1; }, //decrement

	[](cell x) {float n = -amx_ctof(x);  return amx_ftoc(n); },		//negatef
	[](cell x) {float n = amx_ctof(x) + 1;  return amx_ftoc(n); },	//incrementf
	[](cell x) {float n = amx_ctof(x) - 1;  return amx_ftoc(n); }	//decrementf
};
std::vector <std::function<cell(cell, cell)>> binary_functions =
{
	[](cell a, cell b) { return a + b;  }, //plus
	[](cell a, cell b) { return a - b;  }, //minus
	[](cell a, cell b) { return a * b;  }, //multiplies
	[](cell a, cell b) { return a / b;  }, //divides
	[](cell a, cell b) { return a % b;  }, //modulus
	[](cell a, cell b) { return a == b; }, //equal_to
	[](cell a, cell b) { return a != b; }, //not_equal_to
	[](cell a, cell b) { return a > b;	}, //greater
	[](cell a, cell b) { return a < b;  }, //less
	[](cell a, cell b) { return a >= b; }, //greater_equal
	[](cell a, cell b) { return a <= b; }, //less_equal
	[](cell a, cell b) { return a && b; }, //logical_and
	[](cell a, cell b) { return a || b; }, //logical_or
	[](cell a, cell b) { return a & b;  }, //bit_and
	[](cell a, cell b) { return a | b;  }, //bit_or
	[](cell a, cell b) { return a ^ b;  }, //bit_xor
	[](cell a, cell b) { float n = amx_ctof(a) + amx_ctof(b);  return amx_ftoc(n); }, //plusf
	[](cell a, cell b) { float n = amx_ctof(a) - amx_ctof(b);  return amx_ftoc(n); }, //minusf
	[](cell a, cell b) { float n = amx_ctof(a) * amx_ctof(b);  return amx_ftoc(n); }, //multipliesf
	[](cell a, cell b) { float n = amx_ctof(a) / amx_ctof(b);  return amx_ftoc(n); }  //dividesf
};
//random
//retval

namespace Natives
{
	//native i@_make_function(func[FTSIZE], const fname[], type, argc, flags);
	cell AMX_NATIVE_CALL functional_make_function(AMX* amx, cell* params)
	{
		cell *dest_addr = NULL;
		amx_GetAddr(amx, params[1], &dest_addr);

		cell *name_addr = NULL;
		amx_GetAddr(amx, params[2], &name_addr);

		char name[MAX_FUNC_NAME];
		amx_GetString(name, name_addr, 0, sizeof(name));
		
		int funcidx = 0;
		if (amx_FindPublic(amx, name, &funcidx) == AMX_ERR_NONE)
		{
			functionID id(static_cast<uint8_t>(params[3]), static_cast<uint16_t>(params[5]), static_cast<uint8_t>(params[4]), static_cast<uint32_t>(funcidx));
			dest_addr[0] = id.getFirst();
			dest_addr[1] = id.getSecond();
			return true;
		}		
		return false;
	}	
}
