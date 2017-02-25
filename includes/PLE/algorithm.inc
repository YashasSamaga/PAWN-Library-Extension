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
native bool:sbsearch(search[], source[][], &idx, size_major = sizeof(source), size_minor = sizeof(source[]));
native bool:ibsearch(key, array[], &idx, size = sizeof(array));
native bool:fbsearch(Float:key, Float:array[], &idx, Float:error = 0.01, size = sizeof(array));

native bool:all_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:any_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:none_of(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:for_each(range[], numcells, func[FTSIZE]);
native find(range[], numcells, search_value);
native find_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native find_if_not(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native find_end(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native find_first_of(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native adjacent_find(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native count(range[], numcells, value);
native count_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native mismatch(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:equal(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:is_permutation(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search_n(range[], numcells, n, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native noret:copy(source[], numcells, dest[]);
native noret:copy_if(source[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:copy_backward(source[], numcells, dest_end[]);
native noret:swap(&val1, &val2);
native noret:swap_ranges(range1[], numcells1, range2[]);
native noret:transform(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:transform2(range1[], numcells1, range2[], dest[], {_, func_bool2, func_cell2}:func[FTSIZE]);
native replace(range[], numcells, search_value, replace_value);
native replace_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native replace_copy(range[], numcells, dest[], search_value, replace_value);
native replace_copy_if(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native noret:fill(range[], numcells, value);
//fill_n = fill
native noret:generate(range[], numcells, {func_bool0, func_cell0, _}:func[FTSIZE]);
//generate_n = generate
native remove(range[], numcells, value);
native remove_if(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native remove_copy(range[], numcells, dest[], value);
native remove_copy_if(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native unique(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native unique_copy(range[], numcells, dest[], {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native noret:reverse(range[], numcells);
native noret:reverse_copy(range[], numcells, dest[]);
native noret:rotate(range[], middle, end);
native noret:rotate_copy(range[], middle, end, dest[]);
native noret:shuffle(range[], end);
//sample not implemented

native bool:is_partitioned(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native stable_partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:partition_copy(range[], numcells, dest1[], dest2[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_point(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);

native noret:sort(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:partial_sort(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native partial_sort_copy(range[], range_numcells, dest[], dest_numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:is_sorted(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:nth_element(range[], nth, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native lower_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native upper_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:equal_range(range[], numcells, value, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:binary_search(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native merge(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:inplace_merge(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:includes(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_union(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_intersection(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_symmetric_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//push_heap, pop_heap, make_heap, sort_heap, is_heap, is_heap_until not implemented

//min, max already implemented
//minmax not implemented
native noret:minmax_element(range[], numcells, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native min_element(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native max_element(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native bool:lexicographical_compare(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:next_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:prev_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
