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

#if defined PLE_CTYPE_INCLUDED
	#endinput
#endif
#define PLE_CTYPE_INCLUDED

/* dependencies */
#include <PLE/config>

native isalnum(c);
native isalpha(c);
native isblank(c);
native iscntrl(c);
native isdigit(c);
native isgraph(c);
native islower(c);
native isprint(c);
native ispunct(c);
native isspace(c);
native isupper(c);
native isxdigit(c);
