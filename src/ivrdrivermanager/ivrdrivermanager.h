#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRDriverManager_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRDriverManager_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRDriverManagerProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

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
