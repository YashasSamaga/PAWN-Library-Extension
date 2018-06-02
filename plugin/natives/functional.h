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

#ifndef PLE_FUNCTIONAL_H_INCLUDED
#define PLE_FUNCTIONAL_H_INCLUDED

#include "main.h"
#include "iscript.h"

#include <cstdint>

namespace PLE::functional
{
    constexpr int MAX_BINDS = 4;
    constexpr int FTSIZE = MAX_BINDS + 2;

    typedef cell(*NativeFunctionPtr)(AMX*, cell[]);

    namespace function_types
    {
        constexpr int invalid = 0x00;
        constexpr int publicf = 0x01;
        constexpr int native = 0x02;
        constexpr int defaultv = 0x04;
    }

    namespace function_flags
    {
        constexpr int not = 0x01;
        constexpr int bind1 = 0x02;
        constexpr int bind2 = 0x04;
        constexpr int bind3 = 0x08;
        constexpr int bind4 = 0x10;
    }

    class function
    {
    public:
        using uint8_t = std::uint8_t;
        using uint16_t = std::uint16_t;
        using uint32_t = std::uint32_t;

        function(cell p_params[FTSIZE]) { decode(p_params); }
        function(uint8_t argc, uint16_t flags, int16_t funcidx, int8_t scriptKey)
        {
            //public
            info.type = function_types::publicf;
            info.argc = argc;
            info.flags = flags;

            expanded.funcidx = funcidx;
            expanded.scriptKey = scriptKey;
        }
        function(uint8_t argc, uint16_t flags, uint32_t addr)
        {
            //function_types::native
            faddress = addr;
            info.type = function_types::native;
            info.argc = argc;
            info.flags = flags;
        }

        void decode(cell p_params[FTSIZE])
        {
            info.type = (p_params[0] & 0xFF000000) >> 24;
            info.argc = (p_params[0] & 0x00FF0000) >> 16;
            info.flags = (p_params[0] & 0x0000FFFF);

            switch (info.type)
            {
            case function_types::publicf:
                expanded.funcidx = (p_params[1] & 0xFFFF0000) >> 16;
                expanded.scriptKey = (p_params[1] & 0x0000FF00) >> 8;
                break;
            case function_types::native:
                faddress = p_params[1];
                break;
            case function_types::defaultv:
                findex = p_params[1];
                break;
            }

            params[0] = p_params[2];
            params[1] = p_params[3];
            params[2] = p_params[4];
            params[3] = p_params[5];
        }
        void encode(cell dest[]) const
        {
            dest[0] = (info.type << 24) | (info.argc << 16) | info.flags;
            switch (info.type)
            {
            case function_types::publicf:
                dest[1] = (expanded.funcidx << 16) | (expanded.scriptKey << 8);
                break;
            case function_types::native:
                dest[1] = faddress;
                break;
            case function_types::defaultv:
                dest[1] = findex;
                break;
            }
        }

        bool IsValidFunctionID(size_t argc) const
        {
            if (IsFlagSet(function_flags::bind1))
                argc++;
            if (IsFlagSet(function_flags::bind2))
                argc++;
            if (IsFlagSet(function_flags::bind3))
                argc++;
            if (IsFlagSet(function_flags::bind4))
                argc++;
            return (argc == info.argc);
        }
        bool IsFlagSet(uint16_t flag) const { return !!(info.flags & flag); }

    private:
        struct info_t {
            uint32_t type : 8;
            uint32_t argc : 8;
            uint32_t flags : 16;
        } info;
        static_assert(sizeof(info_t) == 4);

        /*
            native functions use `faddress`
            public functions use `expanded`
            default functions use `findex`
        */
        union {
            uint32_t faddress;
            uint32_t findex;
            struct expanded_t {
                int16_t funcidx : 16; /* size used in static_assert (1) */
                int8_t scriptKey : 8; /* size used in static_assert (2) */
                uint8_t reserved : 8;
            } expanded;
            static_assert(sizeof(iscript::FunctionIndex_t) == 2); // (1)
            static_assert(sizeof(iscript::ScriptKey_t) == 1); // (2)            
            static_assert(sizeof(expanded_t) == 4);
        };
        static_assert(sizeof(cell) == 4);

        cell params[FTSIZE - 2];

        friend cell ExecuteFunctionC0(AMX*, const function&);
        friend cell ExecuteFunctionC1(AMX*, const function&, cell);
        friend cell ExecuteFunctionC2(AMX*, const function&, cell, cell);
    };

    namespace natives
    {
        extern cell AMX_NATIVE_CALL make_function(AMX* amx, cell* params);
    }
}

#endif /* PLE_FUNCTIONAL_H_INCLUDED */