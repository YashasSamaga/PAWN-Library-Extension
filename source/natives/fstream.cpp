/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

File Functions
Files can be shared across different scripts.

file.cpp

TODO:
- disable throw

*************************************************************************************************************/
#include "main.h"
#include "fstream.h"
#include <cstdio>
#include <vector>
#include <algorithm>

namespace PLE
{
	namespace file
	{
		std::vector <std::fstream> FileList;

		bool IsValidFile(FileHandle_t handle)
		{
			if (handle < 0 || handle >= static_cast<cell>(FileList.size())) return false;
			return FileList[handle].is_open();
		}
		FileHandle_t OpenFile(char *name, cell fmode)
		{
			FileHandle_t handle;
			auto itr = std::find_if(FileList.begin(), FileList.end(), [](const std::fstream& file) { return file.is_open(); });
			if (itr == FileList.end())
			{
				if (FileList.size() == std::numeric_limits<FileHandle_t>::max())
				{
					logprintf("Ran out of file handles");
					return INVALID_FILE_HANDLE;
				}
				handle = static_cast<FileHandle_t>(FileList.size());
				FileList.emplace_back();
				FileList.back().exceptions(0); //disable exceptions
			}
			else
				handle = std::distance(FileList.begin(), itr);

			itr->open(name, openmodes::decode(fmode));
			return (itr->is_open() ? handle : INVALID_FILE_HANDLE);
		}
		void CloseFile(FileHandle_t handle)
		{
			if (!IsValidFile(handle)) return;
			FileList[handle].close();
		}
	}
	namespace natives
	{
		cell AMX_NATIVE_CALL file_open(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> open: expected 2 parameters but found %d parameters.", get_params_count());

			char fname[FILENAME_MAX];
			cell *addr = NULL;
			amx_GetAddr(amx, params[1], &addr);
			amx_GetString(fname, addr, 0, sizeof(fname));

			return file::OpenFile(fname, params[2]);
		}
		cell AMX_NATIVE_CALL file_close(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			file::CloseFile(params[1]);
			return false;
		}
		cell AMX_NATIVE_CALL file_IsValidFile(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			return file::IsValidFile(params[1]);
		}

		cell AMX_NATIVE_CALL file_getch(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = file::FileList[params[1]].get();
			return true;
		}
		cell AMX_NATIVE_CALL file_getstr(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);

			char *str = new char[params[3]];
			file::FileList[params[1]].get(str, params[3], params[4]);
			amx_SetString(dest, str, params[5], false, params[3]);
			delete[] str;
			return true;
		}
		cell AMX_NATIVE_CALL file_peek(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			*addr = file::FileList[params[1]].peek();
			return true;
		}
		cell AMX_NATIVE_CALL file_unget(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]].unget();
			return true;
		}
		cell AMX_NATIVE_CALL file_putback(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			file::FileList[params[1]].putback(params[2]);
			return true;
		}
		cell AMX_NATIVE_CALL file_getline(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);

			char *str = new char[params[3]];
			file::FileList[params[1]].getline(str, params[3], params[4]);
			amx_SetString(dest, str, params[5], false, params[3]);
			delete[] str;
			return true;
		}
		cell AMX_NATIVE_CALL file_ignore(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			if (params[3] == -1)
				file::FileList[params[1]].ignore(params[2]);
			else
				file::FileList[params[1]].ignore(params[2], params[3]);
			return true;
		}
		cell AMX_NATIVE_CALL file_read(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			file::FileList[params[1]].read(reinterpret_cast<char*>(dest), params[3]);
			return true;
		}
		cell AMX_NATIVE_CALL file_extract_number(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell val;
			file::FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = val;
			return true;
		}
		cell AMX_NATIVE_CALL file_extract_float(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			float val;
			file::FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = amx_ftoc(val);
			return true;
		}
		cell AMX_NATIVE_CALL file_extract_bool(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			bool val;
			file::FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			*dest = val;
			return true;
		}
		cell AMX_NATIVE_CALL file_extract_string(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			std::string val;
			file::FileList[params[1]] >> val;

			cell *dest;
			amx_GetAddr(amx, params[2], &dest);
			amx_SetString(dest, val.c_str(), params[3], false, params[4]);
			return true;
		}
		cell AMX_NATIVE_CALL file_gcount(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;
			return file::FileList[params[1]].gcount();
		}
		cell AMX_NATIVE_CALL file_tellg(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;
			return file::FileList[params[1]].tellg();
		}
		cell AMX_NATIVE_CALL file_seekg(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;

			file::FileList[params[1]].seekg(params[2], file::seekdir::decode(params[2]));
			return true;
		}
		cell AMX_NATIVE_CALL file_sync(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;
			file::FileList[params[1]].sync();
			return true;
		}

		cell AMX_NATIVE_CALL file_put(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]].put(params[2]);
			return true;
		}
		cell AMX_NATIVE_CALL file_write(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *src;
			amx_GetAddr(amx, params[2], &src);
			file::FileList[params[1]].write(reinterpret_cast<char*>(src), params[3]);
			return true;
		}
		cell AMX_NATIVE_CALL file_insert_number(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]] << params[2];
			return true;
		}
		cell AMX_NATIVE_CALL file_insert_float(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]] << amx_ctof(params[2]);
			return true;
		}
		cell AMX_NATIVE_CALL file_insert_bool(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]] << static_cast<bool>(params[2]);
			return true;
		}
		cell AMX_NATIVE_CALL file_insert_string(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;

			cell *src;
			amx_GetAddr(amx, params[2], &src);

			char *str = new char[params[3] + 1];
			amx_GetString(str, src, false, params[3] + 1);
			file::FileList[params[1]] << str;
			delete[] str;
			return true;
		}
		cell AMX_NATIVE_CALL file_tellp(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;
			return file::FileList[params[1]].tellp();
		}
		cell AMX_NATIVE_CALL file_seekp(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;

			file::FileList[params[1]].seekg(params[2], file::seekdir::decode(params[2]));
			return true;
		}
		cell AMX_NATIVE_CALL file_flush(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return 0;
			file::FileList[params[1]].flush();
			return true;
		}

		cell AMX_NATIVE_CALL file_good(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].good();
		}
		cell AMX_NATIVE_CALL file_eof(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].eof();
		}
		cell AMX_NATIVE_CALL file_fail(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return true;
			return file::FileList[params[1]].fail();
		}
		cell AMX_NATIVE_CALL file_bad(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return true;
			return file::FileList[params[1]].bad();
		}
		cell AMX_NATIVE_CALL file_rdstate(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::iostate::encode(file::FileList[params[1]].rdstate());
		}
		cell AMX_NATIVE_CALL file_setstate(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]].setstate(file::iostate::decode(params[2]));
			return true;
		}
		cell AMX_NATIVE_CALL file_clear(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]].clear(file::iostate::decode(params[2]));
			return true;
		}
		cell AMX_NATIVE_CALL file_copyfmt(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			if (!file::IsValidFile(params[2])) return false;
			file::FileList[params[1]].copyfmt(file::FileList[params[2]]);
			return true;
		}
		cell AMX_NATIVE_CALL file_fill(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].fill(params[2]);
		}

		cell AMX_NATIVE_CALL file_tie(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			if (!file::IsValidFile(params[2]) == -1)
				file::FileList[params[1]].tie(nullptr);
			else
				file::FileList[params[1]].tie(&file::FileList[params[2]]);
			return true;
		}

		cell AMX_NATIVE_CALL file_getflags(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::fmtflags::encode(file::FileList[params[1]].flags());
		}
		cell AMX_NATIVE_CALL file_setflags(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::fmtflags::encode(file::FileList[params[1]].flags(file::fmtflags::decode(params[2])));
		}
		cell AMX_NATIVE_CALL file_setf(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::fmtflags::encode(file::FileList[params[1]].setf(file::fmtflags::decode(params[2]), file::fmtflags::decode(params[3])));
		}
		cell AMX_NATIVE_CALL file_unsetf(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			file::FileList[params[1]].unsetf(file::fmtflags::decode(params[2]));
			return true;
		}
		cell AMX_NATIVE_CALL file_getprecision(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].precision();
		}
		cell AMX_NATIVE_CALL file_setprecision(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].precision(params[2]);
		}
		cell AMX_NATIVE_CALL file_getwidth(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].width();
		}
		cell AMX_NATIVE_CALL file_setwidth(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] file>> : expected  parameters but found %d parameters.", get_params_count());
			if (!file::IsValidFile(params[1])) return false;
			return file::FileList[params[1]].width(params[2]);
		}
	}
}