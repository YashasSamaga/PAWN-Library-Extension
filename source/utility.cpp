/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

utility.cpp
*************************************************************************************************************/
#pragma once

#include "main.h"
/************************************************************************************************************/
namespace Utility
{
	cell strcmp4b(const cell* s1, const cell* s2) //strcmp for PAWN strings; takes two PAWN strings instead of C strings
	{
		while (*s1 && (*s1 == *s2))
		{
			s1++;
			s2++;
		}
		return *s1 - *s2;
	}
}