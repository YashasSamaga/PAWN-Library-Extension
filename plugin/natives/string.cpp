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
#include "string.h"

#include <cstring>
#include <string>
/************************************************************************************************************/
namespace PLE::string::natives
{
	//native memmove(destination[], const source[], numbytes);
	cell AMX_NATIVE_CALL memmove(AMX * amx, cell* params)
	{
		cell* dest = NULL;
		cell* source = NULL;

		amx_GetAddr(amx, params[1], &dest);
		amx_GetAddr(amx, params[2], &source);
		size_t numbytes = params[3];

		std::memmove(dest, source, numbytes);
		return 0;
	}
	//native strcpy(destination[], const source[], size_dest = sizeof(destination));
	cell AMX_NATIVE_CALL strcpy(AMX * amx, cell* params)
	{
		cell* dest = NULL;
		cell* source = NULL;

		amx_GetAddr(amx, params[1], &dest);
		amx_GetAddr(amx, params[2], &source);
		size_t size_dest = params[3];

		while(*source && --size_dest)
			*dest++ = *source++;

		*dest = '\0';	
		return 0;
	}
	//native strncpy(destination[], const source[], num, size_dest = sizeof(destination), size_src = sizeof(source));
	cell AMX_NATIVE_CALL strncpy(AMX * amx, cell* params)
	{
		cell* dest = NULL;
		cell* source = NULL;

		amx_GetAddr(amx, params[1], &dest);
		amx_GetAddr(amx, params[2], &source);
		size_t num = params[3];
		size_t size_dest = params[4];
		size_t size_src = params[5];

		while (num-- && --size_dest && --size_src && *source != '\0') 
			*dest++ = *source++;

		*dest = '\0';
		return 0;
	}
	//native strncat(destination[], const source[], num, size_dest = sizeof(destination));
	cell AMX_NATIVE_CALL strncat(AMX * amx, cell* params)
	{
		cell* dest = NULL;
		cell* source = NULL;

		amx_GetAddr(amx, params[1], &dest);
		amx_GetAddr(amx, params[2], &source);
		size_t n = params[3];
		size_t size_dest = params[4];

		if (*dest && size_dest)
		{
			while (--size_dest && (*++dest != '\0')) {}

			while (n-- && --size_dest && *source != '\0')
				*dest++ = *source++;
		}		

		*dest = '\0';
		return 0;
	}
	//native strncmp(const str1[], const str2[], num);
	cell AMX_NATIVE_CALL strncmp(AMX * amx, cell* params)
	{
		cell* str1 = NULL;
		cell* str2 = NULL;

		amx_GetAddr(amx, params[1], &str1);
		amx_GetAddr(amx, params[2], &str2);
		size_t num = params[3];
	
		for (; num--; ++str1, ++str2) 
			if (*str1 != *str2) 
				return *str1 - *str2;

		return 0;
	}
	//native memchr(const source[], value, num);
	cell AMX_NATIVE_CALL memchr(AMX * amx, cell* params)
	{
		cell *str = NULL, *start = NULL;

		amx_GetAddr(amx, params[1], &str);		
		cell chr = params[2];
		int num = params[3];

		start = str;
		while (num--)
			if (*str++ == chr) 
				return str - start - 1;

		return -1;
	}
	//native strchr(const source[], value, idx = 0);
	cell AMX_NATIVE_CALL strchr(AMX * amx, cell* params)
	{
		cell *str = NULL, *start = NULL;

		amx_GetAddr(amx, params[1], &str);		
		cell chr = params[2];
		str += params[3];

		start = str;
		while (*str != '\0')
			if (*str++ == chr) return str - start - 1;

		return -1;
	}
	//native strrchr(const source[], value, size_src = sizeof(source));
	cell AMX_NATIVE_CALL strrchr(AMX * amx, cell* params)
	{
		cell *start = NULL, *last_found = NULL;
		amx_GetAddr(amx, params[1], &start);

		last_found = start;
		cell chr = params[2];

		cell *str = start;

		unsigned int size_src = params[3];

		while (*str && --size_src)
			if (*str++ == chr) last_found = str;

		return last_found - start - 1;
	}
	//native strcspn(const str1[], const str2[]);
	cell AMX_NATIVE_CALL strcspn(AMX * amx, cell* params)
	{
		cell *str1 = NULL;
		cell *str2 = NULL;
		amx_GetAddr(amx, params[1], &str1);
		amx_GetAddr(amx, params[2], &str2);

		cell *start1 = str1;
		cell *start2 = str2;

		while (*str1)
		{
			str2 = start2;
			while (*str2)
				if(*str2++ == *str1)
					return str1 - start1;
			str1++;
		}			
		return -1;
	}
	//native strpbrk(const str1[], const str2[]);
	cell AMX_NATIVE_CALL strpbrk(AMX * amx, cell* params)
	{
		cell *str1 = NULL;
		cell *str2 = NULL;
		amx_GetAddr(amx, params[1], &str1);
		amx_GetAddr(amx, params[2], &str2);

		//cell *start1 = str1;
		cell *start2 = str2;

		while (*str1)
		{
			str2 = start2;
			while (*str2)
				if (*str2++ == *str1)
					return *str1;
			str1++;
		}
		return -1;
	}
	//native strspn(const str1[], const str2[]);
	cell AMX_NATIVE_CALL strspn(AMX * amx, cell* params)
	{
		cell *str1 = NULL;
		cell *str2 = NULL;
		amx_GetAddr(amx, params[1], &str1);
		amx_GetAddr(amx, params[2], &str2);

		cell *start1 = str1;
		cell *start2 = str2;

		while (*str1)
		{
			str2 = start2;
			while (*str2)
			{
				if (*str2 == *str1) break;
				str2++;
			}
			if (*str2 == '\0') return str1 - start1;
			str1++;
		}
		return str1 - start1;
	}
	//native strtok(const source[], destination[], &idx, delimiter[], size_dest = sizeof(destination));
	cell AMX_NATIVE_CALL strtok(AMX * amx, cell* params)
	{
		cell *str1 = NULL, *start1 = NULL, *str2 = NULL, *str3 = NULL, *start3 = NULL, *idx = NULL;

		amx_GetAddr(amx, params[1], &start1);
		amx_GetAddr(amx, params[2], &str2);
		amx_GetAddr(amx, params[3], &idx);
		amx_GetAddr(amx, params[4], &start3);

		int size_dest = params[5];

		str1 = start1 + *idx;

		while (*str1)
		{
			str3 = start3;
			while (*str3)
			{
				if (*str3 == *str1) break;
				str3++;
			}
			if (*str3 == '\0') break;
			str1++;
		}		

		while (*str1)
		{
			str3 = start3;
			while (*str3)
			{
				if (*str3 == *str1)
				{
					*str2 = '\0';
					*idx = (str1 - start1);
					return *idx;
				}
				str3++;
			}
			if(!(--size_dest))
			{
				*str2 = '\0';
				*idx = (str1 - start1);
				return *idx;
			}
			*str2++ = *str1++;
		}
		//should never reach here
		*idx += (str1 - start1);
		return *idx;
	}
	//native memset(destination[], value, num);
	cell AMX_NATIVE_CALL memset(AMX * amx, cell* params)
	{
		cell *str = NULL;
		amx_GetAddr(amx, params[1], &str);

		cell chr = params[2];
		unsigned int n = static_cast<unsigned int>(params[3]);

		while (n--)
			*str++ = chr;

		return -1;
	}
	//native bool:strreplace(source[], const search[], const replace[], size_src = sizeof(source));
	cell AMX_NATIVE_CALL strreplace(AMX * amx, cell* params)
	{
		cell *source = NULL, *search = NULL, *replace = NULL, len;
		bool replaced = false;

		amx_GetAddr(amx, params[1], &source);
		amx_GetAddr(amx, params[2], &search);
		amx_GetAddr(amx, params[3], &replace);

		amx_StrLen(source, &len);
		len++;
		char* csource = new char[len];
		amx_GetString(csource, source, 0, len);

		amx_StrLen(search, &len);
		len++;
		char* csearch = new char[len];
		amx_GetString(csearch, search, 0, len);

		amx_StrLen(replace, &len);
		len++;
		char* creplace = new char[len];
		amx_GetString(creplace, replace, 0, len);

		std::string ssource = csource;

		size_t index = 0;
		while (true) 
		{
			index = ssource.find(csearch, index);
			if (index == std::string::npos) break;

			replaced = true;

			ssource.replace(index, len - 1, creplace);
			index += len;
		}
		amx_SetString(source, ssource.c_str(), 0, 0, params[4]);
		return replaced;
	}
	//native strtrim(source[]); //returns the length of the new string
	cell AMX_NATIVE_CALL strtrim(AMX * amx, cell* params)
	{
		cell *start = NULL, *str = NULL, len;
		amx_GetAddr(amx, params[1], &start);

		str = start;
		while (*str == ' ') { *str++; }

		amx_StrLen(str, &len);
		int shift = str - start;		

		if (*str == '\0') return 0;
				
		cell *end = str + len - 1;		

		while (*end == ' ') { *end--; }
		*end++;

		start = str;
		while (*str != *end)
			*(str - shift) = *str++;

		*(str - shift) = '\0';
		return end - start;
	}
	//native strtolower(source[]); //returns length of the string
	cell AMX_NATIVE_CALL strtolower(AMX * amx, cell* params)
	{
		cell *str = NULL, *start = NULL;		

		amx_GetAddr(amx, params[1], &str);
		start = str;

		while (*str)
		{
			*str = tolower(*str);
			str++;
		}

		return str - start;
	}
	//native strtoupper(source[]); //returns length of the string
	cell AMX_NATIVE_CALL strtoupper(AMX * amx, cell* params)
	{
		cell *str = NULL, *start = NULL;

		amx_GetAddr(amx, params[1], &str);
		start = str;

		while (*str)
		{
			*str = toupper(*str);
			str++;
		}

		return str - start;
	}
	//native strerror(errorid, errormsg[], size_errormsg = sizeof(errormsg)); TODO
	cell AMX_NATIVE_CALL strerror(AMX * amx, cell* params)
	{
		cell *str = NULL;

		amx_GetAddr(amx, params[2], &str);
		amx_SetString(str, std::strerror(params[1]), 0, 0, params[3]);
		return true;
	}
    //native starts_with(const source[], const x[]);
    cell AMX_NATIVE_CALL starts_with(AMX * amx, cell* params)
	{
		cell *source = NULL;
		amx_GetAddr(amx, params[1], &source);

        cell *x = NULL;
        amx_GetAddr(amx, params[2], &x);

        if (*x == '\0')
            return true;

        while (*source == *x) 
        {
            if (*x == '\0')
                return true;
        }
        return false;
	}	
    //native ends_with(const source[], const x[]);
    cell AMX_NATIVE_CALL ends_with(AMX * amx, cell* params)
	{
		cell *source = NULL;
		amx_GetAddr(amx, params[1], &source);

        cell *x = NULL;
        amx_GetAddr(amx, params[2], &x);

        int source_len, x_len;
        amx_StrLen(source, &source_len);
        amx_StrLen(source, &x_len);

        if (x_len < source_len)
            return false;

        for (int i = 1; i <= x_len; i++)
            if (source[source_len - i] != x[x_len - i])
                return false;

        return true;
	}	
}