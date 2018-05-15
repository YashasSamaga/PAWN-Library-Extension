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

#ifndef PLE_FSTREAM_H_INCLUDED
#define PLE_FSTREAM_H_INCLUDED

#include "main.h"
#include <fstream>

namespace PLE::fstream
{
	typedef cell FileHandle_t;
	constexpr FileHandle_t INVALID_FILE_HANDLE = -1;

	namespace openmodes
	{
		typedef cell openmode_t;

		constexpr openmode_t app = 0x01;
		constexpr openmode_t binary = 0x02;
		constexpr openmode_t trunc = 0x04;
		constexpr openmode_t ate = 0x08;
		constexpr openmode_t in = 0x10;
		constexpr openmode_t out = 0x20;

		static constexpr std::ios::openmode decode(openmode_t pmode)
		{
			std::ios::openmode mode(0);
			if (pmode & openmodes::app)
				mode |= std::ios::app;
			if (pmode & openmodes::binary)
				mode |= std::ios::binary;
			if (pmode & openmodes::trunc)
				mode |= std::ios::trunc;
			if (pmode & openmodes::ate)
				mode |= std::ios::ate;
			if (pmode & openmodes::in)
				mode |= std::ios::in;
			if (pmode & openmodes::out)
				mode |= std::ios::out;
			return mode;
		}
	}

	namespace seekdir
	{
		typedef cell seekdir_t;

		constexpr seekdir_t beg = 0;
		constexpr seekdir_t end = 1;
		constexpr seekdir_t cur = 2;

		static constexpr std::ios::seekdir decode(seekdir_t pdir)
		{
			switch (pdir)
			{
			case fstream::seekdir::end:
				return std::ios::end;
			case fstream::seekdir::cur:
				return std::ios::cur;
			default:
				return std::ios::beg;
			}
		}
	}

	namespace iostate
	{
		typedef cell iostate_t;

		constexpr iostate_t goodbit = 0x01;
		constexpr iostate_t badbit = 0x02;
		constexpr iostate_t failbit = 0x04;
		constexpr iostate_t eofbit = 0x08;

		static constexpr std::ios::iostate decode(iostate_t pstate)
		{
			std::ios::iostate state(0);
			if (pstate & fstream::iostate::goodbit)
				state |= std::ios::goodbit;
			if (pstate & fstream::iostate::badbit)
				state |= std::ios::badbit;
			if (pstate & fstream::iostate::failbit)
				state |= std::ios::failbit;
			if (pstate & fstream::iostate::eofbit)
				state |= std::ios::eofbit;
			return state;
		}

		static constexpr iostate_t encode(std::ios::iostate pstate)
		{
			iostate_t state(0);
			if (pstate & std::ios::goodbit)
				state |= fstream::iostate::goodbit;
			if (pstate & std::ios::badbit)
				state |= fstream::iostate::badbit;
			if (pstate & std::ios::failbit)
				state |= fstream::iostate::failbit;
			if (pstate & std::ios::eofbit)
				state |= fstream::iostate::eofbit;
			return state;
		}
	}

	namespace fmtflags
	{
		typedef cell fmtflag_t;

		constexpr fmtflag_t dec = 0x01;
		constexpr fmtflag_t oct = 0x02;
		constexpr fmtflag_t hex = 0x04;
		constexpr fmtflag_t basefield = dec | oct | hex;
		constexpr fmtflag_t left = 0x08;
		constexpr fmtflag_t right = 0x10;
		constexpr fmtflag_t internal = 0x20;
		constexpr fmtflag_t adjustfield = left | right | internal;
		constexpr fmtflag_t scientific = 0x40;
		constexpr fmtflag_t fixed = 0x80;
		constexpr fmtflag_t floatfield = scientific | fixed;
		constexpr fmtflag_t boolalpha = 0x100;
		constexpr fmtflag_t showbase = 0x200;
		constexpr fmtflag_t showpoint = 0x400;
		constexpr fmtflag_t showpos = 0x800;
		constexpr fmtflag_t skipws = 0x1000;
		constexpr fmtflag_t unitbuf = 0x2000;
		constexpr fmtflag_t uppercase = 0x4000;

		static constexpr std::ios::fmtflags decode(fmtflag_t pflags)
		{
			std::ios::fmtflags flags(0);
			if (pflags & fstream::fmtflags::dec)
				flags |= std::ios::dec;
			if (pflags & fstream::fmtflags::oct)
				flags |= std::ios::oct;
			if (pflags & fstream::fmtflags::hex)
				flags |= std::ios::hex;
			if (pflags & fstream::fmtflags::left)
				flags |= std::ios::left;
			if (pflags & fstream::fmtflags::right)
				flags |= std::ios::right;
			if (pflags & fstream::fmtflags::internal)
				flags |= std::ios::internal;
			if (pflags & fstream::fmtflags::scientific)
				flags |= std::ios::scientific;
			if (pflags & fstream::fmtflags::fixed)
				flags |= std::ios::fixed;
			if (pflags & fstream::fmtflags::boolalpha)
				flags |= std::ios::boolalpha;
			if (pflags & fstream::fmtflags::showbase)
				flags |= std::ios::showbase;
			if (pflags & fstream::fmtflags::showpoint)
				flags |= std::ios::showpoint;
			if (pflags & fstream::fmtflags::showpos)
				flags |= std::ios::showpos;
			if (pflags & fstream::fmtflags::skipws)
				flags |= std::ios::skipws;
			if (pflags & fstream::fmtflags::unitbuf)
				flags |= std::ios::unitbuf;
			if (pflags & fstream::fmtflags::uppercase)
				flags |= std::ios::uppercase;
			return flags;
		}

		static constexpr fmtflag_t encode(std::ios::fmtflags pflags)
		{
			fmtflag_t flags(0);
			if (pflags & std::ios::dec)
				flags |= fstream::fmtflags::dec;
			if (pflags & std::ios::oct)
				flags |= fstream::fmtflags::oct;
			if (pflags & std::ios::hex)
				flags |= fstream::fmtflags::hex;
			if (pflags & std::ios::left)
				flags |= fstream::fmtflags::left;
			if (pflags & std::ios::right)
				flags |= fstream::fmtflags::right;
			if (pflags & std::ios::internal)
				flags |= fstream::fmtflags::internal;
			if (pflags & std::ios::scientific)
				flags |= fstream::fmtflags::scientific;
			if (pflags & std::ios::fixed)
				flags |= fstream::fmtflags::fixed;
			if (pflags & std::ios::boolalpha)
				flags |= fstream::fmtflags::boolalpha;
			if (pflags & std::ios::showbase)
				flags |= fstream::fmtflags::showbase;
			if (pflags & std::ios::showpoint)
				flags |= fstream::fmtflags::showpoint;
			if (pflags & std::ios::showpos)
				flags |= fstream::fmtflags::showpos;
			if (pflags & std::ios::skipws)
				flags |= fstream::fmtflags::skipws;
			if (pflags & std::ios::unitbuf)
				flags |= fstream::fmtflags::unitbuf;
			if (pflags & std::ios::uppercase)
				flags |= fstream::fmtflags::uppercase;
			return flags;
		}
	}

	namespace natives
	{
		extern cell AMX_NATIVE_CALL open(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL close(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL is_valid(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getch(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getstr(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL peek(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL unget(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL putback(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getline(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL ignore(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL read(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL extract_number(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL extract_float(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL extract_bool(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL extract_string(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL insert_number(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL insert_float(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL insert_bool(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL insert_string(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL gcount(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL tellg(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL seekg(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL sync(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL put(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL write(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL tellp(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL seekp(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL flush(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL good(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL eof(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL fail(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL bad(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL rdstate(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL setstate(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL clear(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL copyfmt(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL fill(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL tie(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getflags(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL setflags(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL setf(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL unsetf(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getprecision(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL setprecision(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL getwidth(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL setwidth(AMX * amx, cell* params);
	}
};
#endif /* PLE_FSTREAM_H_INCLUDED */