/*
** PAWN Library Extension (PLE)
**
** Configuration file
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

#if defined PLE_CONFIG_INCLUDED
	#endinput
#endif
#define PLE_CONFIG_INCLUDED

/* dependencies */
#include <PLE/iscript> //UNDEFINED_SCRIPT_IDENTIFIER, SCRIPT_IDENTIFIER_SIZE, PLE_HEADER_FORMAT

/* user configuration file */
#tryinclude "../../include/ple_config.inc"

/*
** Script identifier is a string which is 'expected' (but not enforced) to
** uniquely identify different scripts. This is assigned during compile time by
** the user. The script identifier can be assigned by defining the
** "SCRIPT_IDENTIFIER" with the identifying string.
**
** See iscript.inc to know more about script identifiers
*/
#if !defined SCRIPT_IDENTIFIER
	#define SCRIPT_IDENTIFIER UNDEFINED_SCRIPT_IDENTIFIER
#endif

/*
** Higher versions of PLE have a higher value of PLE_INCLUDE_VERSION_KEY.
** PLE reports if there is a version mismatch between the compiled script and
** the plugin. In most cases, a script compiled for older version of PLE will
** work with a closer higher version of the plugin without issues.
*/
#define PLE_INCLUDE_VERSION_KEY 0x01000000

/*
** Every script compiled for PLE will have a header which be searched for by the
** plugin. The header will contain important information about the script.
**
** See iscript.inc to learn more about the PLE header.
*/
/*
** __ple_header_start marks the begining of the header and hence, the header
** must immediately follow the variable.
*/
public _ple_header_start;
stock _fix__ple_header_start = _ple_header_start;

/* ple header */
static const _ple_header[PLE_HEADER_FORMAT] =
{
	0x01,
	(_:PLE_HEADER_FORMAT)*cellbits/charbits,
	 
	PLE_INCLUDE_VERSION_KEY,
	0x00,
	
	0x00,
	debug,
	__Pawn,
	0x00,
	
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	
	{SCRIPT_IDENTIFIER},
	
	INVALID_SCRIPT_KEY,
	0x00,
	0x00,
	0x00,
	
	0x00,
	0x00,
	0x00,
	0x0408
};
/*
** __ple_header_end marks the ending of the header and hence, the header
** must immediately preceed the variable.
*/
public _ple_header_end;
stock _fix_ple_header_end = _ple_header_end;

/* fake public (DO NOT USE) */
forward _ple_fake_public();
public _ple_fake_public()
{
	return _ple_header[PLE_HEADER_SCRIPTKEY];
}

/* See iscript.inc to learn about script keys */
stock GetScriptKey()
{
	return _ple_header[PLE_HEADER_SCRIPTKEY];
}
