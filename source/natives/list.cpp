/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

STL Lists for PAWN
list.cpp

*************************************************************************************************************/
#include "main.h"
#include "list.h"
#include "functional.h"
#include "interface.h"

#include <list>
#include <algorithm>
/************************************************************************************************************/
std::vector<PawnList> active_lists;
std::vector<unsigned int> unused_list_ids;
cell list_maxid = 0;
/************************************************************************************************************/
bool IsValidListID(cell listid)
{
	if (listid > list_maxid || listid < 0) return false;
	if (active_lists[listid].IsUnused()) return false;
	return true;
}
/************************************************************************************************************/
namespace
{
	cell AMX_NATIVE_CALL list_create(AMX* amx, cell* params)
	{
		enum
		{
			INIT_LIST_EMPTY = 0,
			INIT_LIST_COPY,
			INIT_LIST_FILL,
			INIT_LIST_PTR1_COPY,
			INIT_LIST_PTR2_COPY
		};

		cell *addr1, *addr2;
		switch (params[1])
		{
		case INIT_LIST_EMPTY:
			break;
		case INIT_LIST_COPY:
			if (!IsValidListID(params[1]))
				return INVALID_LIST_ID;
			break;
		case INIT_LIST_FILL:
			error_if(params[3] < 0, "[PLE] list initilization (fill constructor) >> number of elements is negative"), INVALID_LIST_ID;
			break;
		case INIT_LIST_PTR1_COPY:
			amx_GetAddr(amx, params[3], &addr1);
			error_if(addr1 == NULL, "[PLE] list initilization (range copy using a raw pointer) >> invalid pointer passed"), INVALID_LIST_ID;
			//return implicit in the above statement
		case INIT_LIST_PTR2_COPY:
			amx_GetAddr(amx, params[3], &addr1);
			amx_GetAddr(amx, params[4], &addr2);
			error_if(addr1 == NULL || addr2 == NULL, "[PLE] list initilization (range copy using raw pointers) >> invalid pointers passed"), INVALID_LIST_ID;
			error_if(addr2 < addr1, "[PLE] list initilization (range copy using raw pointers) >> starting position greater than ending position"), INVALID_LIST_ID;
			//return implicit in the above statement
		}

		cell id;
		if (unused_list_ids.size())
		{
			id = unused_list_ids.back();
			unused_list_ids.pop_back();	
		}
		else
		{
			id = list_maxid = active_lists.size();
			active_lists.push_back(PawnList());
		}	
		active_lists[id].Initilize(id, params[2]);

		switch (params[1])
		{
		case INIT_LIST_EMPTY:			
			break;
		case INIT_LIST_COPY:
			active_lists[id].container.assign(active_lists[params[3]].container.begin(), active_lists[params[3]].container.end());
			break;
		case INIT_LIST_FILL:
			active_lists[id].container.assign(static_cast<size_t>(params[3]), params[4]);
			break;
		case INIT_LIST_PTR1_COPY:
			active_lists[id].container.assign(addr1, addr1 + params[3]);
			break;
		case INIT_LIST_PTR2_COPY:
			active_lists[id].container.assign(addr1, addr2);
			break;
		}		
		return id;
	}
	cell AMX_NATIVE_CALL list_destroy(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].Reset();
			unused_list_ids.push_back(id);
			return true;
		}
		return false;
	}

	//Capacity
	cell AMX_NATIVE_CALL list_empty(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			return active_lists[id].container.empty();
		return false;
	}
	cell AMX_NATIVE_CALL list_size(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			return active_lists[id].container.size();
		return false;
	}
	cell AMX_NATIVE_CALL list_max_size(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			return active_lists[id].container.max_size();
		return 0;
	}

	//Element Access
	cell AMX_NATIVE_CALL list_back(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			return active_lists[id].container.back();
		return 0;
	}
	cell AMX_NATIVE_CALL list_front(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			return active_lists[id].container.front();
		return 0;
	}

	//Modifiers
	cell AMX_NATIVE_CALL list_clear(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
			active_lists[id].container.clear();
		return false;
	}
	cell AMX_NATIVE_CALL list_get(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			const cell idx = params[2];
			if (idx < 0 || idx >= active_lists[id].container.size())
				return false;

			auto itr = active_lists[id].container.begin();
			std::advance(itr, idx);
			return *itr;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_set(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			const cell idx = params[2];
			if (idx < 0 || idx >= active_lists[id].container.size())
				return false;

			auto itr = active_lists[id].container.begin();
			std::advance(itr, idx);
			*itr = params[3];
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_insert(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto &container = active_lists[id].container;
			auto itr = container.begin();
			std::advance(itr, params[2]);
			container.insert(itr, params[3]);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_erase(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto &container = active_lists[id].container;
			auto itr = container.begin();
			std::advance(itr, params[2]);
			container.erase(itr);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_assign(AMX* amx, cell* params)
	{
		enum
		{
			ASSIGN_LIST_COPY,
			ASSIGN_LIST_FILL,
			ASSIGN_LIST_PTR1_COPY,
			ASSIGN_LIST_PTR2_COPY
		};

		const cell id = params[1];
		if (!IsValidListID(id)) return false;
		
		switch (params[1])
		{
		case ASSIGN_LIST_COPY:
			if (!IsValidListID(params[1]))
				return false;
			active_lists[id].container.assign(active_lists[params[3]].container.begin(), active_lists[params[3]].container.end());
			break;
		case ASSIGN_LIST_FILL:
			error_if(params[3] < 0, "[PLE] list>> assign: (fill) >> number of elements is negative"), false;
			active_lists[id].container.assign(static_cast<size_t>(params[3]), params[4]);
			break;
		case ASSIGN_LIST_PTR1_COPY:
			cell *addr;
			amx_GetAddr(amx, params[3], &addr);
			error_if(addr == NULL, "[PLE] list>> assign: (range copy using a raw pointer) >> invalid pointer passed"), false;
			active_lists[id].container.assign(addr, addr + params[3]);
			break;
		case ASSIGN_LIST_PTR2_COPY:
			cell *addr1, *addr2;
			amx_GetAddr(amx, params[3], &addr1);
			amx_GetAddr(amx, params[4], &addr2);
			error_if(addr1 == NULL || addr2 == NULL, "[PLE] list>> assign: (range copy using raw pointers) >> invalid pointers passed"), false;
			error_if(addr2 < addr1, "[PLE] list>> assign: (range copy using raw pointers) >> starting position greater than ending position"), false;
			active_lists[id].container.assign(addr1, addr2);
			break;
		}
		return true;
	}
	cell AMX_NATIVE_CALL list_push_front(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.push_front(params[2]);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_pop_front(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.pop_front();
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_push_back(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.push_back(params[2]);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_pop_back(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.pop_back();
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_resize(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.resize(static_cast<size_t>(params[2]), params[3]);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_swap(AMX* amx, cell* params)
	{
		const cell id1 = params[1];
		const cell id2 = params[2];
		if (IsValidListID(id1) && IsValidListID(id2))
		{
			active_lists[id1].container.swap(active_lists[id2].container);
			return true;
		}
		return false;
	}

	//Operations
	//merge, splice not implemented
	//max, min
	cell AMX_NATIVE_CALL list_find(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto& container = active_lists[id].container;
			size_t dist = std::distance(std::find(container.begin(), container.end(), params[2]), container.end());
			if (dist == container.size())
				return -1;
			return static_cast<cell>(dist);
		}
		return -1;
	}
	cell AMX_NATIVE_CALL list_find_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto& container = active_lists[id].container;

			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] list>> find_if: function object 'func' is not valid");

			size_t dist = std::distance(std::find_if(container.begin(), container.end(), [&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); }), container.end());
			if (dist == container.size())
				return -1;
			return static_cast<cell>(dist);
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_count(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto& container = active_lists[id].container;
			return std::count(container.begin(), container.end(), params[2]);			
		}
		return -1;
	}
	cell AMX_NATIVE_CALL list_count_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			auto& container = active_lists[id].container;

			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] list>> count_if: function object 'func' is not valid");

			return std::count_if(container.begin(), container.end(), [&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); });
		
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_remove(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.remove(params[2]);
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_remove_if(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] list>> remove_if: function object 'func' is not valid");

			active_lists[id].container.remove_if([&amx, &fid, &func](cell x) { return ExecuteFunctionCC1O2O3O4(amx, &fid, x); });
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_unqiue(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(2), "[PLE] list>> unique: function object 'func' is not valid");

			active_lists[id].container.unique([&amx, &fid, &func](cell x, cell y) { return ExecuteFunctionCC1C2O3O4O5(amx, &fid, x, y); });
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_sort(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(2), "[PLE] list>> sort: function object 'func' is not valid");

			active_lists[id].container.sort([&amx, &fid, &func](cell x, cell y) { return ExecuteFunctionCC1C2O3O4O5(amx, &fid, x, y); });
			return true;
		}
		return false;
	}

	cell AMX_NATIVE_CALL list_reverse(AMX* amx, cell* params)
	{
		//TO:DO Pred
		const cell id = params[1];
		if (IsValidListID(id))
		{
			active_lists[id].container.reverse();
			return true;
		}
		return false;
	}

	cell AMX_NATIVE_CALL list_equal(AMX* amx, cell* params)
	{
		const cell listid1 = params[1], listid2 = params[2];
		if (IsValidListID(listid1) && IsValidListID(listid2))
			if (active_lists[listid1].GetTagID() == active_lists[listid2].GetTagID())
				return (active_lists[listid1].container == active_lists[listid2].container);
		return false;
	}
	cell AMX_NATIVE_CALL list_greater_than(AMX* amx, cell* params)
	{
		const cell listid1 = params[1], listid2 = params[2];
		if (IsValidListID(listid1) && IsValidListID(listid2))
			if (active_lists[listid1].GetTagID() == active_lists[listid2].GetTagID())
				return (active_lists[listid1].container > active_lists[listid2].container);
		return false;
	}
	cell AMX_NATIVE_CALL list_lesser_than(AMX* amx, cell* params)
	{
		const cell listid1 = params[1], listid2 = params[2];
		if (IsValidListID(listid1) && IsValidListID(listid2))
			if (active_lists[listid1].GetTagID() == active_lists[listid2].GetTagID())
				return (active_lists[listid1].container < active_lists[listid2].container);
		return false;
	}

	cell AMX_NATIVE_CALL list_for_each(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			cell* func = NULL;
			amx_GetAddr(amx, params[2], &func);
			functionID fid(func);
			error_if(!fid.IsFunctionValid(1), "[PLE] list>> for_each: function object 'func' is not valid");

			auto& container = active_lists[id].container;
			auto itr = container.begin(), end = container.end();
			while (itr != end)
			{
				ExecuteFunctionCC1O2O3O4(amx, &fid, *itr);
				++itr;
			}
			return true;
		}
		return false;
	}
	cell AMX_NATIVE_CALL list_data(AMX* amx, cell* params)
	{
		const cell id = params[1];
		if (IsValidListID(id))
		{
			cell *addr;
			amx_GetAddr(amx, params[2], &addr);
			auto itr = active_lists[id].container.begin(), end = active_lists[id].container.end();
			while (itr != end)
				*addr++ = *itr++;
			return true;
		}
		return false;
	}
}