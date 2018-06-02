/*
** PAWN Library Extension (PLE)
**
** String Library
** To be included automatically by every PLE header. The inclusion of this file
** will automatically add the PLE header to the AMX binary and provides basic
** set of functions necessary to interact with the plugin.
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

#if defined PLE_STRING_INCLUDED
	#endinput
#endif
#define PLE_STRING_INCLUDED

/* dependencies */
#include <PLE/config>

#if !defined NULL
	#define NULL 0
#endif

//memcpy already implemented
native memmove(destination[], const source[], numbytes);
native strcpy(destination[], const source[], size_dest = sizeof(destination));
native strncpy(destination[], const source[], num, size_dest = sizeof(destination),  size_src = sizeof(source));
//strcat - already implemented by PAWN Standard Library
native strncat(destination[], const source[], num, size_dest = sizeof(destination));
native memcmp(const src1[], const src2[], num) = strncmp; //mem natives use cells instead of bytes, therefore, memcmp is as good as strncmp; unit of memory = cell
//strcmp already implemented
//strcoll not implemented
native strncmp(const str1[], const str2[], num);
//strxfrm not implemented
native memchr(const source[], value, num);
native strchr(const source[], value, idx = 0);
native strcspn(const str1[], const str2[]); //returns the index - same as C++ implementation
native strpbrk(const str1[], const str2[]); //returns the character instead of a pointer (C++ implementation returns a pointer)
native strrchr(const source[], value, size_src = sizeof(source));
native strspn(const str1[], const str2[]);
native strstr(const source[], const search[], bool:ignorecase=false, pos=0) = strfind;
native strtok(const source[], destination[], &idx, delimiter[], size_dest = sizeof(destination)); //better than C++ implementation
native memset(destination[], value, num);
native strerror(errorid, errormsg[], size_errormsg = sizeof(errormsg));
//strlen - already implemented by PAWN Standard Library

//Bonus Natives
native bool:strreplace(source[], const search[], const replace[], size_src = sizeof(source)); //returns true if something was replaced
native strtrim(source[]); //returns the length of the new string
native strtolower(source[]); //returns length of the string
native strtoupper(source[]); //returns length of the string

native starts_with(const source[], const x[]);
native ends_with(const source[], const x[]);
