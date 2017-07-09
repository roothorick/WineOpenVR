#include "common.h"
#include <cstring>

#ifdef __x86_64__
#define WOVR_EXPORT extern "C" __attribute__((ms_abi))
#else
#define WOVR_EXPORT extern "C"
#endif

// These are all defined in their respective ivrxxx_xxx.cpp's
vr::IVRSystem* getIVRSystemProxy_010();
vr::IVRSystem* getIVRSystemProxy_011();
vr::IVRSystem* getIVRSystemProxy_012();
vr::IVRSystem* getIVRSystemProxy_014();
vr::IVRSystem* getIVRSystemProxy_015();
vr::IVRSystem* getIVRSystemProxy_016();

vr::IVRApplications* getIVRApplicationsProxy_003();
vr::IVRApplications* getIVRApplicationsProxy_004();
vr::IVRApplications* getIVRApplicationsProxy_005();
vr::IVRApplications* getIVRApplicationsProxy_006();

vr::IVRSettings* getIVRSettingsProxy_001();
vr::IVRSettings* getIVRSettingsProxy_002();

vr::IVRChaperone* getIVRChaperoneProxy_003();

vr::IVRChaperoneSetup* getIVRChaperoneSetupProxy_005();

vr::IVRCompositor* getIVRCompositorProxy_011();
vr::IVRCompositor* getIVRCompositorProxy_012();
vr::IVRCompositor* getIVRCompositorProxy_013();
vr::IVRCompositor* getIVRCompositorProxy_014();
vr::IVRCompositor* getIVRCompositorProxy_015();
vr::IVRCompositor* getIVRCompositorProxy_016();
vr::IVRCompositor* getIVRCompositorProxy_018();
vr::IVRCompositor* getIVRCompositorProxy_019();
vr::IVRCompositor* getIVRCompositorProxy_020();

vr::IVRNotifications* getIVRNotificationsProxy_002();

vr::IVROverlay* getIVROverlayProxy_010();
vr::IVROverlay* getIVROverlayProxy_011();
vr::IVROverlay* getIVROverlayProxy_012();
vr::IVROverlay* getIVROverlayProxy_013();
vr::IVROverlay* getIVROverlayProxy_014();
vr::IVROverlay* getIVROverlayProxy_016();

vr::IVRRenderModels* getIVRRenderModelsProxy_002();
vr::IVRRenderModels* getIVRRenderModelsProxy_004();
vr::IVRRenderModels* getIVRRenderModelsProxy_005();

vr::IVRTrackedCamera* getIVRTrackedCameraProxy_002();
vr::IVRTrackedCamera* getIVRTrackedCameraProxy_003();

vr::IVRExtendedDisplay* getIVRExtendedDisplayProxy_001();

vr::IVRScreenshots* getIVRScreenshotsProxy_001();

vr::IVRResources* getIVRResourcesProxy_001();

vr::IVRDriverManager* getIVRDriverManagerProxy_001();

/* Interface dispatcher. Try to acquire the native impl, then create and return our proxy. */
WOVR_EXPORT void * WOVR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
	printf("WOVR info: App requested API version %s\n", pchInterfaceVersion);

	// I'm not terribly worried about leaking proxy objects, as there'll only be a half dozen or so of these ever
	// created in any sane case.

	if( strcmp(pchInterfaceVersion, "IVRSystem_010") != 0 )
		return getIVRSystemProxy_010();
	if( strcmp(pchInterfaceVersion, "IVRSystem_011") != 0 )
		return getIVRSystemProxy_011();
	if( strcmp(pchInterfaceVersion, "IVRSystem_012") != 0 )
		return getIVRSystemProxy_012();
	if( strcmp(pchInterfaceVersion, "IVRSystem_014") != 0 )
		return getIVRSystemProxy_014();
	if( strcmp(pchInterfaceVersion, "IVRSystem_015") != 0 )
		return getIVRSystemProxy_015();
	if( strcmp(pchInterfaceVersion, "IVRSystem_016") != 0 )
		return getIVRSystemProxy_016();

	if( strcmp(pchInterfaceVersion, "IVRApplications_003") != 0)
		return getIVRApplicationsProxy_003();
	if( strcmp(pchInterfaceVersion, "IVRApplications_004") != 0)
		return getIVRApplicationsProxy_004();
	if( strcmp(pchInterfaceVersion, "IVRApplications_005") != 0)
		return getIVRApplicationsProxy_005();
	if( strcmp(pchInterfaceVersion, "IVRApplications_006") != 0)
		return getIVRApplicationsProxy_006();

	if( strcmp(pchInterfaceVersion, "IVRSettings_001") != 0)
		return getIVRSettingsProxy_001();
	if( strcmp(pchInterfaceVersion, "IVRSettings_002") != 0)
		return getIVRSettingsProxy_002();

	if( strcmp(pchInterfaceVersion, "IVRChaperone_003") != 0)
		return getIVRChaperoneProxy_003();

	if( strcmp(pchInterfaceVersion, "IVRChaperoneSetup_005") != 0)
		return getIVRChaperoneSetupProxy_005();

	if( strcmp(pchInterfaceVersion, "IVRCompositor_011") != 0 )
		return getIVRCompositorProxy_011();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_012") != 0 )
		return getIVRCompositorProxy_012();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_013") != 0 )
		return getIVRCompositorProxy_013();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_014") != 0 )
		return getIVRCompositorProxy_014();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_015") != 0 )
		return getIVRCompositorProxy_015();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_016") != 0 )
		return getIVRCompositorProxy_016();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_018") != 0 )
		return getIVRCompositorProxy_018();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_019") != 0 )
		return getIVRCompositorProxy_019();
	if( strcmp(pchInterfaceVersion, "IVRCompositor_020") != 0 )
		return getIVRCompositorProxy_020();

	if( strcmp(pchInterfaceVersion, "IVRNotifications_002") != 0 )
		return getIVRNotificationsProxy_002();

	if( strcmp(pchInterfaceVersion, "IVROverlay_010") != 0 )
		return getIVROverlayProxy_011();
	if( strcmp(pchInterfaceVersion, "IVROverlay_011") != 0 )
		return getIVROverlayProxy_011();
	if( strcmp(pchInterfaceVersion, "IVROverlay_012") != 0 )
		return getIVROverlayProxy_012();
	if( strcmp(pchInterfaceVersion, "IVROverlay_013") != 0 )
		return getIVROverlayProxy_013();
	if( strcmp(pchInterfaceVersion, "IVROverlay_014") != 0 )
		return getIVROverlayProxy_014();
	if( strcmp(pchInterfaceVersion, "IVROverlay_016") != 0 )
		return getIVROverlayProxy_016();

	if( strcmp(pchInterfaceVersion, "IVRRenderModels_002") != 0 )
		return getIVRRenderModelsProxy_002();
	if( strcmp(pchInterfaceVersion, "IVRRenderModels_004") != 0 )
		return getIVRRenderModelsProxy_004();
	if( strcmp(pchInterfaceVersion, "IVRRenderModels_005") != 0 )
		return getIVRRenderModelsProxy_005();

	if( strcmp(pchInterfaceVersion, "IVRExtendedDisplay_001") != 0 )
		return getIVRExtendedDisplayProxy_001();

	if( strcmp(pchInterfaceVersion, "IVRTrackedCamera_002") != 0 )
		return getIVRTrackedCameraProxy_002();
	if( strcmp(pchInterfaceVersion, "IVRTrackedCamera_003") != 0 )
		return getIVRTrackedCameraProxy_003();

	if( strcmp(pchInterfaceVersion, "IVRScreenshots_001") != 0 )
		return getIVRScreenshotsProxy_001();

	if( strcmp(pchInterfaceVersion, "IVRResources_001") != 0 )
		return getIVRResourcesProxy_001();

	if( strcmp(pchInterfaceVersion, "IVRDriverManager_001") != 0 )
		return getIVRDriverManagerProxy_001();

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
