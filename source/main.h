/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

main.h

*************************************************************************************************************/
#pragma once
#pragma warning(disable : 4996)

#include "lib/sdk/amx/amx.h"
#include "lib/sdk/plugincommon.h"
/***********************************************************************************************/
#define PLE_MAGIC_KEY 0x3A7B8C
#define PLE_PLUGIN_VERSION_KEY 0xAB000001

#define PLUGIN_MAJOR_VERSION 1
#define PLUGIN_MINOR_VERSION 0
#define PLUGIN_PATCH_VERSION 0
/***********************************************************************************************/
typedef void(*logprintf_t)(char *, ...);
extern logprintf_t logprintf;


#define MAX_FUNC_NAME 32

#define BYTES_PER_CELL 4
#define BITS_PER_CELL (BYTES_PER_CELL*8)

#define warn_if(x,...) if(x) logprintf(__VA_ARGS__), 0; 
#define error_if(x,...) if(x) return logprintf(__VA_ARGS__), 0; 
#define check_params(n) (params[0] == n*BYTES_PER_CELL)
