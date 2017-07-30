#include "d3dproxy.h"
#include <d3d11.h>
#include <cstdio>

bool initted = false;

int32_t ID3DProxy::GetD3D9AdapterIndex()
{
    ERR("stub!");
    return -1;
}

void ID3DProxy::GetDXGIOutputInfo( int32_t *pnAdapterIndex )
{
    ERR("stub!");
    *pnAdapterIndex = 0;
    return;
}

void ID3DProxy::GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
{
    ERR("stub!");
}

// IVRCompositor
EVRCompositorError ID3DProxy::GetMirrorTextureD3D11( EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
{
    WARN("stub!");
    return VRCompositorError_RequestFailed;
}

void ID3DProxy::ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
{
    WARN("stub!");
    return;
}

EVRCompositorError ID3DProxy::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
{
    ERR("stub!");
    return VRCompositorError_RequestFailed;
}

EVRCompositorError ID3DProxy::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
{
    WARN("stub!");
    return VRCompositorError_RequestFailed;
}

EVROverlayError ID3DProxy::GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
{
    WARN("stub!");
    return VROverlayError_RequestFailed;
}

EVROverlayError ID3DProxy::SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
{
    WARN("stub!");
    return VROverlayError_RequestFailed;
}

EVRRenderModelError ID3DProxy::LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
{
    WARN("stub!");
    // (Pretend to) load forever
    return VRRenderModelError_Loading;
}

EVRRenderModelError ID3DProxy::LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
{
    WARN("stub!");
    // (Pretend to) load forever
    return VRRenderModelError_Loading;
}

void ID3DProxy::FreeTextureD3D11( void *pD3D11Texture2D )
{
    WARN("stub!");
    return;
}

void ID3DProxy::ExtendedDisplay_GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
{
    ERR("stub!");
    *pnAdapterIndex = -1;
    *pnAdapterOutputIndex = -1;
    return;
}

EVRTrackedCameraError ID3DProxy::GetVideoStreamTextureD3D11( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
{
    ERR("stub!");
}

bool Init()
{
    // TODO
    return true;
}

ID3DProxy* D3DProxy()
{
    if(!Init()) return NULL;
    static ID3DProxy ret;
    return &ret;
}
