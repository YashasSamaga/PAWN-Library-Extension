/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

STL Lists for PAWN
list.h

*************************************************************************************************************/
#pragma once

#include "main.h"

#include <list>
/************************************************************************************************************/
#define INVALID_LIST_ID -1
/************************************************************************************************************/
class PawnList
{
public:
	std::list<cell> container;
	PawnList() { listid = INVALID_LIST_ID; }

	void Initilize(cell id, cell tagid)
	{
		this->listid = id;
		this->tagid = tagid;
		container.clear();
	}
	void Reset()
	{
		listid = INVALID_LIST_ID;
	}
	bool IsUnused() const
	{
		return (listid == INVALID_LIST_ID);
	}
	cell GetTagID() const
	{
		return this->tagid;
	}

private:
	cell listid;
	cell tagid;
};
/************************************************************************************************************/
namespace Natives
{
	
}