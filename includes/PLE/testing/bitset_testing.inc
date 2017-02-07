/*****************************************************************************************************************
PAWN Library Extension

Bitset Testing
bitset.inc
******************************************************************************************************************/
#if defined _PLE_BITSETT_INC
	#endinput
#else
	#define _PLE_BITSETT_INC
#endif

#if !defined _PLE_CONFIG_INC
	#include <PLE/config>
#endif
/*****************************************************************************************************************/
#include <PLE/bitset>

static _count = 0;
forward bitset_testing_func1(bitpos);
public bitset_testing_func1(bitpos)
{
	_count++;
	return 0;
}

stock bitset_inc_test()
{
	new bitset:b1<50>, bitset:b2<50>, bitset:b3<50>;
	new str[60];

	for(new i = 0; i < 50; i += 5)
		bitset_set(b1, i);

	if(_:b1[2] != 0b00010000100001000) print("[TEST1] bitset_set failed.");

	bitset_tostring(b1, str);
	if(strcmp(str, "10000100001000010000100001000010000100001000010000")) print("[TEST2] bitset_tostring failed.");

	if(bitset_count(b1) != 10) print("[TEST3] bitset_count failed.");

	if(bitset_size(b1) != 50) print("[TEST4] bitset_size failed.");

	if(bitset_any(b1) == false) print("[TEST5] bitset_any failed.");
	if(bitset_all(b1) == true) print("[TEST6] bitset_all failed.");
	if(bitset_none(b1) == true) print("[TEST7] bitset_none failed.");

	if(bitset_any(b2) == true) print("[TEST8] bitset_any failed.");
	if(bitset_all(b2) == true) print("[TEST9] bitset_all failed.");
	if(bitset_none(b2) == false) print("[TEST10] bitset_none failed.");

	if(bitset_test(b2, 0) == false) print("[TEST11] bitset_test failed.");
	if(bitset_test(b2, 1) == true) print("[TEST12] bitset_test failed.");

	bitset_reset(b1, 0);
	bitset_flip(b1, 1);

	bitset_tostring(b1, str);
	if(str[0] != '0') print("[TEST13] bitset_reset failed.");
	if(str[1] != '1') print("[TEST14] bitset_flip failed.");

	new str2[60];
	bitset_and(b1, b1, b3);
	bitset_tostring(b3, str2);
	if(strcmp(str, str2)) print("[TEST15] bitset_and failed.");

	if(!bitset_equal(b1, b3)) print("[TEST16] bitset_equal failed.");
	
	bitset_xor(b3, b3, b3);
	if(bitset_none(b3) == false) print("[TEST16] bitset_xor failed.");

	new function:myfunc<cell(cell)>;
	make_function(myfunc, "bitset_testing_func1", 1);

	_count = 0;
	bitset_foreach_set(b1, myfunc);
	if(_count != bitset_count(b1)) print("[TEST17] bitset_foreach_set failed.");

	_count = 0;
	bitset_foreach_notset(b1, myfunc);
	if(_count != (bitset_size(b1) - bitset_count(b1))) print("[TEST16] bitset_foreach_notset failed.");

	new idx = 0;
	if(!bitset_find_set(b1, idx) || idx != 1) print("[TEST17] bitset_find_set failed.");

	idx = 7;
	if(!bitset_find_set(b1, idx) || idx != 10) print("[TEST18] bitset_find_set failed.");

	idx = 0;
	if(!bitset_find_notset(b1, idx) || idx != 0) print("[TEST19] bitset_find_notset failed.");

	idx = 7;
	if(!bitset_find_notset(b1, idx) || idx != 7) print("[TEST20] bitset_find_notset failed.");
}
