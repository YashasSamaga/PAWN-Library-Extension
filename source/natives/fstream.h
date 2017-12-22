/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

File Functions
file.h

*************************************************************************************************************/
#ifndef PLE_FSTREAM_H_INCLUDED
#define PLE_FSTREAM_H_INCLUDED

#include "main.h"
#include <fstream>

namespace PLE
{
	namespace file
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
				case file::seekdir::end:
					return std::ios::end;
				case file::seekdir::cur:
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
				if (pstate & file::iostate::goodbit)
					state |= std::ios::goodbit;
				if (pstate & file::iostate::badbit)
					state |= std::ios::badbit;
				if (pstate & file::iostate::failbit)
					state |= std::ios::failbit;
				if (pstate & file::iostate::eofbit)
					state |= std::ios::eofbit;
				return state;
			}

			static constexpr iostate_t encode(std::ios::iostate pstate)
			{
				iostate_t state(0);
				if (pstate & std::ios::goodbit)
					state |= file::iostate::goodbit;
				if (pstate & std::ios::badbit)
					state |= file::iostate::badbit;
				if (pstate & std::ios::failbit)
					state |= file::iostate::failbit;
				if (pstate & std::ios::eofbit)
					state |= file::iostate::eofbit;
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
				if (pflags & file::fmtflags::dec)
					flags |= std::ios::dec;
				if (pflags & file::fmtflags::oct)
					flags |= std::ios::oct;
				if (pflags & file::fmtflags::hex)
					flags |= std::ios::hex;
				if (pflags & file::fmtflags::left)
					flags |= std::ios::left;
				if (pflags & file::fmtflags::right)
					flags |= std::ios::right;
				if (pflags & file::fmtflags::internal)
					flags |= std::ios::internal;
				if (pflags & file::fmtflags::scientific)
					flags |= std::ios::scientific;
				if (pflags & file::fmtflags::fixed)
					flags |= std::ios::fixed;
				if (pflags & file::fmtflags::boolalpha)
					flags |= std::ios::boolalpha;
				if (pflags & file::fmtflags::showbase)
					flags |= std::ios::showbase;
				if (pflags & file::fmtflags::showpoint)
					flags |= std::ios::showpoint;
				if (pflags & file::fmtflags::showpos)
					flags |= std::ios::showpos;
				if (pflags & file::fmtflags::skipws)
					flags |= std::ios::skipws;
				if (pflags & file::fmtflags::unitbuf)
					flags |= std::ios::unitbuf;
				if (pflags & file::fmtflags::uppercase)
					flags |= std::ios::uppercase;
				return flags;
			}

			static constexpr fmtflag_t encode(std::ios::fmtflags pflags)
			{
				fmtflag_t flags(0);
				if (pflags & std::ios::dec)
					flags |= file::fmtflags::dec;
				if (pflags & std::ios::oct)
					flags |= file::fmtflags::oct;
				if (pflags & std::ios::hex)
					flags |= file::fmtflags::hex;
				if (pflags & std::ios::left)
					flags |= file::fmtflags::left;
				if (pflags & std::ios::right)
					flags |= file::fmtflags::right;
				if (pflags & std::ios::internal)
					flags |= file::fmtflags::internal;
				if (pflags & std::ios::scientific)
					flags |= file::fmtflags::scientific;
				if (pflags & std::ios::fixed)
					flags |= file::fmtflags::fixed;
				if (pflags & std::ios::boolalpha)
					flags |= file::fmtflags::boolalpha;
				if (pflags & std::ios::showbase)
					flags |= file::fmtflags::showbase;
				if (pflags & std::ios::showpoint)
					flags |= file::fmtflags::showpoint;
				if (pflags & std::ios::showpos)
					flags |= file::fmtflags::showpos;
				if (pflags & std::ios::skipws)
					flags |= file::fmtflags::skipws;
				if (pflags & std::ios::unitbuf)
					flags |= file::fmtflags::unitbuf;
				if (pflags & std::ios::uppercase)
					flags |= file::fmtflags::uppercase;
				return flags;
			}
		}
	}

	namespace natives
	{
		extern cell AMX_NATIVE_CALL file_open(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_close(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_IsValidFile(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getch(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getstr(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_peek(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_unget(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_putback(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getline(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_ignore(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_read(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_extract_number(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_extract_float(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_extract_bool(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_extract_string(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_insert_number(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_insert_float(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_insert_bool(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_insert_string(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_gcount(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_tellg(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_seekg(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_sync(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_put(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_write(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_tellp(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_seekp(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_flush(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_good(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_eof(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_fail(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_bad(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_rdstate(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_setstate(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_clear(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_copyfmt(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_fill(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_tie(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getflags(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_setflags(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_setf(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_unsetf(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getprecision(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_setprecision(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_getwidth(AMX * amx, cell* params);
		extern cell AMX_NATIVE_CALL file_setwidth(AMX * amx, cell* params);
	}
};
#endif /* PLE_FSTREAM_H_INCLUDED */