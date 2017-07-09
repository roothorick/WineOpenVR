#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRResources_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRResources_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRResourcesProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

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
