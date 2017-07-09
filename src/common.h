#pragma once

#include <cstdio>

// HACK: No idea where this should actually be defined
#define nullptr 0x0
// If _WIN32 is defined, openvr.h will decorate the exported functions with __declspec(dllimport) which implies
// __attribute__((ms_abi)). This makes things explode, as we need to call them with SysV ABI.
#undef _WIN32
#include "openvr.h"
using namespace vr;

#ifdef __x86_64__
// MS instead of SysV ABI for 64bit
#define WOVR_ENTRY __attribute__((ms_abi))
#else
// Thispointer-in-ECX for 32bit
#define WOVR_ENTRY __attribute__((force_align_arg_pointer,thiscall))
#endif
