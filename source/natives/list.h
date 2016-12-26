/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

STL Lists for PAWN
list.h

*************************************************************************************************************/
#pragma once

#include "..\main.h"

#include <vector>
#include <memory>
/************************************************************************************************************/
class SLE_list;
extern vector<unique_ptr<SLE_list>> active_lists;
extern vector<unsigned int> unused_list_ids;

enum
{
	INVALID_LIST_ID = -1,
	INVALID_ITERATOR_ID = -1,
};
enum
{
	INIT_LIST_EMPTY = 0,
	INIT_LIST_COPY,
	INIT_LIST_FILL,
	INIT_LIST_ARRAY_COPY
};
/************************************************************************************************************/
class SLE_list
{
public:
	unique_ptr<list<cell>> container;

	//Empty List Constructor
	SLE_list(AMX * amx, int templateid) : amx(amx), templateid(templateid)
	{
		container = unique_ptr<list<cell>> (new std::list<cell>());
	}

	//List Copy Constructor
	SLE_list(AMX * amx, int templateid, list<cell> * lst) : amx(amx), templateid(templateid)
	{
		container = unique_ptr<list<cell>>(new std::list<cell>(*lst));
	}

	//List Array Copy Constructor
	SLE_list(AMX * amx, int templateid, cell *addr, size_t n) : amx(amx), templateid(templateid)
	{
		container = unique_ptr<list<cell>>(new std::list<cell>(addr, addr + n));
	}

	//List Fill Constructor
	SLE_list(AMX * amx, int templateid, size_t n, cell val) : amx(amx), templateid(templateid)
	{
		container = unique_ptr<list<cell>>(new std::list<cell>(n, val));
	}

	AMX * amx;
	int templateid;
};
/*
class ListIterator
{
public:
	ListIterator(SLE_list * lst, std::list<cell>::iterator itrp) : parent(lst)
	{
		parent = lst;
		itr = itrp;
	}
	inline void advance(int steps)
	{
		std::advance(itr, steps);
	}
	inline unsigned int distance(ListIterator * litr)
	{
		if (litr->parent == parent)
			return std::distance(itr, litr->itr);
		logprintf(" [ERROR] Iterators passed to std::distance do not point to elements of the same iterator.");
		return 0;
	}
	SLE_list * parent;
	std::list<cell>::iterator itr;
};*/

class ForeachList
{
public:
	ForeachList(AMX * amx, cell * counter, std::list<cell>::const_iterator itr, std::list<cell>::const_iterator end) : amx(amx), counter(counter), itr(itr), end(end)
	{

	}
	inline cell iterate()
	{
		bool cond = itr != end;
		if (cond)
		{
			*counter = *itr++;
		}
		return cond;
	}
	AMX * amx;
	cell * counter;
	std::list<cell>::const_iterator itr;
	std::list<cell>::const_iterator end;
};
/************************************************************************************************************/
extern unsigned int list_maxid;

cell AMX_NATIVE_CALL test(AMX* amx, cell* params);

//Create/Destroy
cell AMX_NATIVE_CALL SLE_list_Create(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_Destroy(AMX* amx, cell* params);

//Capacity
cell AMX_NATIVE_CALL SLE_list_empty(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_size(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_max_size(AMX* amx, cell* params);

//Element Access
cell AMX_NATIVE_CALL SLE_list_back(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_front(AMX* amx, cell* params);

//Modifiers
cell AMX_NATIVE_CALL SLE_list_assign2(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_push_front(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_pop_front(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_push_back(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_pop_back(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_insert(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_erase(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_resize(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_swap(AMX* amx, cell* params);

//Algorithm Helper Functions
cell AMX_NATIVE_CALL SLE_algo_foreach_list_init(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_algo_foreach_list_get(AMX* amx, cell* params);

//Iterator Functions
cell AMX_NATIVE_CALL SLE_list_iter_copy(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_begin(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_end(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_iterator_advance(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_iterator_distance(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_iterator_equal(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_itr_dereference(AMX* amx, cell* params);

//Operations
cell AMX_NATIVE_CALL SLE_list_remove(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_unqiue(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_sort(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_reverse(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_merge(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_splice(AMX* amx, cell* params);

//Relational Operations
cell AMX_NATIVE_CALL SLE_list_equal(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_greater_than(AMX* amx, cell* params);
cell AMX_NATIVE_CALL SLE_list_lesser_than(AMX* amx, cell* params);
