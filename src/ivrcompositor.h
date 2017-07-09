#include "common.h"
#include "d3dproxy.h"

namespace fns_IVRCompositor
{
	inline void SetTrackingSpace( ETrackingUniverseOrigin eOrigin )
	{
		VRCompositor()->SetTrackingSpace(eOrigin);
		return;
	}

	inline ETrackingUniverseOrigin GetTrackingSpace()
	{
		return VRCompositor()->GetTrackingSpace();
	}

	inline EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return VRCompositor()->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	inline EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return VRCompositor()->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	inline EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose )
	{
		return VRCompositor()->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
	}

	inline EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
	{
		static bool bReportedTextureType = false;
		if(!bReportedTextureType)
		{
			switch(pTexture->eType)
			{
				case TextureType_DirectX:
					printf("WOVR info: IVRCompositor::Submit: DirectX 11 application.\n");
					break;

				case TextureType_OpenGL:
					printf("WOVR info: IVRCompositor::Submit: OpenGL application.\n");
					break;

				case TextureType_Vulkan:
					printf("WOVR info: IVRCompositor::Submit: Vulkan application.\n");
					break;

				case TextureType_DirectX12:
					printf("WOVR info: IVRCompositor::Submit: DirectX 12 application.\n");
					break;

				default:
					printf("WOVR error: IVRCompositor::Submit: Unknown texture type!\n");
					return VRCompositorError_InvalidTexture;
			}
		}

		if(pTexture->eType == TextureType_DirectX || pTexture->eType == TextureType_DirectX12)
			return D3DProxy()->Submit(eEye, pTexture, pBounds, nSubmitFlags);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VRCompositor()->Submit(eEye, pTexture, pBounds, nSubmitFlags);
	}

	inline void ClearLastSubmittedFrame()
	{
		VRCompositor()->ClearLastSubmittedFrame();
		return;
	}

	inline void PostPresentHandoff()
	{
		VRCompositor()->PostPresentHandoff();
		return;
	}

	inline bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo )
	{
		return VRCompositor()->GetFrameTiming(pTiming, unFramesAgo);
	}

	inline uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames )
	{
		return VRCompositor()->GetFrameTimings(pTiming, nFrames);
	}

	inline float GetFrameTimeRemaining()
	{
		return VRCompositor()->GetFrameTimeRemaining();
	}

	inline void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes )
	{
		VRCompositor()->GetCumulativeStats(pStats, nStatsSizeInBytes);
		return;
	}

	inline void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground )
	{
		VRCompositor()->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
		return;
	}

	inline HmdColor_t GetCurrentFadeColor( bool bBackground )
	{
		return VRCompositor()->GetCurrentFadeColor(bBackground);
	}

	inline void FadeGrid( float fSeconds, bool bFadeIn )
	{
		VRCompositor()->FadeGrid(fSeconds, bFadeIn);
		return;
	}

	inline float GetCurrentGridAlpha()
	{
		return VRCompositor()->GetCurrentGridAlpha();
	}

	inline EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
	{
		if(pTextures->eType == TextureType_DirectX || pTextures->eType == TextureType_DirectX12)
			return D3DProxy()->SetSkyboxOverride(pTextures, unTextureCount);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VRCompositor()->SetSkyboxOverride(pTextures, unTextureCount);
	}

	inline void ClearSkyboxOverride()
	{
		VRCompositor()->ClearSkyboxOverride();
		return;
	}

	inline void CompositorBringToFront()
	{
		VRCompositor()->CompositorBringToFront();
		return;
	}

	inline void CompositorGoToBack()
	{
		VRCompositor()->CompositorGoToBack();
		return;
	}

	inline void CompositorQuit()
	{
		VRCompositor()->CompositorQuit();
		return;
	}

	inline bool IsFullscreen()
	{
		return VRCompositor()->IsFullscreen();
	}

	inline uint32_t GetCurrentSceneFocusProcess()
	{
		return VRCompositor()->GetCurrentSceneFocusProcess();
	}

	inline uint32_t GetLastFrameRenderer()
	{
		return VRCompositor()->GetLastFrameRenderer();
	}

	inline bool CanRenderScene()
	{
		return VRCompositor()->CanRenderScene();
	}

	inline void ShowMirrorWindow()
	{
		VRCompositor()->ShowMirrorWindow();
		return;
	}

	inline void HideMirrorWindow()
	{
		VRCompositor()->HideMirrorWindow();
		return;
	}

	inline bool IsMirrorWindowVisible()
	{
		return VRCompositor()->IsMirrorWindowVisible();
	}

	inline void CompositorDumpImages()
	{
		VRCompositor()->CompositorDumpImages();
		return;
	}

	inline bool ShouldAppRenderWithLowResources()
	{
		return VRCompositor()->ShouldAppRenderWithLowResources();
	}

	inline void ForceInterleavedReprojectionOn( bool bOverride )
	{
		VRCompositor()->ForceInterleavedReprojectionOn(bOverride);
		return;
	}

	inline void ForceReconnectProcess()
	{
		VRCompositor()->ForceReconnectProcess();
		return;
	}

	inline void SuspendRendering( bool bSuspend )
	{
		VRCompositor()->SuspendRendering(bSuspend);
		return;
	}

	inline vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
	{
		return D3DProxy()->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView);
	}

	inline void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
	{
		D3DProxy()->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView);
		return;
	}

	inline vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle )
	{
		return VRCompositor()->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
	}

	inline bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		return VRCompositor()->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
	}

	inline void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		VRCompositor()->LockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	inline void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		VRCompositor()->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	inline uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return VRCompositor()->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
	}

	inline uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return VRCompositor()->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize);
	}
}
