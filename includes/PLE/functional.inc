/************************************************************************************************************************
PAWN Library Extension

Functions
functional.inc
************************************************************************************************************************/
#if defined _PLE_FUNCTIONAL_INC
	#endinput
#else
	#define _PLE_FUNCTIONAL_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/iscript>

/***********************************************************************************************************************/
/*
functionID (6 cells)
byte 	1				bits 0-7 	: type
byte	2				bits 8-15 	: argc
byte	3,4				bits 16-31 	: flags
byte	5,6,7,8			bits 32-63  : address
byte	9,10,11,12  	bind1
byte	13,14,15,16 	bind2
byte    17,18,19,20     bind3
byte    21,22,23,24     bind4
*/

#define FTSIZE 6
#define function:%0<%1(%2)> %0[FTSIZE]

#define placeholder:: funcobj_ph_
#define funcobj_ph__1 PLE_@placeholder_tag:0
#define funcobj_ph__2 PLE_@placeholder_tag:0
#define funcobj_ph__3 PLE_@placeholder_tag:0

enum
{
    FUNCTION_ID_INVALID			=	0x00,
	FUNCTION_ID_TYPE_PUBLIC 	= 	0x01,
	FUNCTION_ID_TYPE_NATIVE     =   0x02,
    FUNCTION_ID_TYPE_DEFAULT 	= 	0x04
}

enum
{
	FUNCTION_FLAG_NOT 		= 	0x01,
	FUNCTION_FLAG_BIND1 	= 	0x02,
	FUNCTION_FLAG_BIND2 	= 	0x04,
	FUNCTION_FLAG_BIND3     =   0x08,
	FUNCTION_FLAG_BIND4     =   0x10,
	FUNCTION_FLAG_VAARGS 	= 	0x20
}
/***********************************************************************************************************************/
native argArray(arr[]);
native argReference(&var);

native _make_function(func[FTSIZE], const fname[], argc, type, flags, scriptkey);
stock make_function(func[FTSIZE], const fname[], argc, type = FUNCTION_ID_TYPE_PUBLIC, flags = 0, scriptKey = INVALID_SCRIPT_KEY)
{
    _make_function(func, fname, argc, type, flags, scriptKey);
    return func;
}

native invoke_fn(func[FTSIZE], ...);
/***********************************************************************************************************************/
stock not_fn(func[FTSIZE])
{
	func[0] ^= FUNCTION_FLAG_NOT;
	return func;
}
stock bind1st(func[FTSIZE], val)
{
    func[0] |= FUNCTION_FLAG_BIND1;
    func[2] = val;
    return func;
}
stock bind2nd(func[FTSIZE], val)
{
    func[0] |= FUNCTION_FLAG_BIND2;
    func[3] = val;
    return func;
}
stock bind3rd(func[FTSIZE], val)
{
    func[0] |= FUNCTION_FLAG_BIND3;
    func[4] = val;
    return func;
}
/*stock bind(func[FTSIZE], {PLE_@placeholder_tag, Float, _}:arg1 = PLE_@placeholder_tag:0, {PLE_@placeholder_tag, Float, _}:arg2 = PLE_@placeholder_tag:0, {PLE_@placeholder_tag, Float, _}:arg3 = PLE_@placeholder_tag:0, const tag_arg1 = tagof(arg1), const tag_arg2 = tagof(arg2), const tag_arg3 = tagof(arg3))
{
	if(tag_arg1 == (tagof(PLE_@placeholder_tag:)))
	    func[0] &= ~FUNCTION_FLAG_BIND1;
	else
	{
	    func[0] |= FUNCTION_FLAG_BIND1;
	    func[2] = _:arg1;
	}

	if(tag_arg2 == (tagof(PLE_@placeholder_tag:)))
        func[0] &= ~FUNCTION_FLAG_BIND2;
	else
	{
        func[0] |= FUNCTION_FLAG_BIND2;
        func[3] = _:arg2;
	}

	if(tag_arg2 == (tagof(PLE_@placeholder_tag:)))
        func[0] &= ~FUNCTION_FLAG_BIND3;
	else
	{
        func[0] |= FUNCTION_FLAG_BIND3;
        func[4] = _:arg3;
	}
	return func;
}*/
/************************************************* FUNCTION TEMPLATES **************************************************/
#define functions:: do_func_
#define fixed_functions:: do_fixed_func_

#define do_func_negate				func_bool1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_negate, 			0, 0, 0, 0}
#define do_func_logical_not 		func_bool1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_logical_not, 		0, 0, 0, 0}
#define do_func_bit_not				func_bool1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_bit_not,			0, 0, 0, 0}
#define do_func_increment			func_cell1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_increment,		0, 0, 0, 0}
#define do_func_decrement			func_cell1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_decrement,		0, 0, 0, 0}

#define do_func_negatef				func_bool1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_negatef,			0, 0, 0, 0}
#define do_func_incrementf			func_cell1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_incrementf,		0, 0, 0, 0}
#define do_func_decrementf			func_cell1:{FUNCTION_ID_TYPE_DEFAULT << 24 | 1 << 16, _func_decrementf,		0, 0, 0, 0}

#define do_func_plus 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_plus,				0, 0, 0, 0}
#define do_func_minus 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_minus,			0, 0, 0, 0}
#define do_func_multiplies 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_multiplies,		0, 0, 0, 0}
#define do_func_divides 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_divides,			0, 0, 0, 0}
#define do_func_modulus 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_modulus,			0, 0, 0, 0}
#define do_func_equal_to 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_equal_to,			0, 0, 0, 0}
#define do_func_not_equal_to 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_not_equal_to,		0, 0, 0, 0}
#define do_func_greater 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_greater,			0, 0, 0, 0}
#define do_func_less 				func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_less,				0, 0, 0, 0}
#define do_func_greater_equal 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_greater_equal,	0, 0, 0, 0}
#define do_func_less_equal 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_less_equal,		0, 0, 0, 0}
#define do_func_logical_and 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_logical_and,		0, 0, 0, 0}
#define do_func_logical_or 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_logical_or,		0, 0, 0, 0}
#define do_func_bit_and 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_bit_or,			0, 0, 0, 0}
#define do_func_bit_or 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_bit_and,			0, 0, 0, 0}
#define do_func_bit_xor				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_bit_xor,			0, 0, 0, 0}

#define do_func_plusf				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_plusf,			0, 0, 0, 0}
#define do_func_minusf 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_minusf,			0, 0, 0, 0}
#define do_func_multipliesf 		func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_multipliesf,		0, 0, 0, 0}
#define do_func_dividesf 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_dividesf,			0, 0, 0, 0}
#define do_func_equal_tof 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_equal_to,			0, 0, 0, 0}
#define do_func_not_equal_tof 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_not_equal_to,		0, 0, 0, 0}
#define do_func_greaterf			func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_greater,			0, 0, 0, 0}
#define do_func_lessf 				func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_less,				0, 0, 0, 0}
#define do_func_greater_equalf 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_greater_equal,	0, 0, 0, 0}
#define do_func_less_equalf 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_less_equal,		0, 0, 0, 0}

// compiler bug fix
#define do_fixed_func_plus			{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_plus,			0, 0, 0, 0}
#define do_fixed_func_minus			{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_plus,			0, 0, 0, 0}
#define do_fixed_func_equal_to 		{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_equal_to,		0, 0, 0, 0}
#define do_fixed_func_greater 		{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_greater,			0, 0, 0, 0}
#define do_fixed_func_less 			{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_less,			0, 0, 0, 0}
#define do_fixed_func_increment		{FUNCTION_ID_TYPE_DEFAULT << 24 | 2 << 16, _func_increment,		0, 0, 0, 0}

enum
{
	_func_negate = 0,
	_func_logical_not = 1,
	_func_bit_not,
    _func_increment,
    _func_decrement,

    _func_negatef,
    _func_incrementf,
    _func_decrementf,

	_func_plus = 0,
	_func_minus = 1,
	_func_multiplies = 2,
	_func_divides,
	_func_modulus,
	_func_equal_to,
	_func_not_equal_to,
	_func_greater,
	_func_less,
	_func_greater_equal,
	_func_less_equal,
	_func_logical_and,
	_func_logical_or,
	_func_bit_or,
	_func_bit_and,
	_func_bit_xor,

	_func_plusf,
	_func_minusf,
	_func_multipliesf,
	_func_dividesf
}
