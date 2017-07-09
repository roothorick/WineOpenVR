#include "common.h"
#include "proxy_getters.h"
#include <cstring>

#ifdef __x86_64__
#define WOVR_EXPORT extern "C" __attribute__((ms_abi))
#else
#define WOVR_EXPORT extern "C"
#endif

/* Interface dispatcher. Try to acquire the native impl, then create and return our proxy. */
WOVR_EXPORT void * WOVR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
	printf("WOVR info: App requested API version %s\n", pchInterfaceVersion);

	// I'm not terribly worried about leaking proxy objects, as there'll only be a half dozen or so of these ever
	// created in any sane case.

	// IVRSystem
	if( strcmp(pchInterfaceVersion, "IVRSystem_016") != 0 )
		return getIVRSystemProxy_016();

	// IVRApplications
	if( strcmp(pchInterfaceVersion, "IVRApplications_006") != 0)
		return getIVRApplicationsProxy_006();

	// Not yet converted to ABI-switching system
	void* ntv = VR_GetGenericInterface(pchInterfaceVersion, peError);

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

	if( strstr(pchInterfaceVersion, "IVROverlay") != 0 )
		return getIVROverlayProxy( (IVROverlay*) ntv );

	if( strstr(pchInterfaceVersion, "IVRRenderModels") != 0 )
		return getIVRRenderModelsProxy( (IVRRenderModels*) ntv );

	if( strstr(pchInterfaceVersion, "IVRExtendedDisplay") != 0 )
		return getIVRExtendedDisplayProxy( (IVRExtendedDisplay*) ntv );

	if( strstr(pchInterfaceVersion, "IVRTrackedCamera") != 0 )
		return getIVRTrackedCameraProxy( (IVRTrackedCamera*) ntv );

	if( strstr(pchInterfaceVersion, "IVRScreenshots") != 0 )
		return getIVRScreenshotsProxy( (IVRScreenshots*) ntv );

	if( strstr(pchInterfaceVersion, "IVRResources") != 0 )
		return getIVRResourcesProxy( (IVRResources*) ntv );

	// Fallthrough for unknowns
	printf("WOVR WARNING: App requested unknown interface!\n");

	// Passing the native interface directly will cause cryptic crashes due to calling convention differences.
	// Fail now and give the app a chance to do without.
	*peError = VRInitError_Init_InvalidInterface;
	return NULL;
}

WOVR_EXPORT uint32_t  WOVR_GetInitToken()
{
	return VR_GetInitToken();
}

WOVR_EXPORT const char * WOVR_GetVRInitErrorAsEnglishDescription(EVRInitError error)
{
	return VR_GetVRInitErrorAsEnglishDescription(error);
}

WOVR_EXPORT const char * WOVR_GetVRInitErrorAsSymbol(EVRInitError error)
{
	return VR_GetVRInitErrorAsSymbol(error);
}

WOVR_EXPORT uint32_t  WOVR_InitInternal(EVRInitError *peError, EVRApplicationType eApplicationType)
{
	// printf("c\n");
	return VR_InitInternal(peError, eApplicationType);
}

WOVR_EXPORT bool  WOVR_IsHmdPresent()
{
	return VR_IsHmdPresent();
}

WOVR_EXPORT bool  WOVR_IsInterfaceVersionValid(const char *pchInterfaceVersion)
{
	printf("WOVR info: App requested version %s\n", pchInterfaceVersion);
	return VR_IsInterfaceVersionValid(pchInterfaceVersion);
}

WOVR_EXPORT bool  WOVR_IsRuntimeInstalled()
{
	return VR_IsRuntimeInstalled();
}

WOVR_EXPORT const char * WOVR_RuntimePath()
{
	// FIXME: This should convert to a Wndows X:\\ type path before returning
	return VR_RuntimePath();
}

WOVR_EXPORT void  WOVR_ShutdownInternal()
{
	VR_ShutdownInternal();
}
