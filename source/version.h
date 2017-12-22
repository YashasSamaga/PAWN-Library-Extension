/************************************************************************************************************
PAWN Library Extension

version.h

*************************************************************************************************************/
#ifndef PLE_VERSION_H_INCLUDED
#define PLE_VERSION_H_INCLUDED

#include <cstdint>

#if !defined(PLUGIN_MAJOR_VERSION) || !defined(PLUGIN_MINOR_VERSION) || !defined(PLUGIN_PATCH_VERSION)
#error "Plugin version not defined"
#endif

constexpr std::uint32_t PLE_PLUGIN_VERSION_KEY = PLUGIN_MAJOR_VERSION << 24 | PLUGIN_MINOR_VERSION << 16 | PLUGIN_PATCH_VERSION << 8; 

#endif /* PLE_VERSION_H_INCLUDED */