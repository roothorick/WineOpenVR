#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRChaperone_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRChaperone_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRChaperoneProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

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
		TRACE("");
		return VRChaperone()->GetCalibrationState();
	}

	WOVR_ENTRY bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		TRACE("");
		return VRChaperone()->GetPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		TRACE("");
		return VRChaperone()->GetPlayAreaRect(rect);
	}

	WOVR_ENTRY void ReloadInfo( void )
	{
		TRACE("");
		VRChaperone()->ReloadInfo();
		return;
	}

	WOVR_ENTRY void SetSceneColor( HmdColor_t color )
	{
		TRACE("");
		VRChaperone()->SetSceneColor(color);
		return;
	}

	WOVR_ENTRY void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		TRACE("");
		VRChaperone()->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	WOVR_ENTRY bool AreBoundsVisible()
	{
		TRACE("");
		return VRChaperone()->AreBoundsVisible();
	}

	WOVR_ENTRY void ForceBoundsVisible( bool bForce )
	{
		TRACE("");
		VRChaperone()->ForceBoundsVisible(bForce);
		return;
	}
};

IVRChaperone* GETTER ()
{
	return (IVRChaperone*) new PROXYCLASS ();
}
