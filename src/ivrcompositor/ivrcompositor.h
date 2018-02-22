#include "common.h"
#include "d3dproxy.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRCompositor_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRCompositor_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRCompositorProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

class CLONECLASS
{
public:
	WOVR_ENTRY virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) = 0;
	WOVR_ENTRY virtual ETrackingUniverseOrigin GetTrackingSpace() = 0;
	WOVR_ENTRY virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
	WOVR_ENTRY virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;
#if ABIVER >= 12
	WOVR_ENTRY virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) = 0;
#endif
	WOVR_ENTRY virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) = 0;
	WOVR_ENTRY virtual void ClearLastSubmittedFrame() = 0;
	WOVR_ENTRY virtual void PostPresentHandoff() = 0;
	WOVR_ENTRY virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) = 0;
#if ABIVER >= 18
	WOVR_ENTRY virtual uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames ) = 0;
#endif
	WOVR_ENTRY virtual float GetFrameTimeRemaining() = 0;
#if ABIVER >= 15
	WOVR_ENTRY virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;
#endif
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
#if ABIVER >= 12
	WOVR_ENTRY virtual bool ShouldAppRenderWithLowResources() = 0;
#endif
#if ABIVER >= 13
	WOVR_ENTRY virtual void ForceInterleavedReprojectionOn( bool bOverride ) = 0;
#endif
#if ABIVER >= 14
	WOVR_ENTRY virtual void ForceReconnectProcess() = 0;
	WOVR_ENTRY virtual void SuspendRendering( bool bSuspend ) = 0;
#endif
#if ABIVER >= 15
#if ABIVER < 16
	WOVR_ENTRY virtual vr::EVRCompositorError RequestScreenshot( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotType GetCurrentScreenshotType() = 0;
#endif
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
#if ABIVER >= 20
	WOVR_ENTRY virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) = 0;
#endif
	WOVR_ENTRY virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	WOVR_ENTRY virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
#endif // >= 15
#if ABIVER >= 19
	WOVR_ENTRY virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
	WOVR_ENTRY virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
#endif
#if ABIVER >= 21
#if ABIVER >= 22
	WOVR_ENTRY virtual void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) = 0;
#else // ABIVER == 21
	WOVR_ENTRY virtual void SetExplicitTimingMode( bool bExplicitTimingMode ) = 0;
#endif
	WOVR_ENTRY virtual EVRCompositorError SubmitExplicitTimingData() = 0;
#endif
};

class PROXYCLASS : public CLONECLASS
{
public:
	WOVR_ENTRY void SetTrackingSpace( ETrackingUniverseOrigin eOrigin )
	{
		TRACE("");
		VRCompositor()->SetTrackingSpace(eOrigin);
		return;
	}

	WOVR_ENTRY ETrackingUniverseOrigin GetTrackingSpace()
	{
		TRACE("");
		return VRCompositor()->GetTrackingSpace();
	}

	WOVR_ENTRY EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		TRACEHOT("");
		return VRCompositor()->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

	WOVR_ENTRY EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount )
	{
		TRACEHOT("");
		return VRCompositor()->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
	}

#if ABIVER >= 12
	WOVR_ENTRY EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose )
	{
		TRACEHOT("");
		return VRCompositor()->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
	}
#endif

	WOVR_ENTRY EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags )
	{
		TRACEHOT("");
		static bool bReportedTextureType = false;
		if(!bReportedTextureType)
		{
			switch(pTexture->eType)
			{
				case TextureType_DirectX:
					INFO("DirectX 11 application.");
					break;

				case TextureType_OpenGL:
					INFO("OpenGL application.");
					break;

				case TextureType_Vulkan:
					INFO("Vulkan application.");
					break;

				case TextureType_DirectX12:
					INFO("DirectX 12 application.");
					break;

				default:
					ERR("Unknown texture type!");
					return VRCompositorError_InvalidTexture;
			}
			bReportedTextureType = true;
		}

		if(pTexture->eType == TextureType_DirectX || pTexture->eType == TextureType_DirectX12)
			return D3DProxy()->Submit(eEye, pTexture, pBounds, nSubmitFlags);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VRCompositor()->Submit(eEye, pTexture, pBounds, nSubmitFlags);
	}

	WOVR_ENTRY void ClearLastSubmittedFrame()
	{
		TRACEHOT("");
		VRCompositor()->ClearLastSubmittedFrame();
		return;
	}

	WOVR_ENTRY void PostPresentHandoff()
	{
		TRACEHOT("");
		VRCompositor()->PostPresentHandoff();
		return;
	}

	WOVR_ENTRY bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo )
	{
		TRACEHOT("");
		return VRCompositor()->GetFrameTiming(pTiming, unFramesAgo);
	}

#if ABIVER >= 18
	WOVR_ENTRY uint32_t GetFrameTimings( Compositor_FrameTiming *pTiming, uint32_t nFrames )
	{
		TRACEHOT("");
		return VRCompositor()->GetFrameTimings(pTiming, nFrames);
	}
#endif

	WOVR_ENTRY float GetFrameTimeRemaining()
	{
		TRACEHOT("");
		return VRCompositor()->GetFrameTimeRemaining();
	}

#if ABIVER >= 15
	WOVR_ENTRY void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes )
	{
		TRACEHOT("");
		VRCompositor()->GetCumulativeStats(pStats, nStatsSizeInBytes);
		return;
	}
#endif

	WOVR_ENTRY void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground )
	{
		TRACE("");
		VRCompositor()->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
		return;
	}

	WOVR_ENTRY void GetCurrentFadeColor( HmdColor_t* ret, bool bBackground )
	{
		TRACE("");
		// ERP hack
		*ret = VRCompositor()->GetCurrentFadeColor(bBackground);
		return;
	}

	WOVR_ENTRY void FadeGrid( float fSeconds, bool bFadeIn )
	{
		TRACE("");
		VRCompositor()->FadeGrid(fSeconds, bFadeIn);
		return;
	}

	WOVR_ENTRY float GetCurrentGridAlpha()
	{
		TRACE("");
		return VRCompositor()->GetCurrentGridAlpha();
	}

	WOVR_ENTRY EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount )
	{
		TRACE("");
		if(pTextures->eType == TextureType_DirectX || pTextures->eType == TextureType_DirectX12)
			return D3DProxy()->SetSkyboxOverride(pTextures, unTextureCount);
		else // Natively supported (OpenGL or Vulkan); pass directly.
			return VRCompositor()->SetSkyboxOverride(pTextures, unTextureCount);
	}

	WOVR_ENTRY void ClearSkyboxOverride()
	{
		TRACE("");
		VRCompositor()->ClearSkyboxOverride();
		return;
	}

	WOVR_ENTRY void CompositorBringToFront()
	{
		TRACE("");
		VRCompositor()->CompositorBringToFront();
		return;
	}

	WOVR_ENTRY void CompositorGoToBack()
	{
		TRACE("");
		VRCompositor()->CompositorGoToBack();
		return;
	}

	WOVR_ENTRY void CompositorQuit()
	{
		TRACE("");
		VRCompositor()->CompositorQuit();
		return;
	}

	WOVR_ENTRY bool IsFullscreen()
	{
		TRACE("");
		return VRCompositor()->IsFullscreen();
	}

	WOVR_ENTRY uint32_t GetCurrentSceneFocusProcess()
	{
		TRACE("");
		return VRCompositor()->GetCurrentSceneFocusProcess();
	}

	WOVR_ENTRY uint32_t GetLastFrameRenderer()
	{
		TRACEHOT("");
		return VRCompositor()->GetLastFrameRenderer();
	}

	WOVR_ENTRY bool CanRenderScene()
	{
		TRACEHOT("");
		return VRCompositor()->CanRenderScene();
	}

	WOVR_ENTRY void ShowMirrorWindow()
	{
		TRACE("");
		VRCompositor()->ShowMirrorWindow();
		return;
	}

	WOVR_ENTRY void HideMirrorWindow()
	{
		TRACE("");
		VRCompositor()->HideMirrorWindow();
		return;
	}

	WOVR_ENTRY bool IsMirrorWindowVisible()
	{
		TRACE("");
		return VRCompositor()->IsMirrorWindowVisible();
	}

	WOVR_ENTRY void CompositorDumpImages()
	{
		TRACE("");
		VRCompositor()->CompositorDumpImages();
		return;
	}

#if ABIVER >= 12
	WOVR_ENTRY bool ShouldAppRenderWithLowResources()
	{
		TRACE("");
		return VRCompositor()->ShouldAppRenderWithLowResources();
	}
#endif

#if ABIVER >= 13
	WOVR_ENTRY void ForceInterleavedReprojectionOn( bool bOverride )
	{
		TRACE("");
		VRCompositor()->ForceInterleavedReprojectionOn(bOverride);
		return;
	}
#endif

#if ABIVER >= 14
	WOVR_ENTRY void ForceReconnectProcess()
	{
		TRACE("");
		VRCompositor()->ForceReconnectProcess();
		return;
	}

	WOVR_ENTRY void SuspendRendering( bool bSuspend )
	{
		TRACE("");
		VRCompositor()->SuspendRendering(bSuspend);
		return;
	}
#endif

#if ABIVER >= 15
#if ABIVER < 16
	WOVR_ENTRY vr::EVRCompositorError RequestScreenshot( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName )
	{
		WARN("stub!");
		return VRCompositorError_RequestFailed;
	}

	WOVR_ENTRY vr::EVRScreenshotType GetCurrentScreenshotType()
	{
		WARN("stub!");
		return VRScreenshotType_None;
	}
#endif

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView )
	{
		TRACE("");
		return D3DProxy()->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView);
	}

#if ABIVER >= 20
	WOVR_ENTRY void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView )
	{
		TRACE("");
		D3DProxy()->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView);
		return;
	}
#endif

	WOVR_ENTRY vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle )
	{
		TRACE("");
		return VRCompositor()->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
	}

	WOVR_ENTRY bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		TRACE("");
		return VRCompositor()->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
	}

	WOVR_ENTRY void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		TRACE("");
		VRCompositor()->LockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}

	WOVR_ENTRY void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle )
	{
		TRACE("");
		VRCompositor()->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
		return;
	}
#endif // >= 15

#if ABIVER >= 19
	WOVR_ENTRY uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		TRACE("");
		return VRCompositor()->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
	}

	WOVR_ENTRY uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		TRACE("");
		return VRCompositor()->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize);
	}
#endif

#if ABIVER >= 21
#if ABIVER >= 22
	WOVR_ENTRY void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode )
#else // ABIVER == 21
	WOVR_ENTRY void SetExplicitTimingMode( bool bExplicitTimingMode )
#endif
	{
		TRACE("");
#if ABIVER >= 22
		VRCompositor()->SetExplicitTimingMode(eTimingMode);
#else // ABIVER == 21
		VRCompositor()->SetExplicitTimingMode( bExplicitTimingMode ?
					VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff : 
					VRCompositorTimingMode_Implicit
				);
#endif
	}
	
	WOVR_ENTRY EVRCompositorError SubmitExplicitTimingData()
	{
		TRACEHOT("");
		return VRCompositor()->SubmitExplicitTimingData();
	}
#endif
};

// Declared in proxy_getters.h
vr::IVRCompositor* GETTER ()
{
	return (IVRCompositor*) new PROXYCLASS ();
}
