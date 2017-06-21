#pragma once

#include <cstdio>

// HACK: No idea where this should actually be defined
#define nullptr 0x0
#pragma GCC diagnostic ignored "-Wattributes"
#include "openvr.h"
#pragma GCC diagnostic warning "-Wattributes"
using namespace vr;

// Thispointer-in-ECX for 32bit
#define THISCALL __attribute__((thiscall))
// MS instead of SysV ABI for 64bit
#define MSABI __attribute__((ms_abi))
