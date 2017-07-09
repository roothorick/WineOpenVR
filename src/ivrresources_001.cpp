#include "ivrresources.h"

class clone_IVRResources_001
{
public:
	WOVR_ENTRY virtual uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen ) = 0;
	WOVR_ENTRY virtual uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen ) = 0;
};

class proxy_IVRResources_001 : public clone_IVRResources_001
{
public:
	WOVR_ENTRY uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen )
	{
		return fns_IVRResources::LoadSharedResource(pchResourceName, pchBuffer, unBufferLen);
	}
	WOVR_ENTRY uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen )
	{
		return fns_IVRResources::GetResourceFullPath(pchResourceName, pchResourceTypeDirectory, pchPathBuffer, unBufferLen);
	}
};

IVRResources* getIVRResourcesProxy_001()
{
	return (IVRResources*) new proxy_IVRResources_001();
}
