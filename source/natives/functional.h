/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

functional
functional.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#include <cstdint>
#include <functional>
#include <vector>
/************************************************************************************************************/
#define FTSIZE 4

enum
{
	FUNCTION_ID_INVALID			=	0x00,
	FUNCTION_ID_INVALID2		=	0x01,
	FUNCTION_ID_TYPE_PUBLIC		=	0x02,
	FUNCTION_ID_TYPE_NATIVE		=	0x04,
	FUNCTION_ID_TYPE_DEFAULT	=	0x08
};
enum
{
	FUNCTION_ARGC_0 = 0,
	FUNCTION_ARGC_1,
	FUNCTION_ARGC_2,
	FUNCTION_ARGC_3,
	FUNCTION_ARGC_4,
	FUNCTION_ARGC_5,
	FUNCTION_ARGC_6,
	FUNCTION_ARGC_8,
	FUNCTION_ARGC_9,
	FUNCTION_ARGC_10,
	FUNCTION_ARGC_11,
	FUNCTION_ARGC_12,
	FUNCTION_ARGC_13,
	FUNCTION_ARGC_14,
	FUNCTION_ARGC_15,
	FUNCTION_ARGC_16,
	FUNCTION_ARGC_18,
	FUNCTION_ARGC_19,
	FUNCTION_ARGC_20,
	FUNCTION_ARGC_21,
	FUNCTION_ARGC_22,
	FUNCTION_ARGC_23,
	FUNCTION_ARGC_24,
	FUNCTION_ARGC_25,
	FUNCTION_ARGC_26,
	FUNCTION_ARGC_28,
	FUNCTION_ARGC_29,
	FUNCTION_ARGC_30,
	FUNCTION_ARGC_31
};
enum
{
	FUNCTION_FLAG_NOT		=	0x01,
	FUNCTION_FLAG_BIND1		=	0x02,
	FUNCTION_FLAG_BIND2		=	0x04,
	FUNCTION_FLAG_VAARGS	=	0x08
};

typedef struct functionID
{
	uint32_t address;
	uint8_t argc;
	uint16_t flags;
	uint8_t type;

	cell *params;

	functionID(uint8_t type, uint16_t flags, uint8_t argc, uint32_t address) : type(type), flags(flags), argc(argc), address(address) { }
	functionID(cell *func)
	{
		address = func[1];
		params = &func[2];

		argc = static_cast<uint8_t>((0xFF000000 & func[0]) >> 24);
		flags = static_cast<uint16_t>((0x00FFFF00 & func[0]) >> 8);
		type = static_cast<uint8_t>(0x000000FF & func[0]);
	}
	functionID(uint32_t cell1, uint32_t cell2)
	{
		address = cell2;

		argc = static_cast<uint8_t>((0xFF000000 & cell1) >> 24);
		flags = static_cast<uint16_t>((0x00FFFF00 & cell1) >> 8);
		type = static_cast<uint8_t>(0x000000FF & cell1);
	}

	bool IsFunctionValid(int _argc)
	{
		int actual_argc = argc;
		if (IsFlagSet(FUNCTION_FLAG_BIND1)) actual_argc--;
		if (IsFlagSet(FUNCTION_FLAG_BIND2)) actual_argc--;

		return ((type & (FUNCTION_ID_TYPE_PUBLIC | FUNCTION_ID_TYPE_NATIVE | FUNCTION_ID_TYPE_DEFAULT))
			&&  ((type & (FUNCTION_ID_INVALID | FUNCTION_ID_INVALID2 | 0xF0)) == 0) && (actual_argc == _argc));
	}
	bool IsFlagSet(uint16_t flag) const
	{
		return ((flags & flag) == flag);
	}
	uint32_t getFirst() const
	{
		return (type | flags << 8 | argc << 24);
	}
	uint32_t getSecond() const
	{
		return address;
	}
}functionID;

extern cell ExecuteFunctionCC1C2(AMX *amx, functionID *fid, cell cparam1, cell cparam2);
extern cell ExecuteFunctionCO1O2(AMX *amx, functionID *fid);
extern cell ExecuteFunctionCC1O2(AMX *amx, functionID *fid, cell cparam);

extern std::vector <std::function<cell(cell)>> unary_functions;
extern std::vector <std::function<cell(cell, cell)>> binary_functions;

namespace Natives
{
	cell AMX_NATIVE_CALL functional_make_function(AMX* amx, cell* params);
}
