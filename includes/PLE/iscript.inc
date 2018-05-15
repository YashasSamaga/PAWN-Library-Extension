/*
** PAWN Library Extension (PLE)
**
** IScript (Script Interface)
** IScript is the interface between the plugin and the scripts.
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

#if defined PLE_ISCRIPT_INCLUDED
	#endinput
#endif
#define PLE_ISCRIPT_INCLUDED

/* dependencies */
#include <PLE/config>

/*
** Scripts which were not compiled for PLE will function normally with PLE.
** These kind of scripts will use UNSUPPORTED_SCRIPT_IDENTIFIER as its script
** identifier and the scripts which use PLE but do not have a script identifier
** will use UNDEFINED_SCRIPT_IDENTIFIER as their script identifier.
**
** These two script identifiers are reserved for use by the plugin and must not
** be used in a script.
*/
#define SCRIPT_IDENTIFIER_SIZE 32
#define UNDEFINED_SCRIPT_IDENTIFIER "Undefined"
#define UNSUPPORTED_SCRIPT_IDENTIFIER "Unsupported"

/*
** Script key is a 8-bit signed number assigned by the plugin to each script at
** runtime and is guaranteed to be unique. As the script key is a signed 8-bit
** number, the maximum number of simultaneously loaded scripts is limited to 128
*/
#define INVALID_SCRIPT_KEY -1

/*
** GetScriptType returns the type of script which is guaranteed to be one of the
** following:
*/
enum
{
	ISCRIPT_TYPE_INVALID = 0, 		/* invalid script */
	ISCRIPT_TYPE_SUPPORTED = 1,   	/* script was compiled for PLE */
	ISCRIPT_TYPE_UNSUPPORTED = 2 	/* script was not compiled for PLE */
};

/* PLE header format */
enum PLE_HEADER_FORMAT
{
	PLE_HEADER_VERSION,
	PLE_HEADER_SIZE,
	PLE_HEADER_INC_VERSION,
	PLE_HEADER_RESERVED4,

	PLE_HEADER_FLAGS,
	PLE_HEADER_DEBUG_LEVEL,
	PLE_HEADER_COMPILER_VERSION,
	PLE_HEADER_RESERVED8,

	PLE_HEADER_RESERVED9,
	PLE_HEADER_RESERVED10,
	PLE_HEADER_RESERVED11,
	PLE_HEADER_RESERVED12,
	PLE_HEADER_RESERVED13,
	PLE_HEADER_RESERVED14,
	PLE_HEADER_RESERVED15,
	PLE_HEADER_RESERVED16,
	PLE_HEADER_RESERVED17,
	PLE_HEADER_RESERVED18,
	PLE_HEADER_RESERVED19,
	PLE_HEADER_RESERVED20,
	PLE_HEADER_RESERVED21,
	PLE_HEADER_RESERVED22,
	PLE_HEADER_RESERVED23,
	PLE_HEADER_RESERVED24,

	PLE_HEADER_SCRIDENTIFIER[SCRIPT_IDENTIFIER_SIZE],

	PLE_HEADER_SCRIPTKEY,
	PLE_HEADER_RESERVED58,
	PLE_HEADER_RESERVED59,
	PLE_HEADER_RESERVED60,

	PLE_HEADER_RESERVED61,
	PLE_HEADER_RESERVED62,
	PLE_HEADER_RESERVED63,
	PLE_HEADER_SIGNATURE_END
}

/*
** The following callbacks are called in every script except for the (un)loaded
** when any (supported or unsupported) script is (un)loaded.
*/
forward OnScriptLoad(scriptKey, scriptIdentifier[]);
forward OnScriptUnload(scriptKey, scriptIdentifier[]);


//GetScriptKey is defined in config.inc

/* returns true if the given scriptKey is associated with a loaded script */
native bool:IsValidScript(scriptKey);

/* returns the type of script */
native GetScriptType(scriptKey);

/* returns the largest script key */
native GetScriptPoolSize();

/* stores the script identifier in 'dest' array
   returns true on success, otherwise false (invalid scriptKey) */
native bool:GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));

/* stores the script keys of the scripts with the given identfier in 'scriptID'
   returns the number of scripts with the given identifier */
native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));

/* stores the given script's PLE header in `ple_header`
   returns true on success, false if the script is an unsupported script */
native bool:GetScriptPLEHeader(scriptKey, ple_header[PLE_HEADER_FORMAT]);
