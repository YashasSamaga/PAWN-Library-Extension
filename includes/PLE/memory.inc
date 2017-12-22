/******************************************************************************************************************
PAWN Library Extension

memory.inc
******************************************************************************************************************/
#if defined _PLE_MEMORY_INC
	#endinput
#else
	#define _PLE_MEMORY_INC
#endif
/*****************************************************************************************************************/
#if defined DYNAMIC_MEMORY_SIZE
	#if DYNAMIC_MEMORY_SIZE < 0
		#error "DYNAMIC_MEMORY_SIZE must be greater than zero."
	#endif
#else
	#define DYNAMIC_MEMORY_SIZE 1048576
#endif

#pragma dynamic DYNAMIC_MEMORY_SIZE
