#include "common.h"

class clone_IVRScreenshots
{
public:
	THISCALL virtual vr::EVRScreenshotError RequestScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;
	THISCALL virtual vr::EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const vr::EVRScreenshotType *pSupportedTypes, int numTypes ) = 0;
	THISCALL virtual vr::EVRScreenshotType GetScreenshotPropertyType( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError ) = 0;
 	THISCALL virtual uint32_t GetScreenshotPropertyFilename( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError ) = 0;
	THISCALL virtual vr::EVRScreenshotError UpdateScreenshotProgress( vr::ScreenshotHandle_t screenshotHandle, float flProgress ) = 0;
	THISCALL virtual vr::EVRScreenshotError TakeStereoScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename ) = 0;
	THISCALL virtual vr::EVRScreenshotError SubmitScreenshot( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename ) = 0;
};

class proxy_IVRScreenshots : public clone_IVRScreenshots
{
public:
	proxy_IVRScreenshots(IVRScreenshots* real) { realImpl = real; }

	THISCALL vr::EVRScreenshotError RequestScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return realImpl->RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename);
	}

	THISCALL vr::EVRScreenshotError HookScreenshot( VR_ARRAY_COUNT( numTypes ) const vr::EVRScreenshotType *pSupportedTypes, int numTypes )
	{
		return realImpl->HookScreenshot(pSupportedTypes, numTypes);
	}

	THISCALL vr::EVRScreenshotType GetScreenshotPropertyType( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError )
	{
		return realImpl->GetScreenshotPropertyType(screenshotHandle, pError);
	}

 	THISCALL uint32_t GetScreenshotPropertyFilename( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError )
	{
		return realImpl->GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, pError);

	}

	THISCALL vr::EVRScreenshotError UpdateScreenshotProgress( vr::ScreenshotHandle_t screenshotHandle, float flProgress )
	{
		return realImpl->UpdateScreenshotProgress(screenshotHandle, flProgress);
	}

	THISCALL vr::EVRScreenshotError TakeStereoScreenshot( vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename )
	{
		return realImpl->TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename);
	}

	THISCALL vr::EVRScreenshotError SubmitScreenshot( vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename )
	{
		return realImpl->SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename);
	}

private:
	IVRScreenshots* realImpl;
};

IVRScreenshots* getIVRScreenshotsProxy(IVRScreenshots* real)
{
	return (IVRScreenshots*) new proxy_IVRScreenshots(real);
}
