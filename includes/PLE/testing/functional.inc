/************************************************************************************************************
PAWN Library Extension

Functions
functional.inc
*************************************************************************************************************/
#if defined _PLE_FUNCTIONAL_INC
	#endinput
#else
	#define _PLE_FUNCTIONAL_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/interface>
/*****************************************************************************************************************/
/*
** Function Information Encoding
** -----------------------------------------------------------------------------
** All the information required for a function object is stored in an array
** of 5 cells. This would mean that if the function object is passed as an
** argument to a function, it would behave like a reference: all modifications
** done to the argument in the function will corresponding modify the actual
** parameter.
**
** In the current version, function objects can bind to a maximum of 3 optional
** arguments.
**
** LOW INDEX
**  	byte	1				bits 0-7 	: type
**  	byte	2,3				bits 8-23 	: flags
**  	byte	4				bits 24-31 	: argc
**  	byte	5,6,7,8			bits 32-63  : address
**  	byte	9,10,11,12  	bind1
**  	byte	13,14,15,16 	bind2
**  	byte	17,18,19,20     bind3
** HIGH INDEX
*/

#define FTSIZE 5

/*
** Declaration format:
** -----------------------------------------------------------------------------
**
** 	function<ret-type(params)> myfunc;
**
** The content inside the  <> is ignored by the library. It exists for improving
** the readability of the code by specifying the return type and the parameters
** of the function to which the 'myfunc' will be pointing to.
**
** Even though, writing anything inside <> would work, it is advised to follow
** the scheme outlined above. There are plans to give different tags to function
** objects which point to different types.
**
** The define isn't smart enough to allow multiple declarations in one line.
** As of now, each declaration must be on a separate line terminated by a ';'.
**
** Example declarations:
** 
**  function<_(_)> myfunc;
**  function<Float(Float,Float)> add_floats = functions::plusf;
*/

#define function%9<%0(%1)>%2; new %2[FTSIZE];

/*
** Supported function types:
** -----------------------------------------------------------------------------
**
** Public Functions:
**  The function object can point to public functions declared in the same
**  script.
**
** Native functions:
**  The function object can point to a native function. The native function can
**  be from another plugin too.
**
** Builtin functions:
**  This library comes with over two dozen builtin functions for common tasks.
**
*/
enum
{
    FUNCTION_ID_INVALID			=	0x00,
    FUNCTION_ID_INVALID2 		= 	0x01,
	FUNCTION_ID_TYPE_PUBLIC 	= 	0x02,
	FUNCTION_ID_TYPE_NATIVE     =   0x04,
    FUNCTION_ID_TYPE_DEFAULT 	= 	0x08
}
enum
{
	FUNCTION_ARGC_0  = 0,
 	FUNCTION_ARGC_1  = 1<<24,
	FUNCTION_ARGC_2  = 2<<24,
	FUNCTION_ARGC_3  = 3<<24,
	FUNCTION_ARGC_4  = 4<<24,
	FUNCTION_ARGC_5  = 5<<24,
	FUNCTION_ARGC_6  = 6<<24,
	FUNCTION_ARGC_7  = 7<<24,
	FUNCTION_ARGC_8  = 8<<24,
	FUNCTION_ARGC_9  = 9<<24,
	FUNCTION_ARGC_10 = 10<<24,
 	FUNCTION_ARGC_11 = 11<<24,
	FUNCTION_ARGC_12 = 12<<24,
	FUNCTION_ARGC_13 = 13<<24,
	FUNCTION_ARGC_14 = 14<<24,
	FUNCTION_ARGC_15 = 15<<24,
	FUNCTION_ARGC_16 = 16<<24,
	FUNCTION_ARGC_17 = 17<<24,
	FUNCTION_ARGC_18 = 18<<24,
	FUNCTION_ARGC_19 = 19<<24,
	FUNCTION_ARGC_20 = 20<<24,
 	FUNCTION_ARGC_21 = 21<<24,
	FUNCTION_ARGC_22 = 22<<24,
	FUNCTION_ARGC_23 = 23<<24,
	FUNCTION_ARGC_24 = 24<<24,
	FUNCTION_ARGC_25 = 25<<24,
	FUNCTION_ARGC_26 = 26<<24,
	FUNCTION_ARGC_27 = 27<<24,
	FUNCTION_ARGC_28 = 28<<24,
	FUNCTION_ARGC_29 = 29<<24,
	FUNCTION_ARGC_30 = 30<<24,
 	FUNCTION_ARGC_31 = 31<<24
}
enum
{
 	FUNCTION_FLAG_NOT 		= 	0x01<<8,
	FUNCTION_FLAG_BIND1 	= 	0x02<<8,
	FUNCTION_FLAG_BIND2 	= 	0x04<<8,
	FUNCTION_FLAG_BIND3 	= 	0x08<<8,
}

native i@_make_function(func[FTSIZE], const fname[], type, argc, flags);

stock make_function(func[FTSIZE], const fname[], argc, type = FUNCTION_ID_TYPE_PUBLIC, flags = 0)
{
    i@_make_function(func, fname, type, argc, flags);
    return func;
}

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
/*
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
*/
/************************************************* FUNCTION TEMPLATES **************************************************/
#define functions:: do_func_
#define fixed_functions:: do_fixed_func_

#define do_func_negate				func_bool1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_negate, 			0, 0}
#define do_func_logical_not 		func_bool1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_logical_not, 		0, 0}
#define do_func_bit_not				func_bool1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_bit_not,			0, 0}
#define do_func_increment			func_cell1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_increment,		0, 0}
#define do_func_decrement			func_cell1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_decrement,		0, 0}

#define do_func_negatef				func_bool1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_negatef,			0, 0}
#define do_func_incrementf			func_cell1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_incrementf,		0, 0}
#define do_func_decrementf			func_cell1:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_1, _func_decrementf,		0, 0}

#define do_func_plus 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_plus,				0, 0}
#define do_func_minus 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_minus,			0, 0}
#define do_func_multiplies 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_multiplies,		0, 0}
#define do_func_divides 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_divides,			0, 0}
#define do_func_modulus 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_modulus,			0, 0}
#define do_func_equal_to 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_equal_to,			0, 0}
#define do_func_not_equal_to 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_not_equal_to,		0, 0}
#define do_func_greater 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_greater,			0, 0}
#define do_func_less 				func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_less,				0, 0}
#define do_func_greater_equal 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_greater_equal,	0, 0}
#define do_func_less_equal 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_less_equal,		0, 0}
#define do_func_logical_and 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_logical_and,		0, 0}
#define do_func_logical_or 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_logical_or,		0, 0}
#define do_func_bit_and 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_bit_or,			0, 0}
#define do_func_bit_or 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_bit_and,			0, 0}
#define do_func_bit_xor				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_bit_xor,			0, 0}

#define do_func_plusf				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_plusf,			0, 0}
#define do_func_minusf 				func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_minusf,			0, 0}
#define do_func_multipliesf 		func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_multipliesf,		0, 0}
#define do_func_dividesf 			func_cell2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_dividesf,			0, 0}
#define do_func_equal_tof 			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_equal_to,			0, 0}
#define do_func_not_equal_tof 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_not_equal_to,		0, 0}
#define do_func_greaterf			func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_greater,			0, 0}
#define do_func_lessf 				func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_less,				0, 0}
#define do_func_greater_equalf 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_greater_equal,	0, 0}
#define do_func_less_equalf 		func_bool2:{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_less_equal,		0, 0}

// compiler bug fix
#define do_fixed_func_plus			{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_plus,			0, 0}
#define do_fixed_func_minus			{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_plus,			0, 0}
#define do_fixed_func_equal_to 		{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_equal_to,		0, 0}
#define do_fixed_func_greater 		{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_greater,			0, 0}
#define do_fixed_func_less 			{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_less,			0, 0}
#define do_fixed_func_increment		{FUNCTION_ID_TYPE_DEFAULT | FUNCTION_ARGC_2, _func_increment,		0, 0}

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
