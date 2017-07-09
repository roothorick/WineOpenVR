#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRResources_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRResources_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRResourcesProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

class CLONECLASS
{
public:
	WOVR_ENTRY virtual uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen ) = 0;
	WOVR_ENTRY virtual uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen )
	{
		return VRResources()->LoadSharedResource(pchResourceName, pchBuffer, unBufferLen);
	}
	WOVR_ENTRY uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen )
	{
		// XXX: This should translate to a Windows X:\\etc path.
		return VRResources()->GetResourceFullPath(pchResourceName, pchResourceTypeDirectory, pchPathBuffer, unBufferLen);
	}
};

IVRResources* GETTER ()
{
	return (IVRResources*) new PROXYCLASS ();
}
