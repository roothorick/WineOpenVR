#include <cstdio>

// HACK: No idea where this should actually be defined
#define nullptr 0x0
#include "openvr.h"
using namespace vr;

#include "repacked_structs.h"

#define THISCALL __attribute__((thiscall))

class clone_IVRSystem
{
public:
	THISCALL virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	THISCALL virtual void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ ) = 0; // ERP hack
	THISCALL virtual void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) = 0;
	THISCALL virtual bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates ) = 0;
	THISCALL virtual void GetEyeToHeadTransform(HmdMatrix34_t* ret, EVREye eEye ) = 0; // ERP hack
	THISCALL virtual bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) = 0;
	THISCALL virtual int32_t GetD3D9AdapterIndex() = 0;
	THISCALL virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex ) = 0;
	THISCALL virtual bool IsDisplayOnDesktop() = 0;
	THISCALL virtual bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) = 0;
	THISCALL virtual void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) = 0;
	THISCALL virtual void ResetSeatedZeroPose() = 0;
	THISCALL virtual void GetSeatedZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret) = 0; // ERP hack
	THISCALL virtual void GetRawZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret) = 0; // ERP hack
	THISCALL virtual uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex ) = 0;
	THISCALL virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId ) = 0;
	THISCALL virtual void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform ) = 0;
	THISCALL virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType ) = 0;
	THISCALL virtual vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	THISCALL virtual ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	THISCALL virtual bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	THISCALL virtual bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	THISCALL virtual float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	THISCALL virtual int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	THISCALL virtual uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0;
	THISCALL virtual void GetMatrix34TrackedDeviceProperty(HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError ) = 0; // ERP hack
	THISCALL virtual uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError ) = 0;
	THISCALL virtual const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) = 0;
	THISCALL virtual bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent ) = 0; // Struct packing mismatch
	THISCALL virtual bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) = 0; // Struct packing mismatch
	THISCALL virtual const char *GetEventTypeNameFromEnum( EVREventType eType ) = 0;
	THISCALL virtual void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard ) = 0; // ERP hack
	THISCALL virtual bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize ) = 0;
	THISCALL virtual bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose ) = 0;
	THISCALL virtual void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) = 0;
	THISCALL virtual const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) = 0;
	THISCALL virtual const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) = 0;
	THISCALL virtual bool CaptureInputFocus() = 0;
	THISCALL virtual void ReleaseInputFocus() = 0;
	THISCALL virtual bool IsInputFocusCapturedByAnotherProcess() = 0;
	THISCALL virtual uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) = 0;
	THISCALL virtual vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;
	THISCALL virtual void AcknowledgeQuit_Exiting() = 0;
	THISCALL virtual void AcknowledgeQuit_UserPrompt() = 0;
};

class proxy_IVRSystem : public clone_IVRSystem
{
public:
	proxy_IVRSystem(IVRSystem* real) { realImpl = real; }

	THISCALL void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
	{
		realImpl->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
		return;
	}

	THISCALL void GetProjectionMatrix(HmdMatrix44_t* ret, EVREye eEye, float fNearZ, float fFarZ )
	{
		// ERP hack
		*ret = realImpl->GetProjectionMatrix(eEye, fNearZ, fFarZ);
		return;
	}

	THISCALL void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
	{
		realImpl->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
		return;
	}

	THISCALL bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates )
	{
		return realImpl->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
	}

	THISCALL void GetEyeToHeadTransform(HmdMatrix34_t* ret, EVREye eEye )
	{
		// ERP hack
		*ret = realImpl->GetEyeToHeadTransform(eEye);
		return;
	}

	THISCALL bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter )
	{
		return realImpl->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
	}

	THISCALL int32_t GetD3D9AdapterIndex()
	{
		// STUB
		printf("WOVR fixme: GetD3D9AdapterIndex stub!\n");
		return 0;
	}

	THISCALL void GetDXGIOutputInfo( int32_t *pnAdapterIndex )
	{
		// STUB
		printf("WOVR fixme: GetDXGIOutputInfo stub!\n");
		pnAdapterIndex = 0;
		return;
	}

	THISCALL bool IsDisplayOnDesktop()
	{
		return realImpl->IsDisplayOnDesktop();
	}

	THISCALL bool SetDisplayVisibility( bool bIsVisibleOnDesktop )
	{
		return realImpl->SetDisplayVisibility(bIsVisibleOnDesktop);
	}

	THISCALL void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount )
	{
		realImpl->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
		return;
	}

	THISCALL void ResetSeatedZeroPose()
	{
		realImpl->ResetSeatedZeroPose();
		return;
	}

	THISCALL void GetSeatedZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret)
	{
		// ERP hack
		*ret = realImpl->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	THISCALL void GetRawZeroPoseToStandingAbsoluteTrackingPose(HmdMatrix34_t* ret)
	{
		// ERP hack
		*ret = realImpl->GetRawZeroPoseToStandingAbsoluteTrackingPose();
		return;
	}

	THISCALL uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex)
	{
		return realImpl->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
	}

	THISCALL EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId )
	{
		return realImpl->GetTrackedDeviceActivityLevel(unDeviceId);
	}
	THISCALL void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform )
	{
		// Gotcha: The real method really does return nothing and take a pointer to struct for its first argument.
		// No ERP hack here.
		realImpl->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
		return;
	}

	THISCALL vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType )
	{
		return realImpl->GetTrackedDeviceIndexForControllerRole(unDeviceType);
	}

	THISCALL vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return realImpl->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
	}

	THISCALL ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return realImpl->GetTrackedDeviceClass(unDeviceIndex);
	}

	THISCALL bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return realImpl->IsTrackedDeviceConnected(unDeviceIndex);
	}

	THISCALL bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return realImpl->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	THISCALL float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return realImpl->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	THISCALL int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return realImpl->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	THISCALL uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return realImpl->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	THISCALL void GetMatrix34TrackedDeviceProperty(HmdMatrix34_t* ret, vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		// ERP hack
		*ret = realImpl->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
		return;
	}

	THISCALL uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError)
	{
		return realImpl->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
	}

	THISCALL const char *GetPropErrorNameFromEnum( ETrackedPropertyError error )
	{
		return realImpl->GetPropErrorNameFromEnum(error);
	}

	THISCALL bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
	{
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;

		//printf("WOVR trace: PollNextEvent: winpack %u, linpack %u, passed %u\n", sizeof(Repacked_VREvent_t), sizeof(VREvent_t), uncbVREvent);

		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		ret = realImpl->PollNextEvent(&linpacked, sizeof(VREvent_t) );

		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	THISCALL bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
	{
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;

		ret = realImpl->PollNextEventWithPose(eOrigin, &linpacked, sizeof(VREvent_t), pTrackedDevicePose);

		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	THISCALL const char *GetEventTypeNameFromEnum( EVREventType eType )
	{
		return realImpl->GetEventTypeNameFromEnum(eType);
	}

	THISCALL void GetHiddenAreaMesh(HiddenAreaMesh_t* ret, EVREye eEye, EHiddenAreaMeshType type )
	{
		// ERP hack
		*ret = realImpl->GetHiddenAreaMesh(eEye, type);
		return;
	}

	THISCALL bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize )
	{
		return realImpl->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize);
	}

	THISCALL bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose )
	{
		return realImpl->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose);
	}

	THISCALL void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec )
	{
		realImpl->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
		return;
	}

	THISCALL const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId )
	{
		return realImpl->GetButtonIdNameFromEnum(eButtonId);
	}

	THISCALL const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType )
	{
		return realImpl->GetControllerAxisTypeNameFromEnum(eAxisType);
	}

	THISCALL bool CaptureInputFocus()
	{
		return realImpl->CaptureInputFocus();
	}

	THISCALL void ReleaseInputFocus()
	{
		return realImpl->ReleaseInputFocus();
	}

	THISCALL bool IsInputFocusCapturedByAnotherProcess()
	{
		return realImpl->IsInputFocusCapturedByAnotherProcess();
	}

	THISCALL uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
	{
		return realImpl->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
	}

	THISCALL vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return realImpl->PerformFirmwareUpdate(unDeviceIndex);
	}

	THISCALL void AcknowledgeQuit_Exiting()
	{
		realImpl->AcknowledgeQuit_Exiting();
		return;
	}

	THISCALL void AcknowledgeQuit_UserPrompt()
	{
		realImpl->AcknowledgeQuit_UserPrompt();
		return;
	}

private:
	IVRSystem* realImpl;
};

IVRSystem* getIVRSystemProxy (IVRSystem* real)
{
	// XXX: Do we need error checking?
	return (IVRSystem*) new proxy_IVRSystem(real);
};
