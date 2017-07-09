#include "ivroverlay.h"

class clone_IVROverlay_016
{
public:
	WOVR_ENTRY virtual EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual vr::VROverlayHandle_t GetHighQualityOverlay() = 0;
	WOVR_ENTRY virtual uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError ) = 0;
	WOVR_ENTRY virtual uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayName( VROverlayHandle_t ulOverlayHandle, const char *pchName ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight ) = 0;
	WOVR_ENTRY virtual const char *GetOverlayErrorNameFromEnum( EVROverlayError error ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID ) = 0;
	WOVR_ENTRY virtual uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float fTexelAspect ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds ) = 0;
	WOVR_ENTRY virtual uint32_t GetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, vr::EVROverlayError *pError ) = 0;
	WOVR_ENTRY virtual vr::EVROverlayError SetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize ) = 0;
	WOVR_ENTRY virtual vr::EVROverlayError GetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform ) = 0;
	WOVR_ENTRY virtual vr::EVROverlayError SetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform ) = 0;
	WOVR_ENTRY virtual EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform ) = 0;
	WOVR_ENTRY virtual bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent ) = 0; // Mismatched struct packing
	WOVR_ENTRY virtual EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale ) = 0;
	WOVR_ENTRY virtual bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults ) = 0;
	WOVR_ENTRY virtual bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex ) = 0;
	WOVR_ENTRY virtual bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual vr::VROverlayHandle_t GetGamepadFocusOverlay() = 0;
	WOVR_ENTRY virtual EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo ) = 0;
	WOVR_ENTRY virtual EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture ) = 0;
	WOVR_ENTRY virtual EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds ) = 0;
	WOVR_ENTRY virtual EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight ) = 0;
	WOVR_ENTRY virtual EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle ) = 0;
	WOVR_ENTRY virtual bool IsDashboardVisible() = 0;
	WOVR_ENTRY virtual bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId ) = 0;
	WOVR_ENTRY virtual void ShowDashboard( const char *pchOverlayToShow ) = 0;
	WOVR_ENTRY virtual vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice() = 0;
	WOVR_ENTRY virtual EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;
	WOVR_ENTRY virtual EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;
	WOVR_ENTRY virtual uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText ) = 0;
	WOVR_ENTRY virtual void HideKeyboard() = 0;
	WOVR_ENTRY virtual void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform ) = 0;
	WOVR_ENTRY virtual void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect ) = 0;
	WOVR_ENTRY virtual EVROverlayError SetOverlayIntersectionMask( VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize ) = 0;
	WOVR_ENTRY virtual EVROverlayError GetOverlayFlags( VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags ) = 0;
	WOVR_ENTRY virtual VRMessageOverlayResponse ShowMessageOverlay( const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text ) = 0;
};

class proxy_IVROverlay_016 : public clone_IVROverlay_016
{
public:
	WOVR_ENTRY EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle )
	{
		return fns_IVROverlay::FindOverlay( pchOverlayKey, pOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle )
	{
		return fns_IVROverlay::CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::DestroyOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::SetHighQualityOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY vr::VROverlayHandle_t GetHighQualityOverlay()
	{
		return fns_IVROverlay::GetHighQualityOverlay();
	}

	WOVR_ENTRY uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return fns_IVROverlay::GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	WOVR_ENTRY uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return fns_IVROverlay::GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	WOVR_ENTRY EVROverlayError SetOverlayName( VROverlayHandle_t ulOverlayHandle, const char *pchName )
	{
		return fns_IVROverlay::SetOverlayName(ulOverlayHandle, pchName);
	}

	WOVR_ENTRY EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight )
	{
		return fns_IVROverlay::GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
	}

	WOVR_ENTRY const char *GetOverlayErrorNameFromEnum( EVROverlayError error )
	{
		return fns_IVROverlay::GetOverlayErrorNameFromEnum(error);
	}

	WOVR_ENTRY EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID )
	{
		return fns_IVROverlay::SetOverlayRenderingPid(ulOverlayHandle, unPID);
	}

	WOVR_ENTRY uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::GetOverlayRenderingPid(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled )
	{
		return fns_IVROverlay::SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
	}

	WOVR_ENTRY EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled )
	{
		return fns_IVROverlay::GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
	}

	WOVR_ENTRY EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue )
	{
		return fns_IVROverlay::SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
	}

	WOVR_ENTRY EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue )
	{
		return fns_IVROverlay::GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
	}

	WOVR_ENTRY EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha )
	{
		return fns_IVROverlay::SetOverlayAlpha(ulOverlayHandle, fAlpha);
	}

	WOVR_ENTRY EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha )
	{
		return fns_IVROverlay::GetOverlayAlpha(ulOverlayHandle, pfAlpha);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float fTexelAspect )
	{
		return fns_IVROverlay::SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect )
	{
		return fns_IVROverlay::GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect);
	}

	WOVR_ENTRY EVROverlayError SetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder )
	{
		return fns_IVROverlay::SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
	}

	WOVR_ENTRY EVROverlayError GetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder )
	{
		return fns_IVROverlay::GetOverlaySortOrder(ulOverlayHandle, punSortOrder);
	}

	WOVR_ENTRY EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters )
	{
		return fns_IVROverlay::SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
	}

	WOVR_ENTRY EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters )
	{
		return fns_IVROverlay::GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
	}

	WOVR_ENTRY EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters )
	{
		return fns_IVROverlay::SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
	}

	WOVR_ENTRY EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters )
	{
		return fns_IVROverlay::GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace )
	{
		return fns_IVROverlay::SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace )
	{
		return fns_IVROverlay::GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds )
	{
		return fns_IVROverlay::SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds )
	{
		return fns_IVROverlay::GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	WOVR_ENTRY uint32_t GetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, vr::EVROverlayError *pError )
	{
		return fns_IVROverlay::GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError);
	}

	WOVR_ENTRY vr::EVROverlayError SetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor )
	{
		return fns_IVROverlay::SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType )
	{
		return fns_IVROverlay::GetOverlayTransformType(ulOverlayHandle, peTransformType);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return fns_IVROverlay::SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return fns_IVROverlay::GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return fns_IVROverlay::SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return fns_IVROverlay::GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName )
	{
		return fns_IVROverlay::SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize )
	{
		return fns_IVROverlay::GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
	}

	WOVR_ENTRY vr::EVROverlayError GetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return fns_IVROverlay::GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	WOVR_ENTRY vr::EVROverlayError SetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return fns_IVROverlay::SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	WOVR_ENTRY EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::ShowOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::HideOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::IsOverlayVisible(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform )
	{
		return fns_IVROverlay::GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
	}

	WOVR_ENTRY bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		return fns_IVROverlay::PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent);
	}

	WOVR_ENTRY EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod )
	{
		return fns_IVROverlay::GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
	}

	WOVR_ENTRY EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod )
	{
		return fns_IVROverlay::SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
	}

	WOVR_ENTRY EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale )
	{
		return fns_IVROverlay::GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	WOVR_ENTRY EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale )
	{
		return fns_IVROverlay::SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	WOVR_ENTRY bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults )
	{
		return fns_IVROverlay::ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
	}

	WOVR_ENTRY bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex )
	{
		return fns_IVROverlay::HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
	}

	WOVR_ENTRY bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::IsHoverTargetOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY vr::VROverlayHandle_t GetGamepadFocusOverlay()
	{
		return fns_IVROverlay::GetGamepadFocusOverlay();
	}

	WOVR_ENTRY EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay )
	{
		return fns_IVROverlay::SetGamepadFocusOverlay(ulNewFocusOverlay);
	}

	WOVR_ENTRY EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo )
	{
		return fns_IVROverlay::SetOverlayNeighbor(eDirection, ulFrom, ulTo);
	}

	WOVR_ENTRY EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom )
	{
		return fns_IVROverlay::MoveGamepadFocusToNeighbor(eDirection, ulFrom);
	}

	WOVR_ENTRY EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
	{
		return fns_IVROverlay::SetOverlayTexture(ulOverlayHandle, pTexture);
	}

	WOVR_ENTRY EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::ClearOverlayTexture(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth )
	{
		return fns_IVROverlay::SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
	}

	WOVR_ENTRY EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath )
	{
		return fns_IVROverlay::SetOverlayFromFile(ulOverlayHandle, pchFilePath);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
	{
		return fns_IVROverlay::GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
	}

	WOVR_ENTRY EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle )
	{
		return fns_IVROverlay::ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
	}

	WOVR_ENTRY EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight )
	{
		return fns_IVROverlay::GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight);
	}

	WOVR_ENTRY EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle )
	{
		return fns_IVROverlay::CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
	}

	WOVR_ENTRY bool IsDashboardVisible()
	{
		return fns_IVROverlay::IsDashboardVisible();
	}

	WOVR_ENTRY bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return fns_IVROverlay::IsActiveDashboardOverlay(ulOverlayHandle);
	}

	WOVR_ENTRY EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId )
	{
		return fns_IVROverlay::SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
	}

	WOVR_ENTRY EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId )
	{
		return fns_IVROverlay::GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
	}

	WOVR_ENTRY void ShowDashboard( const char *pchOverlayToShow )
	{
		return fns_IVROverlay::ShowDashboard(pchOverlayToShow);
	}

	WOVR_ENTRY vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice()
	{
		return fns_IVROverlay::GetPrimaryDashboardDevice();
	}

	WOVR_ENTRY EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return fns_IVROverlay::ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	WOVR_ENTRY EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return fns_IVROverlay::ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	WOVR_ENTRY uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText )
	{
		return fns_IVROverlay::GetKeyboardText(pchText, cchText);
	}

	WOVR_ENTRY void HideKeyboard()
	{
		fns_IVROverlay::HideKeyboard();
		return;
	}

	WOVR_ENTRY void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform )
	{
		fns_IVROverlay::SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
		return;
	}

	WOVR_ENTRY void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect )
	{
		fns_IVROverlay::SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
		return;
	}

	WOVR_ENTRY EVROverlayError SetOverlayIntersectionMask( VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize )
	{
		return fns_IVROverlay::SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize);
	}

	WOVR_ENTRY EVROverlayError GetOverlayFlags( VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags )
	{
		return fns_IVROverlay::GetOverlayFlags(ulOverlayHandle, pFlags);
	}

	WOVR_ENTRY VRMessageOverlayResponse ShowMessageOverlay( const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text )
	{
		return fns_IVROverlay::ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text);
	}
};

IVROverlay* getIVROverlayProxy_016()
{
	return (IVROverlay*) new proxy_IVROverlay_016();
}
