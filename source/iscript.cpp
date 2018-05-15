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
#include "version.h"
#include "iscript.h"

#include "natives/algorithm.h"
#include "natives/bitset.h"
#include "natives/chrono.h"
#include "natives/complex.h"
#include "natives/ctype.h"
#include "natives/errno.h"
#include "natives/fstream.h"
#include "natives/functional.h"
#include "natives/isc.h"
#include "natives/math.h"
#include "natives/string.h"
#include "natives/system.h"

#include <algorithm>
#include <vector>
#include <cfenv>

namespace PLE::iscript
{
    static struct { char name[MAX_SYMBOL_LEN]; cell value; } PublicVariablesTable[] =
    {
        { "file_EOF", EOF },
        { "file_SEEK_SET", SEEK_SET },
        { "file_SEEK_CUR", SEEK_CUR },
        { "file_SEEK_END", SEEK_END },
        { "file_BUFSIZ", BUFSIZ },
        { "file_FILENAME_MAX", FILENAME_MAX },
        { "file_FOPEN_MAX", FOPEN_MAX },
        { "file_L_tmpnam", L_tmpnam },
        { "file_TMP_MAX", TMP_MAX },

        { "MATH_ERRNO", MATH_ERRNO },
        { "MATH_ERREXCEPT", MATH_ERREXCEPT },

        { "FE_DIVBYZERO", FE_DIVBYZERO },
        { "FE_INEXACT", FE_INEXACT },
        { "FE_INVALID", FE_INVALID },
        { "FE_OVERFLOW", FE_OVERFLOW },
        { "FE_UNDERFLOW", FE_UNDERFLOW },
        { "FE_ALL_EXCEPT", FE_ALL_EXCEPT },

        { "E2BIG", E2BIG },
        { "EACCES", EACCES },
        { "EADDRINUSE", EADDRINUSE },
        { "EADDRNOTAVAIL", EADDRNOTAVAIL },
        { "EAFNOSUPPORT", EAFNOSUPPORT },
        { "EAGAIN", EAGAIN },
        { "EALREADY", EALREADY },
        { "EBADF", EBADF },
        { "EBADMSG", EBADMSG },
        { "EBUSY", EBUSY },
        { "ECANCELED", ECANCELED },
        { "ECHILD", ECHILD },
        { "ECONNABORTED", ECONNABORTED },
        { "ECONNREFUSED", ECONNREFUSED },
        { "ECONNRESET", ECONNRESET },
        { "EDEADLK", EDEADLK },
        { "EDESTADDRREQ", EDESTADDRREQ },
        { "EDOM", EDOM },
        { "EEXIST", EEXIST },
        { "EFAULT", EFAULT },
        { "EFBIG", EFBIG },
        { "EHOSTUNREACH", EHOSTUNREACH },
        { "EIDRM", EIDRM },
        { "EILSEQ", EILSEQ },
        { "EINPROGRESS", EINPROGRESS },
        { "EINTR", EINTR },
        { "EINVAL", EINVAL },
        { "EIO", EIO },
        { "EISCONN", EISCONN },
        { "EISDIR", EISDIR },
        { "ELOOP", ELOOP },
        { "EMFILE", EMFILE },
        { "EMLINK", EMLINK },
        { "EMSGSIZE", EMSGSIZE },
        { "ENAMETOOLONG", ENAMETOOLONG },
        { "ENETDOWN", ENETDOWN },
        { "ENETRESET", ENETRESET },
        { "ENETUNREACH", ENETUNREACH },
        { "ENFILE", ENFILE },
        { "ENOBUFS", ENOBUFS },
        { "ENODATA", ENODATA },
        { "ENODEV", ENODEV },
        { "ENOENT", ENOENT },
        { "ENOEXEC", ENOEXEC },
        { "ENOLCK", ENOLCK },
        { "ENOLINK", ENOLINK },
        { "ENOMEM", ENOMEM },
        { "ENOMSG", ENOMSG },
        { "ENOPROTOOPT", ENOPROTOOPT },
        { "ENOSPC", ENOSPC },
        { "ENOSR", ENOSR },
        { "ENOSTR", ENOSTR },
        { "ENOSYS", ENOSYS },
        { "ENOTCONN", ENOTCONN },
        { "ENOTDIR", ENOTDIR },
        { "ENOTEMPTY", ENOTEMPTY },
        { "ENOTRECOVERABLE", ENOTRECOVERABLE },
        { "ENOTSOCK", ENOTSOCK },
        { "ENOTSUP", ENOTSUP },
        { "ENOTTY", ENOTTY },
        { "ENXIO", ENXIO },
        { "EOPNOTSUPP", EOPNOTSUPP },
        { "EOVERFLOW", EOVERFLOW },
        { "EOWNERDEAD", EOWNERDEAD },
        { "EPERM", EPERM },
        { "EPIPE", EPIPE },
        { "EPROTO", EPROTO },
        { "EPROTONOSUPPORT", EPROTONOSUPPORT },
        { "EPROTOTYPE", EPROTOTYPE },
        { "ERANGE", ERANGE },
        { "EROFS", EROFS },
        { "ESPIPE", ESPIPE },
        { "ETIME", ETIME },
        { "ESRCH", ESRCH },
        { "ETIMEDOUT", ETIMEDOUT },
        { "ETXTBSY", ETXTBSY },
        { "EWOULDBLOCK", EWOULDBLOCK },
        { "EXDEV", EXDEV },
        { 0, 0 }
    };

    static AMX_NATIVE_INFO NativeFunctionsTable[] =
    {
        #define CURRENT_NATIVE_LIBRARY algorithm
        #define REGISTER_NATIVE(lib,func,prefix) {#prefix#func, lib::natives::func}

        //system

        { "system_system", system::natives::system },
        { "system_getenv", system::natives::getenv },

        //interface
        { "IsValidScript", iscript::natives::IsValidScript },
        { "GetScriptType", iscript::natives::GetScriptType },
        { "GetScriptPLEHeader", iscript::natives::GetScriptPLEHeader },
        { "GetScriptPoolSize", iscript::natives::GetScriptPoolSize },
        { "GetScriptIdentifierFromKey", iscript::natives::GetScriptIdentifierFromKey },
        { "GetScriptKeyFromIdentifier", iscript::natives::GetScriptKeyFromIdentifier },

        //inter script communication
        { "GetAMXHeader", isc::natives::GetAMXHeader },
        { "ReadAMXMemory", isc::natives::ReadAMXMemory },
        { "WriteAMXMemory", isc::natives::WriteAMXMemory },
        { "ReadAMXMemoryArray", isc::natives::ReadAMXMemoryArray },
        { "WriteAMXMemoryArray", isc::natives::WriteAMXMemoryArray },
        { "GetExternalFunctionID", isc::natives::GetExternalFunctionID },
        { "CallExternalFunction", isc::natives::CallExternalFunction },
        { "GetExternalFunctionInfo", isc::natives::GetExternalFunctionInfo },
        { "GetExternalVariableID", isc::natives::GetExternalVariableID },
        { "GetExternalVariableInfo", isc::natives::GetExternalVariableInfo },
        { "GetExternalVariable", isc::natives::GetExternalVariable },
        { "SetExternalVariable", isc::natives::SetExternalVariable },

        //ctype
        { "isalnum", ctype::natives::isalnum },
        { "isalpha", ctype::natives::isalpha },
        { "isblank", ctype::natives::isblank },
        { "iscntrl", ctype::natives::iscntrl },
        { "isdigit", ctype::natives::isdigit },
        { "isgraph", ctype::natives::isgraph },
        { "islower", ctype::natives::islower },
        { "isprint", ctype::natives::isprint },
        { "ispunct", ctype::natives::ispunct },
        { "isspace", ctype::natives::isspace },
        { "isupper", ctype::natives::isupper },
        { "isxdigit", ctype::natives::isxdigit },

        //string
        { "memmove", string::natives::memmove },
        { "strcpy", string::natives::strcpy },
        { "strncpy", string::natives::strncpy },
        { "strncat", string::natives::strncat },
        { "strncmp", string::natives::strncmp },
        { "memchr", string::natives::memchr },
        { "strchr", string::natives::strchr },
        { "strrchr", string::natives::strrchr },
        { "strcspn", string::natives::strcspn },
        { "strpbrk", string::natives::strpbrk },
        { "strspn", string::natives::strspn },
        { "strtok", string::natives::strtok },
        { "memset", string::natives::memset },
        { "strreplace", string::natives::strreplace },
        { "strtrim", string::natives::strtrim },
        { "strtolower", string::natives::strtolower },
        { "strtoupper", string::natives::strtoupper },
        { "strerror", string::natives::strerror },

        //file
        { "file_open", fstream::natives::open },
        { "file_close", fstream::natives::close },
        { "file_is_valid", fstream::natives::is_valid },
        { "file_getch", fstream::natives::getch },
        { "file_getstr", fstream::natives::getstr },
        { "file_peek", fstream::natives::peek },
        { "file_unget", fstream::natives::unget },
        { "file_putback", fstream::natives::putback },
        { "file_getline", fstream::natives::getline },
        { "file_ignore", fstream::natives::ignore },
        { "file_read", fstream::natives::read },
        { "file_extract_number", fstream::natives::extract_number },
        { "file_extract_float", fstream::natives::extract_float },
        { "file_extract_bool", fstream::natives::extract_bool },
        { "file_extract_string", fstream::natives::extract_string },
        { "file_insert_number", fstream::natives::insert_number },
        { "file_insert_float", fstream::natives::insert_float },
        { "file_insert_bool", fstream::natives::insert_bool },
        { "file_insert_string", fstream::natives::insert_string },
        { "file_gcount", fstream::natives::gcount },
        { "file_tellg", fstream::natives::tellg },
        { "file_seekg", fstream::natives::seekg },
        { "file_sync", fstream::natives::sync },
        { "file_put", fstream::natives::put },
        { "file_write", fstream::natives::write },
        { "file_tellp", fstream::natives::tellp },
        { "file_seekp", fstream::natives::seekp },
        { "file_flush", fstream::natives::flush },
        { "file_good", fstream::natives::good },
        { "file_eof", fstream::natives::eof },
        { "file_fail", fstream::natives::fail },
        { "file_bad", fstream::natives::bad },
        { "file_rdstate", fstream::natives::rdstate },
        { "file_setstate", fstream::natives::setstate },
        { "file_clear", fstream::natives::clear },
        { "file_copyfmt", fstream::natives::copyfmt },
        { "file_fill", fstream::natives::fill },
        { "file_tie", fstream::natives::tie },
        { "file_getflags", fstream::natives::getflags },
        { "file_setflags", fstream::natives::setflags },
        { "file_setf", fstream::natives::setf },
        { "file_unsetf", fstream::natives::unsetf },
        { "file_getprecision", fstream::natives::getprecision },
        { "file_setprecision", fstream::natives::setprecision },
        { "file_getwidth", fstream::natives::getwidth },
        { "file_setwidth", fstream::natives::setwidth },

        //chrono
        { "system_clock_now", chrono::natives::system_clock_now },
        { "steady_clock_now", chrono::natives::steady_clock_now },
        { "timespec_get", chrono::natives::timespec_get },
        { "timespec_add", chrono::natives::timespec_add },
        { "timespec_diff", chrono::natives::timespec_diff },
        { "timespec_diff_as_seconds", chrono::natives::timespec_diff_as_seconds },
        { "timespec_diff_as_milliseconds", chrono::natives::timespec_diff_as_milliseconds },
        { "timespec_diff_as_microseconds", chrono::natives::timespec_diff_as_microseconds },
        { "timespec_diff_as_nanoseconds", chrono::natives::timespec_diff_as_nanoseconds },
        { "to_universal", chrono::natives::to_universal },
        { "to_local", chrono::natives::to_local },
        { "to_timestamp", chrono::natives::to_timestamp },
        { "difftime", chrono::natives::difftime },
        { "asctime", chrono::natives::asctime },
        { "strftime", chrono::natives::strftime },

        //errno
        { "errno", ov_errno::natives::ov_errno },
        { "clearerrno", ov_errno::natives::clearerrno },

        //functional
        { "_make_function", functional::natives::make_function },

        //algorithm
        { "ibsearch", algorithm::natives::ibsearch },
        { "fbsearch", algorithm::natives::fbsearch },
        { "sbsearch", algorithm::natives::sbsearch },
        { "all_of", algorithm::natives::all_of },
        { "any_of", algorithm::natives::any_of },
        { "none_of", algorithm::natives::none_of },
        { "for_each", algorithm::natives::for_each },
        { "find", algorithm::natives::find },
        { "find_if", algorithm::natives::find_if },
        { "find_if_not", algorithm::natives::find_if_not },
        { "find_end", algorithm::natives::find_end },
        { "find_first_of", algorithm::natives::find_first_of },
        { "adjacent_find", algorithm::natives::adjacent_find },
        { "count", algorithm::natives::count },
        { "count_if", algorithm::natives::count_if },
        { "mismatch", algorithm::natives::mismatch },
        { "equal", algorithm::natives::equal },
        { "is_permutation", algorithm::natives::is_permutation },
        { "search", algorithm::natives::search },
        { "search_n", algorithm::natives::search_n },
        { "copy", algorithm::natives::copy },
        { "copy_if", algorithm::natives::copy_if },
        { "copy_backward",algorithm::natives::copy_backward },
        { "swap", algorithm::natives::swap },
        { "swap_ranges", algorithm::natives::swap_ranges },
        { "transform", algorithm::natives::transform },
        { "transform2", algorithm::natives::transform2 },
        { "replace", algorithm::natives::replace },
        { "replace_if", algorithm::natives::replace_if },
        { "replace_copy", algorithm::natives::replace_copy },
        { "replace_copy_if", algorithm::natives::replace_copy_if },
        { "fill", algorithm::natives::fill },
        { "generate", algorithm::natives::generate },
        { "remove", algorithm::natives::remove },
        { "remove_if", algorithm::natives::remove_if },
        { "remove_copy", algorithm::natives::remove_copy },
        { "remove_copy_if", algorithm::natives::remove_copy_if },
        { "unique", algorithm::natives::unique },
        { "unique_copy", algorithm::natives::unique_copy },
        { "reverse", algorithm::natives::reverse },
        { "reverse_copy", algorithm::natives::reverse_copy },
        { "rotate", algorithm::natives::rotate },
        { "rotate_copy", algorithm::natives::rotate_copy },
        { "shuffle", algorithm::natives::shuffle },
        { "sample", algorithm::natives::sample },
        { "is_partitioned", algorithm::natives::is_partitioned },
        { "partition", algorithm::natives::partition },
        { "stable_partition", algorithm::natives::stable_partition },
        { "partition_copy", algorithm::natives::partition_copy },
        { "partition_point", algorithm::natives::partition_point },
        { "sort", algorithm::natives::sort },
        { "partial_sort", algorithm::natives::partial_sort },
        { "partial_sort_copy", algorithm::natives::partial_sort_copy },
        { "is_sorted", algorithm::natives::is_sorted },
        { "nth_element", algorithm::natives::nth_element },
        { "lower_bound", algorithm::natives::lower_bound },
        { "upper_bound", algorithm::natives::upper_bound },
        { "equal_range", algorithm::natives::equal_range },
        { "binary_search", algorithm::natives::binary_search },
        { "merge", algorithm::natives::merge },
        { "inplace_merge", algorithm::natives::inplace_merge },
        { "includes", algorithm::natives::includes },
        { "set_union", algorithm::natives::set_union },
        { "set_intersection", algorithm::natives::set_intersection },
        { "set_difference", algorithm::natives::set_difference },
        { "set_symmetric_difference", algorithm::natives::set_symmetric_difference },
        { "is_heap", algorithm::natives::is_heap },
        { "is_heap_until", algorithm::natives::is_heap_until },
        { "make_heap", algorithm::natives::make_heap },
        { "sort_heap", algorithm::natives::sort_heap },
        { "push_heap", algorithm::natives::push_heap },
        { "pop_heap", algorithm::natives::pop_heap },
        { "minmax_element", algorithm::natives::minmax_element },
        { "min_element", algorithm::natives::min_element },
        { "max_element", algorithm::natives::max_element },
        { "lexicographical_compare", algorithm::natives::lexicographical_compare },
        { "next_permutation", algorithm::natives::next_permutation },
        { "prev_permutation", algorithm::natives::prev_permutation },       
        { "iota", algorithm::natives::iota },
        { "accumulate", algorithm::natives::accumulate },
        { "inner_product", algorithm::natives::inner_product },
        { "adjacent_difference", algorithm::natives::adjacent_difference },
        { "partial_sum", algorithm::natives::partial_sum },
        { "gcd", algorithm::natives::gcd },
        { "lcm", algorithm::natives::lcm },
       

        //math
        { "exp", math::natives::exp },
        { "frexp", math::natives::frexp },
        { "ldexp", math::natives::ldexp },
        { "modf", math::natives::modf },
        { "log", math::natives::log },
        { "log10", math::natives::log10 },
        { "exp2", math::natives::exp2 },
        { "expm1", math::natives::expm1 },
        { "log2", math::natives::log2 },
        { "log1p", math::natives::log1p },
        { "cbrt", math::natives::cbrt },
        { "hypot", math::natives::hypot },
        { "fmod", math::natives::fmod },
        { "remainder", math::natives::remainder },
        { "copysign", math::natives::copysign },
        { "fdim", math::natives::fdim },
        { "fmin", math::natives::fmin },
        { "fmax", math::natives::fmax },
        { "fma", math::natives::fma },
        {"fclamp", math::natives::fclamp },
        { "cbrt", math::natives::cbrt },
        { "math_errhandling", math::natives::ov_math_errhandling },

        //complex
        { "cabs", complex::natives::cabs },
        { "carg", complex::natives::carg },
        { "cnorm", complex::natives::cnorm },
        { "cconj", complex::natives::cconj },
        { "cpolar", complex::natives::cpolar },
        { "ccos", complex::natives::ccos },
        { "csin", complex::natives::csin },
        { "ctan", complex::natives::ctan },
        { "cacos", complex::natives::cacos },
        { "casin", complex::natives::casin },
        { "catan", complex::natives::catan },
        { "ccosh", complex::natives::ccosh },
        { "csinh", complex::natives::csinh },
        { "ctanh", complex::natives::ctanh },
        { "cacosh", complex::natives::cacosh },
        { "casinh", complex::natives::casinh },
        { "catanh", complex::natives::catanh },
        { "cexp", complex::natives::cexp },
        { "clog", complex::natives::clog },
        { "clog10", complex::natives::clog10 },
        { "cpow", complex::natives::cpow },
        { "csqrt", complex::natives::csqrt },
        { "cnegate", complex::natives::cnegate },
        { "cadd", complex::natives::cadd },
        { "csub", complex::natives::csub },
        { "cmul", complex::natives::cmul },
        { "cdiv", complex::natives::cdiv },
        { "cequal", complex::natives::cequal },

        //bitset
        { "bitset_count", bitset::natives::count },
        { "bitset_size", bitset::natives::size },
        { "bitset_test", bitset::natives::test },
        { "bitset_any", bitset::natives::any },
        { "bitset_none", bitset::natives::none },
        { "bitset_all", bitset::natives::all },
        { "bitset_set", bitset::natives::set },
        { "bitset_reset", bitset::natives::reset },
        { "bitset_flip", bitset::natives::flip },
        { "bitset_set_all", bitset::natives::set_all },
        { "bitset_reset_all", bitset::natives::reset_all },
        { "bitset_flip_all", bitset::natives::flip_all },
        { "bitset_tostring", bitset::natives::tostring },
        { "bitset_and", bitset::natives::and },
        { "bitset_or", bitset::natives:: or },
        { "bitset_xor", bitset::natives::xor },
        { "bitset_equal", bitset::natives::equal },
        { "bitset_foreach_set", bitset::natives::foreach_set },
        { "bitset_foreach_notset", bitset::natives::foreach_notset },
        { "bitset_find_set", bitset::natives::find_set },
        { "bitset_find_notset", bitset::natives::find_notset },
        { 0, 0 }
    };

    static std::vector <IScript> IScriptList;

    void IScript::load(AMX * p_amx, ScriptKey_t p_scriptKey)
    {
        amx = p_amx;
        scriptKey = p_scriptKey;
        scriptIdentifier = ScriptIdentifier::unsupported;

        ple_header = nullptr;
        startof_header_marker = -1;
        type = interface_type::unsupported;

        if (amx_FindPubVar(amx, "_ple_header_start", &startof_header_marker) == AMX_ERR_NONE
            && amx_FindPubVar(amx, "_ple_header_end", &endof_header_marker) == AMX_ERR_NONE)
        {
            if ((endof_header_marker - startof_header_marker) == (sizeof(PLE_HEADER) + sizeof(cell)))
            {
                cell *ple_header_phys_addr;
                amx_GetAddr(amx, startof_header_marker + sizeof(cell), &ple_header_phys_addr);

                PLE_HEADER *possible_hdr = reinterpret_cast<PLE_HEADER*>(ple_header_phys_addr);
                if (possible_hdr->size == sizeof(PLE_HEADER) && possible_hdr->signature_end == 0x0408)
                {
                    ple_header = possible_hdr;
                    type = interface_type::supported;

                    char cstr_scriptidentifier[ScriptIdentifier::max_length];
                    amx_GetString(cstr_scriptidentifier, ple_header->scriptidentifier, 0, ScriptIdentifier::max_length);
                    scriptIdentifier = cstr_scriptidentifier;

                    ple_header->scriptkey = p_scriptKey;

                    if (PLE_PLUGIN_VERSION_KEY > ple_header->inc_version)
                        logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s' (ScriptKey: %d).\nThe script is using an older version of PLE.", cstr_scriptidentifier, scriptKey);
                    else if (PLE_PLUGIN_VERSION_KEY < ple_header->inc_version)
                        logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s' (ScriptKey: %d).\nThe script is using a newer version of PLE.", cstr_scriptidentifier, scriptKey);

                    if (scriptIdentifier == ScriptIdentifier::undefined)
                        logprintf("[NOTICE] PAWN Library Extension: A loaded script (ScriptKey: %d) does not have a script identifier.", scriptKey);
                    else
                    {
                        int duplicate_count = 0;
                        for (auto &&intrf : IScriptList)
                        {
                            if (intrf.empty()) continue;
                            if (intrf.GetScriptKey() == scriptKey) continue;

                            if (intrf.GetScriptIdentifier() == scriptIdentifier)
                                duplicate_count++;

                            intrf.Trigger_OnScriptLoad(scriptKey, scriptIdentifier);
                        }
                        if (duplicate_count)
                            logprintf("[WARNING] PAWN Library Extension: Script identifier '%s' is being used by %d scripts.", cstr_scriptidentifier, duplicate_count + 1);
                    }
                }
            }
        }

        if (type != interface_type::supported)
            logprintf("[NOTICE] PAWN Library Extension: A script (ScriptKey:%d) was loaded which does not have a functional PLE header.", scriptKey);

        for (const auto& entry : PublicVariablesTable)
        {
            cell pubvar_addr;
            if (amx_FindPubVar(amx, entry.name, &pubvar_addr) == AMX_ERR_NONE)
            {
                cell *pubvar_phyaddr;
                amx_GetAddr(amx, pubvar_addr, &pubvar_phyaddr);
                *pubvar_phyaddr = entry.value;
            }
        }
        amx_Register(amx, NativeFunctionsTable, -1);
    }

    void IScript::unload()
    {
        type = interface_type::invalid;
        for (const auto& intrf : IScriptList)
        {
            if (intrf.GetScriptKey() == scriptKey) continue;
            if (intrf.empty()) continue;

            intrf.Trigger_OnScriptUnload(scriptKey, scriptIdentifier);
        }
    }

    void IScript::Trigger_OnScriptLoad(ScriptKey_t scriptKey, const std::string& scriptIdentifier) const
    {
        //public OnScriptLoad(scriptKey, scriptIdentifier[])

        cell cbidx;
        if (amx_FindPublic(amx, "OnScriptLoad", &cbidx) != AMX_ERR_NONE)
            return;

        cell addr;
        amx_PushString(amx, &addr, NULL, scriptIdentifier.c_str(), NULL, NULL);
        amx_Push(amx, scriptKey);

        amx_Exec(amx, NULL, cbidx);
        amx_Release(amx, addr);
    }
    void IScript::Trigger_OnScriptUnload(ScriptKey_t scriptKey, const std::string& scriptIdentifier) const
    {
        //public OnScriptUnload(scriptKey, scriptIdentifier[])

        cell cbidx;
        if (amx_FindPublic(amx, "OnScriptUnload", &cbidx) != AMX_ERR_NONE)
            return;

        cell addr;
        amx_PushString(amx, &addr, NULL, scriptIdentifier.c_str(), NULL, NULL);
        amx_Push(amx, scriptKey);

        amx_Exec(amx, NULL, cbidx);
        amx_Release(amx, addr);
    }

    void AddInterface(AMX *amx)
    {
        ScriptKey_t scriptKey = std::find_if(IScriptList.begin(), IScriptList.end(), [](const IScript& intrf) { return intrf.empty(); }) - IScriptList.begin(); //find an unused scriptKey
        if (scriptKey == IScriptList.size())
        {
            if ((IScriptList.size() - 1) == std::numeric_limits<ScriptKey_t>::max())
                logprintf("[CRITICAL] The number of scripts loaded exceeds the maximum number of simultaneously loaded scripts supported by the plugin. This may cause undefined behaviour.");

            scriptKey = static_cast<ScriptKey_t>(IScriptList.size());
            IScriptList.emplace_back();
        }

        IScriptList[scriptKey].load(amx, scriptKey);
    }
    void RemoveInterface(AMX *amx)
    {
        ScriptKey_t scriptKey = FindInterface(amx);
        if (scriptKey != INVALID_SCRIPT_KEY)
            IScriptList[scriptKey].unload();
    }
    ScriptKey_t FindInterface(AMX *amx)
    {
        auto intrf_iter = std::find_if(IScriptList.begin(), IScriptList.end(), [&amx](const IScript& intrf) { return intrf.amx == amx; });
        if (intrf_iter == IScriptList.end()) return INVALID_SCRIPT_KEY;
        return intrf_iter->GetScriptKey();
    }
    bool IsValidScript(cell scriptKey)
    {
        if (scriptKey < 0 || scriptKey >= static_cast<cell>(IScriptList.size())) return false;
        return !IScriptList[scriptKey].empty();
    }
    AMX * GetInterfaceAMX(ScriptKey_t scriptKey)
    {
        return IScriptList[scriptKey].amx;
    }

    namespace natives
    {
        //native bool:IsValidScript(scriptKey);
        cell AMX_NATIVE_CALL IsValidScript(AMX * amx, cell* params)
        {
            error_if(!check_params(1), "[PLE] interface>> IsValidScript: expected 1 parameters but found %d parameters.", get_params_count());
            return iscript::IsValidScript(params[1]);
        }
        //native GetScriptType(scriptKey);
        cell AMX_NATIVE_CALL GetScriptType(AMX * amx, cell* params)
        {
            error_if(!check_params(1), "[PLE] interface>> GetScriptType: expected 1 parameters but found %d parameters.", get_params_count());
            if (!iscript::IsValidScript(params[1]))
                return interface_type::invalid;
            return IScriptList[params[1]].GetType();
        }
        //native GetScriptPoolSize();
        cell AMX_NATIVE_CALL GetScriptPoolSize(AMX * amx, cell* params)
        {
            error_if(!check_params(0), "[PLE] interface>> GetScriptPoolSize: expected 0 parameters but found %d parameters.", get_params_count());
            return static_cast<cell>(IScriptList.size() - 1);
        }
        //native bool:GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
        cell AMX_NATIVE_CALL GetScriptIdentifierFromKey(AMX * amx, cell* params)
        {
            error_if(!check_params(3), "[PLE] interface>> GetScriptIdentifierFromKey: expected 3 parameters but found %d parameters.", get_params_count());
            if (iscript::IsValidScript(params[1])) return false;

            cell* addr = NULL;
            amx_GetAddr(amx, params[2], &addr);
            amx_SetString(addr, IScriptList[params[1]].GetScriptIdentifier().c_str(), 0, 0, params[3]);
            return true;
        }
        //native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));
        cell AMX_NATIVE_CALL GetScriptKeyFromIdentifier(AMX * amx, cell* params)
        {
            error_if(!check_params(3), "[PLE] interface>> GetScriptKeyFromIdentifier: expected 3 parameters but found %d parameters.", get_params_count());

            cell *addr = NULL;
            amx_GetAddr(amx, params[1], &addr);

            char cstr_scriptidentifier[ScriptIdentifier::max_length];
            amx_GetString(cstr_scriptidentifier, addr, 0, ScriptIdentifier::max_length);

            cell *scriptIDArray;
            amx_GetAddr(amx, params[2], &scriptIDArray);

            cell count = 0;
            for (auto &&intrf : IScriptList)
            {
                if (intrf.empty()) continue;
                if (intrf.GetScriptIdentifier() != cstr_scriptidentifier) continue;

                if (count == params[3])
                    break;

                *scriptIDArray++ = static_cast<cell>(intrf.GetScriptKey());
                count++;
            }
            return count;
        }
        //native bool:GetScriptPLEHeader(scriptKey, _ple_header[PLE_HEADER]);
        cell AMX_NATIVE_CALL GetScriptPLEHeader(AMX * amx, cell* params)
        {
            error_if(!check_params(2), "[PLE] interface>> GetScriptPLEHeader: expected 2 parameters but found %d parameters.", get_params_count());
            if (iscript::IsValidScript(params[1])) return false;

            cell* addr = NULL;
            amx_GetAddr(amx, params[2], &addr);
            IScript &intrf = IScriptList[params[1]];

            if (intrf.GetType() != interface_type::supported) return false;

            std::memcpy(addr, intrf.GetHeader(), sizeof(PLE_HEADER));
            return true;
        }
    }
}