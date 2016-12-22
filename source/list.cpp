/************************************************************************************************************
Standard Library Extension


list.cpp

*************************************************************************************************************/
#include "main.h"
#include "list.h"

#include <vector>
/************************************************************************************************************/
std::vector<SLE_list *> active_lists;
std::vector<unsigned int> unused_list_ids;
unsigned int list_maxid = 0;

std::vector <ForeachList *> active_foreach_list_loops;
std::vector <unsigned int> unused_foreach_list_ids;
unsigned int foreach_list_loop_maxid;

std::vector <ListIterator *> active_list_iterators;
std::vector <unsigned int> unused_list_iterator_ids;
unsigned int itr_maxid = 0;
/************************************************************************************************************/
inline bool IsValidListID(int listid)
{
	if (listid > static_cast<int>(list_maxid) || listid < 0) return false;
	if (active_lists[listid] == nullptr) return false;
	return true;
}
inline bool IsValidIteratorID(int itrid)
{
	if (itrid > static_cast<int>(itr_maxid) || itrid < 0) return false;
	if (active_list_iterators[itrid] == nullptr) return false;
	return true;
}

//General
cell AMX_NATIVE_CALL SLE_list_Create(AMX* amx, cell* params)
{
	unsigned int id;	
	if (unused_list_ids.size())
	{
		id = unused_list_ids.back();
		unused_list_ids.pop_back();
	}
	else
	{
		id = list_maxid = active_lists.size();
		active_lists.push_back(nullptr);
	}
	switch (static_cast<int>(params[1]))
	{
		case INIT_LIST_EMPTY:
			active_lists[id] = new SLE_list(amx, static_cast<int>(params[2]), active_lists[static_cast<int>(params[3])]);
			break;
		case INIT_LIST_COPY:	
		{
			int id2 = static_cast<int>(params[3]);
			if (id2 > static_cast<int>(list_maxid) || id2 < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
			if (active_lists[id2] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;

			active_lists[id] = new SLE_list(amx, static_cast<int>(params[2]), active_lists[static_cast<int>(params[id2])]);
			break;
		}
		case INIT_LIST_ARRAY_COPY:
		{
			cell* addr = NULL;
			amx_GetAddr(amx, params[3], &addr);
			active_lists[id] = new SLE_list(amx, static_cast<int>(params[2]), addr, static_cast<size_t>(params[4]));
			break;
		}
		case INIT_LIST_FILL:
			active_lists[id] = new SLE_list(amx, static_cast<int>(params[2]), static_cast<size_t>(params[3]), params[4]);
			break;
		case INIT_LIST_RANGE_COPY:		
			break;
	}
	return id;
}
cell AMX_NATIVE_CALL SLE_list_Destroy(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	delete active_lists[id];
	active_lists[id] = nullptr;
	unused_list_ids.push_back(id);
	return 0;
}

//Capacity
cell AMX_NATIVE_CALL SLE_list_empty(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	return active_lists[id]->container->back();
}
cell AMX_NATIVE_CALL SLE_list_size(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	return active_lists[id]->container->size();
}
cell AMX_NATIVE_CALL SLE_list_max_size(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	return active_lists[id]->container->max_size();
	
}

//Element Access
cell AMX_NATIVE_CALL SLE_list_back(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	return active_lists[id]->container->back();
}
cell AMX_NATIVE_CALL SLE_list_front(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	return active_lists[id]->container->front();
}

//Modifiers
cell AMX_NATIVE_CALL SLE_list_assign2(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;

	switch (static_cast<int>(params[2]))
	{
		case INIT_LIST_ARRAY_COPY:
		{
			cell* addr = NULL;
			amx_GetAddr(amx, params[3], &addr);
			active_lists[id]->container->assign(addr, addr + static_cast<size_t>(params[4]));
			break;
		}
		case INIT_LIST_FILL:
			active_lists[id]->container->assign(static_cast<size_t>(params[3]), params[4]);
			break;
		case INIT_LIST_RANGE_COPY:
			break;
	}
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_push_front(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	active_lists[id]->container->push_front(params[2]);
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_pop_front(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	active_lists[id]->container->pop_front();
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_push_back(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	active_lists[id]->container->push_back(params[2]);
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_pop_back(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (id > static_cast<int>(list_maxid) || id < 0) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	if (active_lists[id] == nullptr) return SLE_LIST_ERRORS::INVALID_LIST_ID;
	active_lists[id]->container->pop_back();
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_insert(AMX* amx, cell* params)
{
	//TO:DO insertEx return itr
	enum
	{
		INSERT_TYPE_SINGLE_ELEMENT,
		INSERT_TYPE_FILL,
		INSERT_TYPE_RANGE
	};
	int listid = static_cast<int>(params[1]), itrid = static_cast<int>(params[3]);
	if (IsValidListID(listid) && IsValidIteratorID(itrid))
	{
		switch (static_cast<int>(params[2]))
		{
		case INSERT_TYPE_SINGLE_ELEMENT:
			active_lists[listid]->container->insert(active_list_iterators[itrid]->itr, static_cast<int>(params[4]));
			break;
		case INSERT_TYPE_FILL:
			active_lists[listid]->container->insert(active_list_iterators[itrid]->itr, static_cast<int>(params[4]), static_cast<int>(params[5]));
			break;
		case INSERT_TYPE_RANGE:
		{
			int itrid_first = static_cast<int>(params[4]), itrid_last = static_cast<int>(params[5]);
			if (IsValidIteratorID(itrid_first) && IsValidIteratorID(itrid_last))
				active_lists[listid]->container->insert(active_list_iterators[itrid]->itr, active_list_iterators[itrid_first]->itr, active_list_iterators[itrid_last]->itr);
			break;
		}
		}
	}
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_erase(AMX* amx, cell* params)
{
	//TO:DO eraseEx return itr
	int listid = static_cast<int>(params[1]), itrid = static_cast<int>(params[2]);
	if (IsValidListID(listid) && IsValidIteratorID(itrid))
	{
		if (static_cast<int>(params[3]) == -729)
			active_lists[listid]->container->erase(active_list_iterators[itrid]->itr);
		else
		{
			int itrid2 = static_cast<int>(params[3]);
			if (IsValidIteratorID(itrid2))
				active_lists[listid]->container->erase(active_list_iterators[itrid]->itr, active_list_iterators[itrid2]->itr);
		}
	}
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_resize(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]);
	if (IsValidListID(listid))
		active_lists[listid]->container->resize(static_cast<int>(params[2]), static_cast<int>(params[3]));
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_swap(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]), listid2 = static_cast<int>(params[2]);
	if (IsValidListID(listid) && IsValidListID(listid2))
		active_lists[listid]->container->swap(*active_lists[listid2]->container);
	return 0;
}

//Algorithm Helper Functions
cell AMX_NATIVE_CALL SLE_algo_foreach_list_init(AMX* amx, cell* params)
{
	unsigned int id = -1;
	if (IsValidListID(static_cast<int>(params[1])))
	{		
		cell* addr = NULL;
		amx_GetAddr(amx, params[2], &addr);
		if (unused_foreach_list_ids.size())
		{
			id = unused_foreach_list_ids.back();
			unused_foreach_list_ids.pop_back();
		}
		else
		{
			id = foreach_list_loop_maxid = active_foreach_list_loops.size();
			active_foreach_list_loops.push_back(nullptr);
		}
		active_foreach_list_loops[id] = new ForeachList(amx, addr, active_lists[static_cast<int>(params[1])]->container->cbegin(), active_lists[static_cast<int>(params[1])]->container->cend());
	}
	return id;
}
cell AMX_NATIVE_CALL SLE_algo_foreach_list_get(AMX* amx, cell* params)
{
	// Assuming that people don't try to screw with these internal functions
	// As long as the foreach define makes this call, it shall always be valid.
	// TO:CHECK If iterator remains valid when nodes are removed/added to the list while the foreach is running
	int foreachid = static_cast<int>(params[1]);
	if (foreachid > static_cast<int>(foreach_list_loop_maxid) || foreachid < 0) return 0;
	return active_foreach_list_loops[foreachid]->iterate();
}

//Iterator Access
cell AMX_NATIVE_CALL SLE_list_iter_copy(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (IsValidIteratorID(id))
	{
		unsigned int itrid;
		if (unused_list_iterator_ids.size())
		{
			itrid = unused_list_iterator_ids.back();
			unused_list_iterator_ids.pop_back();
			active_list_iterators[itrid] = new ListIterator(*active_list_iterators[id]);
		}
		else
		{
			itrid = itr_maxid = active_list_iterators.size();
			active_list_iterators.push_back(new ListIterator(*active_list_iterators[id]));
		}
		return itrid;
	}
	return INVALID_ITERATOR_ID;
}
cell AMX_NATIVE_CALL SLE_list_begin(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);	
	if (IsValidListID(id))
	{
		if (IsValidIteratorID(active_lists[id]->itrid_begin))
			return active_lists[id]->itrid_begin;
		else
		{
			unsigned int itrid = 0;
			if (unused_list_iterator_ids.size())
			{
				itrid = active_lists[id]->itrid_begin = unused_list_iterator_ids.back();
				unused_list_iterator_ids.pop_back();
				active_list_iterators[itrid] = new ListIterator(active_lists[id], active_lists[id]->container->begin());
			}
			else
			{
				itrid = active_lists[id]->itrid_begin = itr_maxid = active_list_iterators.size();
				active_list_iterators.push_back(new ListIterator(active_lists[id], active_lists[id]->container->begin()));
			}
			active_lists[id]->itrid_begin = itrid;			
			return itrid;
		}
	}	
	return INVALID_ITERATOR_ID;
}
cell AMX_NATIVE_CALL SLE_list_end(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (IsValidListID(id))
	{
		if (IsValidIteratorID(active_lists[id]->itrid_end))
			return active_lists[id]->itrid_end;
		else
		{
			unsigned int itrid = 0;
			if (unused_list_iterator_ids.size())
			{
				itrid = active_lists[id]->itrid_end = unused_list_iterator_ids.back();
				unused_list_iterator_ids.pop_back();
				active_list_iterators[itrid] = new ListIterator(active_lists[id], active_lists[id]->container->end());
			}
			else
			{
				itrid = active_lists[id]->itrid_end = itr_maxid = active_list_iterators.size();
				active_list_iterators.push_back(new ListIterator(active_lists[id], active_lists[id]->container->end()));
			}
			active_lists[id]->itrid_end = itrid;
			return itrid;
		}
	}
	return INVALID_ITERATOR_ID;
}
cell AMX_NATIVE_CALL SLE_list_iterator_advance(AMX* amx, cell* params)
{	
	int id = static_cast<int>(params[1]);
	if (IsValidIteratorID(id)) 
		active_list_iterators[id]->advance(static_cast<int>(params[2]));
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_iterator_distance(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	if (IsValidIteratorID(id)) {
		return active_list_iterators[id]->distance(active_list_iterators[static_cast<int>(params[2])]);
	}
	return INT32_MAX;
}
cell AMX_NATIVE_CALL SLE_list_iterator_equal(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);
	int id2 = static_cast<int>(params[2]);

	if (IsValidIteratorID(id) && IsValidIteratorID(id2)) 
	if (active_list_iterators[id]->itr == active_list_iterators[id2]->itr) return 1;
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_itr_dereference(AMX* amx, cell* params)
{
	int id = static_cast<int>(params[1]);

	if (IsValidIteratorID(id))
		return *active_list_iterators[id]->itr;
	return 0;
}

cell AMX_NATIVE_CALL test(AMX* amx, cell* params)
{
	printf("%d %d", *active_list_iterators[1]->itr, *active_list_iterators[3]->itr);
	return 0;
}
//Operations
cell AMX_NATIVE_CALL SLE_list_remove(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]);
	if (IsValidListID(listid))
		active_lists[listid]->container->remove(params[2]);
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_unqiue(AMX* amx, cell* params)
{
	//TO:DO Pred
	int listid = static_cast<int>(params[1]);
	if (IsValidListID(listid))
		active_lists[listid]->container->unique();
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_sort(AMX* amx, cell* params)
{
	//TO:DO Pred
	int listid = static_cast<int>(params[1]);
	if (IsValidListID(listid))
		active_lists[listid]->container->sort();
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_reverse(AMX* amx, cell* params)
{
	//TO:DO Pred
	int listid = static_cast<int>(params[1]);
	if (IsValidListID(listid))
		active_lists[listid]->container->reverse();
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_merge(AMX* amx, cell* params)
{
	//TO:DO Pred
	int listid = static_cast<int>(params[1]), listid2 = static_cast<int>(params[2]);;
	if (IsValidListID(listid) && IsValidListID(listid2))
	{
		if(active_lists[listid]->templateid == active_lists[listid2]->templateid)
			active_lists[listid]->container->merge(*active_lists[listid2]->container);
		else logprintf(" [WARNING] Merging lists of different types might lead to data corruption.");
	}
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_splice(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]), itrid = static_cast<int>(params[2]), listid2 = static_cast<int>(params[3]);
	if (IsValidListID(listid) && IsValidListID(listid2) && IsValidIteratorID(itrid))
	{
		if (active_lists[listid]->templateid != active_lists[listid2]->templateid)
		{
			logprintf(" [WARNING] Splicing lists of different types might lead to data corruption.");
			return 0;
		}

		if (static_cast<int>(params[4]) == -729)
		{
			active_lists[listid]->container->splice(active_list_iterators[itrid]->itr, *active_lists[listid2]->container);
		}
		else if(static_cast<int>(params[5]) == -729)
		{
			int first = static_cast<int>(params[4]);
			if(IsValidIteratorID(first))
				active_lists[listid]->container->splice(active_list_iterators[itrid]->itr, *active_lists[listid2]->container, active_list_iterators[first]->itr);
		}
		else
		{
			int first = static_cast<int>(params[4]), last = static_cast<int>(params[5]);
			if (IsValidIteratorID(first) && IsValidIteratorID(last))
				active_lists[listid]->container->splice(active_list_iterators[itrid]->itr, *active_lists[listid2]->container, active_list_iterators[first]->itr, active_list_iterators[last]->itr);
		}
	}
	return 0;
}

//remove_if

//Relational Operators
cell AMX_NATIVE_CALL SLE_list_equal(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]), listid2 = static_cast<int>(params[2]);
	if (IsValidListID(listid) && IsValidListID(listid2))
		if (active_lists[listid]->templateid == active_lists[listid2]->templateid)
			return (*active_lists[listid]->container == *active_lists[listid2]->container);	
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_greater_than(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]), listid2 = static_cast<int>(params[2]);
	if (IsValidListID(listid) && IsValidListID(listid2))
		if (active_lists[listid]->templateid == active_lists[listid2]->templateid)
			return (*active_lists[listid]->container > *active_lists[listid2]->container);
	return 0;
}
cell AMX_NATIVE_CALL SLE_list_lesser_than(AMX* amx, cell* params)
{
	int listid = static_cast<int>(params[1]), listid2 = static_cast<int>(params[2]);
	if (IsValidListID(listid) && IsValidListID(listid2))
		if (active_lists[listid]->templateid == active_lists[listid2]->templateid)
			return (*active_lists[listid]->container < *active_lists[listid2]->container);
	return 0;
}