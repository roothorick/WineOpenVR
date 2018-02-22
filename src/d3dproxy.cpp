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
typedef unsigned int(__stdcall *instanceCallback)(char***);
typedef unsigned int(__stdcall *deviceCallback)(VkPhysicalDevice,char***);

// We resolve the DXGI funcs manually, to ensure we're calling into dxvk
// This also avoids pulling in dxgi.dll on OpenGL and Vulkan apps
HRESULT (__stdcall *p_CreateDXGIFactory)(REFIID riid, void **ppFactory);

void (__stdcall *p_dxvkRegisterInstanceExtCallback)(instanceCallback);
void (__stdcall *p_dxvkRegisterDeviceExtCallback)(deviceCallback);
void (__stdcall *p_dxvkGetVulkanImage)(ID3D11Texture2D*, VkImage*, uint32_t*, uint32_t*, uint32_t*, uint32_t*);
VkInstance (__stdcall *p_dxvkInstanceOfFactory)(IDXGIFactory*);
int32_t (__stdcall *p_dxvkPhysicalDeviceToAdapterIdx)(IDXGIFactory* fac, VkPhysicalDevice dev);
void (__stdcall *p_dxvkPhysicalDeviceToAdapterLUID)(VkPhysicalDevice dev, uint64_t* luid);
void (__stdcall *p_dxvkGetHandlesForVulkanOps)(ID3D11Device*, VkInstance*, VkPhysicalDevice*, VkDevice*, uint32_t*,
        VkQueue*);

// IVRSystem
int32_t ID3DProxy::GetD3D9AdapterIndex()
{
    ERR("stub!");
    return -1;
}

// IVRSystem
void ID3DProxy::GetDXGIOutputInfo( int32_t *pnAdapterIndex )
{
    IDXGIFactory* fac;
    HRESULT hr = p_CreateDXGIFactory(__uuidof(IDXGIFactory), (void**) &fac);
    if (hr != S_OK)
    {
        ERR("Failed to create DXGI Factory: %x", hr);
        *pnAdapterIndex = 0;
        return;
    }
    
    VkInstance instance = p_dxvkInstanceOfFactory(fac);
    
    VkPhysicalDevice pdev;
    // TODO: third arg was added since 1.0.8
    // VRSystem()->GetOutputDevice(&pdev, TextureType_Vulkan, instance);
     VRSystem()->GetOutputDevice( (uint64_t*) &pdev, TextureType_Vulkan);
    
    *pnAdapterIndex = p_dxvkPhysicalDeviceToAdapterIdx(fac, pdev);
    return;
}

// IVRSystem
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

// IVRCompositor
void ID3DProxy::ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
{
    WARN("stub!");
    return;
}

// IVRCompositor
EVRCompositorError ID3DProxy::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
{
    ID3D11Texture2D* d3dTex = (ID3D11Texture2D*) pTexture->handle;
    ID3D11Device* d3ddev;
    d3dTex->GetDevice(&d3ddev);
    VRVulkanTextureData_t vTexData;
    Texture_t texOut;
    texOut.handle = (void*) &vTexData;
    texOut.eType = TextureType_Vulkan;
    texOut.eColorSpace = pTexture->eColorSpace;

    // For whatever reason, VRVulkanTextureData_t has a uint64_t instead of a VkImage.
    VkImage img;
    p_dxvkGetVulkanImage(
        d3dTex,
        &img,
        &vTexData.m_nWidth,
        &vTexData.m_nHeight,
        &vTexData.m_nFormat,
        &vTexData.m_nSampleCount
    );
    vTexData.m_nImage = (uint64_t) img;

    p_dxvkGetHandlesForVulkanOps(
            d3ddev,
            &vTexData.m_pInstance,
            &vTexData.m_pPhysicalDevice,
            &vTexData.m_pDevice,
            &vTexData.m_nQueueFamilyIndex,
            &vTexData.m_pQueue
        );
    
    EVRCompositorError ret = VRCompositor()->Submit(eEye, &texOut, pBounds, nSubmitFlags);
    if(ret != VRCompositorError_None) ERR("Submit failed: %u", ret);
    return ret;
}


// IVRCompositor
EVRCompositorError ID3DProxy::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
{
    // TODO
    WARN("stub!");
    // They'll never know...
    return VRCompositorError_None;
}

// IVROverlay
EVROverlayError ID3DProxy::GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
{
    WARN("stub!");
    return VROverlayError_RequestFailed;
}

// IVROverlay
EVROverlayError ID3DProxy::SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
{
    WARN("stub!");
    return VROverlayError_RequestFailed;
}

// IVRRenderModels
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

// IVRRenderModels
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

// IVRRenderModels
void ID3DProxy::FreeTextureD3D11( void *pD3D11Texture2D )
{
    // TODO:
    // Probably just blindly delete the texture, why not
    WARN("stub!");
    return;
}

// IVRExtendedDisplay
void ID3DProxy::ExtendedDisplay_GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
{
    ERR("stub!");
    *pnAdapterIndex = -1;
    *pnAdapterOutputIndex = -1;
    return;
}

// IVRTrackedCamera
EVRTrackedCameraError ID3DProxy::GetVideoStreamTextureD3D11( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
{
    ERR("stub!");
}

unsigned int ArrayizeExts(char* extsIn, char*** extsOut)
{
  std::vector<char*> extsVec;
  std::vector<char> thisExtV;
  // strlen()+1 so as to include the trailing null
  for(unsigned int i=0; i< strlen(extsIn) + 1 ;i++)
  {
      if(extsIn[i] == ' ' || extsIn[i] == '\0')
      {
          thisExtV.push_back('\0');
          char* thisExtA = (char*) malloc(sizeof(char) * thisExtV.size());
          TRACE("%s",thisExtV.data());
          strcpy(thisExtA, thisExtV.data());
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

__stdcall unsigned int OurInstanceCallback(char*** extsOut)
{
    TRACE("passed ptr %x", extsOut);
    uint32_t extsIn_sz = VRCompositor()->GetVulkanInstanceExtensionsRequired(NULL, 0);
    char* extsIn = new char[extsIn_sz];
    VRCompositor()->GetVulkanInstanceExtensionsRequired(extsIn, extsIn_sz);
    TRACE("%s", extsIn);
    
    unsigned int ret = ArrayizeExts(extsIn, extsOut);
    delete [] extsIn;
    return ret;
}

__stdcall unsigned int OurDeviceCallback(VkPhysicalDevice pdev, char*** extsOut)
{
    uint32_t extsIn_sz = VRCompositor()->GetVulkanDeviceExtensionsRequired(pdev, NULL, 0);
    char* extsIn = new char[extsIn_sz];
    VRCompositor()->GetVulkanDeviceExtensionsRequired(pdev, extsIn, extsIn_sz);
    TRACE("%s", extsIn);
    
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
#define RESOLVE_FUNC(FUNC) p_ ## FUNC = ( typeof(p_ ## FUNC) ) GetProcAddress(dxvkHandle, # FUNC ); \
        if(p_ ## FUNC == NULL) \
        { \
            ERR("Failed to resolve " # FUNC ". This usually means Dxvk is not installed correctly or is an incompatible version."); \
            return false; \
        }

    RESOLVE_FUNC(dxvkRegisterInstanceExtCallback)
    RESOLVE_FUNC(dxvkRegisterDeviceExtCallback)
    RESOLVE_FUNC(dxvkGetVulkanImage)
    RESOLVE_FUNC(dxvkInstanceOfFactory)
    RESOLVE_FUNC(dxvkPhysicalDeviceToAdapterIdx)
    RESOLVE_FUNC(dxvkPhysicalDeviceToAdapterLUID)
    RESOLVE_FUNC(dxvkGetHandlesForVulkanOps)
    RESOLVE_FUNC(CreateDXGIFactory)

#undef RESOLVE_FUNC

    // --- Step 3: Register callbacks
    p_dxvkRegisterInstanceExtCallback(&OurInstanceCallback);
    p_dxvkRegisterDeviceExtCallback(&OurDeviceCallback);

    return true;
}

ID3DProxy* D3DProxy()
{
    if(!initted && !Init()) return NULL;
    initted = true;
    static ID3DProxy ret;
    return &ret;
}
