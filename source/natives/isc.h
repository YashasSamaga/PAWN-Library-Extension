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

#ifndef PLE_ISC_H_INCLUDED
#define PLE_ISC_H_INCLUDED

#include "main.h"

namespace PLE::isc
{
    class function
    {
    public:
        function(uint8_t scriptKey, uint16_t funcidx) { info.scriptKey = scriptKey;	info.funcidx = funcidx; }
        function(uint32_t fid) { decode(fid); }

        void decode(uint32_t fid)
        {
            info.scriptKey = (fid & 0xFF000000) >> 24;
            info.funcidx = (fid & 0x00FFFF00) >> 8;
        }
        void encode(uint32_t& fid) const
        {
            fid = (info.scriptKey << 24) | (info.funcidx << 8);
        }
        iscript::ScriptKey_t GetScriptKey() const { return info.scriptKey; }
        iscript::FunctionIndex_t GetFunctionIndex() const { return info.funcidx; }
    private:
        struct {
            uint32_t scriptKey : 8;
            uint32_t funcidx : 16;
            uint32_t reserved : 8;
        } info;
        static_assert(sizeof(cell) == 4);
        static_assert(sizeof(iscript::ScriptKey_t) == 1);
        static_assert(sizeof(iscript::FunctionIndex_t) == 2);
    };

    class variable
    {
    public:
        variable(uint8_t scriptKey, uint16_t varidx) { info.scriptKey = scriptKey;	info.varidx = varidx; }
        variable(uint32_t vid) { decode(vid); }

        void decode(uint32_t vid)
        {
            info.scriptKey = (vid & 0xFF000000) >> 24;
            info.varidx = (vid & 0x00FFFF00) >> 8;
        }
        void encode(uint32_t& vid)
        {
            vid = (info.scriptKey << 24) | (info.varidx << 8);
        }
        iscript::ScriptKey_t GetScriptKey() const { return info.scriptKey; }
        iscript::VariableIndex_t GetVariableIndex() const { return info.varidx; }
    private:
        struct {
            uint32_t scriptKey : 8;
            uint32_t varidx : 16;
            uint32_t reserved : 8;
        } info;
        static_assert(sizeof(cell) == 4);
        static_assert(sizeof(iscript::ScriptKey_t) == 1);
        static_assert(sizeof(iscript::VariableIndex_t) == 2);
    };

    namespace natives
    {
        //native GetAMXHeader(scriptKey, hdr[AMX_HEADER]);
        extern cell AMX_NATIVE_CALL GetAMXHeader(AMX * amx, cell *params);
        //native ReadAMXMemory(scriptKey, address, &val);
        extern cell AMX_NATIVE_CALL ReadAMXMemory(AMX * amx, cell *params);
        //native WriteAMXMemory(scriptKey, address, val);
        extern cell AMX_NATIVE_CALL WriteAMXMemory(AMX * amx, cell *params);
        //native ReadAMXMemoryArray(scriptKey, address, dest[], numcells);
        extern cell AMX_NATIVE_CALL ReadAMXMemoryArray(AMX * amx, cell *params);
        //native WriteAMXMemoryArray(scriptKey, address, src[], numcells);
        extern cell AMX_NATIVE_CALL WriteAMXMemoryArray(AMX * amx, cell *params);
        //native GetExternalFunctionID(scriptKey, const name[]);
        extern cell AMX_NATIVE_CALL GetExternalFunctionID(AMX * amx, cell* params);
        //native CallExternalFunction(extFuncID, &ret, const format[], ...);
        extern cell AMX_NATIVE_CALL CallExternalFunction(AMX * amx, cell* params);
        //native GetExternalFunctionInfo(extFuncID, &scriptKey, &varidx);
        extern cell AMX_NATIVE_CALL GetExternalFunctionInfo(AMX * amx, cell* params);
        //native GetExternalVariableID(scriptKey, const name[]);
        extern cell AMX_NATIVE_CALL GetExternalVariableID(AMX * amx, cell* params);
        //native GetExternalVariable(extVarID, &result);
        extern cell AMX_NATIVE_CALL GetExternalVariableInfo(AMX * amx, cell* params);
        //native SetExternalVariable(extVarID, value);
        extern cell AMX_NATIVE_CALL GetExternalVariable(AMX * amx, cell* params);
        //native GetExternalVariableInfo(extVarID, &scriptKey, &varidx);
        extern cell AMX_NATIVE_CALL SetExternalVariable(AMX * amx, cell* params);
    }
}

#endif /* PLE_ISC_H_INCLUDED */