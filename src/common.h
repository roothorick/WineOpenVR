#pragma once

#include <cstdio>

// HACK: No idea where this should actually be defined
#define nullptr 0x0
#pragma GCC diagnostic ignored "-Wattributes"
#include "openvr.h"
#pragma GCC diagnostic warning "-Wattributes"
using namespace vr;

#ifdef __x86_64__
// MS instead of SysV ABI for 64bit
#define WOVR_ENTRY __attribute__((ms_abi))
#else
// Thispointer-in-ECX for 32bit
#define WOVR_ENTRY __attribute__((thiscall))
#endif
