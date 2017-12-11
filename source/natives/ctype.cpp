/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Character types
ctype.cpp

NOTES:
 - tolower & toupper implemented in PAWN 'core' library

*************************************************************************************************************/
#include "main.h"
#include "ctype.h"
#include <cctype>

namespace PLE::natives
{
	//native isalnum(c);
	cell AMX_NATIVE_CALL ctype_isalnum(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isalnum: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isalnum(params[1]);
	}
	//native isalpha(c);
	cell AMX_NATIVE_CALL ctype_isalpha(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isalpha: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isalpha(params[2]);
	}
	//native isblank(c);
	cell AMX_NATIVE_CALL ctype_isblank(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isblank: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isblank(params[2]);
	}
	//native iscntrl(c);
	cell AMX_NATIVE_CALL ctype_iscntrl(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> iscntrl: expected 1 parameters but found %d parameters.", get_params_count());
		return std::iscntrl(params[2]);
	}
	//native isdigit(c);
	cell AMX_NATIVE_CALL ctype_isdigit(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isdigit: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isdigit(params[2]);
	}
	//native isgraph(c);
	cell AMX_NATIVE_CALL ctype_isgraph(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isgraph: expected 1 parameters but found %d parameters.", get_params_count());
		return isgraph(params[2]);
	}
	//native islower(c);
	cell AMX_NATIVE_CALL ctype_islower(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> islower: expected 1 parameters but found %d parameters.", get_params_count());
		return std::islower(params[2]);
	}
	//native isprint(c);
	cell AMX_NATIVE_CALL ctype_isprint(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isprint: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isprint(params[2]);
	}
	//native ispunct(c);
	cell AMX_NATIVE_CALL ctype_ispunct(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> ispunct: expected 1 parameters but found %d parameters.", get_params_count());
		return std::ispunct(params[2]);
	}
	//native isspace(c);
	cell AMX_NATIVE_CALL ctype_isspace(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isspace: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isspace(params[2]);
	}
	//native isupper(c);
	cell AMX_NATIVE_CALL ctype_isupper(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isupper: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isupper(params[2]);
	}
	//native isxdigit(c);
	cell AMX_NATIVE_CALL ctype_isxdigit(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] ctype>> isxdigit: expected 1 parameters but found %d parameters.", get_params_count());
		return std::isxdigit(params[2]);
	}
}
