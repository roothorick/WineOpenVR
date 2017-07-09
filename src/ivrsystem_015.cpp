#include "ivrsystem.h"

class clone_IVRSystem_015
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

class proxy_IVRSystem_015 : public clone_IVRSystem_015
{
public:
	WOVR_ENTRY void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
	{
		fns_IVRSystem::GetRecommendedRenderTargetSize(pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ )
	{
		// ERP hack
		*ret = fns_IVRSystem::GetProjectionMatrix(eEye, fNearZ, fFarZ);
		return;
	}

	WOVR_ENTRY void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
	{
		fns_IVRSystem::GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
		return;
	}

	WOVR_ENTRY bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates )
	{
		return fns_IVRSystem::ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
	}

	WOVR_ENTRY void GetEyeToHeadTransform(HmdMatrix34_t* ret, EVREye eEye )
	{
		// ERP hack
		*ret = fns_IVRSystem::GetEyeToHeadTransform(eEye);
		return;
	}

	WOVR_ENTRY bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter )
	{
		return fns_IVRSystem::GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
	}

	WOVR_ENTRY int32_t GetD3D9AdapterIndex()
	{
		return fns_IVRSystem::GetD3D9AdapterIndex();
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex )
	{
		fns_IVRSystem::GetDXGIOutputInfo(pnAdapterIndex);
		return;
	}

	WOVR_ENTRY bool IsDisplayOnDesktop()
	{
		return fns_IVRSystem::IsDisplayOnDesktop();
	}

	WOVR_ENTRY bool SetDisplayVisibility( bool bIsVisibleOnDesktop )
	{
		return fns_IVRSystem::SetDisplayVisibility(bIsVisibleOnDesktop);
	}

	WOVR_ENTRY void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount )
	{
		fns_IVRSystem::GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
		return;
	}

	WOVR_ENTRY void ResetSeatedZeroPose()
	{
		fns_IVRSystem::ResetSeatedZeroPose();
		return;
	}

	WOVR_ENTRY void GetSeatedZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret)
	{
		// ERP hack
		*ret = fns_IVRSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY void GetRawZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret)
	{
		// ERP hack
		*ret = fns_IVRSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	WOVR_ENTRY uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex)
	{
		return fns_IVRSystem::GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
	}

	WOVR_ENTRY EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId )
	{
		return fns_IVRSystem::GetTrackedDeviceActivityLevel(unDeviceId);
	}
	WOVR_ENTRY void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform )
	{
		// Gotcha: The real method really does return nothing and take a pointer to struct for its first argument.
		// No ERP hack here.
		fns_IVRSystem::ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
		return;
	}

	WOVR_ENTRY vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType )
	{
		return fns_IVRSystem::GetTrackedDeviceIndexForControllerRole(unDeviceType);
	}

	WOVR_ENTRY vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return fns_IVRSystem::GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
	}

	WOVR_ENTRY ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return fns_IVRSystem::GetTrackedDeviceClass(unDeviceIndex);
	}

	WOVR_ENTRY bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return fns_IVRSystem::IsTrackedDeviceConnected(unDeviceIndex);
	}

	WOVR_ENTRY bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return fns_IVRSystem::GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return fns_IVRSystem::GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return fns_IVRSystem::GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return fns_IVRSystem::GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	WOVR_ENTRY void GetMatrix34TrackedDeviceProperty(HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		// ERP hack
		*ret = fns_IVRSystem::GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
		return;
	}

	WOVR_ENTRY uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError)
	{
		return fns_IVRSystem::GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
	}

	WOVR_ENTRY const char *GetPropErrorNameFromEnum( ETrackedPropertyError error )
	{
		return fns_IVRSystem::GetPropErrorNameFromEnum(error);
	}

	WOVR_ENTRY bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		return fns_IVRSystem::PollNextEvent(pEvent, uncbVREvent);
	}

	WOVR_ENTRY bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
	{
		return fns_IVRSystem::PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose);
	}

	WOVR_ENTRY const char *GetEventTypeNameFromEnum( EVREventType eType )
	{
		return fns_IVRSystem::GetEventTypeNameFromEnum(eType);
	}

	WOVR_ENTRY void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type )
	{
		// ERP hack
		*ret = fns_IVRSystem::GetHiddenAreaMesh(eEye, type);
		return;
	}

	WOVR_ENTRY bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize )
	{
		return fns_IVRSystem::GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize);
	}

	WOVR_ENTRY bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose )
	{
		return fns_IVRSystem::GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose);
	}

	WOVR_ENTRY void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec )
	{
		fns_IVRSystem::TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
		return;
	}

	WOVR_ENTRY const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId )
	{
		return fns_IVRSystem::GetButtonIdNameFromEnum(eButtonId);
	}

	WOVR_ENTRY const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType )
	{
		return fns_IVRSystem::GetControllerAxisTypeNameFromEnum(eAxisType);
	}

	WOVR_ENTRY bool CaptureInputFocus()
	{
		return fns_IVRSystem::CaptureInputFocus();
	}

	WOVR_ENTRY void ReleaseInputFocus()
	{
		return fns_IVRSystem::ReleaseInputFocus();
	}

	WOVR_ENTRY bool IsInputFocusCapturedByAnotherProcess()
	{
		return fns_IVRSystem::IsInputFocusCapturedByAnotherProcess();
	}

	WOVR_ENTRY uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
	{
		return fns_IVRSystem::DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
	}

	WOVR_ENTRY vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return fns_IVRSystem::PerformFirmwareUpdate(unDeviceIndex);
	}

	WOVR_ENTRY void AcknowledgeQuit_Exiting()
	{
		fns_IVRSystem::AcknowledgeQuit_Exiting();
		return;
	}

	WOVR_ENTRY void AcknowledgeQuit_UserPrompt()
	{
		fns_IVRSystem::AcknowledgeQuit_UserPrompt();
		return;
	}
};

IVRSystem* getIVRSystemProxy_015 ()
{
	// XXX: Do we need error checking?
	return (IVRSystem*) new proxy_IVRSystem_015;
};
