#include "common.h"

namespace fns_IVRResources
{
	inline uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen )
	{
		return VRResources()->LoadSharedResource(pchResourceName, pchBuffer, unBufferLen);
	}
	inline uint32_t GetResourceFullPath( const char *pchResourceName, const char *pchResourceTypeDirectory, char *pchPathBuffer, uint32_t unBufferLen )
	{
		// XXX: This should translate to a Windows X:\\etc path.
		return VRResources()->GetResourceFullPath(pchResourceName, pchResourceTypeDirectory, pchPathBuffer, unBufferLen);
	}
}
