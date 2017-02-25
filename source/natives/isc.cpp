/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interscript communication (ISC)
isc.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"

#include "isc.h"

#include <stdlib.h>
/************************************************************************************************************/
namespace Natives
{
	enum
	{
		AMX_HDR_SIZE,
		AMX_HDR_MAGIC,
		AMX_HDR_FILE_VERSION,
		AMX_HDR_AMX_VERSION,
		AMX_HDR_FLAGS,
		AMX_HDR_DEFSIZE,
		AMX_HDR_COD,
		AMX_HDR_DAT,
		AMX_HDR_HEA,
		AMX_HDR_STP,
		AMX_HDR_CIP,
		AMX_HDR_PUBLICS,
		AMX_HDR_NATIVES,
		AMX_HDR_LIBRARIES,
		AMX_HDR_PUBVARS,
		AMX_HDR_TAGS,
		AMX_HDR_NAMETABLE
	};
	//native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
	cell AMX_NATIVE_CALL isc_GetAMXHeader(AMX * amx, cell *params)
	{
		error_if(!check_params(2), "[PLE] isc>> : expected 2 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return false;

		cell* dest_hdr = NULL;
		amx_GetAddr(amx, params[2], &dest_hdr);

		AMX_HEADER * src_hdr = (AMX_HEADER *)Interface::GetInterfaceAMX(scriptKey)->base;
		dest_hdr[AMX_HDR_SIZE] = src_hdr->size;
		dest_hdr[AMX_HDR_MAGIC] = src_hdr->magic;
		dest_hdr[AMX_HDR_FILE_VERSION] = src_hdr->file_version;
		dest_hdr[AMX_HDR_AMX_VERSION] = src_hdr->amx_version;
		dest_hdr[AMX_HDR_FLAGS] = src_hdr->flags;
		dest_hdr[AMX_HDR_DEFSIZE] = src_hdr->defsize;
		dest_hdr[AMX_HDR_COD] = src_hdr->cod;
		dest_hdr[AMX_HDR_DAT] = src_hdr->dat;
		dest_hdr[AMX_HDR_HEA] = src_hdr->hea;
		dest_hdr[AMX_HDR_STP] = src_hdr->stp;
		dest_hdr[AMX_HDR_CIP] = src_hdr->cip;
		dest_hdr[AMX_HDR_PUBLICS] = src_hdr->publics;
		dest_hdr[AMX_HDR_NATIVES] = src_hdr->natives;
		dest_hdr[AMX_HDR_LIBRARIES] = src_hdr->libraries;
		dest_hdr[AMX_HDR_PUBVARS] = src_hdr->pubvars;
		dest_hdr[AMX_HDR_TAGS] = src_hdr->tags;
		dest_hdr[AMX_HDR_NAMETABLE] = src_hdr->nametable;
		return true;
	}
	//native ReadAMXMemory(scriptKey, address, &val); //address relative to the script's DAT segment
	cell AMX_NATIVE_CALL isc_ReadAMXMemory(AMX * amx, cell *params)
	{
		error_if(!check_params(3), "[PLE] isc>> ReadAMXMemory: expected 3 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return false;

		cell* read_addr = NULL;
		amx_GetAddr(Interface::GetInterfaceAMX(scriptKey), params[2], &read_addr);

		cell* dest_addr = NULL;
		amx_GetAddr(amx, params[3], &dest_addr);

		*dest_addr = *read_addr;
		return true;
	}
	//native WriteAMXMemory(scriptKey, address, val); //address relative to the script's DAT segment
	cell AMX_NATIVE_CALL isc_WriteAMXMemory(AMX * amx, cell *params)
	{
		error_if(!check_params(3), "[PLE] isc>> WriteAMXMemory: expected 3 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return false;

		cell* dest_addr = NULL;
		amx_GetAddr(Interface::GetInterfaceAMX(scriptKey), params[2], &dest_addr);

		*dest_addr = params[3];
		return true;
	}
	//native ReadAMXMemoryArray(scriptKey, address, dest[], numcells); //address relative to the script's DAT segment
	cell AMX_NATIVE_CALL isc_ReadAMXMemoryArray(AMX * amx, cell *params)
	{
		error_if(!check_params(4), "[PLE] isc>> ReadAMXMemoryArray: expected 4 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return false;

		cell* read_addr = NULL;
		amx_GetAddr(Interface::GetInterfaceAMX(scriptKey), params[2], &read_addr);

		cell* dest_addr = NULL;
		amx_GetAddr(amx, params[3], &dest_addr);

		int numcells = params[4];
		while (numcells-- > 0)
			*dest_addr++ = *read_addr++;
		return true;
	}
	//native WriteAMXMemoryArray(scriptKey, address, src[], numcells); //address relative to the script's DAT segment
	cell AMX_NATIVE_CALL isc_WriteAMXMemoryArray(AMX * amx, cell *params)
	{
		error_if(!check_params(4), "[PLE] isc>> WriteAMXMemoryArray: expected 4 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return false;

		cell* dest_addr = NULL;
		amx_GetAddr(Interface::GetInterfaceAMX(scriptKey), params[2], &dest_addr);

		cell* src_addr = NULL;
		amx_GetAddr(amx, params[3], &src_addr);

		int numcells = params[4];
		while (numcells-- > 0)
			*dest_addr++ = *src_addr++;
		return true;
	}

	//native GetExternalFunctionID(scriptKey, const name[]);
	cell AMX_NATIVE_CALL isc_GetExternalFunctionID(AMX* amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] isc>> GetExternalFunctionID: expected 2 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return INVALID_EXT_FID;

		cell *name_addr = NULL;
		amx_GetAddr(amx, params[2], &name_addr);

		char name[32];
		amx_GetString(name, name_addr, 0, sizeof(name));

		int funcidx, amx_error = amx_FindPublic(Interface::GetInterfaceAMX(scriptKey), name, &funcidx);
		if (amx_error == AMX_ERR_NONE)
		{
			externalFunctionID id(static_cast<uint8_t>(scriptKey), static_cast<uint16_t>(funcidx));
			return id;
		}
		return INVALID_EXT_FID;
	}
	//native CallExternalFunction(extFuncID, &ret, const format[], ...);
	cell AMX_NATIVE_CALL isc_CallExternalFunction(AMX* amx, cell* params)
	{
		error_if(!check_params_min(3), "[PLE] isc>> CallExternalFunction: expected at least 3 parameters but found %d parameters.", get_params_count());
		const externalFunctionID id = params[1];
		if (id.reserved != VALIDITY_EFID_RESBITS) return false;

		const unsigned int scriptKey = id.scriptKey;
		if (Interface::IsValidScript(scriptKey)) return false;

		AMX * target_amx = Interface::GetInterfaceAMX(scriptKey);
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
						size[size_count++] = static_cast<uint8_t>(format[len++]);
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
					memcpy(phys_addr, arr_addr, arraysizes[array_count] * 4);
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
		if (param_count) logprintf("[WARNING] PAWN Library Extension >> number of specifiers give to CallExternalFunction does not agree with the number of paramters. (Difference: %d)", param_count);

		cell *retval;
		amx_GetAddr(target_amx, params[2], &retval);
		amx_Exec(target_amx, retval, id.funcidx);
		amx_Release(target_amx, release_addr);
		return true;
	}
	//native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);
	cell AMX_NATIVE_CALL isc_GetExternalFunctionInfo(AMX* amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] isc>> GetExternalFunctionInfo: expected 3 parameters but found %d parameters.", get_params_count());
		const externalFunctionID id = params[1];
		if (id.reserved != VALIDITY_EFID_RESBITS) return false;

		cell *addr;
		amx_GetAddr(amx, params[2], &addr);
		*addr = id.scriptKey;

		amx_GetAddr(amx, params[3], &addr);
		*addr = id.funcidx;
		return true;
	}

	//native GetExternalVariableID(scriptKey, const name[]);
	cell AMX_NATIVE_CALL isc_GetExternalVariableID(AMX* amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] isc>> GetExternalVariableID: expected 2 parameters but found %d parameters.", get_params_count());
		const unsigned int scriptKey = params[1];
		if (Interface::IsValidScript(scriptKey)) return INVALID_EXT_VID;

		cell *name_addr = NULL, tmp;
		amx_GetAddr(amx, params[2], &name_addr);

		char search_pubvar[32], cur_pubvar[32];
		amx_GetString(search_pubvar, name_addr, 0, sizeof(search_pubvar));

		AMX * target_amx = Interface::GetInterfaceAMX(scriptKey);
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
				externalVariableID id(static_cast<uint8_t>(scriptKey), static_cast<uint16_t>(mid));
				return id;
			}
		}
		return INVALID_EXT_VID;
	}
	//native GetExternalVariable(extVarID, &result);
	cell AMX_NATIVE_CALL isc_GetExternalVariableInfo(AMX* amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] isc>> GetExternalVariable: expected 2 parameters but found %d parameters.", get_params_count());
		const externalVariableID id(params[1]);
		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		cell *addr;
		amx_GetAddr(amx, params[2], &addr);
		*addr = id.scriptKey;

		amx_GetAddr(amx, params[3], &addr);
		*addr = id.varidx;
		return true;
	}
	//native SetExternalVariable(extVarID, value);
	cell AMX_NATIVE_CALL isc_GetExternalVariable(AMX* amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] isc>> SetExternalVariable: expected 2 parameters but found %d parameters.", get_params_count());
		const externalVariableID id = params[1];
		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		AMX * target_amx = Interface::GetInterfaceAMX(id.scriptKey);

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
	//native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
	cell AMX_NATIVE_CALL isc_SetExternalVariable(AMX* amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] isc>> GetExternalVariableInfo: expected 3 parameters but found %d parameters.", get_params_count());
		const externalVariableID id = params[1];
		if (id.reserved != VALIDITY_EVID_RESBITS) return false;

		AMX * target_amx = Interface::GetInterfaceAMX(id.scriptKey);
		cell pubvar_addr;

		char name[32];
		amx_GetPubVar(target_amx, id.varidx, name, &pubvar_addr);

		cell *pubvar_phyaddr;
		amx_GetAddr(target_amx, pubvar_addr, &pubvar_phyaddr);

		*pubvar_phyaddr = params[2];
		return true;
	}
}
