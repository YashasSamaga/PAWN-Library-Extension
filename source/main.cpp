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

/************************************************************************************************************
main.cpp

//TODO
split
stock functions calling with fake public
overloads for bitset, time IO operations
user config for namespaces complex:: in ple_config.inc
#pragma library
debug library
matrix.cpp library
invoke using address function
managed & unmanaged pointers
setjmp longjmp
bitset operator[]
biset shifts
hash
invoke functional
functional target, target_type
functional address func calls
basic_string
array
forward_list
set
multiset
map
multimap
chrono
unordered_set/multiset
unordered_map/multimap
stack
deque
queue
priority_queue
iterator
valarray
random
threads
regex
streams
pair
tuple
atexit publics
atinit publics
stdlib string interconversions
amx exports
functionset
bigint
HP Timers
benchmark
*************************************************************************************************************/
#include "main.h"
#include "version.h"
#include "iscript.h"

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>

extern void *pAMXFunctions;
logprintf_t logprintf;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{	
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	 
	logprintf("***********************************************************");
	logprintf("  PAWN Library Extension v%d.%d.%d loaded", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
	logprintf("  Version Key: %h", PLE_PLUGIN_VERSION_KEY);
    logprintf("");
#if defined _MSC_FULL_VER
    logprintf("  (MSVC) _MSC_FULL_VER: %d", _MSC_FULL_VER);
#elif defined __GNUG__
    logprintf("  (G++) __VERSION__: %s", __VERSION__);
#endif
    logprintf("  __cplusplus: %d", __cplusplus);
    logprintf("  __DATE__: %s, __TIME__: %s", __DATE__, __TIME__);
	logprintf("***********************************************************");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("*** PAWN Library Extension v%d.%d.%d unloaded ***", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{	
	PLE::iscript::AddInterface(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{	
	PLE::iscript::RemoveInterface(amx);
	return AMX_ERR_NONE;
}