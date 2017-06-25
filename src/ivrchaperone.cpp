#include "common.h"

class clone_IVRChaperone
{
public:
	THISCALL virtual ChaperoneCalibrationState GetCalibrationState() = 0;
	THISCALL virtual bool GetPlayAreaSize( float *pSizeX, float *pSizeZ ) = 0;
	THISCALL virtual bool GetPlayAreaRect( HmdQuad_t *rect ) = 0;
	THISCALL virtual void ReloadInfo( void ) = 0;
	THISCALL virtual void SetSceneColor( HmdColor_t color ) = 0;
	THISCALL virtual void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor ) = 0;
	THISCALL virtual bool AreBoundsVisible() = 0;
	THISCALL virtual void ForceBoundsVisible( bool bForce ) = 0;
};

class proxy_IVRChaperone : public clone_IVRChaperone
{
public:
	proxy_IVRChaperone(IVRChaperone* real) { realImpl = real; }

	THISCALL ChaperoneCalibrationState GetCalibrationState()
	{
		return realImpl->GetCalibrationState();
	}

	THISCALL bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return realImpl->GetPlayAreaSize(pSizeX, pSizeZ);
	}

	THISCALL bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		return realImpl->GetPlayAreaRect(rect);
	}

	THISCALL void ReloadInfo( void )
	{
		realImpl->ReloadInfo();
		return;
	}

	THISCALL void SetSceneColor( HmdColor_t color )
	{
		realImpl->SetSceneColor(color);
		return;
	}

	THISCALL void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		realImpl->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	THISCALL bool AreBoundsVisible()
	{
		return realImpl->AreBoundsVisible();
	}

	THISCALL void ForceBoundsVisible( bool bForce )
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
