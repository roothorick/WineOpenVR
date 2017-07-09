#include "common.h"

namespace fns_IVRChaperone
{
	inline ChaperoneCalibrationState GetCalibrationState()
	{
		return VRChaperone()->GetCalibrationState();
	}

	inline bool GetPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return VRChaperone()->GetPlayAreaSize(pSizeX, pSizeZ);
	}

	inline bool GetPlayAreaRect( HmdQuad_t *rect )
	{
		return VRChaperone()->GetPlayAreaRect(rect);
	}

	inline void ReloadInfo( void )
	{
		VRChaperone()->ReloadInfo();
		return;
	}

	inline void SetSceneColor( HmdColor_t color )
	{
		VRChaperone()->SetSceneColor(color);
		return;
	}

	inline void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor )
	{
		VRChaperone()->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
		return;
	}

	inline bool AreBoundsVisible()
	{
		return VRChaperone()->AreBoundsVisible();
	}

	inline void ForceBoundsVisible( bool bForce )
	{
		VRChaperone()->ForceBoundsVisible(bForce);
		return;
	}
}
