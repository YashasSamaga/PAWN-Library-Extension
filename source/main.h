/************************************************************************************************************
PAWN Library Extension

main.h

*************************************************************************************************************/
#ifndef PLE_MAIN_H_INCLUDED
#define PLE_MAIN_H_INCLUDED

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>
#include <samplog/PluginLogger.h>

typedef void(*logprintf_t)(char *, ...);
extern logprintf_t logprintf;

extern samplog::CPluginLogger logger;
using LogLevel = samplog::LogLevel;

#define PLE_PLUGIN_VERSION_KEY 0x0001

#define PLUGIN_MAJOR_VERSION 1
#define PLUGIN_MINOR_VERSION 0
#define PLUGIN_PATCH_VERSION 0

#define MAX_SYMBOL_LEN sNAMEMAX + 1

#define BYTES_PER_CELL PAWN_CELL_SIZE/8
#define BITS_PER_CELL (BYTES_PER_CELL*8)

#define warn_if(x,...) if(x) logprintf(__VA_ARGS__), 0
#define error_if(x,...) if(x) return logprintf(__VA_ARGS__), 0

#define check_params(n) (params[0] == n*BYTES_PER_CELL)
#define check_params_min(n) (params[0] >= n*BYTES_PER_CELL)
#define get_params_count() (params[0]/(BYTES_PER_CELL))

#endif /* PLE_MAIN_H_INCLUDED */