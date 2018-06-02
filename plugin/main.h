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

#ifndef PLE_MAIN_H_INCLUDED
#define PLE_MAIN_H_INCLUDED

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>

typedef void (*logprintf_t)(const char*, ...);
extern logprintf_t logprintf;

#define MAX_SYMBOL_LEN sNAMEMAX + 1

#define BYTES_PER_CELL PAWN_CELL_SIZE/8
#define BITS_PER_CELL (BYTES_PER_CELL*8)

#define warn_if(x,...) if(x) logprintf(__VA_ARGS__), 0
#define error_if(x,...) if(x) return logprintf(__VA_ARGS__), 0

#define check_params(n) (params[0] == n*BYTES_PER_CELL)
#define check_params_min(n) (params[0] >= n*BYTES_PER_CELL)
#define get_params_count() (params[0]/(BYTES_PER_CELL))

#endif /* PLE_MAIN_H_INCLUDED */