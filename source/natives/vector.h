/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

STL Vector for PAWN
vector.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#include <vector>
#include <list>
/************************************************************************************************************/
#define INVALID_VECTOR_ID -1
/************************************************************************************************************/
class PawnVector
{
public:
	std::vector<cell> container;
	PawnVector() { vectorid = INVALID_VECTOR_ID; }

	void Initilize(cell id, cell tagid)
	{
		this->vectorid = id;
		this->tagid = tagid;
		container.clear();
	}
	void Reset()
	{
		vectorid = INVALID_VECTOR_ID;
	}
	bool IsUnused() const
	{
		return (vectorid == INVALID_VECTOR_ID);
	}
	cell GetTagID() const
	{
		return this->tagid;
	}

private:
	cell vectorid;
	cell tagid;
};
/************************************************************************************************************/
namespace Natives
{
	cell AMX_NATIVE_CALL vector_create(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_destroy(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_assign(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_get(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_set(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_front(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_back(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_data(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_empty(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_size(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_max_size(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_reserve(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_capacity(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_shrink_to_fit(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_clear(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_erase(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_insert(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_push_back(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_pop_back(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_resize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_swap(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_equal(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_greater_than(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_lesser_than(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_find(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_find_if(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_count(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_count_if(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_remove(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_remove_if(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_unique(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_sort(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_reverse(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vector_foreach_getValINC(AMX* amx, cell* params);
}