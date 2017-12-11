/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

Collection of useful algorithms (mostly from C++ standard/template library along with addititional functions)
algorithm.h

*************************************************************************************************************/
#ifndef PLE_ALGORITHM_H_INCLUDED
#define PLE_ALGORITHM_H_INCLUDED

#include "main.h"

namespace PLE::natives
{
	extern cell AMX_NATIVE_CALL algo_sbsearch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_fbsearch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_ibsearch(AMX * amx, cell* params);

	extern cell AMX_NATIVE_CALL algo_all_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_any_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_none_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_for_each(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_find(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_find_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_find_if_not(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_find_end(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_find_first_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_adjacent_find(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_count(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_count_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_mismatch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_equal(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_is_permutation(AMX * amx, cell* params);
	
	extern cell AMX_NATIVE_CALL algo_search(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_search_n(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_copy_backward(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_swap(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_swap_ranges(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_transform(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_transform2(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_replace(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_replace_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_replace_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_replace_copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_fill(AMX * amx, cell* params);
	//fill_n = fill
	extern cell AMX_NATIVE_CALL algo_generate(AMX * amx, cell* params);
	//generate_n = generate
	extern cell AMX_NATIVE_CALL algo_remove(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_remove_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_remove_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_remove_copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_unique(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_unique_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_reverse(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_reverse_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_rotate(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_rotate_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_shuffle(AMX * amx, cell* params);
	//sample

	extern cell AMX_NATIVE_CALL algo_is_partitioned(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_partition(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_stable_partition(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_partition_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_partition_point(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_sort(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_partial_sort(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_partial_sort_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_is_sorted(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_nth_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_lower_bound(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_upper_bound(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_equal_range(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_binary_search(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_merge(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_inplace_merge(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_includes(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_set_union(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_set_intersection(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_set_difference(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_set_symmetric_difference(AMX * amx, cell* params);

	//push_heap, pop_heap, make_heap, sort_heap, is_heap, is_heap_until not implemented

	//max already implemented
	//min already implemented
	//minmax not implemented
	extern cell AMX_NATIVE_CALL algo_min_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_max_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_minmax_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_lexicographical_compare(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_prev_permutation(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL algo_next_permutation(AMX * amx, cell* params);
}

#endif /* PLE_ALGORITHM_H_INCLUDED */