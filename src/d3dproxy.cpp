#include "d3dproxy.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include <vector>

#include <vulkan/vulkan.h>

#include <windows.h>
#include <dxgi.h>
#include <d3d11.h>

bool initted = false;

// Copied from dxvk_interop.h, because we kinda have to anyway
typedef unsigned int(*instanceCallback)(char***);
typedef unsigned int(*deviceCallback)(VkPhysicalDevice,char***);

void (__stdcall *dxvkRegisterInstanceExtCallback)(instanceCallback);
void (__stdcall *dxvkRegisterDeviceExtCallback)(deviceCallback);
void (__stdcall *dxvkGetVulkanImage)(ID3D11Texture2D*, VkImage*, uint32_t*, uint32_t*, uint32_t*, uint32_t*);
VkInstance (__stdcall *dxvkInstanceOfFactory)(IDXGIFactory*);
int32_t (__stdcall *dxvkPhysicalDeviceToAdapterIdx)(IDXGIFactory* fac, VkPhysicalDevice dev);
void (__stdcall *dxvkPhysicalDeviceToAdapterLUID)(VkPhysicalDevice dev, uint64_t* luid);
void (__stdcall *dxvkGetHandlesForVulkanOps)(ID3D11Device*, VkInstance*, VkPhysicalDevice*, VkDevice*, uint32_t*,
        VkQueue*);

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

unsigned int ArrayizeExts(char* extsIn, char*** extsOut)
{
  std::vector<char*> extsVec;
  // strlen()+1 so as to include the trailing null
  for(unsigned int i=0; i< strlen(extsIn) + 1 ;i++)
  {
      std::vector<char> thisExtV;
      
      if(extsIn[i] == ' ' || extsIn[i] == '\0')
      {
          char* thisExtA = (char*) malloc(sizeof(char) * thisExtV.size());
          extsVec.push_back(thisExtA);
          thisExtV.clear();
      }
      else
          thisExtV.push_back(extsIn[i]);
  }
  
  unsigned int nExts = extsVec.size();
  *extsOut = (char**) malloc(sizeof(char*) * nExts);
  for(unsigned int i=0;i<nExts;i++)
      (*extsOut)[i] = extsVec[i];
  
  return nExts;
}

unsigned int OurInstanceCallback(char*** extsOut)
{
    uint32_t extsIn_sz = VRCompositor()->GetVulkanInstanceExtensionsRequired(NULL, 0);
    char* extsIn = new char[extsIn_sz];
    VRCompositor()->GetVulkanInstanceExtensionsRequired(extsIn, extsIn_sz);
    
    unsigned int ret = ArrayizeExts(extsIn, extsOut);
    delete [] extsIn;
    return ret;
}

unsigned int OurDeviceCallback(VkPhysicalDevice pdev, char*** extsOut)
{
    uint32_t extsIn_sz = VRCompositor()->GetVulkanDeviceExtensionsRequired(pdev, NULL, 0);
    char* extsIn = new char[extsIn_sz];
    VRCompositor()->GetVulkanDeviceExtensionsRequired(pdev, extsIn, extsIn_sz);
    
    unsigned int ret = ArrayizeExts(extsIn, extsOut);
    delete [] extsIn;
    return ret;
}

bool Init()
{
    // --- Step 1: Get handle of dxgi.dll (Dxvk)
    
    // The application has no business calling DirectX-related OpenVR methods without linking dxgi.
    // XXX: This will break if some psycho decides to runtime link dxgi but does VR_Init() first.
    HMODULE dxvkHandle = GetModuleHandle("dxgi.dll");
    if(dxvkHandle == NULL)
    {
        ERR("Tried to initialize D3DProxy when dxgi.dll isn't loaded");
        return false;
    }

    // --- Step 2: Resolve Dxvk interop function addresses
#define RESOLVE_FUNC(FUNC) FUNC = ( typeof(FUNC) ) GetProcAddress(dxvkHandle, "FUNC"); \
        if(FUNC == NULL) \
        { \
            ERR("Failed to resolve FUNC. This usually means Dxvk is not installed correctly or is an incompatible version."); \
            return false; \
        }

    RESOLVE_FUNC(dxvkRegisterInstanceExtCallback)
    RESOLVE_FUNC(dxvkRegisterDeviceExtCallback)
    RESOLVE_FUNC(dxvkGetVulkanImage)
    RESOLVE_FUNC(dxvkInstanceOfFactory)
    RESOLVE_FUNC(dxvkPhysicalDeviceToAdapterIdx)
    RESOLVE_FUNC(dxvkPhysicalDeviceToAdapterLUID)
    RESOLVE_FUNC(dxvkGetHandlesForVulkanOps)

#undef RESOLVE_FUNC

    // --- Step 3: Register callbacks
    dxvkRegisterInstanceExtCallback(&OurInstanceCallback);
    dxvkRegisterDeviceExtCallback(&OurDeviceCallback);

    return true;
}

ID3DProxy* D3DProxy()
{
    if(!Init()) return NULL;
    static ID3DProxy ret;
    return &ret;
}
