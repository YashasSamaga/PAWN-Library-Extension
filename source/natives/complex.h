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

#ifndef PLE_COMPLEX_H_INCLUDED
#define PLE_COMPLEX_H_INCLUDED

#include "main.h"
#include <complex>

namespace PLE::complex
{
    namespace complex_offsets
    {
        constexpr int real = 0;
        constexpr int imag = 1;
    }

    namespace natives
    {
        extern cell cabs(AMX * amx, cell* params);
        extern cell carg(AMX * amx, cell* params);
        extern cell cnorm(AMX * amx, cell* params);
        extern cell cconj(AMX * amx, cell* params);
        extern cell cpolar(AMX * amx, cell* params);
        extern cell ccos(AMX * amx, cell* params);
        extern cell csin(AMX * amx, cell* params);
        extern cell ctan(AMX * amx, cell* params);
        extern cell cacos(AMX * amx, cell* params);
        extern cell casin(AMX * amx, cell* params);
        extern cell catan(AMX * amx, cell* params);
        extern cell ccosh(AMX * amx, cell* params);
        extern cell csinh(AMX * amx, cell* params);
        extern cell ctanh(AMX * amx, cell* params);
        extern cell cacosh(AMX * amx, cell* params);
        extern cell casinh(AMX * amx, cell* params);
        extern cell catanh(AMX * amx, cell* params);
        extern cell cexp(AMX * amx, cell* params);
        extern cell clog(AMX * amx, cell* params);
        extern cell clog10(AMX * amx, cell* params);
        extern cell cpow(AMX * amx, cell* params);
        extern cell csqrt(AMX * amx, cell* params);
        extern cell cnegate(AMX * amx, cell* params);
        extern cell cadd(AMX * amx, cell* params);
        extern cell csub(AMX * amx, cell* params);
        extern cell cmul(AMX * amx, cell* params);
        extern cell cdiv(AMX * amx, cell* params);
        extern cell cequal(AMX * amx, cell* params);
    }
}
#endif /* PLE_COMPLEX_H_INCLUDED */