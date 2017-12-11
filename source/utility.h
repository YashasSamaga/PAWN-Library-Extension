/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

utility.h

*************************************************************************************************************/
#ifndef PLE_UTILITY_H_INCLUDED
#define PLE_UTILITY_H_INCLUDED

#include "main.h"

namespace Utility
{
	extern cell strcmp4b(const cell* s1, const cell* s2);
};

#endif /* PLE_UTILITY_H_INCLUDED */