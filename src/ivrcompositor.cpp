#include "common.h"

class clone_IVRCompositor
{
public:
	THISCALL virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) = 0;
	THISCALL virtual ETrackingUniverseOrigin GetTrackingSpace() = 0;
	THISCALL virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
	THISCALL virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
	THISCALL virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) = 0;
	THISCALL virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) = 0;
	THISCALL virtual void ClearLastSubmittedFrame() = 0;
	THISCALL virtual void PostPresentHandoff() = 0;
	THISCALL virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) = 0;
	THISCALL virtual uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames ) = 0;
	THISCALL virtual float GetFrameTimeRemaining() = 0;
	THISCALL virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;
	THISCALL virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;
	THISCALL virtual void GetCurrentFadeColor( HmdColor_t* ret, bool bBackground = false ) = 0; // ERP hack
	THISCALL virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;
	THISCALL virtual float GetCurrentGridAlpha() = 0;
	THISCALL virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) = 0;
	THISCALL virtual void ClearSkyboxOverride() = 0;
	THISCALL virtual void CompositorBringToFront() = 0;
	THISCALL virtual void CompositorGoToBack() = 0;
	THISCALL virtual void CompositorQuit() = 0;
	THISCALL virtual bool IsFullscreen() = 0;
	THISCALL virtual uint32_t GetCurrentSceneFocusProcess() = 0;
	THISCALL virtual uint32_t GetLastFrameRenderer() = 0;
	THISCALL virtual bool CanRenderScene() = 0;
	THISCALL virtual void ShowMirrorWindow() = 0;
	THISCALL virtual void HideMirrorWindow() = 0;
	THISCALL virtual bool IsMirrorWindowVisible() = 0;
	THISCALL virtual void CompositorDumpImages() = 0;
	THISCALL virtual bool ShouldAppRenderWithLowResources() = 0;
	THISCALL virtual void ForceInterleavedReprojectionOn( bool bOverride ) = 0;
	THISCALL virtual void ForceReconnectProcess() = 0;
	THISCALL virtual void SuspendRendering( bool bSuspend ) = 0;
	THISCALL virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
	THISCALL virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) = 0;
	THISCALL virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	THISCALL virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	THISCALL virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	THISCALL virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	THISCALL virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
	THISCALL virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
};

class proxy_IVRCompositor : public clone_IVRCompositor
{
public:
	proxy_IVRCompositor(IVRCompositor* real) { realImpl = real; }

	THISCALL void SetTrackingSpace( ETrackingUniverseOrigin eOrigin )
	{
		realImpl->SetTrackingSpace(eOrigin);
		return;
	}

	THISCALL ETrackingUniverseOrigin GetTrackingSpace()
	{
		return realImpl->GetTrackingSpace();
	}

	THISCALL EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return realImpl->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	THISCALL EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return realImpl->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	THISCALL EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose )
	{
		return realImpl->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
	}

	THISCALL EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
	{
		return realImpl->Submit(eEye, pTexture, pBounds, nSubmitFlags);
	}

	THISCALL void ClearLastSubmittedFrame()
	{
		realImpl->ClearLastSubmittedFrame();
		return;
	}

	THISCALL void PostPresentHandoff()
	{
		realImpl->PostPresentHandoff();
		return;
	}

	THISCALL bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo )
	{
		return realImpl->GetFrameTiming(pTiming, unFramesAgo);
	}

	THISCALL uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames )
	{
		return realImpl->GetFrameTimings(pTiming, nFrames);
	}

	THISCALL float GetFrameTimeRemaining()
	{
		return realImpl->GetFrameTimeRemaining();
	}

	THISCALL void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes )
	{
		realImpl->GetCumulativeStats(pStats, nStatsSizeInBytes);
		return;
	}

	THISCALL void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground )
	{
		realImpl->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
		return;
	}

	THISCALL void GetCurrentFadeColor( HmdColor_t* ret, bool bBackground )
	{
		// ERP hack
		*ret = realImpl->GetCurrentFadeColor(bBackground);
		return;
	}

	THISCALL void FadeGrid( float fSeconds, bool bFadeIn )
	{
		realImpl->FadeGrid(fSeconds, bFadeIn);
		return;
	}

	THISCALL float GetCurrentGridAlpha()
	{
		return realImpl->GetCurrentGridAlpha();
	}

	THISCALL EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
	{
		return realImpl->SetSkyboxOverride(pTextures, unTextureCount);
	}

	THISCALL void ClearSkyboxOverride()
	{
		realImpl->ClearSkyboxOverride();
		return;
	}

	THISCALL void CompositorBringToFront()
	{
		realImpl->CompositorBringToFront();
		return;
	}

	THISCALL void CompositorGoToBack()
	{
		realImpl->CompositorGoToBack();
		return;
	}

	THISCALL void CompositorQuit()
	{
		realImpl->CompositorQuit();
		return;
	}

	THISCALL bool IsFullscreen()
	{
		return realImpl->IsFullscreen();
	}

	THISCALL uint32_t GetCurrentSceneFocusProcess()
	{
		return realImpl->GetCurrentSceneFocusProcess();
	}

	THISCALL uint32_t GetLastFrameRenderer()
	{
		return realImpl->GetLastFrameRenderer();
	}

	THISCALL bool CanRenderScene()
	{
		return realImpl->CanRenderScene();
	}

	THISCALL void ShowMirrorWindow()
	{
		realImpl->ShowMirrorWindow();
		return;
	}

	THISCALL void HideMirrorWindow()
	{
		realImpl->HideMirrorWindow();
		return;
	}

	THISCALL bool IsMirrorWindowVisible()
	{
		return realImpl->IsMirrorWindowVisible();
	}

	THISCALL void CompositorDumpImages()
	{
		realImpl->CompositorDumpImages();
		return;
	}

	THISCALL bool ShouldAppRenderWithLowResources()
	{
		return realImpl->ShouldAppRenderWithLowResources();
	}

	THISCALL void ForceInterleavedReprojectionOn( bool bOverride )
	{
		realImpl->ForceInterleavedReprojectionOn(bOverride);
		return;
	}

	THISCALL void ForceReconnectProcess()
	{
		realImpl->ForceReconnectProcess();
		return;
	}

	THISCALL void SuspendRendering( bool bSuspend )
	{
		realImpl->SuspendRendering(bSuspend);
		return;
	}

	THISCALL vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
	{
		printf("WOVR fixme: GetMirrorTextureD3D11 stub!\n");
		return VRCompositorError_RequestFailed;
	}

	THISCALL void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
	{
		printf("WOVR fixme: ReleaseMirrorTextureD3D11 stub!\n");
		return;
	}

	THISCALL vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle )
	{
		return realImpl->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
	}

	THISCALL bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		return realImpl->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
	}

	THISCALL void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		realImpl->LockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	THISCALL void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		realImpl->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	THISCALL uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return realImpl->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
	}

	THISCALL uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
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
