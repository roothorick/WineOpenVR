#include "common.h"
#include "d3dproxy.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRExtendedDisplay_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRExtendedDisplay_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRExtendedDisplayProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

/*
This probably won't ever work correctly, but this part of the API isn't intended for production use anyway.
It is only implemented in order to "complete" the API.
*/

class CLONECLASS
{
public:
	WOVR_ENTRY virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	WOVR_ENTRY virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRExtendedDisplay()->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight )
	{
		VRExtendedDisplay()->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
		return;
	}

	WOVR_ENTRY void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex )
	{
		D3DProxy()->ExtendedDisplay_GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
	}
};

IVRExtendedDisplay* GETTER ()
{
	return (IVRExtendedDisplay*) new PROXYCLASS ();
}
