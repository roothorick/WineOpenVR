// Entry methods to access the interface proxy classes
#pragma once

// To avoid having to include openvr.h
namespace vr
{
	class IVRSystem;
	class IVRApplications;
	class IVRSettings;
	class IVRChaperone;
	class IVRChaperoneSetup;
	class IVRCompositor;
	class IVRNotifications;
	class IVROverlay;
	class IVRRenderModels;
	class IVRExtendedDisplay;
	class IVRTrackedCamera;
	class IVRScreenshots;
	class IVRResources;
}

// These are defined in their respective ivrxxx_32/64.cpp's
// Arguments are the same as VR_GetGenericInterface
vr::IVRSystem*          getIVRSystemProxy           (vr::IVRSystem*             real);
vr::IVRApplications*    getIVRApplicationsProxy     (vr::IVRApplications*       real);
vr::IVRSettings*        getIVRSettingsProxy         (vr::IVRSettings*           real);
vr::IVRChaperone*       getIVRChaperoneProxy        (vr::IVRChaperone*          real);
vr::IVRChaperoneSetup*  getIVRChaperoneSetupProxy   (vr::IVRChaperoneSetup*     real);
vr::IVRCompositor*      getIVRCompositorProxy       (vr::IVRCompositor*         real);
vr::IVRNotifications*   getIVRNotificationsProxy    (vr::IVRNotifications*      real);
vr::IVROverlay*         getIVROverlayProxy          (vr::IVROverlay*            real);
vr::IVRRenderModels*    getIVRRenderModelsProxy     (vr::IVRRenderModels*       real);
vr::IVRExtendedDisplay* getIVRExtendedDisplayProxy  (vr::IVRExtendedDisplay*    real);
vr::IVRTrackedCamera*   getIVRTrackedCameraProxy    (vr::IVRTrackedCamera*      real);
vr::IVRScreenshots*     getIVRScreenshotsProxy      (vr::IVRScreenshots*        real);
vr::IVRResources*       getIVRResourcesProxy        (vr::IVRResources*          real);
