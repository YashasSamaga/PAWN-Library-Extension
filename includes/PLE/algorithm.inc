/************************************************************************************************************
PAWN Library Extension

Collection of useful algorithms (mostly from C++ standard/template library along with addititional functions)
algorithm.inc
*************************************************************************************************************/
#if defined _PLE_ALGORITHM_INC
	#endinput
#else
	#define _PLE_ALGORITHM_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/functional>
/*************************************************************************************************************/
#if defined MERGE_ALGORITHM_NAMESPACE
	#define algorithm::
#else
	#define algorithm:: algo_
#endif

native bool:algorithm::sbsearch(search[], source[][], &idx, size_major = sizeof(source), size_minor = sizeof(source[]));
native bool:algorithm::ibsearch(key, array[], &idx, size = sizeof(array));
native bool:algorithm::fbsearch(Float:key, Float:array[], &idx, Float:error = 0.01, size = sizeof(array));

native bool:algorithm::all_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:algorithm::any_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:algorithm::none_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:algorithm::for_each(range[], numcells, func[FTSIZE]);
native algorithm::find(range[], numcells, search_value);
native algorithm::find_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::find_if_not(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::find_end(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::find_first_of(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::adjacent_find(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::count(range[], numcells, value);
native algorithm::count_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::mismatch(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:algorithm::equal(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:algorithm::is_permutation(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::search(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::search_n(range[], numcells, n, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native algorithm::copy(source[], numcells, dest[]);
native algorithm::copy_if(source[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::copy_backward(source[], numcells, dest_end[]);
native noret:algorithm::swap(&val1, &val2);
native algorithm::swap_ranges(range1[], numcells1, range2[]);
native algorithm::transform(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::transform2(range1[], numcells1, range2[], dest[], {_, func_bool2, func_cell2}:func[FTSIZE]);
native algorithm::replace(range[], numcells, search_value, replace_value);
native algorithm::replace_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native algorithm::replace_copy(range[], numcells, dest[], search_value, replace_value);
native algorithm::replace_copy_if(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native noret:algorithm::fill(range[], numcells, value);
//fill_n = fill
native noret:algorithm::generate(range[], numcells, {func_bool0, func_cell0, _}:func[FTSIZE]);
//generate_n = generate
native algorithm::remove(range[], numcells, value);
native algorithm::remove_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::remove_copy(range[], numcells, dest[], value);
native algorithm::remove_copy_if(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::unique(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::unique_copy(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native noret:algorithm::reverse(range[], numcells);
native algorithm::reverse_copy(range[], numcells, dest[]);
native algorithm::rotate(range[], middle, end);
native algorithm::rotate_copy(range[], middle, end, dest[]);

//random_shuffle won't be implemented (removed from C++17)
//shuffle
//sample

native bool:algorithm::is_partitioned(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::stable_partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::partition_copy(range[], numcells, dest1[], dest2[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native algorithm::partition_point(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);

native noret:algorithm::sort(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:algorithm::partial_sort(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::partial_sort_copy(range[], range_numcells, dest[], dest_numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:algorithm::is_sorted(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::nth_element(range[], nth, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native algorithm::lower_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::upper_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::equal_range(range[], numcells, value, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:algorithm::binary_search(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native algorithm::merge(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:algorithm::inplace_merge(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:algorithm::includes(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native algorithm::set_union(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::set_intersection(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::set_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::set_symmetric_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//push_heap, pop_heap, make_heap, sort_heap, is_heap, is_heap_until not implemented

//min, max already implemented
//minmax not implemented
native noret:algorithm::minmax_element(range[], numcells, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::min_element(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native algorithm::max_element(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native bool:algorithm::lexicographical_compare(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:algorithm::next_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:algorithm::prev_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
