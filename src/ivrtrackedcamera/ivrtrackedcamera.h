#include "common.h"
#include "d3dproxy.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRTrackedCamera_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRTrackedCamera_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRTrackedCameraProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

#if ABIVER < 3
// XXX: This may explode on 32bit
typedef void* WOVR_TrackedCameraHandle_t;
#else
typedef uint64_t WOVR_TrackedCameraHandle_t;
#endif

class CLONECLASS
{
public:
	WOVR_ENTRY virtual const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, WOVR_TrackedCameraHandle_t *pHandle ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamingService( WOVR_TrackedCameraHandle_t hTrackedCamera ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError GetVideoStreamTextureGL( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) = 0;
	WOVR_ENTRY virtual vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError )
	{
		return VRTrackedCamera()->GetCameraErrorNameFromEnum(eCameraError);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera )
	{
		return VRTrackedCamera()->HasCamera(nDeviceIndex, pHasCamera);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize )
	{
		return VRTrackedCamera()->GetCameraFrameSize(nDeviceIndex, eFrameType, pnWidth, pnHeight, pnFrameBufferSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraIntrinsics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter )
	{
		return VRTrackedCamera()->GetCameraIntrinsics(nDeviceIndex, eFrameType, pFocalLength, pCenter);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection )
	{
		return VRTrackedCamera()->GetCameraProjection(nDeviceIndex, eFrameType, flZNear, flZFar, pProjection);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, WOVR_TrackedCameraHandle_t *pHandle )
	{
		return VRTrackedCamera()->AcquireVideoStreamingService(nDeviceIndex, (TrackedCameraHandle_t*) pHandle);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError ReleaseVideoStreamingService( WOVR_TrackedCameraHandle_t hTrackedCamera )
	{
		return VRTrackedCamera()->ReleaseVideoStreamingService( (TrackedCameraHandle_t) hTrackedCamera);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return VRTrackedCamera()->GetVideoStreamFrameBuffer( (TrackedCameraHandle_t) hTrackedCamera, eFrameType, pFrameBuffer, nFrameBufferSize, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::VRTextureBounds_t *pTextureBounds, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		return VRTrackedCamera()->GetVideoStreamTextureSize(nDeviceIndex, eFrameType, pTextureBounds, pnWidth, pnHeight);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureD3D11( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return D3DProxy()->GetVideoStreamTextureD3D11( (TrackedCameraHandle_t) hTrackedCamera, eFrameType, pD3D11DeviceOrResource, ppD3D11ShaderResourceView, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError GetVideoStreamTextureGL( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, vr::glUInt_t *pglTextureId, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
	{
		return VRTrackedCamera()->GetVideoStreamTextureGL( (TrackedCameraHandle_t) hTrackedCamera, eFrameType, pglTextureId, pFrameHeader, nFrameHeaderSize);
	}

	WOVR_ENTRY vr::EVRTrackedCameraError ReleaseVideoStreamTextureGL( WOVR_TrackedCameraHandle_t hTrackedCamera, vr::glUInt_t glTextureId )
	{
		return VRTrackedCamera()->ReleaseVideoStreamTextureGL( (TrackedCameraHandle_t) hTrackedCamera, glTextureId);
	}
};

IVRTrackedCamera* GETTER ()
{
	return (IVRTrackedCamera*) new PROXYCLASS ();
}
