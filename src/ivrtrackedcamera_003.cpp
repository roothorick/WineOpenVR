#include "ivrtrackedcamera.h"

class clone_IVRTrackedCamera_003
{
public:
	WOVR_ENTRY virtual const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamingService( vr::TrackedCameraHandle_t hTrackedCamera ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId ) = 0;
};

class proxy_IVRTrackedCamera_003 : public clone_IVRTrackedCamera_003
{
public:
	WOVR_ENTRY const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError )
	{
		return fns_IVRTrackedCamera::GetCameraErrorNameFromEnum(eCameraError);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera )
	{
		return fns_IVRTrackedCamera::HasCamera(nDeviceIndex, pHasCamera);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize )
	{
		return fns_IVRTrackedCamera::GetCameraFrameSize(nDeviceIndex, eFrameType, pnWidth, pnHeight, pnFrameBufferSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter )
	{
		return fns_IVRTrackedCamera::GetCameraIntrinsics(nDeviceIndex, eFrameType, pFocalLength, pCenter);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection )
	{
		return fns_IVRTrackedCamera::GetCameraProjection(nDeviceIndex, eFrameType, flZNear, flZFar, pProjection);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle )
	{
		return fns_IVRTrackedCamera::AcquireVideoStreamingService(nDeviceIndex, pHandle);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError ReleaseVideoStreamingService( vr::TrackedCameraHandle_t hTrackedCamera )
	{
		return fns_IVRTrackedCamera::ReleaseVideoStreamingService(hTrackedCamera);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return fns_IVRTrackedCamera::GetVideoStreamFrameBuffer(hTrackedCamera, eFrameType, pFrameBuffer, nFrameBufferSize, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		return fns_IVRTrackedCamera::GetVideoStreamTextureSize(nDeviceIndex, eFrameType, pTextureBounds, pnWidth, pnHeight);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return fns_IVRTrackedCamera::GetVideoStreamTextureD3D11(hTrackedCamera, eFrameType, pD3D11DeviceOrResource, ppD3D11ShaderResourceView, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return fns_IVRTrackedCamera::GetVideoStreamTextureGL(hTrackedCamera, eFrameType, pglTextureId, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId )
	{
		return fns_IVRTrackedCamera::ReleaseVideoStreamTextureGL(hTrackedCamera, glTextureId);
	}
};

IVRTrackedCamera* getIVRTrackedCameraProxy_003()
{
	return (IVRTrackedCamera*) new proxy_IVRTrackedCamera_003();
}
