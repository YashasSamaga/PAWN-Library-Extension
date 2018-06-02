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

#if defined PLE_ISC_INCLUDED
	#endinput
#endif
#define PLE_ISC_INCLUDED

/* dependencies */
#include <PLE/config>

enum AMX_HEADER
{
	AMX_HEADER_SIZE,
	AMX_HEADER_MAGIC,
	AMX_HEADER_FILE_VERSION,
	AMX_HEADER_AMX_VERSION,
	AMX_HEADER_FLAGS,
	AMX_HEADER_DEFSIZE,
	AMX_HEADER_COD,
	AMX_HEADER_DAT,
	AMX_HEADER_HEA,
	AMX_HEADER_STP,
	AMX_HEADER_CIP,
	AMX_HEADER_PUBLICS,
	AMX_HEADER_NATIVES,
	AMX_HEADER_LIBRARIES,
	AMX_HEADER_PUBVARS,
	AMX_HEADER_TAGS,
	AMX_HEADER_NAMETABLE
}
enum AMX_FUNCSTUBNT
{
	AMX_FUNCSTUBNT_ADDRESS,
	AMX_FUNCSTUBNT_NAMEOFS
}

stock const AMX_HEADER_OFFSETS[] =
{
	0, 	//AMX_HEADER_SIZE
	4, 	//AMX_HEADER_MAGIC
	6, 	//AMX_HEADER_FILE_VERSION
	7, 	//AMX_HEADER_AMX_VERSION
	8, 	//AMX_HEADER_FLAGS
	10, //AMX_HEADER_DEFSIZE
	12, //AMX_HEADER_COD
	16, //AMX_HEADER_DAT
	20, //AMX_HEADER_HEA
	24, //AMX_HEADER_STP
	28, //AMX_HEADER_CIP
	32, //AMX_HEADER_PUBLICS
	36, //AMX_HEADER_NATIVES
	40, //AMX_HEADER_LIBRARIES
	44, //AMX_HEADER_PUBVARS
	48, //AMX_HEADER_TAGS
	52 	//AMX_HEADER_NAMETABLE
};

native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
native ReadAMXMemory(scriptKey, address, &val); //address relative to the script's DAT segment
native WriteAMXMemory(scriptKey, address, val); //address relative to the script's DAT segment

native ReadAMXMemoryArray(scriptKey, address, dest[], numcells); //address relative to the script's DAT segment
native WriteAMXMemoryArray(scriptKey, address, src[], numcells); //address relative to the script's DAT segment

native GetExternalFunctionID(scriptKey, const name[], &fid);
native CallExternalFunction(extFuncID, &ret, const format[], ...);
native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);

native GetExternalVariableID(scriptKey, const name[], &vid);
native GetExternalVariable(extVarID, &result);
native SetExternalVariable(extVarID, value);
native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
