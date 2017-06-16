/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" Standard C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of C++ libaries for PAWN.

Memory Management
memory.cpp

*************************************************************************************************************/
#include "main.h"
#include "math.h"

#include <memory>
#include <list>
/************************************************************************************************************/
class MemoryManager
{
public:
	AMX * amx;
	int ScriptKey;
private:
	struct block
	{
		cell *amx_ptr_addr;
		cell *amx_addr;
		cell cells;
	};
	std::list<block> free_blocks16;
	std::list<block> free_blocks32;
	std::list<block> free_blocks64;
	std::list<block> free_blocks128;
	std::list<block> used_blocks;
};

namespace Natives
{		

}	
	
	
	

	
	
