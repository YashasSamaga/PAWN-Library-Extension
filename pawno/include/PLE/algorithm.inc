/************************************************************************************************************
Standard Library Extension


algorithm.inc
*************************************************************************************************************/
#if defined _PLE_ALGORITHM_INC
	#endinput
#else
	#define _PLE_ALGORITHM_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif
/*****************************************************************************************************************/
//Foreach
native PLE_algo_foreach_list_init(list:listid, &val);
native PLE_algo_foreach_list_get(feid);

#define foreach::list(%0(%1)) for(new %1, fel_%0@%1_id = PLE_algo_foreach_list_init(%0, %1); PLE_algo_foreach_list_get(fel_%0@%1_id);)

stock array:ArrayToIterator(_arr[])
{
	#emit LOAD.S.pri _arr
	#emit RETN
}

#define std::%0( std_algo_%0(

stock std_algo_distance({_, literator}:param1, {_, literator}:param2, tag1 = tagof(param1), tag2 = tagof(param2))
{
	static literator:dummy1;
	#pragma unused dummy1
	
	if(tag1 != tag2) return print(" [ERROR] Unknown Function Overload for std::distance");
	if(tag1 == tagof(dummy1))
	{
	    return PLE_list_iterator_distance(native_param:param1, native_param:param2);
	}
	return 0; //TO:DO INTMAX32
}
