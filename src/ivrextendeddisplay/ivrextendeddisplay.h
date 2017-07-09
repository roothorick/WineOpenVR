#include "common.h"
#include "d3dproxy.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRExtendedDisplay_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRExtendedDisplay_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRExtendedDisplayProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

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
