/************************************************************************************************************
PAWN Library Extension

PLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, PLE is not an arbitary
collection of libaries for PAWN.

main.h

*************************************************************************************************************/
#pragma once
#pragma warning(disable : 4996)

#include "..\lib\sdk\amx\amx.h"
#include "..\lib\sdk\plugincommon.h"
/***********************************************************************************************/
#define PLUGIN_INCLUDE_KEY 0x3A7B8C

#define PLUGIN_MAJOR_VERSION 1
#define PLUGIN_MINOR_VERSION 0
#define PLUGIN_PATCH_VERSION 0
/***********************************************************************************************/
typedef void(*logprintf_t)(char *, ...);
extern logprintf_t logprintf;