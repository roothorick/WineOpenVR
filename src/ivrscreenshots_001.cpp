#include "ivrscreenshots.h"

class clone_IVRScreenshots_001
{
public:
	WOVR_ENTRY virtual vr::EVRScreenshotError RequestScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const vr::EVRScreenshotType *pSupportedTypes, int numTypes ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotType GetScreenshotPropertyType( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError ) = 0;
	WOVR_ENTRY virtual uint32_t GetScreenshotPropertyFilename( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotError UpdateScreenshotProgress( vr::ScreenshotHandle_t screenshotHandle, float flProgress ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotError TakeStereoScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;
	WOVR_ENTRY virtual vr::EVRScreenshotError SubmitScreenshot( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename ) = 0;
};

class proxy_IVRScreenshots_001 : public clone_IVRScreenshots_001
{
public:
	WOVR_ENTRY vr::EVRScreenshotError RequestScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return fns_IVRScreenshots::RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename);
	}

	WOVR_ENTRY vr::EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const vr::EVRScreenshotType *pSupportedTypes, int numTypes )
	{
		return fns_IVRScreenshots::HookScreenshot(pSupportedTypes, numTypes);
	}

	WOVR_ENTRY vr::EVRScreenshotType GetScreenshotPropertyType( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError )
	{
		return fns_IVRScreenshots::GetScreenshotPropertyType(screenshotHandle, pError);
	}

	WOVR_ENTRY uint32_t GetScreenshotPropertyFilename( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError )
	{
		return fns_IVRScreenshots::GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, pError);

	}

	WOVR_ENTRY vr::EVRScreenshotError UpdateScreenshotProgress( vr::ScreenshotHandle_t screenshotHandle, float flProgress )
	{
		return fns_IVRScreenshots::UpdateScreenshotProgress(screenshotHandle, flProgress);
	}

	WOVR_ENTRY vr::EVRScreenshotError TakeStereoScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return fns_IVRScreenshots::TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename);
	}

	WOVR_ENTRY vr::EVRScreenshotError SubmitScreenshot( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename )
	{
		return fns_IVRScreenshots::SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename);
	}
};

IVRScreenshots* getIVRScreenshotsProxy_001()
{
	return (IVRScreenshots*) new proxy_IVRScreenshots_001();
}
