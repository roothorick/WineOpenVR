#include "common.h"

class clone_IVRResources
{
public:
	THISCALL virtual uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen ) = 0;
	THISCALL virtual uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen ) = 0;
};

class proxy_IVRResources : public clone_IVRResources
{
public:
	proxy_IVRResources(IVRResources* real) { realImpl = real; }

	THISCALL uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen )
	{
		return realImpl->LoadSharedResource(pchResourceName, pchBuffer, unBufferLen);
	}
	THISCALL uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen )
	{
		// XXX: This should translate to a Windows X:\\etc path.
		return realImpl->GetResourceFullPath(pchResourceName, pchResourceTypeDirectory, pchPathBuffer, unBufferLen);
	}

private:
	IVRResources* realImpl;
};

IVRResources* getIVRResourcesProxy(IVRResources* real)
{
	return (IVRResources*) new proxy_IVRResources(real);
}
