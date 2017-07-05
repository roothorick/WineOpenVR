#include "common.h"
#include "d3dproxy.h"

/*
This probably won't ever work correctly, but this part of the API isn't intended for production use anyway.
It is only implemented in order to "complete" the API.
*/

class clone_IVRExtendedDisplay
{
public:
	WOVR_ENTRY virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) = 0;
};

class proxy_IVRExtendedDisplay : public clone_IVRExtendedDisplay
{
public:
	proxy_IVRExtendedDisplay(IVRExtendedDisplay* real) { realImpl = real; }

	WOVR_ENTRY void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		realImpl->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		realImpl->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
	{
		D3DProxy()->ExtendedDisplay_GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
	}

private:
	IVRExtendedDisplay* realImpl;
};

IVRExtendedDisplay* getIVRExtendedDisplayProxy(IVRExtendedDisplay* real)
{
	return (IVRExtendedDisplay*) new proxy_IVRExtendedDisplay(real);
}
