/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interscript communication (ISC)
isc.cpp

*************************************************************************************************************/
#include "..\main.h"
#include "..\interface.h"

#include "isc.h"

#include <stdlib.h>
/************************************************************************************************************/
typedef struct externalFunctionID 
{
	unsigned short scriptKey : 8;
	unsigned short funcidx : 16;
	unsigned short reserved : 8;

	externalFunctionID(int scriptKey, int funcidx) : scriptKey(scriptKey), funcidx(funcidx), reserved(VALIDITY_EFID_RESBITS) { }
	externalFunctionID(int efid)
	{
		scriptKey = (0xFF000000 & efid) >> 24;
		funcidx = (0xFFFF00 & efid) >> 8;
		reserved = (0xFF & efid);
	}
	operator int() 
	{
		return (scriptKey << 24) + (funcidx << 8) + reserved;
	}
	int operator=(int efid)
	{
		scriptKey = (0xFF000000 & efid) >> 24;
		funcidx = (0xFFFF00 & efid) >> 8;
		reserved = (0xFF & efid);
		return *this;
	}
}externalFunctionID;
typedef struct externalVariableID
{
	unsigned short scriptKey : 8;
	unsigned short varidx : 16;
	unsigned short reserved : 8;

	externalVariableID(int scriptKey, int varidx) : scriptKey(scriptKey), varidx(varidx), reserved(VALIDITY_EVID_RESBITS) { }
	externalVariableID(int evid)
	{
		scriptKey = (0xFF000000 & evid) >> 24;
		varidx = (0xFFFF00 & evid) >> 8;
		reserved = (0xFF & evid);
	}
	operator int()
	{
		return (scriptKey << 24) + (varidx << 8) + reserved;
	}
	int operator=(int evid)
	{
		scriptKey = (0xFF000000 & evid) >> 24;
		varidx = (0xFFFF00 & evid) >> 8;
		reserved = (0xFF & evid);
		return *this;
	}
}externalVariableID;

namespace Natives
{
	cell AMX_NATIVE_CALL isc_GetExternalFunctionID(AMX* amx, cell* params)
	{
		const unsigned int scriptKey = params[1];

		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return INVALID_EXT_FID;
		if (InterfaceList[scriptKey] == nullptr) return INVALID_EXT_FID;

		cell *name_addr = NULL;
		amx_GetAddr(amx, params[2], &name_addr);

		char name[32];
		amx_GetString(name, name_addr, 0, sizeof(name));			

		int funcidx, amx_error = amx_FindPublic(InterfaceList[scriptKey]->amx, name, &funcidx);		
		if (amx_error == AMX_ERR_NONE)
		{
			externalFunctionID id(scriptKey, funcidx);
			return static_cast<int>(id);
		}
		return INVALID_EXT_FID;
	}
	cell AMX_NATIVE_CALL isc_CallExternalFunction(AMX* amx, cell* params)
	{
		const externalFunctionID id = params[1];
		if (id.reserved != VALIDITY_EFID_RESBITS) return false;

		const unsigned int scriptKey = id.scriptKey;
		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return false;
		if (InterfaceList[scriptKey] == nullptr) return false;

		AMX * target_amx = InterfaceList[scriptKey]->amx;	

		cell release_addr = NULL;

		int param_count = (params[0] / 4) - 3, len = 0;
		if (param_count)
		{			
			cell *format = NULL;
			amx_GetAddr(amx, params[3], &format);
			
			int array_count = 0, arraysizes[32];

			while (format[len] && param_count--)
			{
				if (format[len] == 'a')
				{
					char size[6];
					int size_count = 0;

					len += 2;
					while (format[len])
					{
						if (format[len] == ']' || size_count == 6) break;
						size[size_count++] = format[len++];
					}
					if (format[len] != ']' || size_count == 0)
					{
						logprintf("[ERROR] PAWN Library Extension >> 'a' specifier not followed by a valid array size in CallExternalFunction.");
						return false;
					}
					size[size_count] = '\0';
					arraysizes[array_count++] = atoi(size);
				}
				len++;
			}
			while (len--)
			{
				switch (format[len])
				{
					case 'd':
					case 'i':
					case 'f':
					{
						cell* cell_addr = NULL;
						amx_GetAddr(amx, params[len + 4], &cell_addr);
						amx_Push(target_amx, *cell_addr);						
						break;
					}
					case 'a':
					{
						cell* arr_addr = NULL;
						amx_GetAddr(amx, params[len + 4], &arr_addr);

						cell amx_addr, *phys_addr;
						amx_Allot(target_amx, arraysizes[--array_count], &amx_addr, &phys_addr);
						memcpy(phys_addr, arr_addr, arraysizes[array_count]*4);
						amx_Push(target_amx, amx_addr);

						if (release_addr == NULL) release_addr = amx_addr;
						break;
					}
					case 's':
					{
						int strl = 0;
						cell *str = NULL;
						amx_GetAddr(amx, params[len + 4], &str);
						amx_StrLen(str, &strl);
						strl++;

						cell amx_addr, *phys_addr;
						amx_Allot(target_amx, strl, &amx_addr, &phys_addr);
						memcpy(phys_addr, str, strl * 4);
						amx_Push(target_amx, amx_addr);

						if (release_addr == NULL) release_addr = amx_addr;
						break;
					}
				}
			}
		}
		if(param_count) logprintf("[WARNING] PAWN Library Extension >> number of specifiers give to CallExternalFunction does not agree with the number of paramters. (Difference: %d)", param_count);

		cell *ret_addr;
		amx_GetAddr(target_amx, params[2], &ret_addr);
		amx_Exec(target_amx, ret_addr, id.funcidx);
		amx_Release(target_amx, release_addr);
		return true;
	}
	cell AMX_NATIVE_CALL isc_GetExternalFunctionInfo(AMX* amx, cell* params)
	{		
		const externalFunctionID id = params[1];
		if (id.reserved != VALIDITY_EFID_RESBITS) return false;

		cell *addr;
		amx_GetAddr(amx, params[2], &addr);
		*addr = id.scriptKey;

		amx_GetAddr(amx, params[3], &addr);
		*addr = id.funcidx;

		return true;
	}

	cell AMX_NATIVE_CALL isc_GetExternalVariableID(AMX* amx, cell* params)
	{
		const unsigned int scriptKey = params[1];

		if (scriptKey < 0 || scriptKey >= InterfaceList.size()) return INVALID_EXT_VID;
		if (InterfaceList[scriptKey] == nullptr) return INVALID_EXT_VID;

		cell *name_addr = NULL, tmp;
		amx_GetAddr(amx, params[2], &name_addr);

		char search_pubvar[32], cur_pubvar[32];
		amx_GetString(search_pubvar, name_addr, 0, sizeof(search_pubvar));
		
		AMX * target_amx = InterfaceList[scriptKey]->amx;
		int first = 0, last, mid, result; 
		amx_NumPubVars(target_amx, &last);
		last--;

		while (first <= last)
		{
			mid = (first + last) / 2;
			
			amx_GetPubVar(target_amx, mid, cur_pubvar, &tmp);
			result = strcmp(cur_pubvar, search_pubvar);

			if (result > 0)
				last = mid - 1;
			else if (result < 0)
				first = mid + 1;
			else
			{
				externalVariableID id(scriptKey, mid);
				return static_cast<int>(id);
			}
		}
		return INVALID_EXT_VID;
	}
	cell AMX_NATIVE_CALL isc_GetExternalVariableInfo(AMX* amx, cell* params)
	{
		const externalVariableID id(params[1]);

		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		cell *addr;
		amx_GetAddr(amx, params[2], &addr);
		*addr = id.scriptKey;

		amx_GetAddr(amx, params[3], &addr);
		*addr = id.varidx;

		return true;
	}
	cell AMX_NATIVE_CALL isc_GetExternalVariable(AMX* amx, cell* params)
	{
		const externalVariableID id = params[1];
		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		AMX * target_amx = InterfaceList[id.scriptKey]->amx;			

		char name[32];
		cell pubvar_addr;
		amx_GetPubVar(target_amx, id.varidx, name, &pubvar_addr);

		cell *pubvar_phyaddr;
		amx_GetAddr(target_amx, pubvar_addr, &pubvar_phyaddr);

		cell *res_addr;
		amx_GetAddr(amx, params[2], &res_addr);

		*res_addr = *pubvar_phyaddr;
		return true;
	}
	cell AMX_NATIVE_CALL isc_SetExternalVariable(AMX* amx, cell* params)
	{
		const externalVariableID id = params[1];
		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		AMX * target_amx = InterfaceList[id.scriptKey]->amx;
		cell pubvar_addr;

		char name[32];
		amx_GetPubVar(target_amx, id.varidx, name, &pubvar_addr);

		cell *pubvar_phyaddr;
		amx_GetAddr(target_amx, pubvar_addr, &pubvar_phyaddr);

		*pubvar_phyaddr = params[2];
		return true;
	}
}
