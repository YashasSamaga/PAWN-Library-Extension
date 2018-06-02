/*
** PAWN Library Extension (PLE)
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

#ifndef PLE_ALGORITHM_H_INCLUDED
#define PLE_ALGORITHM_H_INCLUDED

#include "main.h"

namespace PLE::algorithm::natives
{
	extern cell AMX_NATIVE_CALL sbsearch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fbsearch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL ibsearch(AMX * amx, cell* params);

	extern cell AMX_NATIVE_CALL all_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL any_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL none_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL for_each(AMX * amx, cell* params);
	//for_each_n = for_each
	extern cell AMX_NATIVE_CALL find(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL find_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL find_if_not(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL find_end(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL find_first_of(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL adjacent_find(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL count(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL count_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL mismatch(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL equal(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL is_permutation(AMX * amx, cell* params);
	
	extern cell AMX_NATIVE_CALL search(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL search_n(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL copy_backward(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL swap(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL swap_ranges(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL transform(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL transform2(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL replace(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL replace_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL replace_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL replace_copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL fill(AMX * amx, cell* params);
	//fill_n = fill
	extern cell AMX_NATIVE_CALL generate(AMX * amx, cell* params);
	//generate_n = generate
	extern cell AMX_NATIVE_CALL remove(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL remove_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL remove_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL remove_copy_if(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL unique(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL unique_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL reverse(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL reverse_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL rotate(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL rotate_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL shuffle(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL sample(AMX * amx, cell* params);

	extern cell AMX_NATIVE_CALL is_partitioned(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL partition(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL stable_partition(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL partition_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL partition_point(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL sort(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL partial_sort(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL partial_sort_copy(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL is_sorted(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL nth_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL lower_bound(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL upper_bound(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL equal_range(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL binary_search(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL merge(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL inplace_merge(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL includes(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL set_union(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL set_intersection(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL set_difference(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL set_symmetric_difference(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL is_heap(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL is_heap_until(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL make_heap(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL sort_heap(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL push_heap(AMX * amx, cell* params);
    extern cell AMX_NATIVE_CALL pop_heap(AMX * amx, cell* params);

	//max already implemented
	//min already implemented
	//minmax not implemented
	extern cell AMX_NATIVE_CALL min_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL max_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL minmax_element(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL lexicographical_compare(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL prev_permutation(AMX * amx, cell* params);
	extern cell AMX_NATIVE_CALL next_permutation(AMX * amx, cell* params);

    //numeric
    extern cell AMX_NATIVE_CALL iota(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL accumulate(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL adjacent_difference(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL inner_product(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL partial_sum(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL gcd(AMX *amx, cell params[]);
	extern cell AMX_NATIVE_CALL lcm(AMX *amx, cell params[]);
}

#endif /* PLE_ALGORITHM_H_INCLUDED */