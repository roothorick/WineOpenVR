#include "common.h"
#include "d3dproxy.h"
#include "repacked_structs.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRSystem_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRSystem_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRSystemProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

class CLONECLASS
{
public:
	WOVR_ENTRY virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ ) = 0; // ERP hack
	WOVR_ENTRY virtual void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) = 0;
	WOVR_ENTRY virtual bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates ) = 0;
	WOVR_ENTRY virtual void GetEyeToHeadTransform(HmdMatrix34_t* ret, EVREye eEye ) = 0; // ERP hack
	WOVR_ENTRY virtual bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) = 0;
	WOVR_ENTRY virtual int32_t GetD3D9AdapterIndex() = 0;
	WOVR_ENTRY virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex ) = 0;
#if ABIVER >= 16
	WOVR_ENTRY virtual void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType ) = 0;
#endif
	WOVR_ENTRY virtual bool IsDisplayOnDesktop() = 0;
	WOVR_ENTRY virtual bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) = 0;
	WOVR_ENTRY virtual void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) = 0;
	WOVR_ENTRY virtual void ResetSeatedZeroPose() = 0;
	WOVR_ENTRY virtual void GetSeatedZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret) = 0; // ERP hack
	WOVR_ENTRY virtual void GetRawZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret) = 0; // ERP hack
	WOVR_ENTRY virtual uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex ) = 0;
	WOVR_ENTRY virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId ) = 0;
	WOVR_ENTRY virtual void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform ) = 0;
	WOVR_ENTRY virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType ) = 0;
	WOVR_ENTRY virtual vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual void GetMatrix34TrackedDeviceProperty(HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0; // ERP hack
	WOVR_ENTRY virtual uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) = 0;
	WOVR_ENTRY virtual bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual const char *GetEventTypeNameFromEnum( EVREventType eType ) = 0;
	WOVR_ENTRY virtual void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard ) = 0; // ERP hack
	WOVR_ENTRY virtual bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) = 0;
	WOVR_ENTRY virtual const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) = 0;
	WOVR_ENTRY virtual const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) = 0;
	WOVR_ENTRY virtual bool CaptureInputFocus() = 0;
	WOVR_ENTRY virtual void ReleaseInputFocus() = 0;
	WOVR_ENTRY virtual bool IsInputFocusCapturedByAnotherProcess() = 0;
	WOVR_ENTRY virtual uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) = 0;
	WOVR_ENTRY virtual vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual void AcknowledgeQuit_Exiting() = 0;
	WOVR_ENTRY virtual void AcknowledgeQuit_UserPrompt() = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
	WOVR_ENTRY void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRSystem()->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetProjectionMatrix( HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ )
	{
		// ERP hack
		*ret = VRSystem()->GetProjectionMatrix(eEye, fNearZ, fFarZ);
		return;
	}

	WOVR_ENTRY void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
	{
		VRSystem()->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
		return;
	}

	WOVR_ENTRY bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates )
	{
		return VRSystem()->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
	}

	WOVR_ENTRY void GetEyeToHeadTransform( HmdMatrix34_t* ret, EVREye eEye )
	{
		*ret = VRSystem()->GetEyeToHeadTransform(eEye);
		return;
	}

	WOVR_ENTRY bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter )
	{
		return VRSystem()->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
	}

	WOVR_ENTRY int32_t GetD3D9AdapterIndex()
	{
		return D3DProxy()->GetD3D9AdapterIndex();
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex )
	{
		D3DProxy()->GetDXGIOutputInfo(pnAdapterIndex);
		return;
	}

#if ABIVER >= 16
	WOVR_ENTRY void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
	{
		if(textureType == TextureType_DirectX || textureType == TextureType_DirectX12)
			D3DProxy()->GetOutputDevice(pnDevice, textureType);
		else // Natively supported (OpenGL or Vulkan); pass directly
			VRSystem()->GetOutputDevice(pnDevice, textureType);
		return;
	}
#endif

	WOVR_ENTRY bool IsDisplayOnDesktop()
	{
		return VRSystem()->IsDisplayOnDesktop();
	}

	WOVR_ENTRY bool SetDisplayVisibility( bool bIsVisibleOnDesktop )
	{
		return VRSystem()->SetDisplayVisibility(bIsVisibleOnDesktop);
	}

	WOVR_ENTRY void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount )
	{
		VRSystem()->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
		return;
	}

	WOVR_ENTRY void ResetSeatedZeroPose()
	{
		VRSystem()->ResetSeatedZeroPose();
		return;
	}

	WOVR_ENTRY void GetSeatedZeroPoseToStandingAbsoluteTrackingPose( HmdMatrix34_t* ret )
	{
		// ERP hack
		*ret = VRSystem()->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY void GetRawZeroPoseToStandingAbsoluteTrackingPose( HmdMatrix34_t* ret )
	{
		// ERP hack
		*ret = VRSystem()->GetRawZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex)
	{
		return VRSystem()->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
	}

	WOVR_ENTRY EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId )
	{
		return VRSystem()->GetTrackedDeviceActivityLevel(unDeviceId);
	}

	WOVR_ENTRY void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform )
	{
		VRSystem()->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
		return;
	}

	WOVR_ENTRY vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType )
	{
		return VRSystem()->GetTrackedDeviceIndexForControllerRole(unDeviceType);
	}

	WOVR_ENTRY vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
	}

	WOVR_ENTRY ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->GetTrackedDeviceClass(unDeviceIndex);
	}

	WOVR_ENTRY bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->IsTrackedDeviceConnected(unDeviceIndex);
	}

	WOVR_ENTRY bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return VRSystem()->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return VRSystem()->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY void GetMatrix34TrackedDeviceProperty( HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		// ERP hack
		*ret = VRSystem()->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
		return;
	}

	WOVR_ENTRY uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
	}

	WOVR_ENTRY const char *GetPropErrorNameFromEnum( ETrackedPropertyError error )
	{
		return VRSystem()->GetPropErrorNameFromEnum(error);
	}

	WOVR_ENTRY bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;
		//printf("WOVR trace: PollNextEvent: winpack %u, linpack %u, passed %u\n", sizeof(Repacked_VREvent_t), sizeof(VREvent_t), uncbVREvent);
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		ret = VRSystem()->PollNextEvent(&linpacked, sizeof(VREvent_t) );
		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	WOVR_ENTRY bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
	{
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;
		ret = VRSystem()->PollNextEventWithPose(eOrigin, &linpacked, sizeof(VREvent_t), pTrackedDevicePose);
		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	WOVR_ENTRY const char *GetEventTypeNameFromEnum( EVREventType eType )
	{
		return VRSystem()->GetEventTypeNameFromEnum(eType);
	}

	WOVR_ENTRY void GetHiddenAreaMesh( HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type )
	{
		// ERP hack
		*ret = VRSystem()->GetHiddenAreaMesh(eEye, type);
		return;
	}

	WOVR_ENTRY bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VRSystem()->GetControllerState(unControllerDeviceIndex, &linpacked, sizeof(VRControllerState_t) );
		repackVRControllerState(&linpacked, pControllerState);
		return ret;
	}

	WOVR_ENTRY bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VRSystem()->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, &linpacked, sizeof(VRControllerState_t), pTrackedDevicePose);
		repackVRControllerState(&linpacked, pControllerState);
		return ret;
	}

	WOVR_ENTRY void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec )
	{
		VRSystem()->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
		return;
	}

	WOVR_ENTRY const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId )
	{
		return VRSystem()->GetButtonIdNameFromEnum(eButtonId);
	}

	WOVR_ENTRY const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType )
	{
		return VRSystem()->GetControllerAxisTypeNameFromEnum(eAxisType);
	}

	WOVR_ENTRY bool CaptureInputFocus()
	{
		return VRSystem()->CaptureInputFocus();
	}

	WOVR_ENTRY void ReleaseInputFocus()
	{
		return VRSystem()->ReleaseInputFocus();
	}

	WOVR_ENTRY bool IsInputFocusCapturedByAnotherProcess()
	{
		return VRSystem()->IsInputFocusCapturedByAnotherProcess();
	}

	WOVR_ENTRY uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
	{
		return VRSystem()->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
	}

	WOVR_ENTRY vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->PerformFirmwareUpdate(unDeviceIndex);
	}

	WOVR_ENTRY void AcknowledgeQuit_Exiting()
	{
		VRSystem()->AcknowledgeQuit_Exiting();
		return;
	}

	WOVR_ENTRY void AcknowledgeQuit_UserPrompt()
	{
		VRSystem()->AcknowledgeQuit_UserPrompt();
		return;
	}
};

IVRSystem* GETTER ()
{
	// XXX: Do we need error checking?
	return (IVRSystem*) new PROXYCLASS ();
};
