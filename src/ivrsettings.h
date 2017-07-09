#include "common.h"

// XXX: IVRSettings contains const static char arrays (i.e. C strings).
// I expect them to not be stored in the class object itself but instead treated as a constant, but this hasn't been
// verified.

namespace fns_IVRSettings
{
	inline const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		return VRSettings()->GetSettingsErrorNameFromEnum(eError);
	}

	inline bool Sync( bool bForce, EVRSettingsError *peError )
	{
		return VRSettings()->Sync(bForce, peError);
	}

	inline void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		VRSettings()->SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

	inline void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		VRSettings()->SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

	inline void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		VRSettings()->SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

	inline void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		VRSettings()->SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

	inline bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetBool(pchSection, pchSettingsKey, peError);
	}

	inline int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetInt32(pchSection, pchSettingsKey, peError);
	}

	inline float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetFloat(pchSection, pchSettingsKey, peError);
	}

	inline void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		VRSettings()->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}

	inline void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		VRSettings()->RemoveSection(pchSection, peError);
		return;
	}

	inline void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		VRSettings()->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
		return;
	}
}
