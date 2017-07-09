#include "ivrextendeddisplay.h"

class clone_IVRExtendedDisplay_001
{
public:
	WOVR_ENTRY virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) = 0;
};

class proxy_IVRExtendedDisplay_001 : public clone_IVRExtendedDisplay_001
{
public:
	WOVR_ENTRY void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		fns_IVRExtendedDisplay::GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		fns_IVRExtendedDisplay::GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
	{
		D3DProxy()->ExtendedDisplay_GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
	}
};

IVRExtendedDisplay* getIVRExtendedDisplayProxy_001()
{
	return (IVRExtendedDisplay*) new proxy_IVRExtendedDisplay_001();
}
