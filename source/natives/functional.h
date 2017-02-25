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
#define FTSIZE 5

enum
{
	FUNCTION_ID_INVALID = 0x00,
	FUNCTION_ID_INVALID2 = 0x01,
	FUNCTION_ID_TYPE_PUBLIC = 0x02,
	FUNCTION_ID_TYPE_NATIVE = 0x04,
	FUNCTION_ID_TYPE_DEFAULT = 0x08
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
	FUNCTION_FLAG_NOT = 0x01,
	FUNCTION_FLAG_BIND1 = 0x02,
	FUNCTION_FLAG_BIND2 = 0x04,
	FUNCTION_FLAG_BIND3 = 0x08,
	FUNCTION_FLAG_VAARGS = 0x10
};
/************************************************************************************************************/
/* originally found in sscanf plugin code */
#define USENAMETABLE(hdr) \
					((hdr)->defsize==sizeof(AMX_FUNCSTUBNT))

#define NUMENTRIES(hdr,field,nextfield) \
					(unsigned)(((hdr)->nextfield - (hdr)->field) / (hdr)->defsize)

#define GETENTRY(hdr,table,index) \
					(AMX_FUNCSTUB *)((unsigned char*)(hdr) + (unsigned)(hdr)->table + (unsigned)index*(hdr)->defsize)

#define GETENTRYNAME(hdr,entry) \
					(USENAMETABLE(hdr) ? \
						(char *)((unsigned char*)(hdr) + (unsigned)((AMX_FUNCSTUBNT*)(entry))->nameofs) : \
				((AMX_FUNCSTUB*)(entry))->name)
/************************************************************************************************************/
typedef struct functionID
{
	uint32_t address;
	uint16_t flags;
	uint8_t argc;	
	uint8_t type;

	cell params[3];

	functionID(uint8_t type, uint8_t argc, uint16_t flags, uint32_t address) : type(type), argc(argc), flags(flags), address(address) { }
	functionID(cell *func)
	{
		address = func[1];
		params[0] = func[2];
		params[1] = func[3];
		params[2] = func[4];

		type = static_cast<uint8_t>(0x000000FF & func[0]);
		argc = static_cast<uint8_t>((0x0000FF00 & func[0]) >> 8);
		flags = static_cast<uint16_t>((0xFFFF0000 & func[0]) >> 16);
		
	}
	functionID(uint32_t cell1, uint32_t cell2)
	{
		address = cell2;

		type = static_cast<uint8_t>(0x000000FF & cell1);
		argc = static_cast<uint8_t>((0x0000FF00 & cell1) >> 8);
		flags = static_cast<uint16_t>((0xFFFF0000 & cell1) >> 16);		
	}

	bool IsFunctionValid(int _argc) const
	{
		if (!(type & (FUNCTION_ID_TYPE_PUBLIC | FUNCTION_ID_TYPE_NATIVE | FUNCTION_ID_TYPE_DEFAULT))
			|| ((type & (FUNCTION_ID_INVALID | FUNCTION_ID_INVALID2 | 0xF0)) != 0)) return false;

		if (IsFlagSet(FUNCTION_FLAG_VAARGS)) return true;

		int actual_argc = argc;
		if (IsFlagSet(FUNCTION_FLAG_BIND1)) actual_argc--;
		if (IsFlagSet(FUNCTION_FLAG_BIND2)) actual_argc--;
		if (IsFlagSet(FUNCTION_FLAG_BIND3)) actual_argc--;

		return (actual_argc == _argc);
	}
	bool IsFlagSet(uint16_t flag) const
	{
		return ((flags & flag) == flag);
	}
	uint32_t getFirst() const
	{
		return (type | argc << 8 | flags << 16);
	}
	uint32_t getSecond() const
	{
		return address;
	}
}functionID;
/************************************************************************************************************/
extern cell ExecuteFunctionCO1O2O3(AMX *amx, functionID *fid);
extern cell ExecuteFunctionCC1O2O3O4(AMX *amx, functionID *fid, cell cparam);
extern cell ExecuteFunctionCC1C2O3O4O5(AMX *amx, functionID *fid, cell cparam1, cell cparam2);
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL functional_argArray(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL functional_argReference(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL functional_make_function(AMX* amx, cell* params);
}
