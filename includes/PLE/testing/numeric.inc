/************************************************************************************************************
PAWN Library Extension

Collection of useful numeric algorithms (mostly from C++ standard/template library along with addititional functions)
numeric.inc
*************************************************************************************************************/
#if defined _PLE_NUMERIC_INC
	#endinput
#else
	#define _PLE_NUMERIC_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/functional>
/***********************************************************************************************************/
native iota(range[], numcells, init, {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::increment);
native accumulate(range[], numcells, init, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
native inner_product(range[], numcells, dest[], init, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::multiplies);
native adjacent_difference(range[], numcells, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::minus);
native partial_sum(range[], numcells, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
native gcd(x, y);
native lcm(x, y);




