#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRDriverManager_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRDriverManager_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRDriverManagerProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

class CLONECLASS
{
public:
	WOVR_ENTRY virtual uint32_t GetDriverCount() const = 0;
	WOVR_ENTRY virtual uint32_t GetDriverName( vr::DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
    WOVR_ENTRY uint32_t GetDriverCount() const
	{
		return VRDriverManager()->GetDriverCount();
	}

	WOVR_ENTRY uint32_t GetDriverName( vr::DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return VRDriverManager()->GetDriverName(nDriver, pchValue, unBufferSize);
	}
};

IVRDriverManager* GETTER ()
{
	return (IVRDriverManager*) new PROXYCLASS ();
}
