#include "common.h"
#include "d3dproxy.h"

class clone_IVRTrackedCamera
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

class proxy_IVRTrackedCamera : public clone_IVRTrackedCamera
{
public:
	proxy_IVRTrackedCamera(IVRTrackedCamera* real) { realImpl = real; }

	WOVR_ENTRY virtual const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError )
	{
		return realImpl->GetCameraErrorNameFromEnum(eCameraError);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera )
	{
		return realImpl->HasCamera(nDeviceIndex, pHasCamera);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize )
	{
		return realImpl->GetCameraFrameSize(nDeviceIndex, eFrameType, pnWidth, pnHeight, pnFrameBufferSize);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter )
	{
		return realImpl->GetCameraIntrinsics(nDeviceIndex, eFrameType, pFocalLength, pCenter);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection )
	{
		return realImpl->GetCameraProjection(nDeviceIndex, eFrameType, flZNear, flZFar, pProjection);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle )
	{
		return realImpl->AcquireVideoStreamingService(nDeviceIndex, pHandle);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamingService( vr::TrackedCameraHandle_t hTrackedCamera )
	{
		return realImpl->ReleaseVideoStreamingService(hTrackedCamera);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return realImpl->GetVideoStreamFrameBuffer(hTrackedCamera, eFrameType, pFrameBuffer, nFrameBufferSize, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		return realImpl->GetVideoStreamTextureSize(nDeviceIndex, eFrameType, pTextureBounds, pnWidth, pnHeight);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return D3DProxy()->GetVideoStreamTextureD3D11(hTrackedCamera, eFrameType, pD3D11DeviceOrResource, ppD3D11ShaderResourceView, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return realImpl->GetVideoStreamTextureGL(hTrackedCamera, eFrameType, pglTextureId, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( vr::TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId )
	{
		return realImpl->ReleaseVideoStreamTextureGL(hTrackedCamera, glTextureId);
	}

private:
	IVRTrackedCamera* realImpl;
};

IVRTrackedCamera* getIVRTrackedCameraProxy(IVRTrackedCamera* real)
{
	return (IVRTrackedCamera*) new proxy_IVRTrackedCamera(real);
}
