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
#include "functional.h"

#include <cstring>
#include <functional>
#include <vector>

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

namespace PLE::functional
{
    static std::vector <std::function<cell(cell)>> unary_functions =
    {
        [](cell x)->cell { return -x; },	//negate
        [](cell x)->cell { return !x; },	//logical_not
        [](cell x)->cell { return ~x; },	//bit_not
        [](cell x)->cell { return x + 1; }, //increment
        [](cell x)->cell { return x - 1; }, //decrement

        [](cell x)->cell { float n = -amx_ctof(x);  return amx_ftoc(n); },		//negatef
        [](cell x)->cell { float n = amx_ctof(x) + 1;  return amx_ftoc(n); },	//incrementf
        [](cell x)->cell { float n = amx_ctof(x) - 1;  return amx_ftoc(n); },	//decrementf
    };

    static std::vector <std::function<cell(cell, cell)>> binary_functions =
    {
        [](cell a, cell b)->cell { return a + b;  }, //plus
        [](cell a, cell b)->cell { return a - b;  }, //minus
        [](cell a, cell b)->cell { return a * b;  }, //multiplies
        [](cell a, cell b)->cell { return a / b;  }, //divides
        [](cell a, cell b)->cell { return a % b;  }, //modulus
        [](cell a, cell b)->cell { return a == b; }, //equal_to
        [](cell a, cell b)->cell { return a != b; }, //not_equal_to
        [](cell a, cell b)->cell { return a > b;  }, //greater
        [](cell a, cell b)->cell { return a < b;  }, //less
        [](cell a, cell b)->cell { return a >= b; }, //greater_equal
        [](cell a, cell b)->cell { return a <= b; }, //less_equal

        [](cell a, cell b)->cell { return a && b; }, //logical_and
        [](cell a, cell b)->cell { return a || b; }, //logical_or
        [](cell a, cell b)->cell { return a & b;  }, //bit_and
        [](cell a, cell b)->cell { return a | b;  }, //bit_or
        [](cell a, cell b)->cell { return a ^ b;  }, //bit_xor

        [](cell a, cell b)->cell { float n = amx_ctof(a) + amx_ctof(b);  return amx_ftoc(n); }, //plusf
        [](cell a, cell b)->cell { float n = amx_ctof(a) - amx_ctof(b);  return amx_ftoc(n); }, //minusf
        [](cell a, cell b)->cell { float n = amx_ctof(a) * amx_ctof(b);  return amx_ftoc(n); }, //multipliesf
        [](cell a, cell b)->cell { float n = amx_ctof(a) / amx_ctof(b);  return amx_ftoc(n); }, //dividesf
        [](cell a, cell b)->cell { return  amx_ctof(a) == amx_ctof(b); }, //equal_tof
        [](cell a, cell b)->cell { return  amx_ctof(a) != amx_ctof(b); }, //not_equal_tof
        [](cell a, cell b)->cell { return  amx_ctof(a) > amx_ctof(b); }, //greaterf
        [](cell a, cell b)->cell { return  amx_ctof(a) < amx_ctof(b); }, //lessf
        [](cell a, cell b)->cell { return  amx_ctof(a) >= amx_ctof(b); }, //greater_equalf
        [](cell a, cell b)->cell { return  amx_ctof(a) <= amx_ctof(b); }, //less_equalf
    };

    static_assert(MAX_BINDS == 4);
    cell ExecuteFunctionC0(AMX *amx, const function& fid)
    {
        cell retval = 0;
        switch (fid.info.type)
        {
        case function_types::native:
        {
            cell params[MAX_BINDS + 1];
            params[0] = fid.info.argc * BYTES_PER_CELL;
            switch (fid.info.argc)
            {
            case 4:
                params[4] = fid.params[3];
                [[fallthrough]];
            case 3:
                params[3] = fid.params[2];
                [[fallthrough]];
            case 2:
                params[2] = fid.params[1];
                [[fallthrough]];
            case 1:
                params[1] = fid.params[0];
            }
            retval = reinterpret_cast<NativeFunctionPtr>(fid.faddress)(amx, params);
            break;
        }
        case function_types::publicf:
        {
            AMX *target_amx = iscript::GetInterfaceAMX(fid.expanded.scriptKey);
            switch (fid.info.argc)
            {
            case 4:
                amx_Push(target_amx, fid.params[3]);
                [[fallthrough]];
            case 3:
                amx_Push(target_amx, fid.params[2]);
                [[fallthrough]];
            case 2:
                amx_Push(target_amx, fid.params[1]);
                [[fallthrough]];
            case 1:
                amx_Push(target_amx, fid.params[0]);
            }
            amx_Exec(target_amx, &retval, fid.expanded.funcidx);
            break;
        }
        case function_types::defaultv:
        {
            switch (fid.info.argc)
            {
            case 2:
                retval = binary_functions[fid.findex](fid.params[0], fid.params[1]);
                break;
            case 1:
                retval = unary_functions[fid.findex](fid.params[0]);
                break;
            }
            break;
        }
        }
        if (fid.IsFlagSet(function_flags::not_fn))
            return !retval;
        return retval;
    }
    cell ExecuteFunctionC1(AMX *amx, const function& fid, cell cparam)
    {
        cell retval = 0;
        switch (fid.info.type)
        {
        case function_types::native:
        {
            cell params[MAX_BINDS + 2];
            params[0] = fid.info.argc * BYTES_PER_CELL;
            switch (fid.info.argc)
            {
            case 5:
                params[1] = fid.params[0];
                params[2] = fid.params[1];
                params[3] = fid.params[2];
                params[4] = fid.params[3];
                params[5] = cparam;
                break;
            case 4:
                params[1] = fid.params[0];
                params[2] = fid.params[1];
                params[3] = fid.params[2];
                params[4] = fid.params[3];

                if (!fid.IsFlagSet(function_flags::bind1))
                    params[1] = cparam;
                else if (!fid.IsFlagSet(function_flags::bind2))
                    params[2] = cparam;
                else if (!fid.IsFlagSet(function_flags::bind3))
                    params[3] = cparam;
                else //BIND 4 must not be set
                    params[4] = cparam;
                break;
            case 3:
                params[1] = fid.params[0];
                params[2] = fid.params[1];
                params[3] = fid.params[2];

                if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind2)) //equivalent to !fid.IsFlagSet(function_flags::bind3)
                    params[3] = cparam;
                else if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind3)) //equivalent to !fid.IsFlagSet(function_flags::bind2)
                    params[2] = cparam;
                else //BIND 2 and 3 must be set
                    params[1] = cparam;
                break;
            case 2:
                if (fid.IsFlagSet(function_flags::bind1))
                {
                    params[1] = fid.params[0];
                    params[2] = cparam;
                }
                else //BIND2 must be set
                {
                    params[1] = cparam;
                    params[2] = fid.params[1];
                }
                break;
            case 1:
                params[1] = cparam;
                break;
            }
            retval = reinterpret_cast<NativeFunctionPtr>(fid.faddress)(amx, params);
            break;
        }
        case function_types::publicf:
        {
            AMX *target_amx = iscript::GetInterfaceAMX(fid.expanded.scriptKey);
            switch (fid.info.argc)
            {
            case 5:
                amx_Push(target_amx, cparam);
                amx_Push(target_amx, fid.params[3]);
                amx_Push(target_amx, fid.params[2]);
                amx_Push(target_amx, fid.params[1]);
                amx_Push(target_amx, fid.params[0]);
                break;
            case 4:
                if (!fid.IsFlagSet(function_flags::bind1))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam);
                }
                else if (!fid.IsFlagSet(function_flags::bind2))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[0]);
                }
                else if (!fid.IsFlagSet(function_flags::bind3))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                else //BIND 4 must not be set
                {
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                break;
            case 3:
                if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind2))
                {
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                else if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind3))
                {
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[0]);
                }
                else //BIND 2 and 3 must be set
                {
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam);
                }
                break;
            case 2:
                if (fid.IsFlagSet(function_flags::bind1))
                {
                    amx_Push(target_amx, cparam);
                    amx_Push(target_amx, fid.params[0]);
                }
                else //BIND 2 must be set
                {
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam);
                }
                break;
            case 1:
                amx_Push(target_amx, cparam);
                break;
            }
            amx_Exec(target_amx, &retval, fid.expanded.funcidx);
            break;
        }
        case function_types::defaultv:
        {
            switch (fid.info.argc)
            {
            case 1:
                retval = unary_functions[fid.findex](cparam);
                break;
            case 2:
                if (fid.IsFlagSet(function_flags::bind1))
                    retval = binary_functions[fid.findex](fid.params[0], cparam);
                else //BIND2 must be set
                    retval = binary_functions[fid.findex](cparam, fid.params[1]);
                break;
            }
            break;
        }
        }
        if (fid.IsFlagSet(function_flags::not_fn))
            return !retval;
        return retval;
    }
    cell ExecuteFunctionC2(AMX *amx, const function& fid, cell cparam1, cell cparam2)
    {
        cell retval = 0;
        switch (fid.info.type)
        {
        case function_types::native:
        {
            cell params[7];
            params[0] = fid.info.argc * BYTES_PER_CELL;
            switch (fid.info.argc)
            {
            case 6:
                params[1] = fid.params[0];
                params[2] = fid.params[1];
                params[3] = fid.params[2];
                params[4] = fid.params[3];
                params[5] = cparam1;
                params[6] = cparam2;
                break;
            case 5:
                params[1] = fid.params[0];
                params[2] = fid.params[1];
                params[3] = fid.params[2];
                params[4] = fid.params[3];
                params[5] = cparam2;

                if (!fid.IsFlagSet(function_flags::bind1))
                    params[1] = cparam1;
                else if (!fid.IsFlagSet(function_flags::bind2))
                    params[2] = cparam1;
                else if (!fid.IsFlagSet(function_flags::bind3))
                    params[3] = cparam1;
                else //BIND 4 must not be set
                    params[4] = cparam1;
                break;
            case 4:
                if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind2)) //equivalent to !fid.IsFlagSet(function_flags::bind3)
                {
                    params[1] = fid.params[0];
                    params[2] = fid.params[1];
                    params[3] = cparam1;
                    params[4] = cparam2;
                }
                else if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind3)) //equivalent to !fid.IsFlagSet(function_flags::bind2)
                {
                    params[1] = fid.params[0];
                    params[2] = cparam1;
                    params[3] = fid.params[2];
                    params[4] = cparam2;
                }
                else  if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind4))
                {
                    params[1] = fid.params[0];
                    params[2] = cparam1;
                    params[3] = cparam2;
                    params[4] = fid.params[3];
                }
                else  if (fid.IsFlagSet(function_flags::bind2) && fid.IsFlagSet(function_flags::bind3))
                {
                    params[1] = cparam1;
                    params[2] = fid.params[1];
                    params[3] = fid.params[2];
                    params[4] = cparam2;
                }
                else  if (fid.IsFlagSet(function_flags::bind2) && fid.IsFlagSet(function_flags::bind4))
                {
                    params[1] = cparam1;
                    params[2] = fid.params[1];
                    params[3] = cparam2;
                    params[4] = fid.params[3];
                }
                else  if (fid.IsFlagSet(function_flags::bind3) && fid.IsFlagSet(function_flags::bind4))
                {
                    params[1] = cparam1;
                    params[2] = cparam2;
                    params[3] = fid.params[2];
                    params[4] = fid.params[3];
                }
                break;
            case 3:
                if (fid.IsFlagSet(function_flags::bind1))
                {
                    params[1] = fid.params[0];
                    params[2] = cparam1;
                    params[3] = cparam2;
                }
                else if (fid.IsFlagSet(function_flags::bind2))
                {
                    params[1] = cparam1;
                    params[2] = fid.params[1];
                    params[3] = cparam1;
                }
                else //BIND 3 must be set
                {
                    params[1] = cparam1;
                    params[2] = cparam2;
                    params[3] = fid.params[2];
                }
                break;
            case 2:
                params[0] = 2 * BYTES_PER_CELL;
                params[1] = cparam1;
                params[2] = cparam2;
                break;
            }
            retval = reinterpret_cast<NativeFunctionPtr>(fid.faddress)(amx, params);
            break;
        }
        case function_types::publicf:
        {
            AMX *target_amx = iscript::GetInterfaceAMX(fid.expanded.scriptKey);
            switch (fid.info.argc)
            {
            case 6:
                amx_Push(target_amx, cparam2);
                amx_Push(target_amx, cparam1);
                amx_Push(target_amx, fid.params[3]);
                amx_Push(target_amx, fid.params[2]);
                amx_Push(target_amx, fid.params[1]);
                amx_Push(target_amx, fid.params[0]);
                break;
            case 5:
                if (!fid.IsFlagSet(function_flags::bind1))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam1);
                }
                else if (!fid.IsFlagSet(function_flags::bind2))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[0]);
                }
                else if (!fid.IsFlagSet(function_flags::bind3))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                else //BIND 4 must not be set
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                break;
            case 4:
                if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind2)) //equivalent to !fid.IsFlagSet(function_flags::bind3)
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, fid.params[0]);
                }
                else if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind3)) //equivalent to !fid.IsFlagSet(function_flags::bind2)
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[0]);
                }
                else  if (fid.IsFlagSet(function_flags::bind1) && fid.IsFlagSet(function_flags::bind4))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[0]);
                }
                else  if (fid.IsFlagSet(function_flags::bind2) && fid.IsFlagSet(function_flags::bind3))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam1);
                }
                else  if (fid.IsFlagSet(function_flags::bind2) && fid.IsFlagSet(function_flags::bind4))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam1);
                }
                else  if (fid.IsFlagSet(function_flags::bind3) && fid.IsFlagSet(function_flags::bind4))
                {
                    amx_Push(target_amx, fid.params[3]);
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                }
                break;
            case 3:
                if (fid.IsFlagSet(function_flags::bind1))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                    amx_Push(target_amx, fid.params[0]);
                }
                else if (fid.IsFlagSet(function_flags::bind2))
                {
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, fid.params[1]);
                    amx_Push(target_amx, cparam1);
                }
                else //BIND 3 must be set
                {
                    amx_Push(target_amx, fid.params[2]);
                    amx_Push(target_amx, cparam2);
                    amx_Push(target_amx, cparam1);
                }
                break;
            case 2:
                amx_Push(target_amx, cparam2);
                amx_Push(target_amx, cparam1);
                break;
            }
            amx_Exec(target_amx, &retval, fid.expanded.funcidx);
            break;
        }
        case function_types::defaultv:
        {
            retval = binary_functions[fid.findex](cparam1, cparam2);
            break;
        }
        }
        if (fid.IsFlagSet(function_flags::not_fn)) return !retval;
        return retval;
    }

    namespace natives
    {
        //native _make_function(func[FTSIZE], const fname[], argc, type = FUNCTION_ID_TYPE_PUBLIC, flags = 0, scriptKey = INVALID_SCRIPT_KEY);
        cell AMX_NATIVE_CALL make_function(AMX *amx, cell* params)
        {
            error_if(!check_params(6), "[PLE] functional>> make_function: expected 6 parameters but found %d parameters.", get_params_count());
            cell *dest_addr = NULL;
            amx_GetAddr(amx, params[1], &dest_addr);
            cell *name_addr = NULL;
            amx_GetAddr(amx, params[2], &name_addr);

            cell argc = params[3];
            error_if(argc > 31, "[PLE] functional>> make_function: 'argc' (%d) must be less than 32", argc);

            char name[MAX_SYMBOL_LEN];
            amx_GetString(name, name_addr, 0, sizeof(name));

            switch (params[4])
            {
            case functional::function_types::publicf:
            {
                int funcidx = 0;
                if (amx_FindPublic(amx, name, &funcidx) == AMX_ERR_NONE)
                {
                    if (params[6] == iscript::INVALID_SCRIPT_KEY)
                        params[6] = iscript::FindInterface(amx);
                    else 
                    {
                        error_if(!iscript::IsValidScript(params[6]), "[PLE] functional>> make_function: Invalid 'scriptkey' (%d) passed.", params[6]);
                    }

                    functional::function id(argc, static_cast<uint16_t>(params[5]), static_cast<uint16_t>(funcidx), static_cast<uint8_t>(params[6]));
                    id.encode(dest_addr);
                    return true;
                }
                break;
            }
            case functional::function_types::native:
            {
                AMX_HEADER * hdr = (AMX_HEADER *)amx->base;
                AMX_FUNCSTUB * func;

                int num = NUMENTRIES(hdr, natives, libraries);
                for (int idx = 0; idx != num; idx++)
                {
                    func = GETENTRY(hdr, natives, idx);
                    if (!std::strcmp(name, GETENTRYNAME(hdr, func)))
                    {
                        functional::function id(argc, static_cast<uint16_t>(params[5]), static_cast<uint32_t>(func->address));
                        id.encode(dest_addr);
                        return true;
                    }
                }
                break;
            }
            default:
                error_if(true, "[PLE] functional>> make_function: unknown function type");
                break;
            }
            return false;
        }
    }
}