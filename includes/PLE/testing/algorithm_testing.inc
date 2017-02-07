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
	if(algorithm::sbsearch("Csdadasd", str_array, idx) == false) print("[TEST1] sbsearch failed.");
	if(idx != 2) printf("[TEST2] sbsearch failed.");
	
	if(algorithm::sbsearch("Zsde", str_array, idx) == true) print("[TEST3] sbsearch failed.");
	
	if(algorithm::ibsearch(4, integer_array, idx) == false) print("[TEST4] ibsearch failed.");
	if(idx != 3) print("[TEST5] ibsearch failed.");

	if(algorithm::ibsearch(6, integer_array, idx) == true) print("[TEST6] ibsearch failed.");
	
	if(algorithm::fbsearch(4.5, float_array, idx) == false) print("[TEST7] fbsearch failed.");
	if(idx != 5) print("[TEST8] fbsearch failed.");

	if(algorithm::fbsearch(6.6, float_array, idx) == true) print("[TEST9] fbsearch failed.");
	
	if(algorithm::all_of(integer_array, sizeof(integer_array), bind1st(functions::greater, 5))) print("[TEST10] all_of failed.");
	if(!algorithm::all_of(integer_array, sizeof(integer_array), bind1st(functions::greater, 45))) print("[TEST11] all_of failed.");
	
	if(algorithm::any_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 55))) print("[TEST12] any_of failed.");
	if(!algorithm::any_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 5))) print("[TEST13] any_of failed.");
	
	if(algorithm::none_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 5))) print("[TEST14] none_of failed.");
	if(!algorithm::none_of(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 55))) print("[TEST15] none_of failed.");
	
	algorithm::for_each(integer_array, sizeof(integer_array), make_function({0,0,0,0},"algorithm_testing_func1", 1));
	if(_count != sizeof(integer_array)) print("[TEST16] for_each failed.");
	
	if(algorithm::find(integer_array, sizeof(integer_array), 5) != 4) print("[TEST17] find failed.");
	if(algorithm::find(integer_array, sizeof(integer_array), 55) != sizeof(integer_array)) print("[TEST18] find failed.");

	if(algorithm::find_if(integer_array, sizeof(integer_array), make_function({0,0,0,0},"algorithm_testing_equal1", 1)) != 0) print("[TEST19] find_if failed.");
	if(algorithm::find_if(integer_array, sizeof(integer_array), bind1st(functions::equal_to, 177)) != sizeof(integer_array)) print("[TEST20] find_if failed.");
	
	if(algorithm::is_permutation({1, 2, 3}, 3, {1, 3, 4})) print("[TEST21] is_permutation failed.");
	if(!algorithm::is_permutation({1, 2, 3}, 3, {1, 3, 2})) print("[TEST22] is_permutation failed.");
	
	if(algorithm::count({1, 2, 3, 4, 1, 2, 1, 1, 1}, 9, 1) != 5) print("[TEST23] count failed.");
	if(algorithm::count_if({1, 2, 3, 4, 1, 2, 1, 1, 1}, 9, bind1st(functions::equal_to, 1)) != 5) print("[TEST24] count_if failed.");
	
	new newarr[4];
	if(algorithm::copy({1, 2, 3, 4}, 4, newarr) != 4) print("[TEST25] copy failed.");
	if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3 || newarr[3] != 4) print("[TEST26] copy failed.");
	
	if(algorithm::copy_if({1, 2, 3, 4}, 4, newarr, bind1st(functions::equal_to, 2)) != 1) print("[TEST27] copy_if failed.");
	if(newarr[0] != 2) print("[TEST28] copy_if failed.");
	
	if(algorithm::copy_backward({4, 3, 2, 1}, 4, newarr[3]) != 4) print("[TEST29] copy_backward failed.");
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST30] copy_backward failed.");
	
	new a = 5, b = 10;
	algorithm::swap(a, b);
	if(a != 10 || b != 5) print("[TEST31] swap failed.");
	
	algorithm::fill(newarr, 4, 100);
	if(newarr[3] != 100 || newarr[2] != 100 || newarr[1] != 100 || newarr[0] != 100) print("[TEST32] fill failed.");
	
	newarr[3] = 4;
	if(algorithm::remove(newarr, 4, 100) != 1) print("[TEST33] remove failed.");
	if(newarr[0] != 4) print("[TEST34] remove failed.");
	
	newarr = {1, 2, 3, 4};
	algorithm::reverse(newarr, 4);
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST35] reverse failed.");
	
	algorithm::reverse_copy({1, 2, 3, 4}, 4, newarr);
	if(newarr[0] != 4 || newarr[1] != 3 || newarr[2] != 2 || newarr[3] != 1) print("[TEST36] reverse_copy failed.");

	if(algorithm::max_element(newarr, 4) != 0) print("[TEST37] max_element failed.");
	if(algorithm::min_element(newarr, 4) != 3) print("[TEST38] min_element failed.");
	
	if(algorithm::remove_if(newarr, 4, not_fn(bind1st(functions::equal_to, 2))) != 1) print("[TEST39] remove_if failed.");
	if(newarr[0] != 2) print("[TEST] remove_if failed.");
	
	if(algorithm::remove_copy({100, 4, 100, 100}, 4, newarr, 100) != 1) print("[TEST] remove_copy failed.");
	if(newarr[0] != 4) print("[TEST] remove_copy failed.");
	
	if(algorithm::remove_copy_if({100, 4, 100, 100}, 4, newarr, bind1st(functions::equal_to, 100)) != 1) print("[TEST] remove_copy_if failed.");
	if(newarr[0] != 4) print("[TEST] remove_copy_if failed.");
	
	algorithm::swap_ranges({128, 128, 128, 128}, 4, newarr);
	if(newarr[0] != 128 || newarr[1] != 128 || newarr[2] != 128 || newarr[3] != 128) print("[TEST] swap_ranges failed.");
	
	if(algorithm::transform({1, 2, 3, 4}, 4, newarr, functions::increment) != 4) print("[TEST] transform failed.");
	if(newarr[0] != 2 || newarr[1] != 3 || newarr[2] != 4 || newarr[3] != 5) print("[TEST] transform failed.");
	
	if(algorithm::transform2({1, 2, 3, 4}, 4, {4, 3, 2, 1}, newarr, functions::plus) != 4) print("[TEST] transform2 failed.");
	if(newarr[0] != 5 || newarr[1] != 5 || newarr[2] != 5 || newarr[3] != 5) print("[TEST] transform2 failed.");
	
	newarr = {1, 2, 2, 3};
	if(algorithm::replace(newarr, 4, 2, 4) != 2) print("[TEST] replace failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace failed.");

	if(algorithm::is_sorted(newarr, 4)) print("[TEST] is_sorted failed.");
	algorithm::sort(newarr, 4);
	if(newarr[0] != 1 || newarr[1] != 3 || newarr[2] != 4 || newarr[3] != 4) print("[TEST] sort failed.");
 	if(!algorithm::is_sorted(newarr, 4)) print("[TEST] is_sorted failed.");

    newarr = {1, 2, 2, 3};
	if(algorithm::replace_if(newarr, 4, bind1st(functions::equal_to, 2), 4) != 2) print("[TEST] replace_if failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_if failed.");
	
	_count = 0;
	algorithm::generate(newarr, 4, make_function({0,0,0,0}, "algorithm_testing_gen", 0));
	
	newarr = {1, 2, 2, 3};
	if(algorithm::unique(newarr, 4) != 3) print("[TEST] unique failed.");
    if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3) print("[TEST] unique failed.");
    
   	if(algorithm::unique_copy({1, 2, 2, 3}, 4, newarr) != 3) print("[TEST] unique_copy failed.");
    if(newarr[0] != 1 || newarr[1] != 2 || newarr[2] != 3) print("[TEST] unique_copy failed.");
    
    if(algorithm::replace_copy({1, 2, 2, 3}, 4, newarr, 2, 4) != 2) print("[TEST] replace_copy failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_copy failed.");
    
	if(algorithm::replace_copy_if({1, 2, 2, 3}, 4, newarr, bind1st(functions::equal_to, 2), 4) != 2) print("[TEST] replace_if failed.");
	if(newarr[0] != 1 || newarr[1] != 4 || newarr[2] != 4 || newarr[3] != 3) print("[TEST] replace_if failed.");
	
	
}

#endinput
native find_end(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native find_first_of(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native adjacent_find(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native mismatch(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native equal(range1[], numcells1, range2[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);
native search_n(range[], numcells, n, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native rotate(range[], middle, end);
native rotate_copy(range[], middle, end, dest[]);

native is_partitioned(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native stable_partition(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_copy(range[], numcells, dest1[], dest2[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native partition_point(range[], numcells, {_, func_bool1, func_cell1}:func[FTSIZE]);

native partial_sort(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native partial_sort_copy(range[], range_numcells, dest[], dest_numcells, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native nth_element(range[], nth, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native lower_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native upper_bound(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native equal_range(range[], numcells, value, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native binary_search(range[], numcells, value, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

native merge(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native inplace_merge(range[], middle, end, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native includes(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::equal_to);

native set_union(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_intersection(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native set_symmetric_difference(range1[], numcells1, range2[], numcells2, dest[], {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);

//push_heap, pop_heap, make_heap, sort_heap, is_heap, is_heap_until not implemented

//min, max already implemented
//minmax not implemented
native minmax_element(range[], numcells, &smallest, &largest, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);


native lexicographical_compare(range1[], numcells1, range2[], numcells2, {_, func_bool2, func_cell2}:func[FTSIZE] = fixed_functions::less);
native next_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE]);
native prev_permutation(range[], numcells, {_, func_bool2, func_cell2}:func[FTSIZE]);
