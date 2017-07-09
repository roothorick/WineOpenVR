#pragma once

// The wrappers for individual IVRSystem functions. The various ivrsystem_xxx.cpp arrange these into a proxy class
// matching their corresponding ABI version.

#include "common.h"
#include "d3dproxy.h"
#include "repacked_structs.h"

namespace fns_IVRSystem
{
	inline void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRSystem()->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
		return;
	}

	inline HmdMatrix44_t GetProjectionMatrix( EVREye eEye, float fNearZ, float fFarZ )
	{
		return VRSystem()->GetProjectionMatrix(eEye, fNearZ, fFarZ);
	}

	inline void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom )
	{
		VRSystem()->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
		return;
	}

	inline bool ComputeDistortion( EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates )
	{
		return VRSystem()->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
	}

	inline HmdMatrix34_t GetEyeToHeadTransform( EVREye eEye )
	{
		return VRSystem()->GetEyeToHeadTransform(eEye);
	}

	inline bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter )
	{
		return VRSystem()->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
	}

	inline int32_t GetD3D9AdapterIndex()
	{
		return D3DProxy()->GetD3D9AdapterIndex();
	}

	inline void GetDXGIOutputInfo( int32_t *pnAdapterIndex )
	{
		D3DProxy()->GetDXGIOutputInfo(pnAdapterIndex);
		return;
	}

	inline void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
	{
		if(textureType == TextureType_DirectX || textureType == TextureType_DirectX12)
			D3DProxy()->GetOutputDevice(pnDevice, textureType);
		else // Natively supported (OpenGL or Vulkan); pass directly
			VRSystem()->GetOutputDevice(pnDevice, textureType);
		return;
	}

	inline bool IsDisplayOnDesktop()
	{
		return VRSystem()->IsDisplayOnDesktop();
	}

	inline bool SetDisplayVisibility( bool bIsVisibleOnDesktop )
	{
		return VRSystem()->SetDisplayVisibility(bIsVisibleOnDesktop);
	}

	inline void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount )
	{
		VRSystem()->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
		return;
	}

	inline void ResetSeatedZeroPose()
	{
		VRSystem()->ResetSeatedZeroPose();
		return;
	}

	inline HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose()
	{
		return VRSystem()->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	}

	inline HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose()
	{
		return VRSystem()->GetRawZeroPoseToStandingAbsoluteTrackingPose();
	}

	inline uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex)
	{
		return VRSystem()->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
	}

	inline EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId )
	{
		return VRSystem()->GetTrackedDeviceActivityLevel(unDeviceId);
	}

	inline void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform )
	{
		VRSystem()->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
		return;
	}

	inline vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType )
	{
		return VRSystem()->GetTrackedDeviceIndexForControllerRole(unDeviceType);
	}

	inline vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
	}

	inline ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->GetTrackedDeviceClass(unDeviceIndex);
	}

	inline bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->IsTrackedDeviceConnected(unDeviceIndex);
	}

	inline bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	inline float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	inline int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return VRSystem()->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	inline uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError )
	{
		return VRSystem()->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	inline HmdMatrix34_t GetMatrix34TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
	}

	inline uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError)
	{
		return VRSystem()->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
	}

	inline const char *GetPropErrorNameFromEnum( ETrackedPropertyError error )
	{
		return VRSystem()->GetPropErrorNameFromEnum(error);
	}

	inline bool PollNextEvent( Repacked_VREvent_t *pEvent, uint32_t uncbVREvent )
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

	inline bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, Repacked_VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose )
	{
		// Struct packing mismatch
		VREvent_t linpacked;
		bool ret;
		ret = VRSystem()->PollNextEventWithPose(eOrigin, &linpacked, sizeof(VREvent_t), pTrackedDevicePose);
		repackVREvent(&linpacked, pEvent);
		return ret;
	}

	inline const char *GetEventTypeNameFromEnum( EVREventType eType )
	{
		return VRSystem()->GetEventTypeNameFromEnum(eType);
	}

	inline HiddenAreaMesh_t GetHiddenAreaMesh( EVREye eEye, EHiddenAreaMeshType type )
	{
		return VRSystem()->GetHiddenAreaMesh(eEye, type);
	}

	inline bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VRSystem()->GetControllerState(unControllerDeviceIndex, &linpacked, sizeof(VRControllerState_t) );
		repackVRControllerState(&linpacked, pControllerState);
		return ret;
	}

	inline bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, Repacked_VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		// HACK: GCC seems to be interpreting #pragma pack differently from MSVC. We substitute our own value just to
		// preserve the stack.
		bool ret = VRSystem()->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, &linpacked, sizeof(VRControllerState_t), pTrackedDevicePose);
		repackVRControllerState(&linpacked, pControllerState);
		return ret;
	}

	inline void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec )
	{
		VRSystem()->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
		return;
	}

	inline const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId )
	{
		return VRSystem()->GetButtonIdNameFromEnum(eButtonId);
	}

	inline const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType )
	{
		return VRSystem()->GetControllerAxisTypeNameFromEnum(eAxisType);
	}

	inline bool CaptureInputFocus()
	{
		return VRSystem()->CaptureInputFocus();
	}

	inline void ReleaseInputFocus()
	{
		return VRSystem()->ReleaseInputFocus();
	}

	inline bool IsInputFocusCapturedByAnotherProcess()
	{
		return VRSystem()->IsInputFocusCapturedByAnotherProcess();
	}

	inline uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
	{
		return VRSystem()->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
	}

	inline vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex )
	{
		return VRSystem()->PerformFirmwareUpdate(unDeviceIndex);
	}

	inline void AcknowledgeQuit_Exiting()
	{
		VRSystem()->AcknowledgeQuit_Exiting();
		return;
	}

	inline void AcknowledgeQuit_UserPrompt()
	{
		VRSystem()->AcknowledgeQuit_UserPrompt();
		return;
	}
}
