#include "common.h"

class clone_IVRCompositor
{
public:
	WOVR_ENTRY virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) = 0;
	WOVR_ENTRY virtual ETrackingUniverseOrigin GetTrackingSpace() = 0;
	WOVR_ENTRY virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
	WOVR_ENTRY virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
	WOVR_ENTRY virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) = 0;
	WOVR_ENTRY virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) = 0;
	WOVR_ENTRY virtual void ClearLastSubmittedFrame() = 0;
	WOVR_ENTRY virtual void PostPresentHandoff() = 0;
	WOVR_ENTRY virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) = 0;
	WOVR_ENTRY virtual uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames ) = 0;
	WOVR_ENTRY virtual float GetFrameTimeRemaining() = 0;
	WOVR_ENTRY virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;
	WOVR_ENTRY virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;
	WOVR_ENTRY virtual void GetCurrentFadeColor( HmdColor_t* ret, bool bBackground = false ) = 0; // ERP hack
	WOVR_ENTRY virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;
	WOVR_ENTRY virtual float GetCurrentGridAlpha() = 0;
	WOVR_ENTRY virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) = 0;
	WOVR_ENTRY virtual void ClearSkyboxOverride() = 0;
	WOVR_ENTRY virtual void CompositorBringToFront() = 0;
	WOVR_ENTRY virtual void CompositorGoToBack() = 0;
	WOVR_ENTRY virtual void CompositorQuit() = 0;
	WOVR_ENTRY virtual bool IsFullscreen() = 0;
	WOVR_ENTRY virtual uint32_t GetCurrentSceneFocusProcess() = 0;
	WOVR_ENTRY virtual uint32_t GetLastFrameRenderer() = 0;
	WOVR_ENTRY virtual bool CanRenderScene() = 0;
	WOVR_ENTRY virtual void ShowMirrorWindow() = 0;
	WOVR_ENTRY virtual void HideMirrorWindow() = 0;
	WOVR_ENTRY virtual bool IsMirrorWindowVisible() = 0;
	WOVR_ENTRY virtual void CompositorDumpImages() = 0;
	WOVR_ENTRY virtual bool ShouldAppRenderWithLowResources() = 0;
	WOVR_ENTRY virtual void ForceInterleavedReprojectionOn( bool bOverride ) = 0;
	WOVR_ENTRY virtual void ForceReconnectProcess() = 0;
	WOVR_ENTRY virtual void SuspendRendering( bool bSuspend ) = 0;
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
	WOVR_ENTRY virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) = 0;
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
	WOVR_ENTRY virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
};

class proxy_IVRCompositor : public clone_IVRCompositor
{
public:
	proxy_IVRCompositor(IVRCompositor* real) { realImpl = real; }

	WOVR_ENTRY void SetTrackingSpace( ETrackingUniverseOrigin eOrigin )
	{
		realImpl->SetTrackingSpace(eOrigin);
		return;
	}

	WOVR_ENTRY ETrackingUniverseOrigin GetTrackingSpace()
	{
		return realImpl->GetTrackingSpace();
	}

	WOVR_ENTRY EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return realImpl->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	WOVR_ENTRY EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return realImpl->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	WOVR_ENTRY EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose )
	{
		return realImpl->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
	}

	WOVR_ENTRY EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
	{
		static bool bReportedTextureType = false;
		if(!bReportedTextureType)
		{
			switch(pTexture->eType)
			{
				case TextureType_DirectX:
					printf("WOVR info: IVRCompositor::Submit: DirectX 9/10/11 application.\n");
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

		return realImpl->Submit(eEye, pTexture, pBounds, nSubmitFlags);
	}

	WOVR_ENTRY void ClearLastSubmittedFrame()
	{
		realImpl->ClearLastSubmittedFrame();
		return;
	}

	WOVR_ENTRY void PostPresentHandoff()
	{
		realImpl->PostPresentHandoff();
		return;
	}

	WOVR_ENTRY bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo )
	{
		return realImpl->GetFrameTiming(pTiming, unFramesAgo);
	}

	WOVR_ENTRY uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames )
	{
		return realImpl->GetFrameTimings(pTiming, nFrames);
	}

	WOVR_ENTRY float GetFrameTimeRemaining()
	{
		return realImpl->GetFrameTimeRemaining();
	}

	WOVR_ENTRY void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes )
	{
		realImpl->GetCumulativeStats(pStats, nStatsSizeInBytes);
		return;
	}

	WOVR_ENTRY void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground )
	{
		realImpl->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
		return;
	}

	WOVR_ENTRY void GetCurrentFadeColor( HmdColor_t* ret, bool bBackground )
	{
		// ERP hack
		*ret = realImpl->GetCurrentFadeColor(bBackground);
		return;
	}

	WOVR_ENTRY void FadeGrid( float fSeconds, bool bFadeIn )
	{
		realImpl->FadeGrid(fSeconds, bFadeIn);
		return;
	}

	WOVR_ENTRY float GetCurrentGridAlpha()
	{
		return realImpl->GetCurrentGridAlpha();
	}

	WOVR_ENTRY EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
	{
		return realImpl->SetSkyboxOverride(pTextures, unTextureCount);
	}

	WOVR_ENTRY void ClearSkyboxOverride()
	{
		realImpl->ClearSkyboxOverride();
		return;
	}

	WOVR_ENTRY void CompositorBringToFront()
	{
		realImpl->CompositorBringToFront();
		return;
	}

	WOVR_ENTRY void CompositorGoToBack()
	{
		realImpl->CompositorGoToBack();
		return;
	}

	WOVR_ENTRY void CompositorQuit()
	{
		realImpl->CompositorQuit();
		return;
	}

	WOVR_ENTRY bool IsFullscreen()
	{
		return realImpl->IsFullscreen();
	}

	WOVR_ENTRY uint32_t GetCurrentSceneFocusProcess()
	{
		return realImpl->GetCurrentSceneFocusProcess();
	}

	WOVR_ENTRY uint32_t GetLastFrameRenderer()
	{
		return realImpl->GetLastFrameRenderer();
	}

	WOVR_ENTRY bool CanRenderScene()
	{
		return realImpl->CanRenderScene();
	}

	WOVR_ENTRY void ShowMirrorWindow()
	{
		realImpl->ShowMirrorWindow();
		return;
	}

	WOVR_ENTRY void HideMirrorWindow()
	{
		realImpl->HideMirrorWindow();
		return;
	}

	WOVR_ENTRY bool IsMirrorWindowVisible()
	{
		return realImpl->IsMirrorWindowVisible();
	}

	WOVR_ENTRY void CompositorDumpImages()
	{
		realImpl->CompositorDumpImages();
		return;
	}

	WOVR_ENTRY bool ShouldAppRenderWithLowResources()
	{
		return realImpl->ShouldAppRenderWithLowResources();
	}

	WOVR_ENTRY void ForceInterleavedReprojectionOn( bool bOverride )
	{
		realImpl->ForceInterleavedReprojectionOn(bOverride);
		return;
	}

	WOVR_ENTRY void ForceReconnectProcess()
	{
		realImpl->ForceReconnectProcess();
		return;
	}

	WOVR_ENTRY void SuspendRendering( bool bSuspend )
	{
		realImpl->SuspendRendering(bSuspend);
		return;
	}

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
	{
		printf("WOVR fixme: GetMirrorTextureD3D11 stub!\n");
		return VRCompositorError_RequestFailed;
	}

	WOVR_ENTRY void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
	{
		printf("WOVR fixme: ReleaseMirrorTextureD3D11 stub!\n");
		return;
	}

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle )
	{
		return realImpl->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
	}

	WOVR_ENTRY bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		return realImpl->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
	}

	WOVR_ENTRY void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		realImpl->LockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	WOVR_ENTRY void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		realImpl->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	WOVR_ENTRY uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return realImpl->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
	}

	WOVR_ENTRY uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return realImpl->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize);
	}

private:
	IVRCompositor* realImpl;
};

// Declared in proxy_getters.h
vr::IVRCompositor* getIVRCompositorProxy (IVRCompositor* real)
{
	return (IVRCompositor*) new proxy_IVRCompositor(real);
}
