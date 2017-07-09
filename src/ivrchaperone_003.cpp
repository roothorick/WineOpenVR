#include "ivrchaperone.h"

class clone_IVRChaperone_003
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

class proxy_IVRChaperone_003 : public clone_IVRChaperone_003
{
public:
	WOVR_ENTRY ChaperoneCalibrationState GetCalibrationState()
	{
		return fns_IVRChaperone::GetCalibrationState();
	}

	WOVR_ENTRY bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return fns_IVRChaperone::GetPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		return fns_IVRChaperone::GetPlayAreaRect(rect);
	}

	WOVR_ENTRY void ReloadInfo( void )
	{
		fns_IVRChaperone::ReloadInfo();
		return;
	}

	WOVR_ENTRY void SetSceneColor( HmdColor_t color )
	{
		fns_IVRChaperone::SetSceneColor(color);
		return;
	}

	WOVR_ENTRY void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		fns_IVRChaperone::GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	WOVR_ENTRY bool AreBoundsVisible()
	{
		return fns_IVRChaperone::AreBoundsVisible();
	}

	WOVR_ENTRY void ForceBoundsVisible( bool bForce )
	{
		fns_IVRChaperone::ForceBoundsVisible(bForce);
		return;
	}
};

IVRChaperone* getIVRChaperoneProxy_003()
{
	return (IVRChaperone*) new proxy_IVRChaperone_003();
}
