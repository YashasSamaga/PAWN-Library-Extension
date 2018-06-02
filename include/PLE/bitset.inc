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

#if defined PLE_BITSET_INCLUDED
	#endinput
#endif
#define PLE_BITSET_INCLUDED

/* dependencies */
#include <PLE/config>
#include <PLE/functional>

#define bitset:%0<%1> bitset:%0[%1/cellbits + 2]={bitset:%1}

forward operator=(bitset:x);
forward bitset:operator=(x);
forward bitset:operator=(bitset:x);

forward bool:operator!(bitset:x);

forward bitset:operator-(bitset:x);
forward bitset:operator++(bitset:x);
forward bitset:operator--(bitset:x);

forward bitset:operator+(bitset:x, bitset:y);
forward bitset:operator+(bitset:x, y);

forward bitset:operator-(bitset:x, bitset:y);
forward bitset:operator-(x, bitset:y);
forward bitset:operator-(bitset:x, y);

forward bitset:operator*(bitset:x, bitset:y);
forward bitset:operator*(bitset:x, y);

forward bitset:operator/(bitset:x, bitset:y);
forward bitset:operator/(x, bitset:y);
forward bitset:operator/(bitset:x, y);

forward bitset:operator%(bitset:x, bitset:y);
forward bitset:operator%(x, bitset:y);
forward bitset:operator%(bitset:x, y);

forward bool:operator<(bitset:x, bitset:y);
forward bool:operator<(x, bitset:y);
forward bool:operator<(bitset:x, y);
forward bool:operator<=(x, bitset:y);
forward bool:operator<=(bitset:x, y);
forward bool:operator<=(bitset:x, bitset:y);

forward bool:operator>(bitset:x, bitset:y);
forward bool:operator>(x, bitset:y);
forward bool:operator>(bitset:x, y);
forward bool:operator>=(x, bitset:y);
forward bool:operator>=(bitset:x, bitset:y);
forward bool:operator>=(bitset:x, y);

forward bool:operator==(bitset:x, bitset:y);
forward bool:operator==(bitset:x, y);
forward bool:operator!=(bitset:x, bitset:y);
forward bool:operator!=(bitset:x, y);

native bool:bitset_test(const bitset:bs[], bitpos);
native bool:bitset_any(const bitset:bs[]);
native bool:bitset_none(const bitset:bs[]);
native bool:bitset_all(const bitset:bs[]);

native bitset_count(const bitset:bs[]);
native bitset_size(const bitset:bs[]);

native bool:bitset_set(bitset:bs[], bitpos);
native bool:bitset_reset(bitset:bs[], bitpos);
native bool:bitset_flip(bitset:bs[], bitpos);
native noret:bitset_set_all(bitset:bs[]);
native noret:bitset_reset_all(bitset:bs[]);
native noret:bitset_flip_all(bitset:bs[]);
native noret:bitset_and(const bitset:bs1[], const bitset:bs2[], bitset:dest[]);
native noret:bitset_or(const bitset:bs1[], const bitset:bs2[], bitset:dest[]);
native noret:bitset_xor(const bitset:bs1[], const bitset:bs2[], bitset:dest[]);

native noret:bitset_tostring(const bitset:bs[], dest[], dest_size = sizeof(dest));
native bool:bitset_equal(const bitset:bs1[], const bitset:bs2[]);

//hash specialization not implemented

native noret:bitset_foreach_set(const bitset:bs[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native noret:bitset_foreach_notset(const bitset:bs[], const {_, func_bool1, func_cell1}:func[FTSIZE]);
native bool:bitset_find_set(const bitset:bs[], &start_bitpos);
native bool:bitset_find_notset(const bitset:bs[], &start_bitpos);
