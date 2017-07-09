#include "common.h"
#include "repacked_structs.h"
#include "d3dproxy.h"

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

namespace fns_IVROverlay
{
	inline EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle )
	{
		return VROverlay()->FindOverlay( pchOverlayKey, pOverlayHandle);
	}

	inline EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle )
	{
		return VROverlay()->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle);
	}

	inline EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->DestroyOverlay(ulOverlayHandle);
	}

	inline EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->SetHighQualityOverlay(ulOverlayHandle);
	}

	inline vr::VROverlayHandle_t GetHighQualityOverlay()
	{
		return VROverlay()->GetHighQualityOverlay();
	}

	inline uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return VROverlay()->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	inline uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError )
	{
		return VROverlay()->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
	}

	inline EVROverlayError SetOverlayName( VROverlayHandle_t ulOverlayHandle, const char *pchName )
	{
		return VROverlay()->SetOverlayName(ulOverlayHandle, pchName);
	}

	inline EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight )
	{
		return VROverlay()->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
	}

	inline const char *GetOverlayErrorNameFromEnum( EVROverlayError error )
	{
		return VROverlay()->GetOverlayErrorNameFromEnum(error);
	}

	inline EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID )
	{
		return VROverlay()->SetOverlayRenderingPid(ulOverlayHandle, unPID);
	}

	inline uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->GetOverlayRenderingPid(ulOverlayHandle);
	}

	inline EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled )
	{
		return VROverlay()->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
	}

	inline EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled )
	{
		return VROverlay()->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
	}

	inline EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue )
	{
		return VROverlay()->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
	}

	inline EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue )
	{
		return VROverlay()->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
	}

	inline EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha )
	{
		return VROverlay()->SetOverlayAlpha(ulOverlayHandle, fAlpha);
	}

	inline EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha )
	{
		return VROverlay()->GetOverlayAlpha(ulOverlayHandle, pfAlpha);
	}

	inline EVROverlayError SetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float fTexelAspect )
	{
		return VROverlay()->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
	}

	inline EVROverlayError GetOverlayTexelAspect( VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect )
	{
		return VROverlay()->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect);
	}

	inline EVROverlayError SetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder )
	{
		return VROverlay()->SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
	}

	inline EVROverlayError GetOverlaySortOrder( VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder )
	{
		return VROverlay()->GetOverlaySortOrder(ulOverlayHandle, punSortOrder);
	}

	inline EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters )
	{
		return VROverlay()->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
	}

	inline EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters )
	{
		return VROverlay()->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
	}

	inline EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters )
	{
		return VROverlay()->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
	}

	inline EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters )
	{
		return VROverlay()->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
	}

	inline EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace )
	{
		return VROverlay()->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
	}

	inline EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace )
	{
		return VROverlay()->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
	}

	inline EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds )
	{
		return VROverlay()->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	inline EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds )
	{
		return VROverlay()->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
	}

	inline uint32_t GetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, vr::EVROverlayError *pError )
	{
		return VROverlay()->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError);
	}

	inline vr::EVROverlayError SetOverlayRenderModel( vr::VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor )
	{
		return VROverlay()->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor);
	}

	inline EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType )
	{
		return VROverlay()->GetOverlayTransformType(ulOverlayHandle, peTransformType);
	}

	inline EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return VROverlay()->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	inline EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform )
	{
		return VROverlay()->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
	}

	inline EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return VROverlay()->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	inline EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform )
	{
		return VROverlay()->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
	}

	inline EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName )
	{
		return VROverlay()->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
	}

	inline EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize )
	{
		return VROverlay()->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
	}

	inline vr::EVROverlayError GetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return VROverlay()->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	inline vr::EVROverlayError SetOverlayTransformOverlayRelative( VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform )
	{
		return VROverlay()->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
	}

	inline EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->ShowOverlay(ulOverlayHandle);
	}

	inline EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->HideOverlay(ulOverlayHandle);
	}

	inline bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->IsOverlayVisible(ulOverlayHandle);
	}

	inline EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform )
	{
		return VROverlay()->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
	}

	inline bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		// Mismatched struct packing
		VREvent_t linpacked;

		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VROverlay()->PollNextOverlayEvent(ulOverlayHandle, &linpacked, sizeof(VREvent_t));

		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	inline EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod )
	{
		return VROverlay()->GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
	}

	inline EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod )
	{
		return VROverlay()->SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
	}

	inline EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale )
	{
		return VROverlay()->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	inline EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale )
	{
		return VROverlay()->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
	}

	inline bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults )
	{
		return VROverlay()->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
	}

	inline bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex )
	{
		return VROverlay()->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
	}

	inline bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->IsHoverTargetOverlay(ulOverlayHandle);
	}

	inline vr::VROverlayHandle_t GetGamepadFocusOverlay()
	{
		return VROverlay()->GetGamepadFocusOverlay();
	}

	inline EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay )
	{
		return VROverlay()->SetGamepadFocusOverlay(ulNewFocusOverlay);
	}

	inline EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo )
	{
		return VROverlay()->SetOverlayNeighbor(eDirection, ulFrom, ulTo);
	}

	inline EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom )
	{
		return VROverlay()->MoveGamepadFocusToNeighbor(eDirection, ulFrom);
	}

	inline EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
	{
		if(pTexture->eType == TextureType_DirectX || pTexture->eType == TextureType_DirectX12)
			return D3DProxy()->SetOverlayTexture(ulOverlayHandle, pTexture);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VROverlay()->SetOverlayTexture(ulOverlayHandle, pTexture);
	}

	inline EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->ClearOverlayTexture(ulOverlayHandle);
	}

	inline EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth )
	{
		return VROverlay()->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
	}

	inline EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath )
	{
		return VROverlay()->SetOverlayFromFile(ulOverlayHandle, pchFilePath);
	}

	inline EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
	{
		if(*pAPIType == TextureType_DirectX || *pAPIType == TextureType_DirectX12)
			return D3DProxy()->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VROverlay()->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
	}

	inline EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle )
	{
		return VROverlay()->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
	}

	inline EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight )
	{
		return VROverlay()->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight);
	}

	inline EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle )
	{
		return VROverlay()->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
	}

	inline bool IsDashboardVisible()
	{
		return VROverlay()->IsDashboardVisible();
	}

	inline bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle )
	{
		return VROverlay()->IsActiveDashboardOverlay(ulOverlayHandle);
	}

	inline EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId )
	{
		return VROverlay()->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
	}

	inline EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId )
	{
		return VROverlay()->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
	}

	inline void ShowDashboard( const char *pchOverlayToShow )
	{
		return VROverlay()->ShowDashboard(pchOverlayToShow);
	}

	inline vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice()
	{
		return VROverlay()->GetPrimaryDashboardDevice();
	}

	inline EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return VROverlay()->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	inline EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue )
	{
		return VROverlay()->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
	}

	inline uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText )
	{
		return VROverlay()->GetKeyboardText(pchText, cchText);
	}

	inline void HideKeyboard()
	{
		VROverlay()->HideKeyboard();
		return;
	}

	inline void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform )
	{
		VROverlay()->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
		return;
	}

	inline void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect )
	{
		VROverlay()->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
		return;
	}

	inline EVROverlayError SetOverlayIntersectionMask( VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize )
	{
		return VROverlay()->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize);
	}

	inline VRMessageOverlayResponse ShowMessageOverlay( const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text )
	{
		return VROverlay()->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text);
	}

	inline EVROverlayError GetOverlayFlags( VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags )
	{
		return VROverlay()->GetOverlayFlags(ulOverlayHandle, pFlags);
	}	
}
