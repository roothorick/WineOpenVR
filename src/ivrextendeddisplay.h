#include "common.h"
#include "d3dproxy.h"

/*
This probably won't ever work correctly, but this part of the API isn't intended for production use anyway.
It is only implemented in order to "complete" the API.
*/

namespace fns_IVRExtendedDisplay
{
	inline void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRExtendedDisplay()->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
		return;
	}

	inline void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRExtendedDisplay()->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
		return;
	}

	inline void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
	{
		D3DProxy()->ExtendedDisplay_GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
	}
}
