#include "common.h"

namespace fns_IVRDriverManager
{
	inline uint32_t GetDriverCount()
	{
		return VRDriverManager()->GetDriverCount();
	}

	inline uint32_t GetDriverName( vr::DriverId_t nDriver, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize )
	{
		return VRDriverManager()->GetDriverName(nDriver, pchValue, unBufferSize);
	}
}
