#include "ivrcompositor.h"

class clone_IVRCompositor_015
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
	WOVR_ENTRY virtual float GetFrameTimeRemaining() = 0;
	WOVR_ENTRY virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;
	WOVR_ENTRY virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;
	WOVR_ENTRY virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;
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
	WOVR_ENTRY virtual vr::EVRCompositorError RequestScreenshot( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotType GetCurrentScreenshotType() = 0;
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
};

class proxy_IVRCompositor_015 : public clone_IVRCompositor_015
{
public:
	WOVR_ENTRY void SetTrackingSpace( ETrackingUniverseOrigin eOrigin )
	{
		fns_IVRCompositor::SetTrackingSpace(eOrigin);
		return;
	}

	WOVR_ENTRY ETrackingUniverseOrigin GetTrackingSpace()
	{
		return fns_IVRCompositor::GetTrackingSpace();
	}

	WOVR_ENTRY EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return fns_IVRCompositor::WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	WOVR_ENTRY EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		return fns_IVRCompositor::GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	WOVR_ENTRY EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose )
	{
		return fns_IVRCompositor::GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
	}

	WOVR_ENTRY EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
	{
		return fns_IVRCompositor::Submit(eEye, pTexture, pBounds, nSubmitFlags);
	}

	WOVR_ENTRY void ClearLastSubmittedFrame()
	{
		fns_IVRCompositor::ClearLastSubmittedFrame();
		return;
	}

	WOVR_ENTRY void PostPresentHandoff()
	{
		fns_IVRCompositor::PostPresentHandoff();
		return;
	}

	WOVR_ENTRY bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo )
	{
		return fns_IVRCompositor::GetFrameTiming(pTiming, unFramesAgo);
	}

	WOVR_ENTRY float GetFrameTimeRemaining()
	{
		return fns_IVRCompositor::GetFrameTimeRemaining();
	}

	WOVR_ENTRY void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes )
	{
		fns_IVRCompositor::GetCumulativeStats(pStats, nStatsSizeInBytes);
		return;
	}

	WOVR_ENTRY void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground )
	{
		fns_IVRCompositor::FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
		return;
	}

	WOVR_ENTRY void FadeGrid( float fSeconds, bool bFadeIn )
	{
		fns_IVRCompositor::FadeGrid(fSeconds, bFadeIn);
		return;
	}

	WOVR_ENTRY EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
	{
		return fns_IVRCompositor::SetSkyboxOverride(pTextures, unTextureCount);
	}

	WOVR_ENTRY void ClearSkyboxOverride()
	{
		fns_IVRCompositor::ClearSkyboxOverride();
		return;
	}

	WOVR_ENTRY void CompositorBringToFront()
	{
		fns_IVRCompositor::CompositorBringToFront();
		return;
	}

	WOVR_ENTRY void CompositorGoToBack()
	{
		fns_IVRCompositor::CompositorGoToBack();
		return;
	}

	WOVR_ENTRY void CompositorQuit()
	{
		fns_IVRCompositor::CompositorQuit();
		return;
	}

	WOVR_ENTRY bool IsFullscreen()
	{
		return fns_IVRCompositor::IsFullscreen();
	}

	WOVR_ENTRY uint32_t GetCurrentSceneFocusProcess()
	{
		return fns_IVRCompositor::GetCurrentSceneFocusProcess();
	}

	WOVR_ENTRY uint32_t GetLastFrameRenderer()
	{
		return fns_IVRCompositor::GetLastFrameRenderer();
	}

	WOVR_ENTRY bool CanRenderScene()
	{
		return fns_IVRCompositor::CanRenderScene();
	}

	WOVR_ENTRY void ShowMirrorWindow()
	{
		fns_IVRCompositor::ShowMirrorWindow();
		return;
	}

	WOVR_ENTRY void HideMirrorWindow()
	{
		fns_IVRCompositor::HideMirrorWindow();
		return;
	}

	WOVR_ENTRY bool IsMirrorWindowVisible()
	{
		return fns_IVRCompositor::IsMirrorWindowVisible();
	}

	WOVR_ENTRY void CompositorDumpImages()
	{
		fns_IVRCompositor::CompositorDumpImages();
		return;
	}

	WOVR_ENTRY bool ShouldAppRenderWithLowResources()
	{
		return fns_IVRCompositor::ShouldAppRenderWithLowResources();
	}

	WOVR_ENTRY void ForceInterleavedReprojectionOn( bool bOverride )
	{
		fns_IVRCompositor::ForceInterleavedReprojectionOn(bOverride);
		return;
	}

	WOVR_ENTRY void ForceReconnectProcess()
	{
		fns_IVRCompositor::ForceReconnectProcess();
		return;
	}

	WOVR_ENTRY void SuspendRendering( bool bSuspend )
	{
		fns_IVRCompositor::SuspendRendering(bSuspend);
		return;
	}

	WOVR_ENTRY vr::EVRCompositorError RequestScreenshot( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName )
	{
		printf("WOVR fixme: IVRCompositor <016 RequestScreenshot: stub!\n");
		return VRCompositorError_RequestFailed;
	}

	WOVR_ENTRY vr::EVRScreenshotType GetCurrentScreenshotType()
	{
		printf("WOVR fixme: IVRCompositor <016 RequestScreenshot: stub!\n");
		return VRScreenshotType_None;
	}

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
	{
		return fns_IVRCompositor::GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView);
	}

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle )
	{
		return fns_IVRCompositor::GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
	}

	WOVR_ENTRY bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		return fns_IVRCompositor::ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
	}

	WOVR_ENTRY void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		fns_IVRCompositor::LockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	WOVR_ENTRY void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		fns_IVRCompositor::UnlockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}
};

// Declared in proxy_getters.h
vr::IVRCompositor* getIVRCompositorProxy_015()
{
	return (IVRCompositor*) new proxy_IVRCompositor_015();
}
