#pragma once

#include <cstdio>
#include "openvr.h"

VR_INTERFACE void *VR_CALLTYPE WOVR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
  printf("WOVR info: App requested API version %s\n", pchInterfaceVersion);
  return VR_GetGenericInterface(pchInterfaceVersion, peError);
}

VR_INTERFACE uint32_t VR_CALLTYPE WOVR_GetInitToken()
{
  return VR_GetInitToken();
}

VR_INTERFACE const char *VR_CALLTYPE WOVR_GetVRInitErrorAsEnglishDescription(EVRInitError error)
{
  return VR_GetVRInitErrorAsEnglishDescription(error);
}

VR_INTERFACE const char*VR_CALLTYPE WOVR_GetVRInitErrorAsSymbol(EVRInitError error)
{
  return VR_GetVRInitErrorAsSymbol(error);
}

VR_INTERFACE uint32_t VR_CALLTYPE WOVR_InitInternal(EVRInitError *peError, EVRApplicationType eApplicationType)
{
  return VR_InitInternal(peError, eApplicationType);
}

VR_INTERFACE bool VR_CALLTYPE WOVR_IsHmdPresent()
{
  return VR_IsHmdPresent();
}

VR_INTERFACE bool VR_CALLTYPE WOVR_IsInterfaceVersionValid(const char *pchInterfaceVersion)
{
  printf("WOVR info: App requested version %s\n", pchInterfaceVersion)
  return VR_IsInterfaceVersionValid(pchInterfaceVersion);
}

VR_INTERFACE bool VR_CALLTYPE WOVR_IsRuntimeInstalled()
{
  return VR_IsRuntimeInstalled();
}

VR_INTERFACE const char *VR_CALLTYPE WOVR_RuntimePath()
{
  // FIXME: This should convert to a Wndows X:\\ type path before returning
  return VR_RuntimePath();
}

VR_INTERFACE void VR_CALLTYPE WOVR_ShutdownInternal()
{
  VR_ShutdownInternal();
}
