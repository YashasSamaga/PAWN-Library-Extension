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
static std::vector <std::function<cell(cell)>> unary_functions =
{
	[](cell x)->cell {return -x; },	//negate
	[](cell x)->cell {return !x; },	//logical_not
	[](cell x)->cell {return ~x; },	//bit_not
	[](cell x)->cell {return x + 1; }, //increment
	[](cell x)->cell {return x - 1; }, //decrement

	[](cell x)->cell {float n = -amx_ctof(x);  return amx_ftoc(n); },		//negatef
	[](cell x)->cell {float n = amx_ctof(x) + 1;  return amx_ftoc(n); },	//incrementf
	[](cell x)->cell {float n = amx_ctof(x) - 1;  return amx_ftoc(n); },	//decrementf
};
/*static std::vector <std::function<cell(AMX*, cell)>> ref_unary_functions =
{
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		return -*phys_addr; 
	},	//ref_negate
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		return static_cast<cell>(!*phys_addr); 
	},	//ref_logical_not
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		return ~*phys_addr; 
	},	//ref_bit_not
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		return *phys_addr + 1; 
	}, //ref_increment
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		return *phys_addr - 1; 
	}, //ref_decrement
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		float n = -amx_ctof(*phys_addr);  
		return amx_ftoc(n); 
	},		//ref_negatef
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		float n = amx_ctof(*phys_addr) + 1;  
		return amx_ftoc(n); 
	},	//ref_incrementf
	[](AMX * amx, cell x)->cell 
	{ 
		cell *phys_addr; 
		amx_GetAddr(amx, x, &phys_addr); 
		if (phys_addr == NULL) return 0; 
		float n = amx_ctof(*phys_addr) - 1;  
		return amx_ftoc(n); 
	},	//ref_decrementf
};
static std::vector <std::function<cell(AMX*, cell)>> array_unary_functions =
{
	[](AMX *amx, cell str)->cell 
	{
		cell *phys_addr;
		amx_GetAddr(amx, str, &phys_addr);
		cell addr = str + *phys_addr;
		amx_GetAddr(amx, addr, &phys_addr);
		if (phys_addr == NULL) return 0;
		return ((!phys_addr[0]) || (((phys_addr[0]) == '\1') && !phys_addr[1]));
	} //str_isnull
};*/
static std::vector <std::function<cell(cell, cell)>> binary_functions =
{
	[](cell a, cell b)->cell { return a + b;  }, //plus
	[](cell a, cell b)->cell { return a - b;  }, //minus
	[](cell a, cell b)->cell { return a * b;  }, //multiplies
	[](cell a, cell b)->cell { return a / b;  }, //divides
	[](cell a, cell b)->cell { return a % b;  }, //modulus
	[](cell a, cell b)->cell { return a == b; }, //equal_to
	[](cell a, cell b)->cell { return a != b; }, //not_equal_to
	[](cell a, cell b)->cell { return a > b;	}, //greater
	[](cell a, cell b)->cell { return a < b;  }, //less
	[](cell a, cell b)->cell { return a >= b; }, //greater_equal
	[](cell a, cell b)->cell { return a <= b; }, //less_equal
	[](cell a, cell b)->cell { return a && b; }, //logical_and
	[](cell a, cell b)->cell { return a || b; }, //logical_or
	[](cell a, cell b)->cell { return a & b;  }, //bit_and
	[](cell a, cell b)->cell { return a | b;  }, //bit_or
	[](cell a, cell b)->cell { return a ^ b;  }, //bit_xor
	[](cell a, cell b)->cell { float n = amx_ctof(a) + amx_ctof(b);  return amx_ftoc(n); }, //plusf
	[](cell a, cell b)->cell { float n = amx_ctof(a) - amx_ctof(b);  return amx_ftoc(n); }, //minusf
	[](cell a, cell b)->cell { float n = amx_ctof(a) * amx_ctof(b);  return amx_ftoc(n); }, //multipliesf
	[](cell a, cell b)->cell { float n = amx_ctof(a) / amx_ctof(b);  return amx_ftoc(n); }  //dividesf
};
/*static std::vector <std::function<cell(AMX*, cell, cell)>> ref_binary_functions =
{
	[](AMX* amx, cell a, cell b)->cell 
	{
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a + *phys_addr_b;
	}, //ref_plus
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a - *phys_addr_b;
	}, //ref_minus
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a * *phys_addr_b;
	}, //ref_multiplies
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a / *phys_addr_b;
	}, //ref_divides
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a % *phys_addr_b;
	}, //ref_modulus
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a == *phys_addr_b;
	}, //ref_equal_to
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a != *phys_addr_b;
	}, //ref_not_equal_to
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a > *phys_addr_b;
	}, //ref_greater
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a < *phys_addr_b;
	}, //ref_less
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a >= *phys_addr_b;
	}, //ref_greater_equal
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a <= *phys_addr_b;
	}, //ref_less_equal
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a && *phys_addr_b;
	}, //ref_logical_and
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a || *phys_addr_b;
	}, //ref_logical_or
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a & *phys_addr_b;
	}, //ref_bit_and
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a | *phys_addr_b;
	}, //ref_bit_or
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		return *phys_addr_a ^ *phys_addr_b;
	}, //ref_bit_xor
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		float n = amx_ctof(*phys_addr_a) + amx_ctof(*phys_addr_b);  
		return amx_ftoc(n);
	}, //ref_plusf
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		float n = amx_ctof(*phys_addr_a) - amx_ctof(*phys_addr_b);
		return amx_ftoc(n); 
	}, //ref_minusf
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		float n = amx_ctof(*phys_addr_a) * amx_ctof(*phys_addr_b);  
		return amx_ftoc(n);
	}, //ref_multipliesf
	[](AMX* amx, cell a, cell b)->cell 
	{ 
		cell *phys_addr_a, *phys_addr_b;
		amx_GetAddr(amx, a, &phys_addr_a);
		amx_GetAddr(amx, b, &phys_addr_b);
		if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
		float n = amx_ctof(*phys_addr_a) / amx_ctof(*phys_addr_b); 
		return amx_ftoc(n);
	}  //ref_dividesf
};
static std::vector <std::function<cell(AMX*, cell, cell)>> array_binary_functions =
{11
	[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a + *phys_addr_b;
}, //ref_plus
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a - *phys_addr_b;
}, //ref_minus
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a * *phys_addr_b;
}, //ref_multiplies
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a / *phys_addr_b;
}, //ref_divides
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a % *phys_addr_b;
}, //ref_modulus
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a == *phys_addr_b;
}, //ref_equal_to
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a != *phys_addr_b;
}, //ref_not_equal_to
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a > *phys_addr_b;
}, //ref_greater
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a < *phys_addr_b;
}, //ref_less
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a >= *phys_addr_b;
}, //ref_greater_equal
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a <= *phys_addr_b;
}, //ref_less_equal
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a && *phys_addr_b;
}, //ref_logical_and
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a || *phys_addr_b;
}, //ref_logical_or
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a & *phys_addr_b;
}, //ref_bit_and
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a | *phys_addr_b;
}, //ref_bit_or
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	return *phys_addr_a ^ *phys_addr_b;
}, //ref_bit_xor
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	float n = amx_ctof(*phys_addr_a) + amx_ctof(*phys_addr_b);
	return amx_ftoc(n);
}, //ref_plusf
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	float n = amx_ctof(*phys_addr_a) - amx_ctof(*phys_addr_b);
	return amx_ftoc(n);
}, //ref_minusf
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	float n = amx_ctof(*phys_addr_a) * amx_ctof(*phys_addr_b);
	return amx_ftoc(n);
}, //ref_multipliesf
[](AMX* amx, cell a, cell b)->cell
{
	cell *phys_addr_a, *phys_addr_b;
	amx_GetAddr(amx, a, &phys_addr_a);
	amx_GetAddr(amx, b, &phys_addr_b);
	if (phys_addr_a == NULL || phys_addr_b == NULL) return 0;
	float n = amx_ctof(*phys_addr_a) / amx_ctof(*phys_addr_b);
	return amx_ftoc(n);
}  //ref_dividesf
};*/
/************************************************************************************************************/
cell ExecuteFunctionCO1O2O3(AMX *amx, functionID *fid)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_NATIVE:
	{
		cell params[4];
		params[0] = fid->argc * BYTES_PER_CELL;
		switch (fid->argc)
		{
		case 3:
			params[3] = fid->params[2];
			//FALLTHROUGH
		case 2:
			params[2] = fid->params[1];
			//FALLTHROUGH
		case 1:
			params[1] = fid->params[0];
		}
		cell(*func)(AMX *amx, cell params[]) = (cell(*)(AMX *amx, cell params[]))(fid->address);
		retval = func(amx, params);
		break;
	}
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		switch (fid->argc)
		{
		case 3:
			amx_Push(amx, fid->params[2]);
			//FALLTHROUGH
		case 2:
			amx_Push(amx, fid->params[1]);
			//FALLTHROUGH
		case 1:
			amx_Push(amx, fid->params[0]);
		}
		amx_Exec(amx, &retval, fid->address);
		break;
	}
	case FUNCTION_ID_TYPE_DEFAULT:
	{
		switch (fid->argc)
		{
		case 2:
			retval = binary_functions[fid->address](fid->params[0], fid->params[1]);
			break;
		case 1:
			retval = unary_functions[fid->address](fid->params[0]);
			break;
		}
		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}
cell ExecuteFunctionCC1O2O3O4(AMX *amx, functionID *fid, cell cparam)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_NATIVE:
	{
		cell params[5];
		switch (fid->argc)
		{
		case 4:
			params[0] = 4 * BYTES_PER_CELL;
			params[1] = fid->params[0];
			params[2] = fid->params[1];
			params[3] = fid->params[2];
			params[4] = cparam;
			break;
		case 3:
			params[0] = 3 * BYTES_PER_CELL;
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				params[1] = fid->params[0];
				if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				{
					params[2] = fid->params[1];
					params[3] = cparam;
				}
				else //BIND3 must be set
				{
					params[2] = cparam;
					params[3] = fid->params[2];
				}
			}
			else
			{
				params[1] = cparam;
				params[2] = fid->params[1];
				params[3] = fid->params[2];
			}
			break;
		case 2:
			params[0] = 2 * BYTES_PER_CELL;
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				params[1] = fid->params[0];
				params[2] = cparam;
			}
			else //BIND2 must be set
			{
				params[1] = cparam;
				params[2] = fid->params[1];
			}
			break;
		case 1:
			params[0] = 1 * BYTES_PER_CELL;
			params[1] = cparam;
			break;		
		}
		cell(*func)(AMX *amx, cell params[]) = (cell(*)(AMX *amx, cell params[]))(fid->address);
		retval = func(amx, params);
		break;
	}
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		switch (fid->argc)
		{
		case 4:
			amx_Push(amx, cparam);
			amx_Push(amx, fid->params[2]);
			amx_Push(amx, fid->params[1]);
			amx_Push(amx, fid->params[0]);
			break;
		case 3:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND3))
			{
				amx_Push(amx, fid->params[2]);
				if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				{
					amx_Push(amx, fid->params[1]);
					amx_Push(amx, cparam);
				}
				else //BIND1 must be set
				{
					amx_Push(amx, cparam);
					amx_Push(amx, fid->params[0]);
				}
			}
			else
			{
				amx_Push(amx, cparam);
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, fid->params[0]);
			}
			break;	
		case 2:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				amx_Push(amx, cparam);
				amx_Push(amx, fid->params[0]);
			}
			else //BIND2 must be set
			{
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, cparam);
			}
			break;
		case 1:
			amx_Push(amx, cparam);
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
			else //BIND2 must be set
				retval = binary_functions[fid->address](cparam, fid->params[1]);
			break;
		}
		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}
cell ExecuteFunctionCC1C2O3O4O5(AMX *amx, functionID *fid, cell cparam1, cell cparam2)
{
	cell retval = 0;
	switch (fid->type)
	{
	case FUNCTION_ID_TYPE_NATIVE:
	{
		cell params[6];		
		switch (fid->argc)
		{
		case 5:
			params[0] = 5 * BYTES_PER_CELL;
			params[1] = fid->params[0];
			params[2] = fid->params[1];
			params[3] = fid->params[2];
			params[4] = cparam1;
			params[5] = cparam2;
			break;
		case 4:
			params[0] = 4 * BYTES_PER_CELL;
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				params[1] = fid->params[0];
				if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				{
					params[2] = fid->params[1];
					params[3] = cparam1;
				}
				else
				{
					params[2] = cparam1;
					params[3] = fid->params[2];					
				}
			}
			else
			{
				params[1] = cparam1;
				params[2] = fid->params[1];
				params[3] = fid->params[2];
			}
			params[4] = cparam2;
			break;
		case 3:
			params[0] = 3 * BYTES_PER_CELL;
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND1))
			{
				params[1] = fid->params[0];
				params[2] = cparam1;	
				params[3] = cparam2;
			}
			else if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
			{
				params[1] = cparam1;				
				params[2] = fid->params[1];
				params[3] = cparam2;
			}
			else
			{
				params[1] = cparam1;
				params[2] = cparam2;
				params[3] = fid->params[2];
			}			
			break;
		case 2:
			params[0] = 2 * BYTES_PER_CELL;
			params[1] = cparam1;
			params[2] = cparam2;
			break;
		}
		cell(*func)(AMX *amx, cell params[]) = (cell(*)(AMX *amx, cell params[]))(fid->address);
		retval = func(amx, params);
		break;
	}
	case FUNCTION_ID_TYPE_PUBLIC:
	{
		switch (fid->argc)
		{
		case 5:
			amx_Push(amx, cparam2);
			amx_Push(amx, cparam1);
			amx_Push(amx, fid->params[2]);
			amx_Push(amx, fid->params[1]);
			amx_Push(amx, fid->params[0]);
			break;
		case 4:
			amx_Push(amx, cparam2);
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND3))
			{
				amx_Push(amx, fid->params[2]);
				if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
				{
					amx_Push(amx, fid->params[1]);
					amx_Push(amx, cparam1);
				}
				else
				{
					amx_Push(amx, cparam1);
					amx_Push(amx, fid->params[0]);
				}
			}
			else
			{
				amx_Push(amx, cparam1);
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, fid->params[0]);
			}
			break;
		case 3:
			if (fid->IsFlagSet(FUNCTION_FLAG_BIND3))
			{
				amx_Push(amx, fid->params[2]);
				amx_Push(amx, cparam2);
				amx_Push(amx, cparam1);
			}
			else if (fid->IsFlagSet(FUNCTION_FLAG_BIND2))
			{
				amx_Push(amx, cparam2);
				amx_Push(amx, fid->params[1]);
				amx_Push(amx, cparam1);
			}
			else
			{
				amx_Push(amx, cparam2);
				amx_Push(amx, cparam1);
				amx_Push(amx, fid->params[0]);
			}
			break;
		case 2:
			amx_Push(amx, cparam2);
			amx_Push(amx, cparam1);
			break;
		}
		amx_Exec(amx, &retval, fid->address);
		break;
	}
	case FUNCTION_ID_TYPE_DEFAULT:
	{
		retval = binary_functions[fid->address](cparam1, cparam2);
		break;
	}
	}
	if (fid->IsFlagSet(FUNCTION_FLAG_NOT)) return !retval;
	return retval;
}
/************************************************************************************************************/
namespace Natives
{	
	//native invoke_fn(func[FTSIZE], ...);
	cell AMX_NATIVE_CALL functional_invoke_fn(AMX* amx, cell* params)
	{
		/*error_if(!check_params_min(1), "[PLE] functional>> invoke_fn: expected at least 1 parameters but found %d parameters.", get_params_count());
		cell* func = NULL;
		amx_GetAddr(amx, params[3], &func);
		functionID fid(func);
		error_if((get_params_count() - 1) != fid.argc, "[PLE] functional>> invoke_fn: expected at least 1 parameters but found %d parameters.", get_params_count());
		cell argc = get_params_count();
		for(int i = 2; i <= argc; i++)
		*/
		//TODO //WIP
		return true;
	}
	//native argArray(arr[]);
	cell AMX_NATIVE_CALL functional_argArray(AMX* amx, cell* params)
	{
		return params[1];
	}
	//native argReference(&var);
	cell AMX_NATIVE_CALL functional_argReference(AMX* amx, cell* params)
	{
		return params[1];
	}
	//native i@_make_function(func[FTSIZE], const fname[], argc, type, flags);
	cell AMX_NATIVE_CALL functional_make_function(AMX* amx, cell* params)
	{
		error_if(!check_params(5), "[PLE] functional>> make_function: expected 5 parameters but found %d parameters.", get_params_count());
		cell *dest_addr = NULL;
		amx_GetAddr(amx, params[1], &dest_addr);
		cell *name_addr = NULL;
		amx_GetAddr(amx, params[2], &name_addr);

		cell argc = params[3];
		error_if(argc > 31, "[PLE] functional>> make_function: 'argc' (%d) must be less than 32", argc);

		char name[MAX_SYMBOL_LEN];
		amx_GetString(name, name_addr, 0, sizeof(name));

		switch (params[4])
		{
			case FUNCTION_ID_TYPE_PUBLIC:
			{
				int funcidx = 0;
				if (amx_FindPublic(amx, name, &funcidx) == AMX_ERR_NONE)
				{
					functionID id(FUNCTION_ID_TYPE_PUBLIC, argc, static_cast<uint16_t>(params[5]), static_cast<uint32_t>(funcidx));
					dest_addr[0] = id.getFirst();
					dest_addr[1] = id.getSecond();
					return true;
				}
				break;
			}
			case FUNCTION_ID_TYPE_NATIVE:
			{
				AMX_HEADER * hdr = (AMX_HEADER *)amx->base;
				AMX_FUNCSTUB * func;

				int num = NUMENTRIES(hdr, natives, libraries);
				for (int idx = 0; idx != num; idx++)
				{
					func = GETENTRY(hdr, natives, idx);
					if (!strcmp(name, GETENTRYNAME(hdr, func)))
					{
						functionID id(FUNCTION_ID_TYPE_NATIVE, argc, static_cast<uint16_t>(params[5]), static_cast<uint32_t>(func->address));
						dest_addr[0] = id.getFirst();
						dest_addr[1] = id.getSecond();
						return true;
					}
				}
				break;
			}
			default:
				error_if(true, "[PLE] functional>> make_function: unknown function type");
			break;
		}
		return false;
	}
}
