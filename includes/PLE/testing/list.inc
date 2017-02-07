/******************************************************************************************************************
Standard Library Extension

list.inc
******************************************************************************************************************/
#if defined _PLE_LIST_INC
	#endinput
#else
	#define _PLE_LIST_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE\config>
#endif
/*****************************************************************************************************************/
#define INVALID_LIST_ID list:-1

/******************************************************************************************************************
 ---- FOR LOCAL LISTS ONLY ---
 list<Tag> identifier(list2); //Clones a copy of list2
 list<Tag> identifier(reserve, value); //Creates a list with reserve space allocated with value as default
 list<Tag> identifier(iterator1, iterator2) //Copies contents of it1 to it2
 list<Tag> identifier(List::ArrayToIterator(array), n); //Copies n elements of the given array to the list
******************************************************************************************************************/
#define list<%0>%1(%2) list:%1 = list:_list_Create(%2, .templateid = tagof(%0:))

/******************************************************************************************************************
 Methods which do not require arguments as per Standard Template Library for C++ documentation require a fake arg
 Use any random integer for such methods
******************************************************************************************************************/
#define List::%0.%1(%2) PLE_list_%1(%0, %2)

/******************************************************************************************************************
 ref<tag>(iterator)
******************************************************************************************************************/
#define ref<%0>(%1) %0:PLE_list_itr_dereference(native_param:%1)

/*****************************************************************************************************************/
native list:PLE_list_Create(init_type, templateid, param1, param2);
native list:PLE_list_Destroy(list:listid);

native PLE_list_empty(list:listid, dummy);
native PLE_list_size(list:listid, dummy);
native PLE_list_max_size(list:listid, dummy);

native PLE_list_front(list:listid, dummy);
native PLE_list_back(list:listid, dummy);

native PLE_list_push_assign2(list:listid, assign_type, param1, param2);
native PLE_list_push_back(list:listid, value);
native PLE_list_push_front(list:listid, value);
native PLE_list_pop_back(list:listid, dummy);
native PLE_list_pop_front(list:listid, dummy);

native PLE_list_insert2(list:listid, insert_type, native_param:itr, native_param:param1, native_param:param2);
native PLE_list_erase(list:listid, native_param:itr, native_param:param1 = native_param:-729);
native PLE_list_resize(list:listid, size, val = 0);
native PLE_list_swap(list:listid, list:listid2);
native PLE_list_remove(list:listid, val);
native PLE_list_unqiue(list:listid);
native PLE_list_sort(list:listid);
native PLE_list_reverse(list:listid);
native PLE_list_merge(list:listid, list:listid2);
native PLE_list_splice(native_param:itr, list:listid, native_param:itr1 = native_param:-729, native_param:itr2 = native_param:-729);
/*****************************************************************************************************************/
// List Constructors
/*****************************************************************************************************************/
enum
{
	INIT_LIST_EMPTY = 0,
	INIT_LIST_COPY,
	INIT_LIST_FILL,
	INIT_LIST_RANGE_COPY,
	INIT_LIST_ARRAY_COPY
}
/*****************************************************************************************************************/
//Overloaded Constructor for local lists
stock list:_list_Create({list, _, literator}:param1 = list:-2, {list, _, literator}:param2 = list:-2, tag1 = tagof(param1), tag2 = tagof(param2), templateid = 0)
{
    static literator:dummy1, list:dummy2, array:dummy3;
    #pragma unused dummy1
    #pragma unused dummy2
    #pragma unused dummy3

	if(_:param2 != -2 && _:param1 >= 0)
	{
	   	if(tagof(dummy2) == tag1)
		    return PLE_list_Create(INIT_LIST_COPY, templateid, _:param1, -2);
		else
		{
		   	if(tagof(dummy1) == tag1)
			{
			    if(tagof(dummy1) == tag2)
	            {
	            }
			    //list<Tag> identifier(iterator1, iterator2) //Copies contents of it1 to it2
			}
			else if(tagof(dummy3) == tag1)
			    return PLE_list_Create(INIT_LIST_ARRAY_COPY, templateid, _:param1, _:param2); //param1 , address of the first element
			else
			  	return PLE_list_Create(INIT_LIST_FILL, templateid, _:param1, _:param2);
		}
	}
	print("[ERROR] Standard Library Extension: Invalid List Constructor");
	return INVALID_LIST_ID;
}
//Overloaded Constructor for global lists/ or local static lists
stock PLE_list_Initilize(&list:listid, {list, _, literator}:param1 = list:-2, {list, _, literator}:param2 = list:-2, templateid, tag1 = tagof(param1), tag2 = tagof(param2))
{
    static literator:dummy1, list:dummy2, array:dummy3;
    #pragma unused dummy1
    #pragma unused dummy2
    #pragma unused dummy3

	if(_:param2 != -2 && _:param1 >= 0)
	{
	   	if(tagof(dummy2) == tag1)
	   	{
		    listid = PLE_list_Create(INIT_LIST_COPY, templateid, _:param1, -2);
			return 0;
		}
		else
		{
		   	if(tagof(dummy1) == tag1)
			{
			    if(tagof(dummy1) == tag2)
	            {
	            }
			    //list<Tag> identifier(iterator1, iterator2) //Copies contents of it1 to it2
			}
			else if(tagof(dummy3) == tag1)
			{
			    listid = PLE_list_Create(INIT_LIST_ARRAY_COPY, templateid, _:param1, _:param2); //param1 , address of the first element
                return 0;
			}
			else
			{
			  	listid = PLE_list_Create(INIT_LIST_FILL, templateid, _:param1, _:param2);
                return 0;
			}
		}
	}
	print("[ERROR] Standard Library Extension: Invalid List Constructor");
	return INVALID_LIST_ID;
}
/*****************************************************************************************************************/
// Methods
/*****************************************************************************************************************/
stock PLE_list_assign(list:listid, {list, _, literator}:param1 = list:-2, {list, _, literator}:param2 = list:-2, tag1 = tagof(param1), tag2 = tagof(param2))
{
    static literator:dummy1, list:dummy2, array:dummy3;
    #pragma unused dummy1
    #pragma unused dummy2
    #pragma unused dummy3

	if(_:param2 != -2 && _:param1 >= 0)
	{
	   	if(tagof(dummy1) == tag1)
		{
		    if(tagof(dummy1) == tag2)
            	return PLE_list_assign(listid, INIT_LIST_FILL, _:param1, _:param2);
		    //list<Tag> identifier(iterator1, iterator2) //Copies contents of it1 to it2
		}
		else if(tagof(dummy3) == tag1)
		    return PLE_list_assign(listid, INIT_LIST_ARRAY_COPY, _:param1, _:param2); //param1 , address of the first element
	}
	print("[ERROR] Standard Library Extension: Invalid List Parameters for Assignment");
	return INVALID_LIST_ID;
}
enum
{
	INSERT_TYPE_SINGLE_ELEMENT,
	INSERT_TYPE_FILL,
	INSERT_TYPE_RANGE
}
stock PLE_list_insert(list:listid, literator:param1, { _, literator}:param2, { _, literator}:param3 = -729, tag2 = tagof(param2), tag3 = tagof(param3))
{
	static dummy1, literator:dummy2;
	if(tagof(dummy1) == tag2)
	{
	    if(tagof(dummy1) == tag3)
	    {
	        if(param3 == -729)
	            return PLE_list_insert2(listid, INSERT_TYPE_SINGLE_ELEMENT, param1, native_param:param2, native_param:0);
	        else
				return PLE_list_insert2(listid, INSERT_TYPE_FILL, param1, native_param:param2, native_param:param3);
	    }
	}
	else if(tagof(dummy2) == tag2 && tagof(dummy2) == tag3)
	    return PLE_list_insert2(listid, INSERT_TYPE_RANGE, param1, native_param:param2, native_param:param3);
	    
	print("[ERROR] Standard Library Extension: Unknown Overload for list insertion");
	return INVALID_ITERATOR_ID;
}
/*****************************************************************************************************************/
native bool:operator==(list:oper1, list:oper2) = PLE_list_equal;
native bool:operator>(list:oper1, list:oper2) = PLE_list_greater_than;
native bool:operator<(list:oper1, list:oper2) = PLE_list_lesser_than;

stock bool:operator>=(list:oper1, list:oper2)
{
	return PLE_list_lesser_than(oper2, oper1);
}
stock bool:operator<=(list:oper1, list:oper2)
{
    return PLE_list_greater_than(oper2, oper1);
}
stock bool:operator!=(list:oper1, list:oper2)
{
	return !PLE_list_equal(oper1, oper2);
}
/*****************************************************************************************************************/
/**************************************************/
/* Compare two integers. If the two elements are equal, return 0.
   If the first argument is greater than the second argument, return 1,
   If the first argument is less than the second argument, return -1. */
//native floatcmp(Float:oper1, Float:oper2);
/**************************************************/
//Only overloads of few cases have been added which appear to be common
//Someone might try to add 5 to an iterator in an attempt to advance the iterator by 5
//But no one would try to multiply an iterator so an overload to take care of multiplication does not exist
//Of course, an idiot could try it and he will end up corrupting the iterator.

native literator:PLE_list_begin(list:listid, dummy);
native literator:PLE_list_end(list:listid, dummy);
native literator:PLE_list_iter_copy(native_param:itr);
native PLE_list_iterator_advance(native_param:itr, steps);
native bool:PLE_list_iterator_equal(native_param:itr1, native_param:itr2);
native PLE_list_iterator_distance(native_param:itr1, native_param:itr2);
native PLE_list_itr_dereference(native_param:itr);
 
forward literator:operator+(literator:oper1, literator:oper2);
forward literator:operator+(literator:oper1, oper2);
forward literator:operator+(oper1, literator:oper2);
forward literator:operator-(literator:oper1, literator:oper2);
forward literator:operator-(literator:oper1, oper2);
forward literator:operator-(oper1, literator:oper2);
forward literator:operator*(literator:oper1, literator:oper2);
forward literator:operator*(literator:oper1, oper2);
forward literator:operator*(oper1, literator:oper2);
forward literator:operator/(literator:oper1, literator:oper2);
forward literator:operator/(literator:oper1, oper2);
forward literator:operator/(oper1, literator:oper2);
forward literator:operator%(literator:oper1, literator:oper2);
forward literator:operator%(literator:oper1, oper2);
forward literator:operator%(oper1, literator:oper2);
forward literator:operator=(oper);
forward bool:operator!(literator:oper);
forward bool:operator>(literator:oper1, literator:oper2);
forward bool:operator<(literator:oper1, literator:oper2);
forward bool:operator>=(literator:oper1, literator:oper2);
forward bool:operator<=(literator:oper1, literator:oper2);

native literator:operator=(literator:oper) = PLE_list_iter_copy;
stock literator:operator++(literator:oper)
{
	PLE_list_iterator_advance(native_param:oper, 1);
    return oper;
}
stock literator:operator--(literator:oper)
{
	PLE_list_iterator_advance(native_param:oper, -1);
    return oper;
 }
stock bool:operator==(literator:oper1, literator:oper2)
    return PLE_list_iterator_equal(native_param:oper1, native_param:oper2);
stock bool:operator!=(literator:oper1, literator:oper2)
    return !PLE_list_iterator_equal(native_param:oper1, native_param:oper2);
    
