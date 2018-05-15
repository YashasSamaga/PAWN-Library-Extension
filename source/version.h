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

#ifndef PLE_VERSION_H_INCLUDED
#define PLE_VERSION_H_INCLUDED

#if !defined(PLUGIN_MAJOR_VERSION) || !defined(PLUGIN_MINOR_VERSION) || !defined(PLUGIN_PATCH_VERSION)
#error "Plugin version not defined"
#endif

constexpr ucell PLE_PLUGIN_VERSION_KEY = static_cast<ucell>(PLUGIN_MAJOR_VERSION) << 24 |
                                         static_cast<ucell>(PLUGIN_MINOR_VERSION) << 16 |
                                         static_cast<ucell>(PLUGIN_PATCH_VERSION) << 8;

#endif /* PLE_VERSION_H_INCLUDED */