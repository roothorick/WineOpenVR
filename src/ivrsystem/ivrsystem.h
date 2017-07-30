#include "common.h"
#include "d3dproxy.h"
#include "repacked_structs.h"

#if ABIVER < 14
#include <cmath> // NAN
#endif

#if ABIVER < 15
typedef ETextureType EGraphicsAPIConvention; // Renamed in 1.0.5
#endif

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
#if ABIVER < 15
	WOVR_ENTRY virtual void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType ) = 0; // ERP hack
#else
	WOVR_ENTRY virtual void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ ) = 0; // ERP hack
#endif
	WOVR_ENTRY virtual void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) = 0;
#if ABIVER < 14
	WOVR_ENTRY virtual void ComputeDistortion( DistortionCoordinates_t* ret, EVREye eEye, float fU, float fV ) = 0; // ERP hack
#else
	WOVR_ENTRY virtual bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates ) = 0;
#endif
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
#if ABIVER >= 10
	WOVR_ENTRY virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType ) = 0;
	WOVR_ENTRY virtual vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
#endif
	WOVR_ENTRY virtual ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	WOVR_ENTRY virtual bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual void GetMatrix34TrackedDeviceProperty(HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0; // ERP hack
	WOVR_ENTRY virtual uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError ) = 0;
	WOVR_ENTRY virtual const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) = 0;
#if ABIVER < 11
	WOVR_ENTRY virtual bool PollNextEvent( Repacked_VREvent_t *pEvent ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
#else // >= 11
	WOVR_ENTRY virtual bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
#endif
	WOVR_ENTRY virtual const char *GetEventTypeNameFromEnum( EVREventType eType ) = 0;
#if ABIVER < 14
	WOVR_ENTRY virtual void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye ) = 0; // ERP hack
	WOVR_ENTRY virtual bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState  ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
#else
	WOVR_ENTRY virtual void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard ) = 0; // ERP hack
	WOVR_ENTRY virtual bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
#endif
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
#if ABIVER < 12
	// These two were added in 0.9.14 without an ABI version bump (was 010)
	WOVR_ENTRY virtual void PerformanceTestEnableCapture( bool bEnable ) = 0;
	WOVR_ENTRY virtual void PerformanceTestReportFidelityLevelChange( int nFidelityLevel ) = 0;
#endif
};

class PROXYCLASS : public CLONECLASS
{
public:
	WOVR_ENTRY void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
	{
		TRACE("");
		VRSystem()->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
		return;
	}

#if ABIVER < 15
	WOVR_ENTRY  void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType )
#else
	WOVR_ENTRY void GetProjectionMatrix( HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ )
#endif
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetProjectionMatrix(eEye, fNearZ, fFarZ);
		return;
	}

	WOVR_ENTRY void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
	{
		TRACEHOT("");
		VRSystem()->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
		return;
	}

#if ABIVER < 14
	WOVR_ENTRY void ComputeDistortion( DistortionCoordinates_t* ret, EVREye eEye, float fU, float fV )
	{
		TRACE("");
		// ERP hack
		const DistortionCoordinates_t nanret = { NAN, NAN, NAN, NAN, NAN, NAN };
		if(!VRSystem()->ComputeDistortion(eEye, fU, fV, ret))
			*ret = nanret;

		return;
	}
#else
	WOVR_ENTRY bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates )
	{
		TRACE("");
		return VRSystem()->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
	}
#endif

	WOVR_ENTRY void GetEyeToHeadTransform( HmdMatrix34_t* ret, EVREye eEye )
	{
		TRACE("");
		*ret = VRSystem()->GetEyeToHeadTransform(eEye);
		return;
	}

	WOVR_ENTRY bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter )
	{
		TRACE("");
		return VRSystem()->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
	}

	WOVR_ENTRY int32_t GetD3D9AdapterIndex()
	{
		TRACE("");
		return D3DProxy()->GetD3D9AdapterIndex();
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex )
	{
		TRACE("");
		D3DProxy()->GetDXGIOutputInfo(pnAdapterIndex);
		return;
	}

#if ABIVER >= 16
	WOVR_ENTRY void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
	{
		TRACE("");
		if(textureType == TextureType_DirectX || textureType == TextureType_DirectX12)
			D3DProxy()->GetOutputDevice(pnDevice, textureType);
		else // Natively supported (OpenGL or Vulkan); pass directly
			VRSystem()->GetOutputDevice(pnDevice, textureType);
		return;
	}
#endif

	WOVR_ENTRY bool IsDisplayOnDesktop()
	{
		TRACE("");
		return VRSystem()->IsDisplayOnDesktop();
	}

	WOVR_ENTRY bool SetDisplayVisibility( bool bIsVisibleOnDesktop )
	{
		TRACE("");
		return VRSystem()->SetDisplayVisibility(bIsVisibleOnDesktop);
	}

	WOVR_ENTRY void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount )
	{
		TRACE("");
		VRSystem()->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
		return;
	}

	WOVR_ENTRY void ResetSeatedZeroPose()
	{
		TRACE("");
		VRSystem()->ResetSeatedZeroPose();
		return;
	}

	WOVR_ENTRY void GetSeatedZeroPoseToStandingAbsoluteTrackingPose( HmdMatrix34_t* ret )
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY void GetRawZeroPoseToStandingAbsoluteTrackingPose( HmdMatrix34_t* ret )
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetRawZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex)
	{
		TRACE("");
		return VRSystem()->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
	}

	WOVR_ENTRY EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId )
	{
		TRACE("");
		return VRSystem()->GetTrackedDeviceActivityLevel(unDeviceId);
	}

	WOVR_ENTRY void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform )
	{
		TRACE("");
		VRSystem()->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
		return;
	}

#if ABIVER >= 10
	WOVR_ENTRY vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType )
	{
		TRACE("");
		return VRSystem()->GetTrackedDeviceIndexForControllerRole(unDeviceType);
	}

	WOVR_ENTRY vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		TRACE("");
		return VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
	}
#endif

	WOVR_ENTRY ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		TRACEHOT("");
		return VRSystem()->GetTrackedDeviceClass(unDeviceIndex);
	}

	WOVR_ENTRY bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		TRACEHOT("");
		return VRSystem()->IsTrackedDeviceConnected(unDeviceIndex);
	}

	WOVR_ENTRY bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		TRACE("");
		return VRSystem()->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		TRACE("");
		return VRSystem()->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		TRACE("");
		return VRSystem()->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		TRACE("");
		return VRSystem()->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY void GetMatrix34TrackedDeviceProperty( HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
		return;
	}

	WOVR_ENTRY uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError)
	{
		TRACE("");
		return VRSystem()->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
	}

	WOVR_ENTRY const char *GetPropErrorNameFromEnum( ETrackedPropertyError error )
	{
		TRACE("");
		return VRSystem()->GetPropErrorNameFromEnum(error);
	}

#if ABIVER < 11
	WOVR_ENTRY bool PollNextEvent( Repacked_VREvent_t *pEvent )
#else
	WOVR_ENTRY bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
#endif
	{
		TRACEHOT("");
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

#if ABIVER < 11
	WOVR_ENTRY bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
#else
	WOVR_ENTRY bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
#endif
	{
		TRACEHOT("");
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;
		ret = VRSystem()->PollNextEventWithPose(eOrigin, &linpacked, sizeof(VREvent_t), pTrackedDevicePose);
		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	WOVR_ENTRY const char *GetEventTypeNameFromEnum( EVREventType eType )
	{
		TRACE("");
		return VRSystem()->GetEventTypeNameFromEnum(eType);
	}

#if ABIVER < 14
	WOVR_ENTRY void GetHiddenAreaMesh( HiddenAreaMesh_t* ret, EVREye eEye )
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetHiddenAreaMesh(eEye, k_eHiddenAreaMesh_Standard);
		return;
	}
#else
	WOVR_ENTRY void GetHiddenAreaMesh( HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type )
	{
		TRACE("");
		// ERP hack
		*ret = VRSystem()->GetHiddenAreaMesh(eEye, type);
		return;
	}
#endif

#if ABIVER < 14
	WOVR_ENTRY bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState )
#else
	WOVR_ENTRY bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize )
#endif
	{
		TRACEHOT("");
		// Struct packing mismatch
		VRControllerState_t linpacked;
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VRSystem()->GetControllerState(unControllerDeviceIndex, &linpacked, sizeof(VRControllerState_t) );
		repackVRControllerState(&linpacked, pControllerState);
		return ret;
	}

#if ABIVER < 14
	WOVR_ENTRY bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose )
#else
	WOVR_ENTRY bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose )
#endif
	{
		TRACE("");
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
		TRACE("");
		VRSystem()->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
		return;
	}

	WOVR_ENTRY const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId )
	{
		TRACE("");
		return VRSystem()->GetButtonIdNameFromEnum(eButtonId);
	}

	WOVR_ENTRY const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType )
	{
		TRACE("");
		return VRSystem()->GetControllerAxisTypeNameFromEnum(eAxisType);
	}

	WOVR_ENTRY bool CaptureInputFocus()
	{
		TRACE("");
		return VRSystem()->CaptureInputFocus();
	}

	WOVR_ENTRY void ReleaseInputFocus()
	{
		TRACE("");
		return VRSystem()->ReleaseInputFocus();
	}

	WOVR_ENTRY bool IsInputFocusCapturedByAnotherProcess()
	{
		TRACEHOT("");
		return VRSystem()->IsInputFocusCapturedByAnotherProcess();
	}

	WOVR_ENTRY uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
	{
		TRACE("");
		return VRSystem()->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
	}

	WOVR_ENTRY vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		TRACE("");
		return VRSystem()->PerformFirmwareUpdate(unDeviceIndex);
	}

	WOVR_ENTRY void AcknowledgeQuit_Exiting()
	{
		TRACE("");
		VRSystem()->AcknowledgeQuit_Exiting();
		return;
	}

	WOVR_ENTRY void AcknowledgeQuit_UserPrompt()
	{
		TRACE("");
		VRSystem()->AcknowledgeQuit_UserPrompt();
		return;
	}

#if ABIVER < 12
	WOVR_ENTRY virtual void PerformanceTestEnableCapture( bool bEnable )
	{
		WARN("stub!");
		return;
	}

	WOVR_ENTRY virtual void PerformanceTestReportFidelityLevelChange( int nFidelityLevel )
	{
		WARN("stub!");
	}
#endif
};

IVRSystem* GETTER ()
{
	// XXX: Do we need error checking?
	return (IVRSystem*) new PROXYCLASS ();
};
