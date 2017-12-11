/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

functional
functional.h

*************************************************************************************************************/
#ifndef PLE_FUNCTIONAL_H_INCLUDED
#define PLE_FUNCTIONAL_H_INCLUDED

#include "main.h"
#include "iscript.h"
#include <cstdint>

namespace PLE::functional
{
	constexpr std::size_t MAX_BINDS = 4;
	constexpr std::size_t FTSIZE = MAX_BINDS + 2;

	typedef cell(*NativeFunctionPtr)(AMX*, cell[]);

	namespace function_types
	{
		enum
		{
			invalid = 0x00,
			publicf = 0x01,
			native = 0x02,
			defaultv = 0x04,
		};
	}
	namespace function_flags
	{
		enum
		{
			not = 0x01,
			bind1 = 0x02,
			bind2 = 0x04,
			bind3 = 0x08,
			bind4 = 0x10,
			vargs = 0x20
		};
	}

	class function
	{
	public:
		using uint8_t = std::uint8_t;
		using uint16_t = std::uint16_t;
		using uint32_t = std::uint32_t;

		function(cell p_params[FTSIZE]) { decode(p_params); }
		function(uint8_t argc, uint16_t flags, int16_t funcidx, int8_t scriptKey)
		{
			//public
			expanded.funcidx = funcidx;
			expanded.scriptKey = scriptKey;
			info.type = function_types::publicf;
			info.argc = argc;
			info.flags = flags;
		}
		function(uint8_t argc, uint16_t flags, uint32_t addr)
		{
			//function_types::native
			faddress = addr;
			info.type = function_types::native;
			info.argc = argc;
			info.flags = flags;
		}

		void decode(cell p_params[FTSIZE]) //allows modification of private members
		{
			info.type = (p_params[0] & 0xFF000000) >> 24;
			info.argc = (p_params[0] & 0x00FF0000) >> 16;
			info.flags = (p_params[0] & 0x0000FFFF);

			switch (info.type)
			{
			case function_types::publicf:
				expanded.funcidx = (p_params[1] & 0xFFFF0000) >> 16;
				expanded.scriptKey = (p_params[1] & 0x0000FF00) >> 8;
				break;
			case function_types::native:
				faddress = p_params[1];
				break;
			case function_types::defaultv:
				findex = p_params[1];
				break;
			}

			params[0] = p_params[2];
			params[1] = p_params[3];
			params[2] = p_params[4];
			params[3] = p_params[5];
		}
		void encode(cell dest[]) const
		{
			dest[0] = (info.type << 24) | (info.argc << 16) | info.flags;
			switch (info.type)
			{
			case function_types::publicf:
				dest[1] = (expanded.funcidx << 16) | (expanded.scriptKey << 8);
				break;
			case function_types::native:
				dest[1] = faddress;
				break;
			case function_types::defaultv:
				dest[1] = findex;
				break;
			}
		}

		bool IsValidFunctionID(size_t argc) const
		{
			if (IsFlagSet(function_flags::bind1))
				argc++;
			if (IsFlagSet(function_flags::bind2))
				argc++;
			if (IsFlagSet(function_flags::bind3))
				argc++;
			if (IsFlagSet(function_flags::bind4))
				argc++;
			return (argc == info.argc) || IsFlagSet(function_flags::vargs);
		}
		bool IsFlagSet(uint16_t flag) const { return !!(info.flags & flag); }

	private:
		struct info_t {
			uint32_t type : 8;
			uint32_t argc : 8;
			uint32_t flags : 16;
		} info;
		static_assert(sizeof(info_t) == 4);

		union {
			uint32_t faddress;
			uint32_t findex;
			struct expanded_t {
				int16_t funcidx : 16;
				int8_t scriptKey : 8;
				uint8_t reserved : 8;
			} expanded;
			static_assert(sizeof(IScript::ScriptKey_t) == 1);
			static_assert(sizeof(IScript::FunctionIndex_t) == 2);
			static_assert(sizeof(expanded_t) == 4);
		};
		static_assert(sizeof(cell) == 4);

		cell params[FTSIZE - 2];

		friend cell ExecuteFunctionC0(AMX *amx, function& fid);
		friend cell ExecuteFunctionC1(AMX *amx, function& fid, cell cparam);
		friend cell ExecuteFunctionC2(AMX *amx, function& fid, cell cparam1, cell cparam2);
	};
}

namespace PLE::natives
{
	cell AMX_NATIVE_CALL functional_argArray(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL functional_argReference(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL functional_make_function(AMX* amx, cell* params);
}

#endif /* PLE_FUNCTIONAL_H_INCLUDED */