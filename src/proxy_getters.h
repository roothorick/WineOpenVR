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

vr::IVRSettings* getIVRSettingsProxy_002();

vr::IVRChaperone* getIVRChaperoneProxy_003();

vr::IVRChaperoneSetup* getIVRChaperoneSetupProxy_005();

vr::IVRCompositor* getIVRCompositorProxy_020();

vr::IVRNotifications* getIVRNotificationsProxy_002();

vr::IVROverlay* getIVROverlayProxy_016();

vr::IVRRenderModels* getIVRRenderModelsProxy_005();

vr::IVRTrackedCamera* getIVRTrackedCameraProxy_003();

vr::IVRExtendedDisplay* getIVRExtendedDisplayProxy_001();

vr::IVRScreenshots* getIVRScreenshotsProxy_001();

// Not yet converted to ABI-switching system
vr::IVRResources*       getIVRResourcesProxy        (vr::IVRResources*          real);
