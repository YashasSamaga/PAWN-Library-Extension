/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

access to the host
system.cpp

*************************************************************************************************************/
#include "main.h"
#include "system.h"

#include <cstdlib>
/************************************************************************************************************/
namespace PLE::natives
{
	//native system(const cmd[]);
	cell AMX_NATIVE_CALL system_system(AMX * amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] system>> system: expected 1 parameters but found %d parameters.", get_params_count());
		cell *addr, len;
		amx_GetAddr(amx, params[1], &addr);	
		amx_StrLen(addr, &len);
		len++;
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		int retval = std::system(text);

		delete[] text;
		return retval;
	}
	//native getenv(const env_var[], dest[], dest_size = sizeof(dest));
	cell AMX_NATIVE_CALL system_getenv(AMX * amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] system>> getenv: expected 3 parameters but found %d parameters.", get_params_count());

		cell *var_addr, len;
		amx_GetAddr(amx, params[1], &var_addr);		
		amx_StrLen(var_addr, &len);
		len++;
		char* env_var = new char[len];

		char *str = std::getenv(env_var);

		cell *dest_addr;
		amx_GetAddr(amx, params[2], &dest_addr);
		amx_SetString(dest_addr, str, 0, 0, params[3]);
		delete[] env_var;
		return 0;
	}
}
