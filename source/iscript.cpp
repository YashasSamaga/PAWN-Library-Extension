/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interface is a layer between the AMX instance and the plugin.
iscript.cpp

*************************************************************************************************************/
#include "main.h"
#include "version.h"
#include "iscript.h"

#include "natives/algorithm.h"
#include "natives/bitset.h"
#include "natives/complex.h"
#include "natives/ctype.h"
#include "natives/errno.h"
#include "natives/fstream.h"
#include "natives/functional.h"
#include "natives/isc.h"
#include "natives/math.h"
#include "natives/memory.h"
#include "natives/numeric.h"
#include "natives/random.h"
#include "natives/string.h"
#include "natives/system.h"
#include "natives/time.h"

#include <algorithm>
#include <vector>
#include <fenv.h>

namespace PLE
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
		//system
		{ "system", natives::system_system },
		{ "getenv", natives::system_getenv },

		//interface
		{ "IsValidScript", natives::iscript_IsValidScript },
		{ "GetScriptType", natives::iscript_GetScriptType },
		{ "GetScriptPLEHeader", natives::iscript_GetScriptPLEHeader },
		{ "GetScriptPoolSize", natives::iscript_GetScriptPoolSize },
		{ "GetScriptIdentifierFromKey", natives::iscript_GetScriptIdentifierFromKey },
		{ "GetScriptKeyFromIdentifier", natives::iscript_GetScriptKeyFromIdentifier },

		//inter script communication
		{ "GetAMXHeader", natives::isc_GetAMXHeader },
		{ "ReadAMXMemory", natives::isc_ReadAMXMemory },
		{ "WriteAMXMemory", natives::isc_WriteAMXMemory },
		{ "ReadAMXMemoryArray", natives::isc_ReadAMXMemoryArray },
		{ "WriteAMXMemoryArray", natives::isc_WriteAMXMemoryArray },
		{ "GetExternalFunctionID", natives::isc_GetExternalFunctionID },
		{ "CallExternalFunction", natives::isc_CallExternalFunction },
		{ "GetExternalFunctionInfo", natives::isc_GetExternalFunctionInfo },
		{ "GetExternalVariableID", natives::isc_GetExternalVariableID },
		{ "GetExternalVariableInfo", natives::isc_GetExternalVariableInfo },
		{ "GetExternalVariable", natives::isc_GetExternalVariable },
		{ "SetExternalVariable", natives::isc_SetExternalVariable },

		//ctype
		{ "isalnum", natives::ctype_isalnum },
		{ "isalpha", natives::ctype_isalpha },
		{ "isblank", natives::ctype_isblank },
		{ "iscntrl", natives::ctype_iscntrl },
		{ "isdigit", natives::ctype_isdigit },
		{ "isgraph", natives::ctype_isgraph },
		{ "islower", natives::ctype_islower },
		{ "isprint", natives::ctype_isprint },
		{ "ispunct", natives::ctype_ispunct },
		{ "isspace", natives::ctype_isspace },
		{ "isupper", natives::ctype_isupper },
		{ "isxdigit", natives::ctype_isxdigit },

		//string
		{ "memmove", natives::string_memmove },
		{ "strcpy", natives::string_strcpy },
		{ "strncpy", natives::string_strncpy },
		{ "strncat", natives::string_strncat },
		{ "strncmp", natives::string_strncmp },
		{ "memchr", natives::string_memchr },
		{ "strchr", natives::string_strchr },
		{ "strrchr", natives::string_strrchr },
		{ "strcspn", natives::string_strcspn },
		{ "strpbrk", natives::string_strpbrk },
		{ "strspn", natives::string_strspn },
		{ "strtok", natives::string_strtok },
		{ "memset", natives::string_memset },
		{ "strreplace", natives::string_strreplace },
		{ "strtrim", natives::string_strtrim },
		{ "strtolower", natives::string_strtolower },
		{ "strtoupper", natives::string_strtoupper },
		{ "strerror", natives::string_strerror },

		//file
		{ "file_open", natives::file_open },
		{ "file_close", natives::file_close },
		{ "file_IsValidFile", natives::file_IsValidFile },
		{ "file_getch", natives::file_getch },
		{ "file_getstr", natives::file_getstr },
		{ "file_peek", natives::file_peek },
		{ "file_unget", natives::file_unget },
		{ "file_putback", natives::file_putback },
		{ "file_getline", natives::file_getline },
		{ "file_ignore", natives::file_ignore },
		{ "file_read", natives::file_read },
		{ "file_extract_number", natives::file_extract_number },
		{ "file_extract_float", natives::file_extract_float },
		{ "file_extract_bool", natives::file_extract_bool },
		{ "file_extract_string", natives::file_extract_string },
		{ "file_insert_number", natives::file_insert_number },
		{ "file_insert_float", natives::file_insert_float },
		{ "file_insert_bool", natives::file_insert_bool },
		{ "file_insert_string", natives::file_insert_string },
		{ "file_gcount", natives::file_gcount },
		{ "file_tellg", natives::file_tellg },
		{ "file_seekg", natives::file_seekg },
		{ "file_sync", natives::file_sync },
		{ "file_put", natives::file_put },
		{ "file_write", natives::file_write },
		{ "file_tellp", natives::file_tellp },
		{ "file_seekp", natives::file_seekp },
		{ "file_flush", natives::file_flush },
		{ "file_good", natives::file_good },
		{ "file_eof", natives::file_eof },
		{ "file_fail", natives::file_fail },
		{ "file_bad", natives::file_bad },
		{ "file_rdstate", natives::file_rdstate },
		{ "file_setstate", natives::file_setstate },
		{ "file_clear", natives::file_clear },
		{ "file_copyfmt", natives::file_copyfmt },
		{ "file_fill", natives::file_fill },
		{ "file_tie", natives::file_tie },
		{ "file_getflags", natives::file_getflags },
		{ "file_setflags", natives::file_setflags },
		{ "file_setf", natives::file_setf },
		{ "file_unsetf", natives::file_unsetf },
		{ "file_getprecision", natives::file_getprecision },
		{ "file_setprecision", natives::file_setprecision },
		{ "file_getwidth", natives::file_getwidth },
		{ "file_setwidth", natives::file_setwidth },

		//time
		{ "now", natives::time_now },
		{ "createtime", natives::time_createtime },
		{ "gettimestamp", natives::time_gettimestamp },
		{ "difftime", natives::time_difftime },
		{ "asctime", natives::time_asctime },
		{ "strftime", natives::time_strftime },

		//errno
		{ "errno", natives::errno_errno },
		{ "clearerrno", natives::errno_clearerrno },

		//functional
		{ "argArray", natives::functional_argArray },
		{ "argReference", natives::functional_argReference },
		{ "_make_function", natives::functional_make_function },

		//algorithm
		{ "ibsearch", natives::algo_ibsearch },
		{ "fbsearch", natives::algo_fbsearch },
		{ "sbsearch", natives::algo_sbsearch },
		{ "all_of", natives::algo_all_of },
		{ "any_of", natives::algo_any_of },
		{ "none_of", natives::algo_none_of },
		{ "for_each", natives::algo_for_each },
		{ "find", natives::algo_find },
		{ "find_if", natives::algo_find_if },
		{ "find_if_not", natives::algo_find_if_not },
		{ "find_end", natives::algo_find_end },
		{ "find_first_of", natives::algo_find_first_of },
		{ "adjacent_find", natives::algo_adjacent_find },
		{ "count", natives::algo_count },
		{ "count_if", natives::algo_count_if },
		{ "mismatch", natives::algo_mismatch },
		{ "equal", natives::algo_equal },
		{ "is_permutation", natives::algo_is_permutation },
		{ "search", natives::algo_search },
		{ "search_n", natives::algo_search_n },
		{ "copy", natives::algo_copy },
		{ "copy_if", natives::algo_copy_if },
		{ "copy_backward", natives::algo_copy_backward },
		{ "swap", natives::algo_swap },
		{ "swap_ranges", natives::algo_swap_ranges },
		{ "transform", natives::algo_transform },
		{ "transform2", natives::algo_transform2 },
		{ "replace", natives::algo_replace },
		{ "replace_if", natives::algo_replace_if },
		{ "replace_copy", natives::algo_replace_copy },
		{ "replace_copy_if", natives::algo_replace_copy_if },
		{ "fill", natives::algo_fill },
		{ "generate", natives::algo_generate },
		{ "remove", natives::algo_remove },
		{ "remove_if", natives::algo_remove_if },
		{ "remove_copy", natives::algo_remove_copy },
		{ "remove_copy_if", natives::algo_remove_copy_if },
		{ "unique", natives::algo_unique },
		{ "unique_copy", natives::algo_unique_copy },
		{ "reverse", natives::algo_reverse },
		{ "reverse_copy", natives::algo_reverse_copy },
		{ "rotate", natives::algo_rotate },
		{ "rotate_copy", natives::algo_rotate_copy },
		{ "shuffle", natives::algo_shuffle },
		{ "sample", natives::algo_sample },
		{ "is_partitioned", natives::algo_is_partitioned },
		{ "partition", natives::algo_partition },
		{ "stable_partition", natives::algo_stable_partition },
		{ "partition_copy", natives::algo_partition_copy },
		{ "partition_point", natives::algo_partition_point },
		{ "sort", natives::algo_sort },
		{ "partial_sort", natives::algo_partial_sort },
		{ "partial_sort_copy", natives::algo_partial_sort_copy },
		{ "is_sorted", natives::algo_is_sorted },
		{ "nth_element", natives::algo_nth_element },
		{ "lower_bound", natives::algo_lower_bound },
		{ "upper_bound", natives::algo_upper_bound },
		{ "equal_range", natives::algo_equal_range },
		{ "binary_search", natives::algo_binary_search },
		{ "merge", natives::algo_merge },
		{ "inplace_merge", natives::algo_inplace_merge },
		{ "includes", natives::algo_includes },
		{ "set_union", natives::algo_set_union },
		{ "set_intersection", natives::algo_set_intersection },
		{ "set_difference", natives::algo_set_difference },
		{ "set_symmetric_difference", natives::algo_set_symmetric_difference },
		{ "minmax_element", natives::algo_minmax_element },
		{ "min_element", natives::algo_min_element },
		{ "max_element", natives::algo_max_element },
		{ "lexicographical_compare", natives::algo_lexicographical_compare },
		{ "next_permutation", natives::algo_next_permutation },
		{ "prev_permutation", natives::algo_prev_permutation },

		//numeric
		{ "iota", natives::numeric_iota },
		{ "accumulate", natives::numeric_accumulate },
		{ "inner_product", natives::numeric_inner_product },
		{ "adjacent_difference", natives::numeric_adjacent_difference },
		{ "partial_sum", natives::numeric_partial_sum },
		{ "gcd", natives::numeric_gcd },
		{ "lcm", natives::numeric_lcm },

		//math
		{ "exp", natives::math_exp },
		{ "frexp", natives::math_frexp },
		{ "ldexp", natives::math_ldexp },
		{ "modf", natives::math_modf },
		{ "log", natives::math_log },
		{ "log10", natives::math_log10 },
		{ "exp2", natives::math_exp2 },
		{ "expm1", natives::math_expm1 },
		{ "log2", natives::math_log2 },
		{ "log1p", natives::math_log1p },
		{ "cbrt", natives::math_cbrt },
		{ "hypot", natives::math_hypot },
		{ "fmod", natives::math_fmod },
		{ "remainder", natives::math_remainder },
		{ "copysign", natives::math_copysign },
		{ "fdim", natives::math_fdim },
		{ "fmin", natives::math_fmin },
		{ "fmax", natives::math_fmax },
		{ "fma", natives::math_fma },
		{"fclamp", natives::math_fclamp },
		{ "cbrt", natives::math_cbrt },
		{ "math_errhandling", natives::math_math_errhandling },

		//complex
		{ "cabs", natives::complex_cabs },
		{ "carg", natives::complex_carg },
		{ "cnorm", natives::complex_cnorm },
		{ "cconj", natives::complex_cconj },
		{ "cpolar", natives::complex_cpolar },
		{ "ccos", natives::complex_ccos },
		{ "csin", natives::complex_csin },
		{ "ctan", natives::complex_ctan },
		{ "cacos", natives::complex_cacos },
		{ "casin", natives::complex_casin },
		{ "catan", natives::complex_catan },
		{ "ccosh", natives::complex_ccosh },
		{ "csinh", natives::complex_csinh },
		{ "ctanh", natives::complex_ctanh },
		{ "cacosh", natives::complex_cacosh },
		{ "casinh", natives::complex_casinh },
		{ "catanh", natives::complex_catanh },
		{ "cexp", natives::complex_cexp },
		{ "clog", natives::complex_clog },
		{ "clog10", natives::complex_clog10 },
		{ "cpow", natives::complex_cpow },
		{ "csqrt", natives::complex_csqrt },
		{ "cnegate", natives::complex_cnegate },
		{ "cadd", natives::complex_cadd },
		{ "csub", natives::complex_csub },
		{ "cmul", natives::complex_cmul },
		{ "cdiv", natives::complex_cdiv },
		{ "cequal", natives::complex_cequal },

		//bitset
		{ "bitset_count", natives::bitset_count },
		{ "bitset_size", natives::bitset_size },
		{ "bitset_test", natives::bitset_test },
		{ "bitset_any", natives::bitset_any },
		{ "bitset_none", natives::bitset_none },
		{ "bitset_all", natives::bitset_all },
		{ "bitset_set", natives::bitset_set },
		{ "bitset_reset", natives::bitset_reset },
		{ "bitset_flip", natives::bitset_flip },
		{ "bitset_set_all", natives::bitset_set_all },
		{ "bitset_reset_all", natives::bitset_reset_all },
		{ "bitset_flip_all", natives::bitset_flip_all },
		{ "bitset_tostring", natives::bitset_tostring },
		{ "bitset_and", natives::bitset_and },
		{ "bitset_or", natives::bitset_or },
		{ "bitset_xor", natives::bitset_xor },
		{ "bitset_equal", natives::bitset_equal },
		{ "bitset_foreach_set", natives::bitset_foreach_set },
		{ "bitset_foreach_notset", natives::bitset_foreach_notset },
		{ "bitset_find_set", natives::bitset_find_set },
		{ "bitset_find_notset", natives::bitset_find_notset },
		{ 0, 0 }
	};

	namespace IScript
	{
		static std::vector <IScript> IScriptList;

		void IScript::load(AMX * p_amx, ScriptKey_t p_scriptKey)
		{
			amx = p_amx;
			scriptKey = p_scriptKey;
			scriptIdentifier = ScriptIdentifier::unsupported;

			ple_header = nullptr;
			startof_header_marker = -1;
			type = interface_type::unsupported;

			if (amx_FindPubVar(amx, "__ple_header_start", &startof_header_marker) == AMX_ERR_NONE
				&& amx_FindPubVar(amx, "__ple_header_end", &endof_header_marker) == AMX_ERR_NONE)
			{
				if ((startof_header_marker - endof_header_marker) == (sizeof(PLE_HEADER) + sizeof(cell)))
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

			for (auto&& entry : PublicVariablesTable)
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
			for (auto&& intrf : IScriptList)
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
			ScriptKey_t scriptKey = INVALID_SCRIPT_KEY;
			auto intrf_iter = std::find_if(IScriptList.begin(), IScriptList.end(), [](const IScript& intrf) { return intrf.empty(); }); //find an unused scriptKey

			if (intrf_iter == IScriptList.end())
			{
				if (IScriptList.size() == std::numeric_limits<ScriptKey_t>::max())
					logprintf("[CRITICAL] The number of scripts loaded exceeds the maximum number of simultaneously loaded scripts supported by the plugin. This may cause undefined behaviour.");

				scriptKey = static_cast<ScriptKey_t>(IScriptList.size());
				IScriptList.emplace_back();
			}
			else
				scriptKey = std::distance(IScriptList.begin(), intrf_iter);

			(*intrf_iter).load(amx, scriptKey);
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
	}
	namespace natives
	{
		//native bool:IsValidScript(scriptKey);
		cell AMX_NATIVE_CALL iscript_IsValidScript(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] interface>> IsValidScript: expected 1 parameters but found %d parameters.", get_params_count());
			return IScript::IsValidScript(params[1]);
		}
		//native GetScriptType(scriptKey);
		cell AMX_NATIVE_CALL iscript_GetScriptType(AMX * amx, cell* params)
		{
			error_if(!check_params(1), "[PLE] interface>> GetScriptType: expected 1 parameters but found %d parameters.", get_params_count());
			if (!IScript::IsValidScript(params[1]))
				return IScript::interface_type::invalid;
			return IScript::IScriptList[params[1]].GetType();
		}
		//native GetScriptPoolSize();
		cell AMX_NATIVE_CALL iscript_GetScriptPoolSize(AMX * amx, cell* params)
		{
			error_if(!check_params(0), "[PLE] interface>> GetScriptPoolSize: expected 0 parameters but found %d parameters.", get_params_count());
			return static_cast<cell>(IScript::IScriptList.size() - 1);
		}
		//native bool:GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
		cell AMX_NATIVE_CALL iscript_GetScriptIdentifierFromKey(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] interface>> GetScriptIdentifierFromKey: expected 3 parameters but found %d parameters.", get_params_count());
			if (IScript::IsValidScript(params[1])) return false;

			cell* addr = NULL;
			amx_GetAddr(amx, params[2], &addr);
			amx_SetString(addr, IScript::IScriptList[params[1]].GetScriptIdentifier().c_str(), 0, 0, params[3]);
			return true;
		}
		//native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));
		cell AMX_NATIVE_CALL iscript_GetScriptKeyFromIdentifier(AMX * amx, cell* params)
		{
			error_if(!check_params(3), "[PLE] interface>> GetScriptKeyFromIdentifier: expected 3 parameters but found %d parameters.", get_params_count());

			cell *addr = NULL;
			amx_GetAddr(amx, params[1], &addr);

			char cstr_scriptidentifier[IScript::ScriptIdentifier::max_length];
			amx_GetString(cstr_scriptidentifier, addr, 0, IScript::ScriptIdentifier::max_length);

			cell *scriptIDArray;
			amx_GetAddr(amx, params[2], &scriptIDArray);

			cell count = 0;
			for (auto &&intrf : IScript::IScriptList)
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
		cell AMX_NATIVE_CALL iscript_GetScriptPLEHeader(AMX * amx, cell* params)
		{
			error_if(!check_params(2), "[PLE] interface>> GetScriptPLEHeader: expected 2 parameters but found %d parameters.", get_params_count());
			if (IScript::IsValidScript(params[1])) return false;

			cell* addr = NULL;
			amx_GetAddr(amx, params[2], &addr);
			IScript::IScript &intrf = IScript::IScriptList[params[1]];

			if (intrf.GetType() != IScript::interface_type::supported) return false;

			std::memcpy(addr, intrf.GetHeader(), sizeof(IScript::PLE_HEADER));
			return true;
		}
	}
}