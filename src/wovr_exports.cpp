// HACK: No idea where this should actually be defined
#define nullptr 0x0
#include "openvr.h"
using namespace vr;

#include <cstdio>
#include <cstring>

#include "proxy_getters.h"

/* Interface dispatcher. Try to acquire the native impl, then create and return our proxy. */
VR_INTERFACE void *VR_CALLTYPE WOVR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
    printf("WOVR info: App requested API version %s\n", pchInterfaceVersion);

    void* ntv = VR_GetGenericInterface(pchInterfaceVersion, peError);
    // XXX: Should we check for error and return early?

    // I'm not terribly worried about leaking proxy objects, as there'll only be a half dozen or so of these ever
    // created in any sane case.
    if( strstr(pchInterfaceVersion, "IVRSystem") != 0 )
        return getIVRSystemProxy( (IVRSystem*) ntv );

    if( strstr(pchInterfaceVersion, "IVRApplications") != 0 )
        return getIVRApplicationsProxy( (IVRApplications*) ntv );

    if( strstr(pchInterfaceVersion, "IVRCompositor") != 0 )
        return getIVRCompositorProxy( (IVRCompositor*) ntv );

    if( strstr(pchInterfaceVersion, "IVRRenderModels") != 0 )
        return getIVRRenderModelsProxy( (IVRRenderModels*) ntv );

    /* TODO: NIYs
    if( strstr(pchInterfaceVersion, "IVRSettings") != 0 )
        return getIVRSettingsProxy( (IVRSettings*) ntv );

    if( strstr(pchInterfaceVersion, "IVRChaperone") != 0 )
        return getIVRChaperoneProxy( (IVRChaperone*) ntv );

    if( strstr(pchInterfaceVersion, "IVRChaperoneSetup") != 0 )
        return getIVRChaperoneSetupProxy( (IVRChaperoneSetup*) ntv );

    if( strstr(pchInterfaceVersion, "IVRNotifications") != 0 )
        return getIVRNotificationsProxy( (IVRNotifications*) ntv );

    if( strstr(pchInterfaceVersion, "IVROverlay") != 0 )
        return getIVROverlayProxy( (IVROverlay*) ntv );

    if( strstr(pchInterfaceVersion, "IVRExtendedDisplay") != 0 )
        return getIVRExtendedDisplayProxy( (IVRExtendedDisplay*) ntv );

    if( strstr(pchInterfaceVersion, "IVRTrackedCamera") != 0 )
        return getIVRTrackedCameraProxy( (IVRTrackedCamera*) ntv );

    if( strstr(pchInterfaceVersion, "IVRScreenshots") != 0 )
        return getIVRScreenshotsProxy( (IVRScreenshots*) ntv );

    if( strstr(pchInterfaceVersion, "IVRResources") != 0 )
        return getIVRResourcesProxy( (IVRResources*) ntv );
    */

    // Fallthrough for NIYs
    printf("WOVR WARNING: App requested unimplemented interface!\n");
    // Pretend to work but let the app segfault if it tries to use it.
    // This is better for debugging because the samples try to load interfaces early and are overzealous about error
    // checking.
    return (void*) 0x1;
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
  printf("WOVR info: App requested version %s\n", pchInterfaceVersion);
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
