/************************************************************************************************************
PAWN Library Extension

Algorithm Testing
algorithm_testing.inc
*************************************************************************************************************/
#if defined _PLE_ALGORITHMT_INC
	#endinput
#else
	#define _PLE_ALGORITHMT_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif

#include <PLE/algorithm>
#include <PLE/functional>
/*****************************************************************************************************************/
static _count = 0;

forward algorithm_testing_func1(n);
public algorithm_testing_func1(n)
{
	_count++;
}

forward algorithm_testing_equal1(n);
public algorithm_testing_equal1(n)
{
	return (n == 1);
}

forward algorithm_testing_gen();
public algorithm_testing_gen()
{
	return _count++;
}


algorithm_testing()
{
	new str_array[19][20] = {"Abcdefg", "Bcefasd", "Csdadasd", "Dqwe213", "Esdas2345", "FSDccwer423", "G234asdfsf",
	   			   "Hzsdeqwrqweas", "Iasdad", "Jasdadad", "Kasdq32234", "Lasda34214", "Mnasdasdaosdasd",
                   "Nasdasdd", "Pqweqwdsd", "QWEqwesd", "Rewasadt", "Stw3erwrs", "Tasdasd"};

	new integer_array[] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	new Float:float_array[] = {1.0, 2.0, 3.0 ,3.3, 3.7, 4.5, 4.8, 5.1, 5.7, 6.7, 6.9, 7.2, 7.8, 8.0};

	new idx = 0;
	if(sbsearch("Csdadasd", str_array, idx) == false) print("[TEST1] sbsearch failed.");
	if(idx != 2) printf("[TEST2] sbsearch failed.");
	
	if(sbsearch("Zsde", str_array, idx) == true) print("[TEST3] sbsearch failed.");
	
	if(ibsearch(4, integer_array, idx) == false) print("[TEST4] ibsearch failed.");
	if(idx != 3) print("[TEST5] ibsearch failed.");

	if(ibsearch(6, integer_array, idx) == true) print("[TEST6] ibsearch failed.");
	
	if(fbsearch(4.5, float_array, idx) == false) print("[TEST7] fbsearch failed.");
	if(idx != 5) print("[TEST8] fbsearch failed.");

	if(fbsearch(6.6, float_array, idx) == true) print("[TEST9] fbsearch failed.");
	
	if(all_of(integer_array, sizeof(integer_array), bind1st(functions::greater, 5))) print("[TEST10] all_of failed.");
	if(!all_of(integer_array, sizeof(integer_array), bind1st(functions::greater, 45))) print("[TEST11] all_of failed.");
	
	if(any_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 55))) print("[TEST12] any_of failed.");
	if(!any_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 5))) print("[TEST13] any_of failed.");
	
	if(none_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 5))) print("[TEST14] none_of failed.");
	if(!none_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 55))) print("[TEST15] none_of failed.");
	
	for_each(integer_array, sizeof(integer_array), make_function({0,0,0,0,0,0},"algorithm_testing_func1", 1));
	if(_count != sizeof(integer_array)) print("[TEST16] for_each failed.");
	
	if(find(integer_array, sizeof(integer_array), 5) != 4) print("[TEST17] find failed.");
	if(find(integer_array, sizeof(integer_array), 55) != sizeof(integer_array)) print("[TEST18] find failed.");

	if(find_if(integer_array, sizeof(integer_array), make_function({0,0,0,0,0,0},"algorithm_testing_equal1", 1)) != 0) print("[TEST19] find_if failed.");
	if(find_if(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 177)) != sizeof(integer_array)) print("[TEST20] find_if failed.");
	
	if(is_permutation({1, 2, 3}, 3, {1, 3, 4})) print("[TEST21] is_permutation failed.");
	if(!is_permutation({1, 2, 3}, 3, {1, 3, 2})) print("[TEST22] is_permutation failed.");
	
	if(count({1, 2, 3, 4, 1, 2, 1, 1, 1}, 9, 1) != 5) print("[TEST23] count failed.");
	if(count_if({1, 2, 3, 4, 1, 2, 1, 1, 1}, 9, bind1st(functions::equal_to, 1)) != 5) print("[TEST24] count_if failed.");
	
	new newarr[4];
	copy({1, 2, 3, 4}, 4, newarr);
	if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3 || newarr[3] != 4) print("[TEST26] copy failed.");
	
	copy_if({1, 2, 3, 4}, 4, newarr, bind1st(functions::equal_to, 2));
	if(newarr[0] != 2) print("[TEST28] copy_if failed.");
	
	copy_backward({4, 3, 2, 1}, 4, newarr[3]);
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST30] copy_backward failed.");
	
	new a = 5, b = 10;
	swap(a, b);
	if(a != 10 || b != 5) print("[TEST31] swap failed.");
	
	fill(newarr, 4, 100);
	if(newarr[3] != 100 || newarr[2] != 100 || newarr[1] != 100 || newarr[0] != 100) print("[TEST32] fill failed.");
	
	newarr[3] = 4;
	if(remove(newarr, 4, 100) != 1) print("[TEST33] remove failed.");
	if(newarr[0] != 4) print("[TEST34] remove failed.");
	
	newarr = {1, 2, 3, 4};
	reverse(newarr, 4);
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST35] reverse failed.");
	
	reverse_copy({1, 2, 3, 4}, 4, newarr);
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST36] reverse_copy failed.");

	if(max_element(newarr, 4) != 0) print("[TEST37] max_element failed.");
	if(min_element(newarr, 4) != 3) print("[TEST38] min_element failed.");
	
	if(remove_if(newarr, 4, not_fn(bind1st(functions::equal_to, 2))) != 1) print("[TEST39] remove_if failed.");
	if(newarr[0] != 2) print("[TEST] remove_if failed.");
	
	if(remove_copy({100, 4, 100, 100}, 4, newarr, 100) != 1) print("[TEST] remove_copy failed.");
	if(newarr[0] != 4) print("[TEST] remove_copy failed.");
	
	if(remove_copy_if({100, 4, 100, 100}, 4, newarr, bind1st(functions::equal_to, 100)) != 1) print("[TEST] remove_copy_if failed.");
	if(newarr[0] != 4) print("[TEST] remove_copy_if failed.");
	
	swap_ranges({128, 128, 128, 128}, 4, newarr);
	if(newarr[0] != 128 || newarr[1] != 128 || newarr[2] != 128 || newarr[3] != 128) print("[TEST] swap_ranges failed.");
	
	transform({1, 2, 3, 4}, 4, newarr, functions::increment);
	if(newarr[0] != 2 || newarr[1] != 3 || newarr[2] != 4 || newarr[3] != 5) print("[TEST] transform failed.");
	
	transform2({1, 2, 3, 4}, 4, {4, 3, 2, 1}, newarr, functions::plus) ;
	if(newarr[0] != 5 || newarr[1] != 5 || newarr[2] != 5 || newarr[3] != 5) print("[TEST] transform2 failed.");
	
	newarr = {1, 2, 2, 3};
	if(replace(newarr, 4, 2, 4) != 2) print("[TEST] replace failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace failed.");

	if(is_sorted(newarr, 4)) print("[TEST] is_sorted failed.");
	sort(newarr, 4);
	if(newarr[0] != 1 || newarr[1] != 3 || newarr[2] != 4 || newarr[3] != 4) print("[TEST] sort failed.");
 	if(!is_sorted(newarr, 4)) print("[TEST] is_sorted failed.");

    newarr = {1, 2, 2, 3};
	if(replace_if(newarr, 4, bind1st(functions::equal_to, 2), 4) != 2) print("[TEST] replace_if failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_if failed.");
	
	_count = 0;
	generate(newarr, 4, make_function({0,0,0,0,0,0}, "algorithm_testing_gen", 0));
	
	newarr = {1, 2, 2, 3};
	if(unique(newarr, 4) != 3) print("[TEST] unique failed.");
    if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3) print("[TEST] unique failed.");
    
   	if(unique_copy({1, 2, 2, 3}, 4, newarr) != 3) print("[TEST] unique_copy failed.");
    if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3) print("[TEST] unique_copy failed.");
    
    if(replace_copy({1, 2, 2, 3}, 4, newarr, 2, 4) != 2) print("[TEST] replace_copy failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_copy failed.");
    
	if(replace_copy_if({1, 2, 2, 3}, 4, newarr, bind1st(functions::equal_to, 2), 4) != 2) print("[TEST] replace_copy_if failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_copy_if failed.");
	
	newarr = {1, 3, 2, 2};
	partial_sort(newarr, 2, 4);
	if(newarr[0] != 1 || newarr[1] != 2) print("[TEST] partial_sort failed.");
	
    newarr = {1, 3, 1, 2};
    nth_element(newarr, 3, 4);
    if(newarr[2] != 2) print("[TEST] nth_element failed.");
    
    newarr = {1, 2, 3, 4};
    rotate(newarr, 2, 4);
    if(newarr[0] != 3 || newarr[1] != 4 || newarr[2] != 1 || newarr[3] != 2) print("[TEST] rotate failed.");
    
    newarr = {5, 5, 5, 5};
    rotate_copy({1, 2, 3, 4}, 2, 4, newarr);
    if(newarr[0] != 3 || newarr[1] != 4 || newarr[2] != 1 || newarr[3] != 2) print("[TEST] rotate_copy failed.");
    
    if(!includes({1, 2, 3, 4, 5, 6, 7, 8}, 8, {3, 4, 5}, 3)) print("[TEST] includes failed.");
    if(includes({1, 2, 3, 4, 5, 6, 7, 8}, 8, {3, 4, 53}, 3)) print("[TEST] includes failed.");
    
    new bigarr[6];
    merge({1, 2, 3}, 3, {2, 3, 4}, 3, bigarr);
    if(bigarr[0] != 1 || bigarr[1] != 2 || bigarr[2] != 2 || bigarr[3] != 3 || bigarr[4] != 3 || bigarr[5] != 4) print("[TEST] merge failed.");

	bigarr = {1, 2, 3, 2, 3, 4};
    inplace_merge(bigarr, 3, 6);
    if(bigarr[0] != 1 || bigarr[1] != 2 || bigarr[2] != 2 || bigarr[3] != 3 || bigarr[4] != 3 || bigarr[5] != 4) print("[TEST] inplace_merge failed.");

	if(set_union({1, 2, 3}, 3, {2, 3, 4}, 3, bigarr) != 4) print("[TEST] set_union failed.");
	if(bigarr[0] != 1 || bigarr[1] != 2 || bigarr[2] != 3 || bigarr[3] != 4) print("[TEST] set_union failed.");
	
	if(set_intersection({1, 2, 3}, 3, {2, 3, 4}, 3, bigarr) != 2) print("[TEST] set_intersection failed.");
	if(bigarr[0] != 2 || bigarr[1] != 3) print("[TEST] set_intersection failed.");
	
	if(set_difference({1, 2, 3}, 3, {2, 3, 4}, 3, bigarr) != 1) print("[TEST] set_difference failed.");
	if(bigarr[0] != 1) print("[TEST] set_difference failed.");
	
	if(set_symmetric_difference({1, 2, 3}, 3, {2, 3, 4}, 3, bigarr) != 2) print("[TEST] set_symmetric_difference failed.");
	if(bigarr[0] != 1 || bigarr[1] != 4) print("[TEST] set_symmetric_difference failed.");

	new smallest_idx, largest_idx;
	minmax_element({1, 2, 3, 4, 5, 6, 7, 8}, 8, smallest_idx, largest_idx);
	if(smallest_idx != 0 || largest_idx != 7) print("[TEST] minmax_element failed.");
	
	if(binary_search({1, 2, 3, 4, 5}, 5, 30)) print("[TEST] binary_search failed.");
	if(!binary_search({1, 2, 3, 4, 5}, 5, 3)) print("[TEST] binary_search failed.");
	
	if(search_n({1, 2, 3, 4, 5, 5, 6, 7}, 7, 2, 5) != 4) print("[TEST] search_n failed.");
    if(search({1, 2, 3, 4, 5, 5, 6, 7}, 7, {5, 6}, 2) != 5) print("[TEST] search failed.");
    
	if(!is_partitioned({1, 3, 5, 7, 2, 4, 6, 8}, 8, bind2nd(functions::modulus, 2))) print("[TEST] is_partitioned failed.");
	if(is_partitioned({1, 3, 4, 7, 2, 4, 6, 8}, 8, bind2nd(functions::modulus, 2))) print("[TEST] is_partitioned failed.");
}

#endinput
native find_end(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native find_first_of(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native adjacent_find(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native mismatch(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native equal(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native stable_partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_copy(range[], numcells, dest1[], dest2[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_point(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);

native lower_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native upper_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native equal_range(range[], numcells, value, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native lexicographical_compare(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native next_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE]);
native prev_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE]);
