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
#include "fstream.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

namespace PLE::fstream
{
	std::vector<std::fstream> FileList;
	bool IsValidFile(FileHandle_t handle)
	{
		if (handle < 0 || handle >= static_cast<cell>(FileList.size()))
            return false;
		return FileList[handle].is_open();
	}
	FileHandle_t OpenFile(const char *name, cell fmode)
	{
		FileHandle_t handle = std::find_if(FileList.begin(), FileList.end(), [](const std::fstream& file) { return file.is_open(); }) - FileList.begin();
		if (handle == FileList.size())
		{
			if ((handle - 1) == std::numeric_limits<FileHandle_t>::max())
			{
				logprintf("[PLE] fstream>> ran out of handles.");
				return INVALID_FILE_HANDLE;
			}
			FileList.emplace_back();
			FileList.back().exceptions(0); //disable exceptions
		}
        FileList[handle].open(name, openmodes::decode(fmode));
		return (FileList[handle].is_open() ? handle : INVALID_FILE_HANDLE);
	}
	void CloseFile(FileHandle_t handle)
	{
		if (!IsValidFile(handle)) 
            return;
		FileList[handle].close();
	}
   
	namespace natives
	{
        //native _fstream_generic_tag:file_open(const fname[], openmode_t:mode = openmode::in | openmode::out);
		cell AMX_NATIVE_CALL open(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_open: expected 2 parameters but found %d parameters.", get_params_count());

			char fname[FILENAME_MAX];
			cell *addr = NULL;
			amx_GetAddr(amx, params[1], &addr);
			amx_GetString(fname, addr, 0, sizeof(fname));

			return OpenFile(fname, params[2]);
		}
		//native file_close({iofs_tags}:file);
        cell AMX_NATIVE_CALL close(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_close: expected 1 parameters but found %d parameters.", get_params_count());
			CloseFile(params[1]);
			return false;
		}
		//native bool:file_is_valid({iofs_tags}:file);
        cell AMX_NATIVE_CALL is_valid(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_is_valid: expected 1 parameters but found %d parameters.", get_params_count());
			return IsValidFile(params[1]);
		}

        //native bool:file_getch({ifs_tags}:file, &ch);
		cell AMX_NATIVE_CALL getch(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_getch: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = FileList[params[1]].get();
			return true;
		}
		//native bool:file_getstr({ifs_tags}:file, dest[], count, delim = '\n', bool:pack = false);
        cell AMX_NATIVE_CALL getstr(AMX * amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] fstream>> file_getstr: expected 5 parameters but found %d parameters.", get_params_count());
			if (!fstream::IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);

            std::string str;
            str.resize(params[3] + 1);
			fstream::FileList[params[1]].get(str.data(), params[3], params[4]);
			amx_SetString(dest, str.c_str(), params[5], false, params[3]);
			return true;
		}
		//native bool:file_peek({ifs_tags}:file, &ch);
        cell AMX_NATIVE_CALL peek(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_peek: expected 2 parameters but found %d parameters.", get_params_count());
			if (!fstream::IsValidFile(params[1])) return false;

			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = fstream::FileList[params[1]].peek();
			return true;
		}
		//native bool:file_unget({ifs_tags}:file);
        cell AMX_NATIVE_CALL unget(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_unget: expected 1 parameters but found %d parameters.", get_params_count());
			if (!fstream::IsValidFile(params[1])) return false;
			fstream::FileList[params[1]].unget();
			return true;
		}
		//native bool:file_putback({ifs_tags}:file, ch);
        cell AMX_NATIVE_CALL putback(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_putback: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			FileList[params[1]].putback(params[2]);
			return true;
		}
		//native bool:file_getline({ifs_tags}:file, dest[], count, delim = '\n', bool:pack = false);
        cell AMX_NATIVE_CALL getline(AMX * amx, cell* params)
		{
			error_if(!check_params(5), "[PLE] fstream>> file_getline: expected 5 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);

            std::string str;
            str.resize(params[3]);
			FileList[params[1]].getline(str.data(), params[3] - 1, params[4]);
			amx_SetString(dest, str.c_str(), params[5], false, params[3]);
			return true;
		}
		//native bool:file_ignore({ifs_tags}:file, count = 1, delim = -1);
        cell AMX_NATIVE_CALL ignore(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_ignore: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			if (params[3] == -1)
				FileList[params[1]].ignore(params[2]);
			else
				FileList[params[1]].ignore(params[2], params[3]);
			return true;
		}
		//native bool:file_read({ifs_tags}:file, raw_dest[], numbytes);
        cell AMX_NATIVE_CALL read(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_read: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			FileList[params[1]].read(reinterpret_cast<char*>(dest), params[3]);
			return true;
		}
		//native bool:file_extract_number({ifs_tags}:file, &num);
        cell AMX_NATIVE_CALL extract_number(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_extract_number: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell val;
			FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = val;
			return true;
		}
		//native bool:file_extract_float({ifs_tags}:file, &Float:flt);
        cell AMX_NATIVE_CALL extract_float(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_extract_float: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			float val;
			FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = amx_ftoc(val);
			return true;
		}
		//native bool:file_extract_bool({ifs_tags}:file, &bool:val);
        cell AMX_NATIVE_CALL extract_bool(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_extract_bool: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			bool val;
			FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = val;
			return true;
		}
		//native bool:file_extract_string({ifs_tags}:file, dest[], pack = false, dest_len = sizeof(dest));
        cell AMX_NATIVE_CALL extract_string(AMX * amx, cell* params)
		{
			error_if(!check_params(4), "[PLE] fstream>> file_extract_string: expected 4 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			std::string val;
			FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			amx_SetString(dest, val.c_str(), params[3], false, params[4]);
			return true;
		}
		//native file_gcount({ifs_tags}:file);
        cell AMX_NATIVE_CALL gcount(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_gcount: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;
			return FileList[params[1]].gcount();
		}
		//native file_tellg({ifs_tags}:file);
        cell AMX_NATIVE_CALL tellg(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_tellg: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;
			return FileList[params[1]].tellg();
		}
		//native bool:file_seekg({ifs_tags}:file, offset, seekdir_t:dir = seekdir::beg);
        cell AMX_NATIVE_CALL seekg(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_seekg: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;

			FileList[params[1]].seekg(params[2], seekdir::decode(params[2]));
			return true;
		}
		//native bool:file_sync({ifs_tags}:file);
        cell AMX_NATIVE_CALL sync(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_sync: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;
			FileList[params[1]].sync();
			return true;
		}

        //native file_put({ofs_tags}:file, ch);
		cell AMX_NATIVE_CALL put(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_put: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]].put(params[2]);
			return true;
		}
		//native file_write({ofs_tags}:file, const raw_src[], numbytes);
        cell AMX_NATIVE_CALL write(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_write: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell *src;
			amx_GetAddr(amx, params[2], &src);
			FileList[params[1]].write(reinterpret_cast<char*>(src), params[3]);
			return true;
		}
		//native file_insert_number({ofs_tags}:file, num);
        cell AMX_NATIVE_CALL insert_number(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_insert_number: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]] << params[2];
			return true;
		}
		//native file_insert_float({ofs_tags}:file, Float:flt);
        cell AMX_NATIVE_CALL insert_float(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_insert_float: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]] << amx_ctof(params[2]);
			return true;
		}
		//native file_insert_bool({ofs_tags}:file, bool:val);
        cell AMX_NATIVE_CALL insert_bool(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_insert_bool: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]] << static_cast<bool>(params[2]);
			return true;
		}
		//native file_insert_string({ofs_tags}:file, const src[], src_len = sizeof(src));
        cell AMX_NATIVE_CALL insert_string(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_insert_string: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;

			cell *src;
			amx_GetAddr(amx, params[2], &src);

            std::string str;
            str.resize(params[3] + 1);
			amx_GetString(str.data(), src, false, params[3] + 1);
			FileList[params[1]] << str;
			return true;
		}
		//native file_tellp({ofs_tags}:file);
        cell AMX_NATIVE_CALL tellp(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_tellp: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;
			return FileList[params[1]].tellp();
		}
		//native file_seekp({ofs_tags}:file, offset, seekdir_t:dir = seekdir::beg);
        cell AMX_NATIVE_CALL seekp(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_seekp: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;

			FileList[params[1]].seekg(params[2], seekdir::decode(params[2]));
			return true;
		}
		//native file_flush({ofs_tags}:file);
        cell AMX_NATIVE_CALL flush(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_flush: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return 0;
			FileList[params[1]].flush();
			return true;
		}

        //native bool:file_good({iofs_tags}:file);
		cell AMX_NATIVE_CALL good(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_good: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].good();
		}
        //native bool:file_eof({iofs_tags}:file);
        cell AMX_NATIVE_CALL eof(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_eof: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].eof();
		}
		//native bool:file_fail({iofs_tags}:file);
        cell AMX_NATIVE_CALL fail(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_fail: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return true;
			return FileList[params[1]].fail();
		}
		//native bool:file_bad({iofs_tags}:file);
        cell AMX_NATIVE_CALL bad(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_bad: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return true;
			return FileList[params[1]].bad();
		}
		//native iostate_t:file_rdstate({iofs_tags}:file);
        cell AMX_NATIVE_CALL rdstate(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_rdstate: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return iostate::encode(FileList[params[1]].rdstate());
		}
		//native file_setstate({iofs_tags}:file, iostate_t:iostate);
        cell AMX_NATIVE_CALL setstate(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_setstate: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]].setstate(iostate::decode(params[2]));
			return true;
		}
		//native file_clear({iofs_tags}:file, iostate_t:iostate = iostate::goodbit);
        cell AMX_NATIVE_CALL clear(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_clear: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]].clear(iostate::decode(params[2]));
			return true;
		}
		//native file_copyfmt({iofs_tags}:file_dest, {iofs_tags}:file_src);
        cell AMX_NATIVE_CALL copyfmt(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_copyfmt: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			if (!IsValidFile(params[2])) return false;
			FileList[params[1]].copyfmt(FileList[params[2]]);
			return true;
		}
		//native iostate_t:file_rdstate({iofs_tags}:file);
        cell AMX_NATIVE_CALL fill(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_rdstate: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].fill(params[2]);
		}

        //native file_tie({iofs_tags}:file, {iofs_tags}:tie_to_file = fstream:-1);
		cell AMX_NATIVE_CALL tie(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_tie: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			if (params[2] == -1)
				FileList[params[1]].tie(nullptr);
			else
				FileList[params[1]].tie(&FileList[params[2]]);
			return true;
		}
		//native fmtflags_t:file_getflags({iofs_tags}:file);
        cell AMX_NATIVE_CALL getflags(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_getflags: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return fmtflags::encode(FileList[params[1]].flags());
		}
		//native file_setflags({iofs_tags}:file, fmtflags_t:flags);
        cell AMX_NATIVE_CALL setflags(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_setflags: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return fmtflags::encode(FileList[params[1]].flags(fmtflags::decode(params[2])));
		}
		//native file_setf({iofs_tags}:file, fmtflags_t:flags, fmtflags_t:mask = fmtflags_t:0);
        cell AMX_NATIVE_CALL setf(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] fstream>> file_setf: expected 3 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return fmtflags::encode(FileList[params[1]].setf(fmtflags::decode(params[2]), fmtflags::decode(params[3])));
		}
		//native file_unsetf({iofs_tags}:file, fmtflags_t:flags);
        cell AMX_NATIVE_CALL unsetf(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_unsetf: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			FileList[params[1]].unsetf(fmtflags::decode(params[2]));
			return true;
		}
		//native file_getprecision({iofs_tags}:file);
        cell AMX_NATIVE_CALL getprecision(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_getprecision: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].precision();
		}
		//native file_setprecision({iofs_tags}:file, digits);
        cell AMX_NATIVE_CALL setprecision(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_setprecision: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].precision(params[2]);
		}
		//native file_getwidth({iofs_tags}:file);
        cell AMX_NATIVE_CALL getwidth(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] fstream>> file_getwidth: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].width();
		}
		//native file_setwidth({iofs_tags}:file, width);
        cell AMX_NATIVE_CALL setwidth(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] fstream>> file_setwidth: expected 2 parameters but found %d parameters.", get_params_count());
			if (!IsValidFile(params[1])) return false;
			return FileList[params[1]].width(params[2]);
		}
	}
}