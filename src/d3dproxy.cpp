#include "d3dproxy.h"
#include <d3d11.h>
#include <cstdio>
#include <windows.h>

bool initted = false;

int32_t ID3DProxy::GetD3D9AdapterIndex()
{
    ERR("stub!");
    return -1;
}

void ID3DProxy::GetDXGIOutputInfo( int32_t *pnAdapterIndex )
{
    // TODO:
    // Query OpenVR for the needed VkPhysicalDevice. Ask dxvk for the matching adapter index. Return that.
    ERR("stub!");
    *pnAdapterIndex = 0;
    return;
}

void ID3DProxy::GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
{
    // TODO:
    // Query OpenVR for the needed VkPhysicalDevice. Ask dxvk for the matching adapter LUID. Return that.
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
    // TODO:
    // if we don't have the Vulkan device, queue, and queue family index in our struct
        // Get them from dxvk
    // Ask dxvk for the backing VkImage, width, height, format, and sample count. Fill out our texture data struct. Submit.

    ERR("stub!");
    return VRCompositorError_RequestFailed;
}

EVRCompositorError ID3DProxy::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
{
    WARN("stub!");
    // XXX: Probably should just fail silently here
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
    // TODO:
    // call LoadTexture_Async. If it returns VRRenderModelError_Loading, then
        // pass that on.
    // if not
        // Create a D3D112Texture2D and copy the texture into it. Immediately free the original texture. Return the D3D texture.
        // (This should be a common method to LoadTextureD3D11_Async and LoadIntoTextureD3D11_Async)

    WARN("stub!");
    // (Pretend to) load forever
    return VRRenderModelError_Loading;
}

EVRRenderModelError ID3DProxy::LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
{
    // TODO:
    // call LoadTexture_Async. If it returns VRRenderModelError_Loading, then
        // pass that on.
    // if not
        // Copy the texture from OpenVR into the app's texture. Immediately free the texture from OpenVR.
        // (This should be a common method to LoadTextureD3D11_Async and LoadIntoTextureD3D11_Async)

    WARN("stub!");
    // (Pretend to) load forever
    return VRRenderModelError_Loading;
}

void ID3DProxy::FreeTextureD3D11( void *pD3D11Texture2D )
{
    // TODO:
    // Probably just blindly delete the texture, why not
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

// TODO: Callback to register with dxvk for providing additional instance and device extensions (one cb each),
// by calling GetVulkanInstanceExtensionsRequired and GetVulkanDeviceExtensionsRequired respectively

// TODO: A DllMain that registers the callbacks

bool Init()
{
    // XXX: Check if the callbacks were successfully registered?
    return true;
}

ID3DProxy* D3DProxy()
{
    if(!Init()) return NULL;
    static ID3DProxy ret;
    return &ret;
}
