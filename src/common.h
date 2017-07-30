#pragma once

#include <cstdio>
#include <cstdarg>

// Info utility functions/macros

// Anything that might be even remotely useful
inline void wovr_trace(const char* fmt, ...)
{
	printf("WOVR trace: "); // No newline

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}
#define _TRACE(fmt, fn, ...) wovr_trace(#fn fmt, ##__VA_ARGS__ )
#define TRACE(fmt, ...) _TRACE(fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__ )
// Print only once. Use for performance-critical methods i.e. IVRCompositor::Submit
#define _TRACEHOT(fmt, fn, ...) \
	{ static bool tracehot_fired = false; if(!tracehot_fired) { _TRACE( fmt, fn, ##__VA_ARGS__ ); tracehot_fired = true; } }
#define TRACEHOT(fmt, ...) _TRACEHOT(fmt, __PRETTY_FUNCTION__, #__VA_ARGS__ )

// Things likely to be useful in the general case
inline void wovr_info(const char* fmt, ...)
{
	printf("WOVR info: ");

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}
#define _INFO(fmt, fn, ...) wovr_info( #fn fmt, ##__VA_ARGS__ )
#define INFO(fmt, ...) _INFO( fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__ )

// Might make the application crash or behave strangely
inline void wovr_warn(const char* fmt, ...)
{
	printf("WOVR WARNING: "); // No newline

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}
#define _WARN(fmt, fn, ...) wovr_warn( #fn fmt, ##__VA_ARGS__ )
#define WARN(fmt, ...) _WARN( fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__ )

// WILL make the application crash
inline void wovr_err(const char* fmt, ...)
{
	// This needs to stand out.
	printf("################################################################################\n\n");
	printf("WOVR ERROR: "); // No newline

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n\n################################################################################\n");
}
#define _ERR(fmt, fn, ...) wovr_err( #fn fmt, ##__VA_ARGS__ )
#define ERR(fmt, ...) _ERR( fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__ )

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
