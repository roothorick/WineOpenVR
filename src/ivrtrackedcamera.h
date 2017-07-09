#include "common.h"
#include "d3dproxy.h"

namespace fns_IVRTrackedCamera
{
	inline const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError )
	{
		return VRTrackedCamera()->GetCameraErrorNameFromEnum(eCameraError);
	}

	inline vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera )
	{
		return VRTrackedCamera()->HasCamera(nDeviceIndex, pHasCamera);
	}

	inline vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize )
	{
		return VRTrackedCamera()->GetCameraFrameSize(nDeviceIndex, eFrameType, pnWidth, pnHeight, pnFrameBufferSize);
	}

	inline vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter )
	{
		return VRTrackedCamera()->GetCameraIntrinsics(nDeviceIndex, eFrameType, pFocalLength, pCenter);
	}

	inline vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection )
	{
		return VRTrackedCamera()->GetCameraProjection(nDeviceIndex, eFrameType, flZNear, flZFar, pProjection);
	}

	inline vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle )
	{
		return VRTrackedCamera()->AcquireVideoStreamingService(nDeviceIndex, pHandle);
	}

	inline vr::EVRTrackedCameraError ReleaseVideoStreamingService( vr::TrackedCameraHandle_t hTrackedCamera )
	{
		return VRTrackedCamera()->ReleaseVideoStreamingService(hTrackedCamera);
	}

	inline vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return VRTrackedCamera()->GetVideoStreamFrameBuffer(hTrackedCamera, eFrameType, pFrameBuffer, nFrameBufferSize, pFrameHeader, nFrameHeaderSize);
	}

	inline vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		return VRTrackedCamera()->GetVideoStreamTextureSize(nDeviceIndex, eFrameType, pTextureBounds, pnWidth, pnHeight);
	}

	inline vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return D3DProxy()->GetVideoStreamTextureD3D11(hTrackedCamera, eFrameType, pD3D11DeviceOrResource, ppD3D11ShaderResourceView, pFrameHeader, nFrameHeaderSize);
	}

	inline vr::EVRTrackedCameraError GetVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return VRTrackedCamera()->GetVideoStreamTextureGL(hTrackedCamera, eFrameType, pglTextureId, pFrameHeader, nFrameHeaderSize);
	}

	inline vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId )
	{
		return VRTrackedCamera()->ReleaseVideoStreamTextureGL(hTrackedCamera, glTextureId);
	}
}
