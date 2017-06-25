#include "common.h"

class clone_IVRChaperone
{
public:
	WOVR_ENTRY virtual ChaperoneCalibrationState GetCalibrationState() = 0;
	WOVR_ENTRY virtual bool GetPlayAreaSize( float *pSizeX, float *pSizeZ ) = 0;
	WOVR_ENTRY virtual bool GetPlayAreaRect( HmdQuad_t *rect ) = 0;
	WOVR_ENTRY virtual void ReloadInfo( void ) = 0;
	WOVR_ENTRY virtual void SetSceneColor( HmdColor_t color ) = 0;
	WOVR_ENTRY virtual void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor ) = 0;
	WOVR_ENTRY virtual bool AreBoundsVisible() = 0;
	WOVR_ENTRY virtual void ForceBoundsVisible( bool bForce ) = 0;
};

class proxy_IVRChaperone : public clone_IVRChaperone
{
public:
	proxy_IVRChaperone(IVRChaperone* real) { realImpl = real; }

	WOVR_ENTRY ChaperoneCalibrationState GetCalibrationState()
	{
		return realImpl->GetCalibrationState();
	}

	WOVR_ENTRY bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return realImpl->GetPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		return realImpl->GetPlayAreaRect(rect);
	}

	WOVR_ENTRY void ReloadInfo( void )
	{
		realImpl->ReloadInfo();
		return;
	}

	WOVR_ENTRY void SetSceneColor( HmdColor_t color )
	{
		realImpl->SetSceneColor(color);
		return;
	}

	WOVR_ENTRY void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		realImpl->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	WOVR_ENTRY bool AreBoundsVisible()
	{
		return realImpl->AreBoundsVisible();
	}

	WOVR_ENTRY void ForceBoundsVisible( bool bForce )
	{
		realImpl->ForceBoundsVisible(bForce);
		return;
	}

private:
	IVRChaperone* realImpl;
};

IVRChaperone* getIVRChaperoneProxy (IVRChaperone* real)
{
	return (IVRChaperone*) new proxy_IVRChaperone(real);
}
