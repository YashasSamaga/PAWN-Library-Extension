/*
** PAWN Library Extension (PLE)
**
** Algorithm
** Collection of algorithms
**
** This file is part of PAWN Library Extension.
**
**   This library is free software: you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation, either version 3 of the License, or
**   (at your option) any later version.
**
**   This library is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
** Copyright (C) 2016-2018  Yashas Samaga
*/

#if defined PLE_ALGORITHM_INCLUDED
	#endinput
#endif
#define PLE_ALGORITHM_INCLUDED

/* dependencies */
#include <PLE/config>
#include <PLE/functional>

//Operations which do not alter ranges
native bool:ibsearch(key, const range[], &idx, size = sizeof(range));
native bool:fbsearch(Float:key, const Float:range[], &idx, Float:error = 0.01, size = sizeof(range));
native bool:sbsearch(const search[], const range[][], &idx, size_major = sizeof(range), size_minor = sizeof(range[]));

native bool:all_of(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:any_of(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:none_of(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:for_each(const range[], numcells, const func[FTSIZE]);
//for_each_n = for_each
native find(const range[], numcells, search_value);
native find_if(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native find_if_not(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native find_end(const range1[], numcells1, const range2[], numcells2, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native find_first_of(const range1[], numcells1, const range2[], numcells2, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native adjacent_find(const range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native count(const range[], numcells, value);
native count_if(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native mismatch(const range1[], numcells1, const range2[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:equal(const range1[], numcells1, const range2[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native bool:is_permutation(const range1[], numcells1, const range2[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search(const range1[], numcells1, const range2[], numcells2, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search_n(const range[], numcells, n, value, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

//Operations which modify ranges
native noret:copy(const source[], numcells, dest[]);
native noret:copy_if(const source[], numcells, dest[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:copy_backward(const source[], numcells, dest_end[]);
native noret:swap(&val1, &val2);
native noret:swap_ranges(range1[], numcells1, range2[]);
native noret:transform(const range[], numcells, dest[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:transform2(const range1[], numcells1, const range2[], dest[], const {_, func_bool2, func_cell2}:func[FTSIZE]);
native replace(range[], numcells, search_value, replace_value);
native replace_if(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native replace_copy(const range[], numcells, dest[], search_value, replace_value);
native replace_copy_if(const range[], numcells, dest[], const {_, func_bool1, func_cell1}:func[FTSIZE], replace_value);
native noret:fill(range[], numcells, value);
//fill_n = fill
native noret:generate(range[], numcells, const {func_bool0, func_cell0, _}:func[FTSIZE]);
//generate_n = generate
native remove(range[], numcells, value);
native remove_if(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native remove_copy(const range[], numcells, dest[], value);
native remove_copy_if(const range[], numcells, dest[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native unique(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native unique_copy(const range[], numcells, dest[], const {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::equal_to);
native noret:reverse(range[], numcells);
native noret:reverse_copy(const range[], numcells, dest[]);
native noret:rotate(range[], middle, end);
native noret:rotate_copy(const range[], middle, end, dest[]);
native noret:shuffle(range[], numcells);
native sample(const range[], numcells, dest[], count);

//Partition functions
native bool:is_partitioned(const range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native stable_partition(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:partition_copy(const range[], numcells, dest1[], dest2[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_point(range[], numcells, const {_, func_bool1, func_cell1}:func[FTSIZE]);

//Sorting functions
native noret:sort(range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:partial_sort(range[], middle, end, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native partial_sort_copy(const range[], range_numcells, dest[], dest_numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:is_sorted(const range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:nth_element(range[], nth, end, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//Binary search functions
native lower_bound(const range[], numcells, value, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native upper_bound(const range[], numcells, value, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:equal_range(const range[], numcells, value, &smallest, &largest, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:binary_search(const range[], numcells, value, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//Set functions
native merge(const range1[], numcells1, const range2[], numcells2, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native noret:inplace_merge(range[], middle, end, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:includes(const range1[], numcells1, const range2[], numcells2, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_union(const range1[], numcells1, const range2[], numcells2, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_intersection(const range1[], numcells1, const range2[], numcells2, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_difference(const range1[], numcells1, const range2[], numcells2, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_symmetric_difference(const range1[], numcells1, const range2[], numcells2, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//Heap operations
native bool:is_heap(const range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
native is_heap_until(const range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
native noret:make_heap(range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
native noret:sort_heap(range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
native noret:push_heap(range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);
native noret:pop_heap(range[], numcells, const {_, func_bool2, func_cell2, _}:func[FTSIZE] = fixed_functions::less);

//Maximumm, minimum, compare, permutation functions
//min, max already implemented
//minmax not implemented
//clamp already implemented
native noret:minmax_element(const range[], numcells, &smallest, &largest, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native min_element(const range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native max_element(const range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native bool:lexicographical_compare(const range1[], numcells1, const range2[], numcells2, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:next_permutation(range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native bool:prev_permutation(range[], numcells, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native iota(range[], numcells, init, const {_, func_bool1, func_cell1}:func[FTSIZE] = fixed_functions::increment);
native accumulate(const range[], numcells, init, const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
native inner_product(const range[], numcells, dest[], init, const {_, func_bool2, func_cell2}:func1[FTSIZE] = fixed_functions::plus, {_, func_bool2, func_cell2}:func2[FTSIZE] = fixed_functions::multiplies);
native adjacent_difference(const range[], numcells, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::minus);
native partial_sum(const range[], numcells, dest[], const {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::plus);
native gcd(x, y);
native lcm(x, y);
