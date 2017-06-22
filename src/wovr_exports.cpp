#include "common.h"
#include "proxy_getters.h"
#include <cstring>

/* Interface dispatcher. Try to acquire the native impl, then create and return our proxy. */
extern "C" void *VR_CALLTYPE WOVR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
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

    if( strstr(pchInterfaceVersion, "IVRSettings") != 0 )
        return getIVRSettingsProxy( (IVRSettings*) ntv );

    if( strstr(pchInterfaceVersion, "IVRChaperone") != 0 )
        return getIVRChaperoneProxy( (IVRChaperone*) ntv );

    if( strstr(pchInterfaceVersion, "IVRChaperoneSetup") != 0 )
        return getIVRChaperoneSetupProxy( (IVRChaperoneSetup*) ntv );

    if( strstr(pchInterfaceVersion, "IVRCompositor") != 0 )
        return getIVRCompositorProxy( (IVRCompositor*) ntv );

    if( strstr(pchInterfaceVersion, "IVRNotifications") != 0 )
        return getIVRNotificationsProxy( (IVRNotifications*) ntv );

    if( strstr(pchInterfaceVersion, "IVRRenderModels") != 0 )
        return getIVRRenderModelsProxy( (IVRRenderModels*) ntv );

    /* TODO: NIYs
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

extern "C" uint32_t VR_CALLTYPE WOVR_GetInitToken()
{
  return VR_GetInitToken();
}

extern "C" const char *VR_CALLTYPE WOVR_GetVRInitErrorAsEnglishDescription(EVRInitError error)
{
  return VR_GetVRInitErrorAsEnglishDescription(error);
}

extern "C" const char *VR_CALLTYPE WOVR_GetVRInitErrorAsSymbol(EVRInitError error)
{
  return VR_GetVRInitErrorAsSymbol(error);
}

extern "C" uint32_t VR_CALLTYPE WOVR_InitInternal(EVRInitError *peError, EVRApplicationType eApplicationType)
{
  return VR_InitInternal(peError, eApplicationType);
}

extern "C" bool VR_CALLTYPE WOVR_IsHmdPresent()
{
  return VR_IsHmdPresent();
}

extern "C" bool VR_CALLTYPE WOVR_IsInterfaceVersionValid(const char *pchInterfaceVersion)
{
  printf("WOVR info: App requested version %s\n", pchInterfaceVersion);
  return VR_IsInterfaceVersionValid(pchInterfaceVersion);
}

extern "C" bool VR_CALLTYPE WOVR_IsRuntimeInstalled()
{
  return VR_IsRuntimeInstalled();
}

extern "C" const char *VR_CALLTYPE WOVR_RuntimePath()
{
  // FIXME: This should convert to a Wndows X:\\ type path before returning
  return VR_RuntimePath();
}

extern "C" void VR_CALLTYPE WOVR_ShutdownInternal()
{
  VR_ShutdownInternal();
}
