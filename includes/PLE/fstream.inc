/*
** PAWN Library Extension (PLE)
**
** File Handling
** Library for file handling
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

#if defined PLE_FSTREAM_INCLUDED
	#endinput
#endif
#define PLE_FSTREAM_INCLUDED

/* dependencies */
#include <PLE/config>

/*
** Every open file stream is assigned a unique number. An invalid file stream is
** identified using INVALID_FILE_STREAM.
*/
#define INVALID_FILE_STREAM __fstream_generic_tag:-1

/*
** All file streams which are opened are internally processed as bidirectional
** file streams. The include however provides a way to write less error-prone
** code by providing separate tags for input-only file stream, output-only file
** stream and input-output file stream.
**
** File types:
** ifstream:- input file stream
** ofstream:- output file stream
** fstream:- input/output file stream
**
** A fstream can be narrowed down to ifstream/ofstream but the other way will
** trigger a warning.
**
** new ifstream:ifs, ofstream:ofs, fstream:iofs;
** ifs = ofs; //warning
** ofs = ifs; //warning
** ifs = iofs; //warning
** ofs = iofs; //warning
** iofs = ifs; //no warning
** iofs = ofs; //no warning
*/

stock fstream:operator=(__fstream_generic_tag:file)
	return fstream:file;
stock ifstream:operator=(__fstream_generic_tag:file)
	return fstream:file;
stock ofstream:operator=(__fstream_generic_tag:file)
	return fstream:file;
stock ifstream:operator=(fstream:file)
	return ifstream:file;
stock ofstream:operator=(fstream:file)
	return ofstream:file;

#define openmode:: openmode_
enum openmode_t
{
    openmode::app = 0x01,
	openmode::binary = 0x02,
	openmode::trunc = 0x04,
	openmode::ate = 0x08,
	openmode::in = 0x10,
	openmode::out = 0x20
}

#define seekdir:: seekdir_
enum seekdir_t
{
	seekdir::beg = 0,
	seekdir::end = 1,
	seekdir::cur = 2
}

#define iostate:: iostate_
enum iostate_t
{
    iostate::goodbit = 0x01,
	iostate::badbit = 0x02,
	iostate::failbit = 0x04,
	iostate::eofbit = 0x08
}

#define fmtflags:: fmtflags_
enum fmtflags_t
{
   	fmtflags::dec = 0x01,
	fmtflags::oct = 0x02,
	fmtflags::hex = 0x04,
	fmtflags::basefield = fmtflags::dec | fmtflags::oct | fmtflags::hex,
	fmtflags::left = 0x08,
	fmtflags::right = 0x10,
	fmtflags::internal = 0x20,
	fmtflags::adjustfield = fmtflags::left | fmtflags::right | fmtflags::internal,
	fmtflags::scientific = 0x40,
	fmtflags::fixed = 0x80,
	fmtflags::floatfield = fmtflags::scientific | fmtflags::fixed,
	fmtflags::boolalpha = 0x100,
	fmtflags::showbase = 0x200,
	fmtflags::showpoint = 0x400,
	fmtflags::showpos = 0x800,
	fmtflags::skipws = 0x1000,
	fmtflags::unitbuf = 0x2000,
	fmtflags::uppercase = 0x4000
}

#define ifs_tags fstream, ifstream, __fstream_generic_tag
#define ofs_tags fstream, ofstream, __fstream_generic_tag
#define iofs_tags fstream, ifstream, ofstream, __fstream_generic_tag

native __fstream_generic_tag:file_open(const fname[], openmode_t:mode = openmode::in | openmode::out);
native file_close({iofs_tags}:file);
native bool:file_IsValidFile({iofs_tags}:file);

native bool:file_getch({ifs_tags}:file, &ch);
native bool:file_getstr({ifs_tags}:file, dest[], count, delim = '\n', bool:pack = false);
native bool:file_peek({ifs_tags}:file, &ch);
native bool:file_unget({ifs_tags}:file);
native bool:file_putback({ifs_tags}:file, ch);
native bool:file_getline({ifs_tags}:file, dest[], count, delim = '\n', bool:pack = false);
native bool:file_ignore({ifs_tags}:file, count = 1, delim = -1);
native bool:file_read({ifs_tags}:file, raw_dest[], numbytes);
native bool:file_extract_number({ifs_tags}:file, &num);
native bool:file_extract_float({ifs_tags}:file, &Float:flt);
native bool:file_extract_bool({ifs_tags}:file, &bool:val);
native bool:file_extract_string({ifs_tags}:file, dest[], pack = false, dest_len = sizeof(dest));
native file_gcount({ifs_tags}:file);
native file_tellg({ifs_tags}:file);
native bool:file_seekg({ifs_tags}:file, offset, seekdir_t:dir = seekdir::beg);
native bool:file_sync({ifs_tags}:file);

native file_put({ofs_tags}:file, ch);
native file_write({ofs_tags}:file, const raw_src[], numbytes);
native file_insert_number({ofs_tags}:file, num);
native file_insert_float({ofs_tags}:file, Float:flt);
native file_insert_bool({ofs_tags}:file, bool:val);
native file_insert_string({ofs_tags}:file, const src[], src_len = sizeof(src));
native file_tellp({ofs_tags}:file);
native file_seekp({ofs_tags}:file, offset, seekdir_t:dir = seekdir::beg);
native file_flush({ofs_tags}:file);

native bool:file_good({iofs_tags}:file);
native bool:file_eof({iofs_tags}:file);
native bool:file_fail({iofs_tags}:file);
native bool:file_bad({iofs_tags}:file);
native iostate_t:file_rdstate({iofs_tags}:file);
native file_setstate({iofs_tags}:file, iostate_t:iostate);
native file_clear({iofs_tags}:file, iostate_t:iostate = iostate::goodbit);
native file_copyfmt({iofs_tags}:file_dest, {iofs_tags}:file_src);
native file_fill({iofs_tags}:file, ch);
native file_tie({iofs_tags}:file, {iofs_tags}:tie_to_file = fstream:-1);
native fmtflags_t:file_getflags({iofs_tags}:file);
native file_setflags({iofs_tags}:file, fmtflags_t:flags);
native file_setf({iofs_tags}:file, fmtflags_t:flags, fmtflags_t:mask = fmtflags_t:0);
native file_unsetf({iofs_tags}:file, fmtflags_t:flags);
native file_getprecision({iofs_tags}:file);
native file_setprecision({iofs_tags}:file, digits);
native file_getwidth({iofs_tags}:file);
native file_setwidth({iofs_tags}:file, width);

/*
** The `!` operator is overloaded to return true if the file handle is invalid.
**
** This allows placing file handles directly in `if` statements. For example:
** new ifstream:inFile = some_file;
** if(inFile) { //valid file }
** else { //invalid file }
*/
//TO BE TESTED
stock bool:operator!(__fstream_generic_tag:file) {
	return !file_IsValidFile(file);
}
stock bool:operator!(fstream:file) {
	return !file_IsValidFile(file);
}
stock bool:operator!(ifstream:file) {
	return !file_IsValidFile(file);
}
stock bool:operator!(ofstream:file) {
	return !file_IsValidFile(file);
}
//TO BE TESED
