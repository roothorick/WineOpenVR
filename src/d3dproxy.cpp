#include "d3dproxy.h"

#include <vector>
#include <cstdio>

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHX
#include <vkel.h>

#include <d3d11.h>

bool initted = false;

VkInstance instance;

int32_t ID3DProxy::GetD3D9AdapterIndex()
{
	printf("WOVR fixme: ID3DProxy::GetD3D9AdapterIndex stub!\n");
	return -1;
}

void ID3DProxy::GetDXGIOutputInfo( int32_t *pnAdapterIndex )
{
	printf("WOVR fixme: ID3DProxy::GetDXGIOutputInfo stub!\n");
	*pnAdapterIndex = 0;
	return;
}

void ID3DProxy::GetOutputDevice( uint64_t *pnDevice, ETextureType textureType )
{
    printf("WOVR fixme: ID3DProxy::GetOutputDevice stub!\n");
}

EVRCompositorError ID3DProxy::GetMirrorTextureD3D11( EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
{
	printf("WOVR fixme: ID3DProxy::GetMirrorTextureD3D11 stub!\n");
	return VRCompositorError_RequestFailed;
}

void ID3DProxy::ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
{
	printf("WOVR fixme: ID3DProxy::ReleaseMirrorTextureD3D11 stub!\n");
	return;
}

EVRCompositorError ID3DProxy::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
{
	printf("WOVR fixme: ID3DProxy::Submit stub!\n");
	return VRCompositorError_RequestFailed;
}

EVRCompositorError ID3DProxy::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
{
	printf("WOVR fixme: ID3DProxy::SetSkyboxOverride stub!\n");
	return VRCompositorError_RequestFailed;
}

EVROverlayError ID3DProxy::GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds )
{
	printf("WOVR fixme: ID3DProxy::GetOverlayTexture stub!\n");
	return VROverlayError_RequestFailed;
}

EVROverlayError ID3DProxy::SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture )
{
	printf("WOVR fixme: ID3DProxy::SetOverlayTexture stub!\n");
	return VROverlayError_RequestFailed;
}

EVRRenderModelError ID3DProxy::LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
{
	printf("WOVR fixme: ID3DProxy::LoadTextureD3D11_Async stub!\n");
	// (Pretend to) load forever
	return VRRenderModelError_Loading;
}

EVRRenderModelError ID3DProxy::LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
{
	printf("WOVR fixme: ID3DProxy::LoadIntoTextureD3D11_Async stub!\n");
	// (Pretend to) load forever
	return VRRenderModelError_Loading;
}

void ID3DProxy::FreeTextureD3D11( void *pD3D11Texture2D )
{
	printf("WOVR fixme: ID3DProxy::FreeTextureD3D11 stub!\n");
	return;
}

void ID3DProxy::ExtendedDisplay_GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
{
	printf("WOVR fixme: ID3DProxy::ExtendedDisplay_GetDXGIOutputInfo stub!\n");
	*pnAdapterIndex = -1;
	*pnAdapterOutputIndex = -1;
	return;
}

EVRTrackedCameraError ID3DProxy::GetVideoStreamTextureD3D11( TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize )
{
	printf("WOVR fixme: ID3DProxy::GetVideoStreamTextureD3D11 stub!\n");
	return VRTrackedCameraError_OperationFailed;
}

void arrayizeStr(char* in, std::vector<const char*> out, int len)
{
	out.clear();
	for(int i=0; i<len; i++)
	{
		if(in[i] == ' ' && in[i+1] != '\0')
		{
			out.push_back( &(in[i+1]) );
			in[i] = '\0';
		}
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL printVkError( VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
{
	printf("WOVR warning: D3DProxy printVkError: %s\n", msg);
	return VK_FALSE;
}

VkDebugReportCallbackEXT validationCallback;

bool Init()
{
	printf("WOVR info: D3DProxy Init: setting up Vulkan\n");

	if(vkelInit() != VK_TRUE)
	{
		printf("WOVR error: D3DProxy Init: vkelInit failed!\n");
		return false;
	}

	// ====================== Instance Creation

	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "WineOpenVR";
		appInfo.applicationVersion = 0x000001; // pre-alpha
		appInfo.pEngineName = "Wine";
		// XXX: Should query Wine version somehow
		appInfo.engineVersion = 0x020B00; // Assuming 2.11 (-staging, but that's implied by using Vulkan at all)
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Used for getting instance and device extensions
		char* in_exts;
		std::vector<const char*> out_exts;
		int len;

		// Get instance extensions needed
		len = VRCompositor()->GetVulkanInstanceExtensionsRequired(NULL, 0);
		if(len > 0)
		{
			in_exts = new char[len];
			VRCompositor()->GetVulkanInstanceExtensionsRequired(in_exts, len);
			arrayizeStr(in_exts, out_exts, len);
		}
		else printf ("WOVR warning: D3DProxy Init: No instance extensions needed?\n");

		// Needed for texture sharing with D3D (which is the whole point!)
		out_exts.push_back(VK_KHX_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME);

		// Needed to print messages from validation layers.
		// We COULD do without...technically. But we REALLY don't want to.
		// Besides, what are the odds it's not available?
		out_exts.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

		VkInstanceCreateInfo instanceInfo = {};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledLayerCount = 0;
		// instanceInfo.ppEnabledLayerNames = ...
		instanceInfo.enabledExtensionCount = out_exts.size();
		instanceInfo.ppEnabledExtensionNames = out_exts.data();

		VkResult res = vkCreateInstance(&instanceInfo, NULL, &instance);
		if(res != VK_SUCCESS)
		{
			printf("WOVR error: D3DProxy Init: failed to create Vulkan instance!\n");
			printf("WOVR error: This is usually caused by graphics drivers or Wine being too old or incompatible.\n");
			printf("WOVR error: Verify your system meets the requirements.\n");
			return false;
		}

		if(vkelInstanceInit(instance) != VK_TRUE)
		{
			printf("WOVR Error: D3DProxy Init: vkelInstanceInit() failed!\n");
			return false;
		}
	}

	// ====================== Setup Debug Callback
	{
		VkDebugReportCallbackCreateInfoEXT cbInfo = {};
		cbInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		cbInfo.flags =  VK_DEBUG_REPORT_ERROR_BIT_EXT |
						VK_DEBUG_REPORT_WARNING_BIT_EXT |
						VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
						VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
						VK_DEBUG_REPORT_DEBUG_BIT_EXT;
		cbInfo.pfnCallback = printVkError;

		if(vkCreateDebugReportCallbackEXT(instance, &cbInfo, NULL, &validationCallback) != VK_SUCCESS)
		{
			printf("WOVR warning: D3DProxy Init: Failed to register validation report callback!\n");
			return false;
		}
	}

	return true;
}

// In case we ever find an application that'll shutdown VR but continue with something else, or even start VR multiple
// times.
void D3DProxy_Shutdown()
{
	vkDestroyDebugReportCallbackEXT(&instance, &validationCallback, NULL);
	vkDestroyInstance(&instance, NULL);
}


ID3DProxy* D3DProxy()
{
	if(!initted)
	{
		if(!Init()) return NULL;
		initted = true;
	}
	static ID3DProxy ret;
	return &ret;
}
