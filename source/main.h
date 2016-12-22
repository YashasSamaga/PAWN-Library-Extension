/************************************************************************************************************
Standard Library Extension

SLE attempts to provide most of the "useful" C++ Libraries in PAWN. The term "useful" here implies that only
the libraries which have potential uses in PAWN have been ported. In other words, SLE is not an arbitary
collection of libaries for PAWN.

main.h

*************************************************************************************************************/
#pragma once

#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

#include <vector>
/***********************************************************************************************/
#define PLUGIN_INCLUDE_KEY 0x3A7B8C

#define PLUGIN_MAJOR_VERSION 1
#define PLUGIN_MINOR_VERSION 0
#define PLUGIN_PATCH_VERSION 0
/***********************************************************************************************/
class Interface;
extern std::vector <Interface *> InterfaceList;

typedef void(*logprintf_t)(char *, ...);
extern logprintf_t logprintf;