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

// These are all defined in their respective ivrxxx_xxx.cpp's
vr::IVRSystem* getIVRSystemProxy_016();

vr::IVRApplications* getIVRApplicationsProxy_006();

// Not yet converted to ABI-switching system
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
