/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

STL Vector for PAWN
vector.cpp

//DELETE VECTORS WHEN AMX ENDS

*************************************************************************************************************/
#include "main.h"
#include "vector.h"
#include "functional.h"

#include <vector>
#include <algorithm>
/************************************************************************************************************/
std::vector<PawnVector> active_vectors;
std::vector<unsigned int> unused_vector_ids;
cell vector_maxid = 0;
/************************************************************************************************************/
bool IsValidVectorID(cell vectorid)
{
	if (vectorid >= vector_maxid || vectorid < 0) return false;
	if (active_vectors[vectorid].IsUnused()) return false;
	return true;
}
/************************************************************************************************************/
namespace Natives
{
	//native vector_create(type, param1, param2);
	cell AMX_NATIVE_CALL vector_create(AMX* amx, cell* params)
	{
		logprintf("CREATE %d %d %d", params[1], params[2], params[3]);
		enum
		{
			INIT_VECTOR_EMPTY = 0,
			INIT_VECTOR_COPY,
			INIT_VECTOR_RESERVE,
			INIT_VECTOR_FILL,
			INIT_VECTOR_PTR1_COPY,
			INIT_VECTOR_PTR2_COPY
		};

		cell *addr1, *addr2;
		switch (params[1])
		{
		case INIT_VECTOR_EMPTY:
			break;
		case INIT_VECTOR_COPY:
			if (!IsValidVectorID(params[1]))
				return INVALID_VECTOR_ID;
			break;
		case INIT_VECTOR_RESERVE:
			error_if(params[2] < 0, "[PLE] vector initilization (reserve constructor) >> amount of reserved memory is negative"), INVALID_VECTOR_ID;
			break;
		case INIT_VECTOR_FILL:
			error_if(params[2] < 0, "[PLE] vector initilization (fill constructor) >> number of elements is negative"), INVALID_VECTOR_ID;
			break;
		case INIT_VECTOR_PTR1_COPY:
			amx_GetAddr(amx, params[2], &addr1);
			error_if(addr1 == NULL, "[PLE] vector initilization (range copy using a raw pointer) >> invalid pointer passed"), INVALID_VECTOR_ID;
			//return implicit in the above statement
		case INIT_VECTOR_PTR2_COPY:
			amx_GetAddr(amx, params[2], &addr1);
			amx_GetAddr(amx, params[3], &addr2);
			error_if(addr1 == NULL || addr2 == NULL, "[PLE] vector initilization (range copy using raw pointers) >> invalid pointers passed"), INVALID_VECTOR_ID;
			error_if(addr2 < addr1, "[PLE] vector initilization (range copy using raw pointers) >> starting position greater than ending position"), INVALID_VECTOR_ID;
			//return implicit in the above statement
		}

		cell id;
		if (unused_vector_ids.size())
		{
			id = unused_vector_ids.back();
			unused_vector_ids.pop_back();
		}
		else
		{
			id = active_vectors.size();
			vector_maxid = id + 1;
			active_vectors.push_back(PawnVector());
		}
		active_vectors[id].Initilize(id, params[2]);

		switch (params[1])
		{
		case INIT_VECTOR_EMPTY:
			break;
		case INIT_VECTOR_COPY:
			active_vectors[id].container.assign(active_vectors[params[2]].container.begin(), active_vectors[params[2]].container.end());
			break;
		case INIT_VECTOR_RESERVE:
			active_vectors[id].container.reserve(static_cast<size_t>(params[2]));
			break;
		case INIT_VECTOR_FILL:
			active_vectors[id].container.assign(static_cast<size_t>(params[2]), params[3]);
			break;
		case INIT_VECTOR_PTR1_COPY:
			active_vectors[id].container.assign(addr1, addr1 + params[2]);
			break;
		case INIT_VECTOR_PTR2_COPY:
			active_vectors[id].container.assign(addr1, addr2);
			break;
		}
		return id;
	}
	//native vector_destroy(vectorid);
	cell AMX_NATIVE_CALL vector_destroy(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].Reset();
			unused_vector_ids.push_back(id);
			return true;
		}
		return false;
	}
	//native vector_assign(type, param1, param2);
	cell AMX_NATIVE_CALL vector_assign(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			enum
			{
				ASSIGN_VECTOR_COPY,
				ASSIGN_VECTOR_FILL,
				ASSIGN_VECTOR_PTR1_COPY,
				ASSIGN_VECTOR_PTR2_COPY
			};

			cell *addr1, *addr2;
			switch (params[1])
			{
			case ASSIGN_VECTOR_COPY:
				if (!IsValidVectorID(params[1]))
					return false;
				active_vectors[id].container.assign(active_vectors[params[3]].container.begin(), active_vectors[params[3]].container.end());
				break;
			case ASSIGN_VECTOR_FILL:
				error_if(params[3] < 0, "[PLE] vector>> assign: (fill constructor) >> number of elements is negative"), false;
				active_vectors[id].container.assign(static_cast<size_t>(params[3]), params[4]);
				break;
			case ASSIGN_VECTOR_PTR1_COPY:
				amx_GetAddr(amx, params[3], &addr1);
				error_if(addr1 == NULL, "[PLE] vector>> assign: (range copy using a raw pointer) >> invalid pointer passed"), false;
				active_vectors[id].container.assign(addr1, addr1 + params[3]);
				break;
			case ASSIGN_VECTOR_PTR2_COPY:
				amx_GetAddr(amx, params[3], &addr1);
				amx_GetAddr(amx, params[4], &addr2);
				error_if(addr1 == NULL || addr2 == NULL, "[PLE] vector>> assign: (range copy using raw pointers) >> invalid pointers passed"), false;
				error_if(addr2 < addr1, "[PLE] vector>> assign: (range copy using raw pointers) >> starting position greater than ending position"), false;
				active_vectors[id].container.assign(addr1, addr2);
				break;
			}
			return true;
		}
		return false;
	}

	//native vector_get(vectorid, pos);
	cell AMX_NATIVE_CALL vector_get(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			const cell idx = params[2];
			if(idx < 0 || idx >= static_cast<cell>(active_vectors[id].container.size()))
				return false;
			return active_vectors[id].container[idx];
		}
		return false;
	}
	//native vector_set(vectorid, pos, value);
	cell AMX_NATIVE_CALL vector_set(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			const cell idx = params[2];
			if (idx < 0 || idx >= static_cast<cell>(active_vectors[id].container.size()))
				return false;

			active_vectors[id].container[idx] = params[3];
			return true;
		}
		return false;
	}
	//native vector_front(vectorid);
	cell AMX_NATIVE_CALL vector_front(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))			
			return active_vectors[id].container.front();
		return false;
	}
	//native vector_back(vectorid);
	cell AMX_NATIVE_CALL vector_back(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
			return active_vectors[id].container.back();
		return false;
	}
	//native vector_data(vectorid, dest[]);
	cell AMX_NATIVE_CALL vector_data(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			return std::copy(active_vectors[id].container.begin(), active_vectors[id].container.end(), addr) - addr;
		}
		return false;
	}
	//native vector_empty(vectorid);	
	cell AMX_NATIVE_CALL vector_empty(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
			return active_vectors[id].container.empty();
		return false;
	}
	
	//native vector_size(vectorid);
	cell AMX_NATIVE_CALL vector_size(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
			return active_vectors[id].container.size();
		return false;
	}
	//native vector_max_size(vectorid);
	cell AMX_NATIVE_CALL vector_max_size(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
			return active_vectors[id].container.max_size();
		return false;
	}
	//native vector_reserve(vectorid, n);
	cell AMX_NATIVE_CALL vector_reserve(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.reserve(params[2]);
			return true;
		}
		return false;
	}
	//native vector_capacity(vectorid);
	cell AMX_NATIVE_CALL vector_capacity(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
			return active_vectors[id].container.capacity();
		return false;
	}
	//native vector_shrink_to_fit(vectorid);
	cell AMX_NATIVE_CALL vector_shrink_to_fit(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.shrink_to_fit();
			return true;
		}
		return false;
	}
	//native vector_clear(vectorid);
	cell AMX_NATIVE_CALL vector_clear(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.clear();
			return true;
		}
		return false;
	}
	//native vector_erase(vectorid, pos);
	cell AMX_NATIVE_CALL vector_erase(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto &container = active_vectors[id].container;
			container.erase(container.begin() + params[2]);
			return true;
		}
		return false;
	}
	//native vector_insert(vectorid, pos, value);
	cell AMX_NATIVE_CALL vector_insert(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto &container = active_vectors[id].container;
			container.insert(container.begin() + params[2], params[3]);
			return true;
		}
		return false;
	}
	//native vector_push_back(vectorid, value);
	cell AMX_NATIVE_CALL vector_push_back(AMX* amx, cell* params)
	{		
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.push_back(params[2]);
			return true;
		}
		return false;
	}
	//native vector_pop_back(vectorid, value);
	cell AMX_NATIVE_CALL vector_pop_back(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.pop_back();
			return true;
		}
		return false;
	}
	//native vector_resize(vectorid, size);
	cell AMX_NATIVE_CALL vector_resize(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			active_vectors[id].container.resize(params[2]);
			return true;
		}
		return false;
	}
	//native vector_swap(vectorid, vectorid2);
	cell AMX_NATIVE_CALL vector_swap(AMX* amx, cell* params)
	{
		const cell id1 = params[1];
		const cell id2 = params[2];
		if (IsValidVectorID(id1) && IsValidVectorID(id2))
		{
			active_vectors[id1].container.swap(active_vectors[id2].container);
			return true;
		}
		return false;
	}

	//native vector_equal(vectorid, vectorid2);
	cell AMX_NATIVE_CALL vector_equal(AMX* amx, cell* params)
	{
		const cell vectorid1 = params[1], vectorid2 = params[2];
		if (IsValidVectorID(vectorid1) && IsValidVectorID(vectorid2))
			if (active_vectors[vectorid1].GetTagID() == active_vectors[vectorid2].GetTagID())
				return (active_vectors[vectorid1].container == active_vectors[vectorid2].container);
		return false;
	}
	//native vector_greater_than(vectorid, vectorid2);
	cell AMX_NATIVE_CALL vector_greater_than(AMX* amx, cell* params)
	{
		const cell vectorid1 = params[1], vectorid2 = params[2];
		if (IsValidVectorID(vectorid1) && IsValidVectorID(vectorid2))
			if (active_vectors[vectorid1].GetTagID() == active_vectors[vectorid2].GetTagID())
				return (active_vectors[vectorid1].container > active_vectors[vectorid2].container);
		return false;
	}
	//native vector_lesser_than(vectorid, vectorid2);
	cell AMX_NATIVE_CALL vector_lesser_than(AMX* amx, cell* params)
	{
		const cell vectorid1 = params[1], vectorid2 = params[2];
		if (IsValidVectorID(vectorid1) && IsValidVectorID(vectorid2))
			if (active_vectors[vectorid1].GetTagID() == active_vectors[vectorid2].GetTagID())
				return (active_vectors[vectorid1].container < active_vectors[vectorid2].container);
		return false;
	}
	
	//native vector_find(vectorid, value);
	cell AMX_NATIVE_CALL vector_find(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto& container = active_vectors[id].container;
			auto itr = std::find(container.begin(), container.end(), params[2]);
			if (itr == container.end()) return -1;
			return itr - container.begin();
		}
		return false;
	}
	//native vector_find_if(vectorid, { _, func_bool1, func_cell1 }:func[FTSIZE]);
	cell AMX_NATIVE_CALL vector_find_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] vector>> find_if: function object 'func' is not valid");

			auto& container = active_vectors[id].container;
			auto itr = std::find_if(container.begin(), container.end(), [&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); });
			if (itr == container.end()) return -1;
			return itr - container.begin();
		}
		return false;
	}
	//native vector_count(vectorid, value);
	cell AMX_NATIVE_CALL vector_count(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto& container = active_vectors[id].container;
			std::count(container.begin(), container.end(), params[2]);
			return true;
		}
		return false;
	}
	//native vector_count_if(vectorid, { _, func_bool1, func_cell1 }:func[FTSIZE]);
	cell AMX_NATIVE_CALL vector_count_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] vector>> count_if: function object 'func' is not valid");

			auto& container = active_vectors[id].container;
			return std::count_if(container.begin(), container.end(), [&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); });
		}
		return false;
	}
	//native vector_remove(vectorid, value);
	cell AMX_NATIVE_CALL vector_remove(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto& container = active_vectors[id].container;
			std::remove(container.begin(), container.end(), params[2]);
			return true;
		}
		return false;
	}
	//native vector_remove_if(vectorid, { _, func_bool1, func_cell1 }:func[FTSIZE]);
	cell AMX_NATIVE_CALL vector_remove_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] vector>> remove_if: function object 'func' is not valid");

			auto& container = active_vectors[id].container;
			std::remove_if(container.begin(), container.end(), [&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); });
			return true;
		}
		return false;
	}
	//native vector_unique(vectorid);
	cell AMX_NATIVE_CALL vector_unique(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(2), "[PLE] vector>> unique: function object 'func' is not valid");

			auto& container = active_vectors[id].container;
			std::unique(container.begin(), container.end(), [&amx, &fid, &func](cell x, cell y) { return ExecuteFunctionCC1C2O3O4O5(amx, &fid, x, y); });
			return true;
		}
		return false;
	}
	//native vector_sort(vectorid, { _, func_bool2, func_cell2 }:func[FTSIZE] = fixed_functions::less);
	cell AMX_NATIVE_CALL vector_sort(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(2), "[PLE] vector>> sort: function object 'func' is not valid");

			auto& container = active_vectors[id].container;
			std::sort(container.begin(), container.end(), [&amx, &fid, &func](cell x, cell y) { return ExecuteFunctionCC1C2O3O4O5(amx, &fid, x, y); });
			return true;
		}
		return false;
	}
	//native vector_reverse(vectorid);
	cell AMX_NATIVE_CALL vector_reverse(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			auto& container = active_vectors[id].container;
			std::reverse(container.begin(), container.end());
			return true;
		}
		return false;
	}
	//native vector_foreach_getValINC(vectorid, &pos, &value);
	cell AMX_NATIVE_CALL vector_foreach_getValINC(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidVectorID(id))
		{
			cell *addr_idx, *addr_val;
			auto &container = active_vectors[id].container;
			amx_GetAddr(amx, params[2], &addr_idx);
			
			if ((*addr_idx) >= container.size())
				return false;

			amx_GetAddr(amx, params[3], &addr_val);
			*addr_val = container[*addr_idx];
			return true;
		}
		return false;
	}
}