#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRChaperone_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRChaperone_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRChaperoneProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

class CLONECLASS
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

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY ChaperoneCalibrationState GetCalibrationState()
	{
		return VRChaperone()->GetCalibrationState();
	}

	WOVR_ENTRY bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return VRChaperone()->GetPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		return VRChaperone()->GetPlayAreaRect(rect);
	}

	WOVR_ENTRY void ReloadInfo( void )
	{
		VRChaperone()->ReloadInfo();
		return;
	}

	WOVR_ENTRY void SetSceneColor( HmdColor_t color )
	{
		VRChaperone()->SetSceneColor(color);
		return;
	}

	WOVR_ENTRY void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		VRChaperone()->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	WOVR_ENTRY bool AreBoundsVisible()
	{
		return VRChaperone()->AreBoundsVisible();
	}

	WOVR_ENTRY void ForceBoundsVisible( bool bForce )
	{
		VRChaperone()->ForceBoundsVisible(bForce);
		return;
	}
};

IVRChaperone* GETTER ()
{
	return (IVRChaperone*) new PROXYCLASS ();
}
