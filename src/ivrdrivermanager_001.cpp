#include "ivrdrivermanager.h"

class clone_IVRDriverManager_001
{
public:
	WOVR_ENTRY virtual uint32_t GetDriverCount() const = 0;
	WOVR_ENTRY virtual uint32_t GetDriverName( vr::DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
};

class proxy_IVRDriverManager_001 : public clone_IVRDriverManager_001
{
	WOVR_ENTRY uint32_t GetDriverCount() const
	{
		return fns_IVRDriverManager::GetDriverCount();
	}

	WOVR_ENTRY uint32_t GetDriverName( vr::DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return fns_IVRDriverManager::GetDriverName(nDriver, pchValue, unBufferSize);
	}
};

IVRDriverManager* getIVRDriverManagerProxy_001()
{
	return (IVRDriverManager*) new proxy_IVRDriverManager_001();
}
