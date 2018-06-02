/*
** PAWN Library Extension (PLE)
**
** This file is part of PAWN Library Extension.
**
**   This library is free software: you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation, either version 3 of the License, or
**   (at your option) any later version.
**
**   This library is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
** Copyright (C) 2016-2018  Yashas Samaga
*/

#include "main.h"
#include "iscript.h"

#include "isc.h"

namespace PLE::isc
{
		namespace amx_header_fields
		{
			enum
			{
				size = 0,
				magic,
				file_version,
				amx_version,
				flags,
				defsize,
				cod,
				dat,
				hea,
				stp,
				cip,
				publics,
				natives,
				libraries,
				pubvars,
				tags,
				nametable
			};
		}
	
	namespace natives
	{
		//native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
		cell AMX_NATIVE_CALL GetAMXHeader(AMX * amx, cell *params)
		{
			error_if(!check_params(2), "[PLE] isc>> : expected 2 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1])) return false;

			cell* dest_hdr = NULL;
			amx_GetAddr(amx, params[2], &dest_hdr);

			AMX_HEADER * src_hdr = (AMX_HEADER *)iscript::GetInterfaceAMX(params[1])->base;
			dest_hdr[isc::amx_header_fields::size] = src_hdr->size;
			dest_hdr[isc::amx_header_fields::magic] = src_hdr->magic;
			dest_hdr[isc::amx_header_fields::file_version] = src_hdr->file_version;
			dest_hdr[isc::amx_header_fields::amx_version] = src_hdr->amx_version;
			dest_hdr[isc::amx_header_fields::flags] = src_hdr->flags;
			dest_hdr[isc::amx_header_fields::defsize] = src_hdr->defsize;
			dest_hdr[isc::amx_header_fields::cod] = src_hdr->cod;
			dest_hdr[isc::amx_header_fields::dat] = src_hdr->dat;
			dest_hdr[isc::amx_header_fields::hea] = src_hdr->hea;
			dest_hdr[isc::amx_header_fields::stp] = src_hdr->stp;
			dest_hdr[isc::amx_header_fields::cip] = src_hdr->cip;
			dest_hdr[isc::amx_header_fields::publics] = src_hdr->publics;
			dest_hdr[isc::amx_header_fields::natives] = src_hdr->natives;
			dest_hdr[isc::amx_header_fields::libraries] = src_hdr->libraries;
			dest_hdr[isc::amx_header_fields::pubvars] = src_hdr->pubvars;
			dest_hdr[isc::amx_header_fields::tags] = src_hdr->tags;
			dest_hdr[isc::amx_header_fields::nametable] = src_hdr->nametable;
			return true;
		}
		//native ReadAMXMemory(scriptKey, address, &val); //address relative to the script's DAT segment
		cell AMX_NATIVE_CALL ReadAMXMemory(AMX * amx, cell *params)
		{
			error_if(!check_params(3), "[PLE] isc>> ReadAMXMemory: expected 3 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1])) return false;

			cell* read_addr = NULL;
			amx_GetAddr(iscript::GetInterfaceAMX(params[1]), params[2], &read_addr);

			cell* dest_addr = NULL;
			amx_GetAddr(amx, params[3], &dest_addr);

			*dest_addr = *read_addr;
			return true;
		}
		//native WriteAMXMemory(scriptKey, address, val); //address relative to the script's DAT segment
		cell AMX_NATIVE_CALL WriteAMXMemory(AMX * amx, cell *params)
		{
			error_if(!check_params(3), "[PLE] isc>> WriteAMXMemory: expected 3 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1])) return false;

			cell* dest_addr = NULL;
			amx_GetAddr(iscript::GetInterfaceAMX(params[1]), params[2], &dest_addr);

			*dest_addr = params[3];
			return true;
		}
		//native ReadAMXMemoryArray(scriptKey, address, dest[], numcells); //address relative to the script's DAT segment
		cell AMX_NATIVE_CALL ReadAMXMemoryArray(AMX * amx, cell *params)
		{
			error_if(!check_params(4), "[PLE] isc>> ReadAMXMemoryArray: expected 4 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1])) return false;

			cell* read_addr = NULL;
			amx_GetAddr(iscript::GetInterfaceAMX(params[1]), params[2], &read_addr);

			cell* dest_addr = NULL;
			amx_GetAddr(amx, params[3], &dest_addr);

			int numcells = params[4];
			while (numcells-- > 0)
				*dest_addr++ = *read_addr++;
			return true;
		}
		//native WriteAMXMemoryArray(scriptKey, address, src[], numcells); //address relative to the script's DAT segment
		cell AMX_NATIVE_CALL WriteAMXMemoryArray(AMX * amx, cell *params)
		{
			error_if(!check_params(4), "[PLE] isc>> WriteAMXMemoryArray: expected 4 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1])) return false;

			cell* dest_addr = NULL;
			amx_GetAddr(iscript::GetInterfaceAMX(params[1]), params[2], &dest_addr);

			cell* src_addr = NULL;
			amx_GetAddr(amx, params[3], &src_addr);

			int numcells = params[4];
			while (numcells-- > 0)
				*dest_addr++ = *src_addr++;
			return true;
		}

		//native GetExternalFunctionID(scriptKey, const name[], &fid);
		cell AMX_NATIVE_CALL GetExternalFunctionID(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] isc>> GetExternalFunctionID: expected 2 parameters but found %d parameters.", get_params_count());

			if (iscript::IsValidScript(params[1]))
				return false;

			cell *name_addr = NULL;
			amx_GetAddr(amx, params[2], &name_addr);

			char name[32];
			amx_GetString(name, name_addr, 0, sizeof(name));

			int funcidx, amx_error = amx_FindPublic(iscript::GetInterfaceAMX(params[1]), name, &funcidx);
			if (amx_error == AMX_ERR_NONE)
			{
				isc::function id(params[1], funcidx);
				return true;
			}
			return false;
		}
		//native CallExternalFunction(extFuncID, &ret, const format[], ...);
		cell AMX_NATIVE_CALL CallExternalFunction(AMX * amx, cell* params)
		{
			error_if(!check_params_min(3), "[PLE] isc>> CallExternalFunction: expected at least 3 parameters but found %d parameters.", get_params_count());
			isc::function fid(params[1]);

			AMX * target_amx = iscript::GetInterfaceAMX(fid.GetScriptKey());
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
			if (param_count) logprintf("[WARNING] PAWN Library Extension >> number of specifiers give to CallExternalFunction does not agree with the number of parameters. (Difference: %d)", param_count);

			cell *retval;
			amx_GetAddr(target_amx, params[2], &retval);
			amx_Exec(target_amx, retval, fid.GetFunctionIndex());
			amx_Release(target_amx, release_addr);
			return true;
		}
		//native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);
		cell AMX_NATIVE_CALL GetExternalFunctionInfo(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] isc>> GetExternalFunctionInfo: expected 3 parameters but found %d parameters.", get_params_count());
			isc::function fid(params[1]);

			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = fid.GetScriptKey();

			amx_GetAddr(amx, params[3], &addr);
			*addr = fid.GetFunctionIndex();
			return true;
		}

		//native GetExternalVariableID(scriptKey, const name[], &vid);
		cell AMX_NATIVE_CALL GetExternalVariableID(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] isc>> GetExternalVariableID: expected 2 parameters but found %d parameters.", get_params_count());
			if (iscript::IsValidScript(params[1])) return false;

			cell *name_addr = NULL, tmp;
			amx_GetAddr(amx, params[2], &name_addr);

			char search_pubvar[32], cur_pubvar[32];
			amx_GetString(search_pubvar, name_addr, 0, sizeof(search_pubvar));

			AMX * target_amx = iscript::GetInterfaceAMX(params[1]);
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
					isc::variable vid(params[1], mid);
					return true;
				}
			}
			return false;
		}
		//native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
		cell AMX_NATIVE_CALL GetExternalVariableInfo(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] isc>> GetExternalVariable: expected 2 parameters but found %d parameters.", get_params_count());
			isc::variable vid(params[1]);
	
			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = vid.GetScriptKey();

			amx_GetAddr(amx, params[3], &addr);
			*addr = vid.GetVariableIndex();
			return true;
		}
		//native GetExternalVariable(extVarID, &result);
		cell AMX_NATIVE_CALL GetExternalVariable(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] isc>> SetExternalVariable: expected 2 parameters but found %d parameters.", get_params_count());
			isc::variable vid(params[1]);

			AMX *target_amx = iscript::GetInterfaceAMX(vid.GetScriptKey());

			char name[32];
			cell pubvar_addr;
			amx_GetPubVar(target_amx, vid.GetVariableIndex(), name, &pubvar_addr);

			cell *pubvar_phyaddr;
			amx_GetAddr(target_amx, pubvar_addr, &pubvar_phyaddr);

			cell *res_addr;
			amx_GetAddr(amx, params[2], &res_addr);

			*res_addr = *pubvar_phyaddr;
			return true;
		}
		//native SetExternalVariable(extVarID, value);
		cell AMX_NATIVE_CALL SetExternalVariable(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] isc>> GetExternalVariableInfo: expected 3 parameters but found %d parameters.", get_params_count());
			isc::variable vid(params[1]);

			AMX * target_amx = iscript::GetInterfaceAMX(vid.GetScriptKey());
			cell pubvar_addr;

			char name[32];
			amx_GetPubVar(target_amx, vid.GetVariableIndex(), name, &pubvar_addr);

			cell *pubvar_phyaddr;
			amx_GetAddr(target_amx, pubvar_addr, &pubvar_phyaddr);

			*pubvar_phyaddr = params[2];
			return true;
		}
	}	
}
