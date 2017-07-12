#pragma once
#include "common.h"

// Proxy class that simulates the OpenVR API's Direct3D functionality

struct ID3DProxy
{
    // IVRSystem
    int32_t GetD3D9AdapterIndex();
    void GetDXGIOutputInfo( int32_t *pnAdapterIndex );
    void GetOutputDevice( uint64_t *pnDevice, ETextureType textureType );

    // IVRCompositor
    EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default );
    EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount );
    EVRCompositorError GetMirrorTextureD3D11( EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView );
    void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView );

    // IVROverlay
    EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds );
    EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture );

    // IVRRenderModels
	EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D );
	EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture );
	void FreeTextureD3D11( void *pD3D11Texture2D );

    // IVRExtendedDisplay
    void ExtendedDisplay_GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex );

    // IVRTrackedCamera
    EVRTrackedCameraError GetVideoStreamTextureD3D11( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize );
};

// Get the Direct3D proxy, initializing it if it hasn't been already.
// Returns NULL if initialization failed.
ID3DProxy* D3DProxy();
