#include "common.h"
#include "repacked_structs.h"

/*
WARNING: openvr.h does not specify packing alignment for these structs:

* VROverlayIntersectionParams_t
* VROverlayIntersectionResults_t
* IntersectionMaskRectangle_t
* IntersectionMaskCircle_t
* VROverlayIntersectionMaskPrimitive_t

How MSVC packs them is presently unknown; the current code just hopes that it agrees with GCC.
If you find an overlay app that's crashing in mysterious ways, check these first.
*/

class clone_IVROverlay
{
public:
	THISCALL virtual EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual vr::VROverlayHandle_t GetHighQualityOverlay() = 0;
	THISCALL virtual uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError ) = 0;
	THISCALL virtual uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError ) = 0;
	THISCALL virtual EVROverlayError SetOverlayName( VROverlayHandle_t ulOverlayHandle, const char *pchName ) = 0;
	THISCALL virtual EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight ) = 0;
	THISCALL virtual const char *GetOverlayErrorNameFromEnum( EVROverlayError error ) = 0;
	THISCALL virtual EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID ) = 0;
	THISCALL virtual uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled ) = 0;
	THISCALL virtual EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled ) = 0;
	THISCALL virtual EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue ) = 0;
	THISCALL virtual EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue ) = 0;
	THISCALL virtual EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha ) = 0;
	THISCALL virtual EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float fTexelAspect ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect ) = 0;
	THISCALL virtual EVROverlayError SetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder ) = 0;
	THISCALL virtual EVROverlayError GetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder ) = 0;
	THISCALL virtual EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters ) = 0;
	THISCALL virtual EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters ) = 0;
	THISCALL virtual EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters ) = 0;
	THISCALL virtual EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds ) = 0;
	THISCALL virtual uint32_t GetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, vr::EVROverlayError *pError ) = 0;
	THISCALL virtual vr::EVROverlayError SetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize ) = 0;
	THISCALL virtual vr::EVROverlayError GetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform ) = 0;
	THISCALL virtual vr::EVROverlayError SetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform ) = 0;
	THISCALL virtual EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform ) = 0;
	THISCALL virtual bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent ) = 0; // Mismatched struct packing
	THISCALL virtual EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod ) = 0;
	THISCALL virtual EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod ) = 0;
	THISCALL virtual EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale ) = 0;
	THISCALL virtual EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale ) = 0;
	THISCALL virtual bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults ) = 0;
	THISCALL virtual bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex ) = 0;
	THISCALL virtual bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual vr::VROverlayHandle_t GetGamepadFocusOverlay() = 0;
	THISCALL virtual EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay ) = 0;
	THISCALL virtual EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo ) = 0;
	THISCALL virtual EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom ) = 0;
	THISCALL virtual EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture ) = 0;
	THISCALL virtual EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth ) = 0;
	THISCALL virtual EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds ) = 0;
	THISCALL virtual EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle ) = 0;
	THISCALL virtual EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight ) = 0;
	THISCALL virtual EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle ) = 0;
	THISCALL virtual bool IsDashboardVisible() = 0;
	THISCALL virtual bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;
	THISCALL virtual EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId ) = 0;
	THISCALL virtual EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId ) = 0;
	THISCALL virtual void ShowDashboard( const char *pchOverlayToShow ) = 0;
	THISCALL virtual vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice() = 0;
	THISCALL virtual EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;
	THISCALL virtual EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) = 0;
	THISCALL virtual uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText ) = 0;
	THISCALL virtual void HideKeyboard() = 0;
	THISCALL virtual void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform ) = 0;
	THISCALL virtual void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect ) = 0;
	THISCALL virtual EVROverlayError SetOverlayIntersectionMask( VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize ) = 0;
	THISCALL virtual VRMessageOverlayResponse ShowMessageOverlay( const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text ) = 0;
	THISCALL virtual EVROverlayError GetOverlayFlags( VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags ) = 0;
};

class proxy_IVROverlay : public clone_IVROverlay
{
public:
	proxy_IVROverlay(IVROverlay* real) { realImpl = real; }

	THISCALL EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle )
	{
		return realImpl->FindOverlay( pchOverlayKey, pOverlayHandle);
	}

	THISCALL EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle )
	{
		return realImpl->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle);
	}

	THISCALL EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->DestroyOverlay(ulOverlayHandle);
	}

	THISCALL EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->SetHighQualityOverlay(ulOverlayHandle);
	}

	THISCALL vr::VROverlayHandle_t GetHighQualityOverlay()
	{
		return realImpl->GetHighQualityOverlay();
	}

	THISCALL uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return realImpl->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	THISCALL uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return realImpl->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	THISCALL EVROverlayError SetOverlayName( VROverlayHandle_t ulOverlayHandle, const char *pchName )
	{
		return realImpl->SetOverlayName(ulOverlayHandle, pchName);
	}

	THISCALL EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight )
	{
		return realImpl->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
	}

	THISCALL const char *GetOverlayErrorNameFromEnum( EVROverlayError error )
	{
		return realImpl->GetOverlayErrorNameFromEnum(error);
	}

	THISCALL EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID )
	{
		return realImpl->SetOverlayRenderingPid(ulOverlayHandle, unPID);
	}

	THISCALL uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->GetOverlayRenderingPid(ulOverlayHandle);
	}

	THISCALL EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled )
	{
		return realImpl->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
	}

	THISCALL EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled )
	{
		return realImpl->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
	}

	THISCALL EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue )
	{
		return realImpl->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
	}

	THISCALL EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue )
	{
		return realImpl->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
	}

	THISCALL EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha )
	{
		return realImpl->SetOverlayAlpha(ulOverlayHandle, fAlpha);
	}

	THISCALL EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha )
	{
		return realImpl->GetOverlayAlpha(ulOverlayHandle, pfAlpha);
	}

	THISCALL EVROverlayError SetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float fTexelAspect )
	{
		return realImpl->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
	}

	THISCALL EVROverlayError GetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect )
	{
		return realImpl->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect);
	}

	THISCALL EVROverlayError SetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder )
	{
		return realImpl->SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
	}

	THISCALL EVROverlayError GetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder )
	{
		return realImpl->GetOverlaySortOrder(ulOverlayHandle, punSortOrder);
	}

	THISCALL EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters )
	{
		return realImpl->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
	}

	THISCALL EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters )
	{
		return realImpl->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
	}

	THISCALL EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters )
	{
		return realImpl->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
	}

	THISCALL EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters )
	{
		return realImpl->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
	}

	THISCALL EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace )
	{
		return realImpl->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
	}

	THISCALL EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace )
	{
		return realImpl->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
	}

	THISCALL EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds )
	{
		return realImpl->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	THISCALL EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds )
	{
		return realImpl->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	THISCALL uint32_t GetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, vr::EVROverlayError *pError )
	{
		return realImpl->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError);
	}

	THISCALL vr::EVROverlayError SetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor )
	{
		return realImpl->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor);
	}

	THISCALL EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType )
	{
		return realImpl->GetOverlayTransformType(ulOverlayHandle, peTransformType);
	}

	THISCALL EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return realImpl->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	THISCALL EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return realImpl->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	THISCALL EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return realImpl->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	THISCALL EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return realImpl->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	THISCALL EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName )
	{
		return realImpl->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
	}

	THISCALL EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize )
	{
		return realImpl->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
	}

	THISCALL vr::EVROverlayError GetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return realImpl->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	THISCALL vr::EVROverlayError SetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return realImpl->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	THISCALL EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->ShowOverlay(ulOverlayHandle);
	}

	THISCALL EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->HideOverlay(ulOverlayHandle);
	}

	THISCALL bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->IsOverlayVisible(ulOverlayHandle);
	}

	THISCALL EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform )
	{
		return realImpl->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
	}

	THISCALL bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		// Mismatched struct packing
		VREvent_t linpacked;

		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = realImpl->PollNextOverlayEvent(ulOverlayHandle, &linpacked, sizeof(VREvent_t));

		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	THISCALL EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod )
	{
		return realImpl->GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
	}

	THISCALL EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod )
	{
		return realImpl->SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
	}

	THISCALL EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale )
	{
		return realImpl->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	THISCALL EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale )
	{
		return realImpl->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	THISCALL bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults )
	{
		return realImpl->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
	}

	THISCALL bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex )
	{
		return realImpl->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
	}

	THISCALL bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->IsHoverTargetOverlay(ulOverlayHandle);
	}

	THISCALL vr::VROverlayHandle_t GetGamepadFocusOverlay()
	{
		return realImpl->GetGamepadFocusOverlay();
	}

	THISCALL EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay )
	{
		return realImpl->SetGamepadFocusOverlay(ulNewFocusOverlay);
	}

	THISCALL EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo )
	{
		return realImpl->SetOverlayNeighbor(eDirection, ulFrom, ulTo);
	}

	THISCALL EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom )
	{
		return realImpl->MoveGamepadFocusToNeighbor(eDirection, ulFrom);
	}

	THISCALL EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
	{
		return realImpl->SetOverlayTexture(ulOverlayHandle, pTexture);
	}

	THISCALL EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->ClearOverlayTexture(ulOverlayHandle);
	}

	THISCALL EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth )
	{
		return realImpl->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
	}

	THISCALL EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath )
	{
		return realImpl->SetOverlayFromFile(ulOverlayHandle, pchFilePath);
	}

	THISCALL EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
	{
		return realImpl->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
	}

	THISCALL EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle )
	{
		return realImpl->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
	}

	THISCALL EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight )
	{
		return realImpl->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight);
	}

	THISCALL EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle )
	{
		return realImpl->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
	}

	THISCALL bool IsDashboardVisible()
	{
		return realImpl->IsDashboardVisible();
	}

	THISCALL bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return realImpl->IsActiveDashboardOverlay(ulOverlayHandle);
	}

	THISCALL EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId )
	{
		return realImpl->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
	}

	THISCALL EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId )
	{
		return realImpl->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
	}

	THISCALL void ShowDashboard( const char *pchOverlayToShow )
	{
		return realImpl->ShowDashboard(pchOverlayToShow);
	}

	THISCALL vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice()
	{
		return realImpl->GetPrimaryDashboardDevice();
	}

	THISCALL EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return realImpl->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	THISCALL EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return realImpl->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	THISCALL uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText )
	{
		return realImpl->GetKeyboardText(pchText, cchText);
	}

	THISCALL void HideKeyboard()
	{
		realImpl->HideKeyboard();
		return;
	}

	THISCALL void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform )
	{
		realImpl->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
		return;
	}

	THISCALL void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect )
	{
		realImpl->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
		return;
	}

	THISCALL EVROverlayError SetOverlayIntersectionMask( VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize )
	{
		return realImpl->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize);
	}

	THISCALL VRMessageOverlayResponse ShowMessageOverlay( const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text )
	{
		return realImpl->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text);
	}

	THISCALL EVROverlayError GetOverlayFlags( VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags )
	{
		return realImpl->GetOverlayFlags(ulOverlayHandle, pFlags);
	}

private:
	IVROverlay* realImpl;
};

IVROverlay* getIVROverlayProxy(IVROverlay* real)
{
	return (IVROverlay*) new proxy_IVROverlay(real);
}
