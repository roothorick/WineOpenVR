#include "common.h"

namespace fns_IVRScreenshots
{
	inline vr::EVRScreenshotError RequestScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return VRScreenshots()->RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename);
	}

	inline vr::EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const vr::EVRScreenshotType *pSupportedTypes, int numTypes )
	{
		return VRScreenshots()->HookScreenshot(pSupportedTypes, numTypes);
	}

	inline vr::EVRScreenshotType GetScreenshotPropertyType( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError )
	{
		return VRScreenshots()->GetScreenshotPropertyType(screenshotHandle, pError);
	}

	inline uint32_t GetScreenshotPropertyFilename( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError )
	{
		return VRScreenshots()->GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, pError);
	}

	inline vr::EVRScreenshotError UpdateScreenshotProgress( vr::ScreenshotHandle_t screenshotHandle, float flProgress )
	{
		return VRScreenshots()->UpdateScreenshotProgress(screenshotHandle, flProgress);
	}

	inline vr::EVRScreenshotError TakeStereoScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return VRScreenshots()->TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename);
	}

	inline vr::EVRScreenshotError SubmitScreenshot( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename )
	{
		return VRScreenshots()->SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename);
	}
}
