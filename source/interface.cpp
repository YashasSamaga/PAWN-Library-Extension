/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Interface is a layer between the AMX instance and the plugin.
interface.cpp

*************************************************************************************************************/
#include "main.h"
#include "interface.h"

#include "natives/isc.h"
#include "natives/ctype.h"
#include "natives/string.h"
#include "natives/file.h"
#include "natives/time.h"
#include "natives/errno.h"
#include "natives/functional.h"
#include "natives/algorithm.h"
#include "natives/numeric.h"
#include "natives/math.h"
#include "natives/complex.h"
#include "natives/bitset.h"

#include <algorithm>
#include <vector>
#include <fenv.h>
/************************************************************************************************************/
struct PUBVAR_ENTRY { char name[32]; cell value; }; static PUBVAR_ENTRY entries[] =
{
	{ "EOF", EOF },
	{ "SEEK_SET", SEEK_SET },
	{ "SEEK_CUR", SEEK_CUR },
	{ "SEEK_END", SEEK_END },
	{ "BUFSIZ", BUFSIZ },
	{ "FILENAME_MAX", FILENAME_MAX },
	{ "FOPEN_MAX", FOPEN_MAX },
	{ "L_tmpnam", L_tmpnam },
	{ "TMP_MAX", TMP_MAX },

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
	{ 0, 0 },
};
static AMX_NATIVE_INFO NativeFunctionsTable[] =
{
	//interface
	{ "__InitAcknowledge", Natives::interface_ScriptInitAcknowledge },

	{ "IsValidScript", Natives::interface_IsValidScript },
	{ "GetScriptType", Natives::interface_GetScriptFlags },
	{ "GetScriptPoolSize", Natives::interface_GetScriptPoolSize },
	{ "GetScriptIdentifierFromKey", Natives::interface_GetScriptIdentifierFromKey },
	{ "GetScriptKeyFromIdentifier", Natives::interface_GetScriptKeyFromIdentifier },

	//inter script communication
	{ "GetAMXHeader", Natives::isc_GetAMXHeader },
	{ "ReadAMXMemory", Natives::isc_ReadAMXMemory },
	{ "WriteAMXMemory", Natives::isc_WriteAMXMemory },
	{ "ReadAMXMemoryArray", Natives::isc_ReadAMXMemoryArray },
	{ "WriteAMXMemoryArray", Natives::isc_WriteAMXMemoryArray },
	{ "GetExternalFunctionID", Natives::isc_GetExternalFunctionID },
	{ "CallExternalFunction", Natives::isc_CallExternalFunction },
	{ "GetExternalFunctionInfo", Natives::isc_GetExternalFunctionInfo },
	{ "GetExternalVariableID", Natives::isc_GetExternalVariableID },
	{ "GetExternalVariableInfo", Natives::isc_GetExternalVariableInfo },
	{ "GetExternalVariable", Natives::isc_GetExternalVariable },
	{ "SetExternalVariable", Natives::isc_SetExternalVariable },

	//ctype
	{ "isalnum", Natives::ctype_isalnum },
	{ "isalpha", Natives::ctype_isalpha },
	{ "isblank", Natives::ctype_isblank },
	{ "iscntrl", Natives::ctype_iscntrl },
	{ "isdigit", Natives::ctype_isdigit },
	{ "isgraph", Natives::ctype_isgraph },
	{ "islower", Natives::ctype_islower },
	{ "isprint", Natives::ctype_isprint },
	{ "ispunct", Natives::ctype_ispunct },
	{ "isspace", Natives::ctype_isspace },
	{ "isupper", Natives::ctype_isupper },
	{ "isxdigit", Natives::ctype_isxdigit },

	//string
	{ "memmove", Natives::string_memmove },
	{ "strcpy", Natives::string_strcpy },
	{ "strncpy", Natives::string_strncpy },
	{ "strncat", Natives::string_strncat },
	{ "strncmp", Natives::string_strncmp },
	{ "memchr", Natives::string_memchr },
	{ "strchr", Natives::string_strchr },
	{ "strrchr", Natives::string_strrchr },
	{ "strcspn", Natives::string_strcspn },
	{ "strpbrk", Natives::string_strpbrk },
	{ "strspn", Natives::string_strspn },
	{ "strtok", Natives::string_strtok },
	{ "memset", Natives::string_memset },
	{ "strreplace", Natives::string_strreplace },
	{ "strtrim", Natives::string_strtrim },
	{ "strtolower", Natives::string_strtolower },
	{ "strtoupper", Natives::string_strtoupper },
	{ "strerror", Natives::string_strerror },

	//file
	{ "file_fexists", Natives::file_fexists },
	{ "file_GetFileLocation", Natives::file_GetFileLocation },
	{ "file_GetFileMode", Natives::file_GetFileMode },
	{ "file_remove", Natives::file_remove },
	{ "file_rename", Natives::file_rename },
	{ "file_tmpfile", Natives::file_tmpfile },
	{ "file_tmpname", Natives::file_tmpname },
	{ "file_fclose", Natives::file_fclose },
	{ "file_fflush", Natives::file_fflush },
	{ "file_fopen", Natives::file_fopen },
	{ "file_fgetc", Natives::file_fgetc },
	{ "file_fgets", Natives::file_fgets },
	{ "file_fputc", Natives::file_fputc },
	{ "file_fputs", Natives::file_fputs },
	{ "file_ungetc", Natives::file_ungetc },
	{ "file_fread", Natives::file_fread },
	{ "file_fwrite", Natives::file_fwrite },
	{ "file_fgetpos", Natives::file_fgetpos },
	{ "file_fsetpos", Natives::file_fsetpos },
	{ "file_ftell", Natives::file_ftell },
	{ "file_rewind", Natives::file_rewind },
	{ "file_fseek", Natives::file_fseek },
	{ "file_clearerr", Natives::file_clearerr },
	{ "file_feof", Natives::file_feof },
	{ "file_ferror", Natives::file_ferror },

	//time
	{ "now", Natives::time_now },
	{ "createtime", Natives::time_createtime },
	{ "gettimestamp", Natives::time_gettimestamp },
	{ "difftime", Natives::time_difftime },
	{ "asctime", Natives::time_asctime },
	{ "strftime", Natives::time_strftime },

	//errno
	{ "errno", Natives::errno_errno },
	{ "clearerrno", Natives::errno_clearerrno },

	//functional
	{ "argArray", Natives::functional_argArray },
	{ "argReference", Natives::functional_argReference },
	{ "_make_function", Natives::functional_make_function },

	//algorithm
	{ "ibsearch", Natives::algo_ibsearch },
	{ "fbsearch", Natives::algo_fbsearch },
	{ "sbsearch", Natives::algo_sbsearch },
	{ "all_of", Natives::algo_all_of },
	{ "any_of", Natives::algo_any_of },
	{ "none_of", Natives::algo_none_of },
	{ "for_each", Natives::algo_for_each },
	{ "find", Natives::algo_find },
	{ "find_if", Natives::algo_find_if },
	{ "find_if_not", Natives::algo_find_if_not },
	{ "find_end", Natives::algo_find_end },
	{ "find_first_of", Natives::algo_find_first_of },
	{ "adjacent_find", Natives::algo_adjacent_find },
	{ "count", Natives::algo_count },
	{ "count_if", Natives::algo_count_if },
	{ "mismatch", Natives::algo_mismatch },
	{ "equal", Natives::algo_equal },
	{ "is_permutation", Natives::algo_is_permutation },
	{ "search", Natives::algo_search },
	{ "search_n", Natives::algo_search_n },
	{ "copy", Natives::algo_copy },
	{ "copy_if", Natives::algo_copy_if },
	{ "copy_backward", Natives::algo_copy_backward },
	{ "swap", Natives::algo_swap },
	{ "swap_ranges", Natives::algo_swap_ranges },
	{ "transform", Natives::algo_transform },
	{ "transform2", Natives::algo_transform2 },
	{ "replace", Natives::algo_replace },
	{ "replace_if", Natives::algo_replace_if },
	{ "replace_copy", Natives::algo_replace_copy },
	{ "replace_copy_if", Natives::algo_replace_copy_if },
	{ "fill", Natives::algo_fill },
	{ "generate", Natives::algo_generate },
	{ "remove", Natives::algo_remove },
	{ "remove_if", Natives::algo_remove_if },
	{ "remove_copy", Natives::algo_remove_copy },
	{ "remove_copy_if", Natives::algo_remove_copy_if },
	{ "unique", Natives::algo_unique },
	{ "unique_copy", Natives::algo_unique_copy },
	{ "reverse", Natives::algo_reverse },
	{ "reverse_copy", Natives::algo_reverse_copy },
	{ "rotate", Natives::algo_rotate },
	{ "rotate_copy", Natives::algo_rotate_copy },
	{ "shuffle", Natives::algo_shuffle },
	{ "is_partitioned", Natives::algo_is_partitioned },
	{ "partition", Natives::algo_partition },
	{ "stable_partition", Natives::algo_stable_partition },
	{ "partition_copy", Natives::algo_partition_copy },
	{ "partition_point", Natives::algo_partition_point },
	{ "sort", Natives::algo_sort },
	{ "partial_sort", Natives::algo_partial_sort },
	{ "partial_sort_copy", Natives::algo_partial_sort_copy },
	{ "is_sorted", Natives::algo_is_sorted },
	{ "nth_element", Natives::algo_nth_element },
	{ "lower_bound", Natives::algo_lower_bound },
	{ "upper_bound", Natives::algo_upper_bound },
	{ "equal_range", Natives::algo_equal_range },
	{ "binary_search", Natives::algo_binary_search },
	{ "merge", Natives::algo_merge },
	{ "inplace_merge", Natives::algo_inplace_merge },
	{ "includes", Natives::algo_includes },
	{ "set_union", Natives::algo_set_union },
	{ "set_intersection", Natives::algo_set_intersection },
	{ "set_difference", Natives::algo_set_difference },
	{ "set_symmetric_difference", Natives::algo_set_symmetric_difference },
	{ "minmax_element", Natives::algo_minmax_element },
	{ "min_element", Natives::algo_min_element },
	{ "max_element", Natives::algo_max_element },
	{ "lexicographical_compare", Natives::algo_lexicographical_compare },
	{ "next_permutation", Natives::algo_next_permutation },
	{ "prev_permutation", Natives::algo_prev_permutation },

	//numeric
	{ "iota", Natives::numeric_iota },
	{ "accumulate", Natives::numeric_accumulate },
	{ "inner_product", Natives::numeric_inner_product },
	{ "adjacent_difference", Natives::numeric_adjacent_difference },
	{ "partial_sum", Natives::numeric_partial_sum },
	{ "gcd", Natives::numeric_gcd },
	{ "lcm", Natives::numeric_lcm },

	//math
	{ "exp", Natives::math_exp },
	{ "frexp", Natives::math_frexp },
	{ "ldexp", Natives::math_ldexp },
	{ "modf", Natives::math_modf },
	{ "log", Natives::math_log },
	{ "log10", Natives::math_log10 },
	{ "exp2", Natives::math_exp2 },
	{ "expm1", Natives::math_expm1 },
	{ "log2", Natives::math_log2 },
	{ "log1p", Natives::math_log1p },
	{ "cbrt", Natives::math_cbrt },
	{ "hypot", Natives::math_hypot },
	{ "fmod", Natives::math_fmod },
	{ "remainder", Natives::math_remainder },
	{ "copysign", Natives::math_copysign },
	{ "fdim", Natives::math_fdim },
	{ "fmin", Natives::math_fmin },
	{ "fmax", Natives::math_fmax },
	{ "fma", Natives::math_fma },
	{ "cbrt", Natives::math_cbrt },
	{ "math_errhandling", Natives::math_math_errhandling },

	//complex
	{ "cabs", Natives::complex_cabs },
	{ "carg", Natives::complex_carg },
	{ "cnorm", Natives::complex_cnorm },
	{ "cconj", Natives::complex_cconj },
	{ "cpolar", Natives::complex_cpolar },
	{ "ccos", Natives::complex_ccos },
	{ "csin", Natives::complex_csin },
	{ "ctan", Natives::complex_ctan },
	{ "cacos", Natives::complex_cacos },
	{ "casin", Natives::complex_casin },
	{ "catan", Natives::complex_catan },
	{ "cexp", Natives::complex_cexp },
	{ "clog", Natives::complex_clog },
	{ "clog10", Natives::complex_clog10 },
	{ "cpow", Natives::complex_cpow },
	{ "csqrt", Natives::complex_csqrt },
	{ "cnegate", Natives::complex_cnegate },
	{ "cadd", Natives::complex_cadd },
	{ "csub", Natives::complex_csub },
	{ "cmul", Natives::complex_cmul },
	{ "cdiv", Natives::complex_cdiv },
	{ "cequal", Natives::complex_cequal },

	//bitset
	{ "bitset_count", Natives::bitset_count },
	{ "bitset_size", Natives::bitset_size },
	{ "bitset_test", Natives::bitset_test },
	{ "bitset_any", Natives::bitset_any },
	{ "bitset_none", Natives::bitset_none },
	{ "bitset_all", Natives::bitset_all },
	{ "bitset_set", Natives::bitset_set },
	{ "bitset_reset", Natives::bitset_reset },
	{ "bitset_flip", Natives::bitset_flip },
	{ "bitset_set_all", Natives::bitset_set_all },
	{ "bitset_reset_all", Natives::bitset_reset_all },
	{ "bitset_flip_all", Natives::bitset_flip_all },
	{ "bitset_tostring", Natives::bitset_tostring },
	{ "bitset_and", Natives::bitset_and },
	{ "bitset_or", Natives::bitset_or },
	{ "bitset_xor", Natives::bitset_xor },
	{ "bitset_equal", Natives::bitset_equal },
	{ "bitset_foreach_set", Natives::bitset_foreach_set },
	{ "bitset_foreach_notset", Natives::bitset_foreach_notset },
	{ "bitset_find_set", Natives::bitset_find_set },
	{ "bitset_find_notset", Natives::bitset_find_notset },
	{ 0, 0 }
};
/************************************************************************************************************/
namespace Interface
{
	static std::vector <Interface> InterfaceList;
	/********************************************************************************************************/
	//Initilizes the interface, registers natives, sets public constants
	int Interface::Initilize(AMX * amx, int ScriptKey)
	{
		this->Reset();
		this->SetFlag(INTERFACE_FLAGS::LOADED);
		this->amx = amx;
		this->ScriptKey = ScriptKey;

		//public OnScriptInit(scriptKey, scriptIdentifier[])
		if (amx_FindPublic(amx, "OnScriptInit", &this->cbidx_OnScriptInit) != AMX_ERR_NONE)
			this->cbidx_OnScriptInit = INVALID_AMX_FUNCIDX;

		//public OnScriptExit(scriptKey, scriptIdentifier[])
		if (amx_FindPublic(amx, "OnScriptExit", &this->cbidx_OnScriptExit) != AMX_ERR_NONE)
			this->cbidx_OnScriptExit = INVALID_AMX_FUNCIDX;

		this->time_loaded = std::chrono::system_clock::now();

		char cur_pubvar[32];
		cell pubvar_addr;
		int numPubVars;
		amx_NumPubVars(amx, &numPubVars);
		for (int i = 0; entries[i].name[0] != 0; i++)
		{
			int first = 0, last, mid, result;
			last = numPubVars - 1;

			while (first <= last)
			{
				mid = (first + last) / 2;

				amx_GetPubVar(amx, mid, cur_pubvar, &pubvar_addr);
				result = strcmp(cur_pubvar, entries[i].name);

				if (result > 0)
					last = mid - 1;
				else if (result < 0)
					first = mid + 1;
				else
				{
					cell *pubvar_phyaddr;
					amx_GetAddr(amx, pubvar_addr, &pubvar_phyaddr);
					*pubvar_phyaddr = entries[i].value;
					break;
				}
			}
		}
		return amx_Register(amx, NativeFunctionsTable, -1);
	}
	//OnScriptInit is called in every script (except the newly initilized) when a script is loaded
	void Interface::Trigger_OnScriptInit(int scriptKey, std::string& scriptIdentifier) const
	{
		if (this->cbidx_OnScriptInit == INVALID_AMX_FUNCIDX) return;

		cell addr;
		amx_PushString(amx, &addr, NULL, scriptIdentifier.c_str(), NULL, NULL);
		amx_Push(amx, scriptKey);

		amx_Exec(this->amx, NULL, this->cbidx_OnScriptInit);
		amx_Release(amx, addr);
	}
	//OnScriptExit is called in every script (except the unloaded script) when a script is unloaded
	void Interface::Trigger_OnScriptExit(int scriptKey, std::string& scriptIdentifier) const
	{
		if (this->cbidx_OnScriptExit == INVALID_AMX_FUNCIDX) return;

		cell addr;
		amx_PushString(amx, &addr, NULL, scriptIdentifier.c_str(), NULL, NULL);
		amx_Push(amx, scriptKey);

		amx_Exec(this->amx, NULL, this->cbidx_OnScriptExit);
		amx_Release(amx, addr);
	}
	/********************************************************************************************************/
	//Returns the scriptKey of the amx's interface
	int FindInterface(AMX * amx)
	{
		auto amx_interface = std::find_if(InterfaceList.begin(), InterfaceList.end(), [&amx](const Interface& intrf) { return intrf.amx == amx; });
		if (amx_interface == InterfaceList.end()) return INVALID_SCRIPT_ID;
		return (*amx_interface).ScriptKey;
	}
	//Creates and intilizes an interface for amx
	int AddInterface(AMX * amx)
	{
		int scriptKey = INVALID_SCRIPT_ID;
		auto amx_interface = std::find_if(InterfaceList.begin(), InterfaceList.end(), [](const Interface& intrf) { return intrf.empty(); }); //find an unused scriptKey

		if (amx_interface == InterfaceList.end())
		{
			scriptKey = InterfaceList.size();
			InterfaceList.push_back(Interface::Interface());
		}
		else
			scriptKey = std::distance(InterfaceList.begin(), amx_interface);

		return InterfaceList[scriptKey].Initilize(amx, scriptKey);
	}
	//Deinitilizes and deletes the interface for amx
	int DeleteInterface(AMX * amx)
	{
		int scriptKey = FindInterface(amx);
		if (scriptKey != INVALID_SCRIPT_ID)
		{
			for (int i = 0, j = InterfaceList.size(); i < j; i++)
			{
				if (i == scriptKey) continue;
				if (InterfaceList[i].empty()) continue;

				InterfaceList[i].Trigger_OnScriptExit(scriptKey, InterfaceList[scriptKey].ScriptIdentifier);
			}
			InterfaceList[scriptKey].Reset();
		}
		return scriptKey;
	}
	//Check if a scriptKey is valid
	bool IsValidScript(const int scriptKey)
	{
		if (scriptKey < 0 || scriptKey >= static_cast<int>(InterfaceList.size())) return false;
		if (InterfaceList[scriptKey].empty()) return false;
		return true;
	}
	//Returns the AMX structure of the interface (validity of scriptKey is not checked)
	AMX * GetInterfaceAMX(const int scriptKey)
	{
		return InterfaceList[scriptKey].amx;
	}
	/********************************************************************************************************/
	void ProcessTick()
	{
		for (int scriptKey = 0, j = InterfaceList.size(); scriptKey < j; scriptKey++)
		{
			if (InterfaceList[scriptKey].empty()) continue;
			if (InterfaceList[scriptKey].IsFlagSet(INTERFACE_FLAGS::LOADED) &&
				!InterfaceList[scriptKey].IsFlagSet(INTERFACE_FLAGS::INTERFACE_INITILIZED))
			{
				Interface *initilizing_interface = &InterfaceList[scriptKey];
				AMX *target_amx = initilizing_interface->amx;
				int funcidx, retval = 0;
				if (amx_FindPublic(target_amx, "__PLEInitilize", &funcidx) == AMX_ERR_NONE)
				{
					amx_Push(target_amx, scriptKey);
					amx_Exec(target_amx, &retval, funcidx);
				}
				//__PLEInitilize calls ScriptInitAcknowledge; retval contains the value returned by ScriptInitAcknowledge
				if (retval == PLE_MAGIC_KEY) initilizing_interface->SetFlag(INTERFACE_FLAGS::SCRIPT_SUPPORTED);
				else
				{
					initilizing_interface->ScriptIdentifier = UNSUPPORTED_SCRIPT_IDENTIFIER;
					initilizing_interface->SetFlag(INTERFACE_FLAGS::SCRIPT_UNSUPPORTED);
					logprintf("[NOTICE] PAWN Library Extension: A script (ScriptKey:%d ScriptIdentifier:%s) was loaded which wasn't compiled for PLE.", scriptKey, initilizing_interface->ScriptIdentifier.c_str());
				}
				initilizing_interface->SetFlag(INTERFACE_FLAGS::INTERFACE_INITILIZED);
				for (int i = 0, j = InterfaceList.size(); i < j; i++)
				{
					if (i == scriptKey) continue;
					if (InterfaceList[i].empty()) continue;

					InterfaceList[i].Trigger_OnScriptInit(scriptKey, InterfaceList[scriptKey].ScriptIdentifier);
				}
				break;
			}
		}
	}
}
namespace Natives
{
	//native __InitAcknowledge(magic_key, version_key, const scriptIdentifier[], size = sizeof(scriptIdentifier));
	cell AMX_NATIVE_CALL interface_ScriptInitAcknowledge(AMX* amx, cell* params)
	{
		error_if(!check_params(4), "[PLE] interface>> Unexpected error during script-acknowledgement call.");

		cell MagicNumber = params[1];
		cell VersionKey = params[2];

		int len;
		cell *addr = NULL;
		amx_GetAddr(amx, params[3], &addr);
		amx_StrLen(addr, &len);

		std::string scriptIdentifier;
		scriptIdentifier.resize(SCRIPT_IDENTIFIER_SIZE);
		amx_GetString(&scriptIdentifier[0], addr, 0, SCRIPT_IDENTIFIER_SIZE);
		scriptIdentifier.resize(len);

		int scriptKey = INVALID_SCRIPT_ID, duplicate_count = 0;
		for (int i = 0, j = Interface::InterfaceList.size(); i < j; i++)
		{
			if (Interface::InterfaceList[i].empty()) continue;
			if (Interface::InterfaceList[i].amx == amx)
			{
				Interface::InterfaceList[i].ScriptIdentifier = scriptIdentifier;
				scriptKey = i;
			}
			else if (Interface::InterfaceList[i].ScriptIdentifier == scriptIdentifier)
				duplicate_count++;
		}

		if (scriptIdentifier == UNDEFINED_SCRIPT_IDENTIFIER)
		{
			logprintf("[NOTICE] PAWN Library Extension: A loaded script does not have a script identifier.");
			logprintf("[NOTICE] Total number of scripts without identifer: %d", duplicate_count);
		}
		else if (duplicate_count)
			logprintf("[WARNING] PAWN Library Extension: Script identifier '%s' is being used by %d scripts.", scriptIdentifier.c_str(), duplicate_count);

		if (PLE_PLUGIN_VERSION_KEY > VersionKey)
			logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s'.\nThe script is using an older version of PLE with a newer version of the plugin.", scriptIdentifier.c_str());
		else if (PLE_PLUGIN_VERSION_KEY < VersionKey)
			logprintf("[WARNING] PAWN Library Extension: The plugin version does not match the include version in script '%s'.\nThe script is using a newer version of PLE with an older version of the plugin.", scriptIdentifier.c_str());

		if (PLE_MAGIC_KEY != MagicNumber)
			logprintf("[WARNING] PAWN Library Extension: The script's ('%s') magic number does not match with the plugin's magic number.\nThis may cause undefined behaviour.", scriptIdentifier.c_str());

		return PLE_MAGIC_KEY;
	}

	//native IsValidScript(scriptKey);
	cell AMX_NATIVE_CALL interface_IsValidScript(AMX* amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] interface>> IsValidScript: expected 1 parameters but found %d parameters.", get_params_count());
		const int scriptKey = params[1];
		return ::Interface::IsValidScript(scriptKey);
	}
	//native GetScriptType(scriptKey);
	cell AMX_NATIVE_CALL interface_GetScriptFlags(AMX* amx, cell* params)
	{
		error_if(!check_params(1), "[PLE] interface>> GetScriptFlags: expected 1 parameters but found %d parameters.", get_params_count());
		const int scriptKey = params[1];
		if (::Interface::IsValidScript(scriptKey)) return Interface::INTERFACE_FLAGS::INVALID;
		return Interface::InterfaceList[scriptKey].GetFlags();
	}
	//native GetScriptPoolSize();
	cell AMX_NATIVE_CALL interface_GetScriptPoolSize(AMX* amx, cell* params)
	{
		error_if(!check_params(0), "[PLE] interface>> GetScriptPoolSize: expected 0 parameters but found %d parameters.", get_params_count());
		return static_cast<cell>(Interface::InterfaceList.size());
	}
	//native GetScriptIdentifierFromKey(scriptKey, dest[], len = sizeof(dest));
	cell AMX_NATIVE_CALL interface_GetScriptIdentifierFromKey(AMX* amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] interface>> GetScriptIdentifierFromKey: expected 3 parameters but found %d parameters.", get_params_count());
		const int scriptKey = params[1];
		if (::Interface::IsValidScript(scriptKey)) return false;

		cell* addr = NULL;
		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, Interface::InterfaceList[scriptKey].ScriptIdentifier.c_str(), 0, 0, static_cast<size_t>(params[3]));
		return true;
	}
	//native GetScriptKeyFromIdentifier(const identifier[], scriptID[], len = sizeof(scriptID));
	cell AMX_NATIVE_CALL interface_GetScriptKeyFromIdentifier(AMX* amx, cell* params)
	{
		error_if(!check_params(3), "[PLE] interface>> GetScriptKeyFromIdentifier: expected 3 parameters but found %d parameters.", get_params_count());
		int len = 0;
		cell *addr = NULL;
		amx_GetAddr(amx, params[1], &addr);
		amx_StrLen(addr, &len);

		std::string scriptIdentifier;
		scriptIdentifier.resize(SCRIPT_IDENTIFIER_SIZE);
		amx_GetString(&scriptIdentifier[0], addr, 0, SCRIPT_IDENTIFIER_SIZE);
		scriptIdentifier.resize(len);

		cell * scriptID;
		amx_GetAddr(amx, params[2], &scriptID);

		cell count = 0;
		for (int i = 0, j = Interface::InterfaceList.size(); i < j; i++)
		{
			if (scriptIdentifier == Interface::InterfaceList[i].ScriptIdentifier)
			{
				if (count < params[3])
				{
					*scriptID++ = static_cast<cell>(Interface::InterfaceList[i].ScriptKey);
					count++;
				}
			}
		}
		return count;
	}
	//native GetScriptStartupTime(scriptKey, _time_t[time_t]);
	cell AMX_NATIVE_CALL interface_GetScriptStartupTime(AMX* amx, cell* params)
	{
		error_if(!check_params(2), "[PLE] interface>> GetScriptStartupTime: expected 2 parameters but found %d parameters.", get_params_count());
		const int scriptKey = params[1];
		if (::Interface::IsValidScript(scriptKey)) return 0;

		cell* time_dest_addr = NULL;
		amx_GetAddr(amx, params[1], &time_dest_addr);

		struct tm * time_dest;
		time_t posix_time = std::chrono::system_clock::to_time_t(Interface::InterfaceList[scriptKey].time_loaded);
		time_dest = gmtime(&posix_time);

		time_dest_addr[second] = time_dest->tm_sec;
		time_dest_addr[minute] = time_dest->tm_min;
		time_dest_addr[hour] = time_dest->tm_hour;
		time_dest_addr[day] = time_dest->tm_mday;
		time_dest_addr[month] = time_dest->tm_mon;
		time_dest_addr[year] = time_dest->tm_year + 1900;
		time_dest_addr[wday] = time_dest->tm_wday;
		time_dest_addr[yday] = time_dest->tm_yday;
		time_dest_addr[isdst] = time_dest->tm_isdst;

		return static_cast<cell>(posix_time);
	}
}