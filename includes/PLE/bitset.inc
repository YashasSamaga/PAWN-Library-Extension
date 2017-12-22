/*
** PAWN Library Extension (PLE)
**
** Bitset
** Library to manipulate bitsets
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

#if defined PLE_BITSET_INCLUDED
	#endinput
#endif
#define PLE_BITSET_INCLUDED

/* dependencies */
#include <PLE/config>
#include <PLE/functional>

#define bitset:%0<%1> bitset:%0[%1/cellbits + 2]={bitset:%1}

forward bitset:operator-(bitset:x);
forward bitset:operator++(bitset:x);
forward bitset:operator--(bitset:x);

forward bitset:operator=(bitset:x);
forward bitset:operator=(x);
forward operator=(bitset:x);

forward bool:operator!(bitset:x);

forward bitset:operator+(bitset:x, bitset:y);
forward bitset:operator-(bitset:x, bitset:y);
forward bitset:operator*(bitset:x, bitset:y);
forward bitset:operator/(bitset:x, bitset:y);
forward bitset:operator%(bitset:x, bitset:y);

forward bitset:operator+(x, bitset:y);
forward bitset:operator-(x, bitset:y);
forward bitset:operator*(x, bitset:y);
forward bitset:operator/(x, bitset:y);
forward bitset:operator%(x, bitset:y);

forward bitset:operator+(bitset:x, y);
forward bitset:operator-(bitset:x, y);
forward bitset:operator*(bitset:x, y);
forward bitset:operator/(bitset:x, y);
forward bitset:operator%(bitset:x, y);

forward bool:operator==(bitset:x, bitset:y);
forward bool:operator!=(bitset:x, bitset:y);
forward bool:operator<(bitset:x, bitset:y);
forward bool:operator>(bitset:x, bitset:y);
forward bool:operator<=(bitset:x, bitset:y);
forward bool:operator>=(bitset:x, bitset:y);

forward bool:operator==(x, bitset:y);
forward bool:operator!=(x, bitset:y);
forward bool:operator<(x, bitset:y);
forward bool:operator>(x, bitset:y);
forward bool:operator<=(x, bitset:y);
forward bool:operator>=(x, bitset:y);

forward bool:operator==(bitset:x, y);
forward bool:operator!=(bitset:x, y);
forward bool:operator<(bitset:x, y);
forward bool:operator>(bitset:x, y);
forward bool:operator<=(bitset:x, y);
forward bool:operator>=(bitset:x, y);

native bitset_count(bitset:bs[]);
native bitset_size(bitset:bs[]);
native bool:bitset_test(bitset:bs[], bitpos);
native bool:bitset_any(bitset:bs[]);
native bool:bitset_none(bitset:bs[]);
native bool:bitset_all(bitset:bs[]);

native bool:bitset_set(bitset:bs[], bitpos);
native bool:bitset_reset(bitset:bs[], bitpos);
native bool:bitset_flip(bitset:bs[], bitpos);

native noret:bitset_set_all(bitset:bs[]);
native noret:bitset_reset_all(bitset:bs[]);
native noret:bitset_flip_all(bitset:bs[]);

native noret:bitset_tostring(bitset:bs[], dest[], dest_size = sizeof(dest));

native noret:bitset_and(bitset:bs1[], bitset:bs2[], bitset:dest[]);
native noret:bitset_or(bitset:bs1[], bitset:bs2[], bitset:dest[]);
native noret:bitset_xor(bitset:bs1[], bitset:bs2[], bitset:dest[]);

native bool:bitset_equal(bitset:bs1[], bitset:bs2[]);

//hash specialization not implemented

//bonus natives
native noret:bitset_foreach_set(bitset:bs[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:bitset_foreach_notset(bitset:bs[], {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:bitset_find_set(bitset:bs[], &start_bitpos);
native bool:bitset_find_notset(bitset:bs[], &start_bitpos);
