#include "ivrsettings.h"

class clone_IVRSettings_002
{
public:
	WOVR_ENTRY virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;
	WOVR_ENTRY virtual bool Sync( bool bForce, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void RemoveSection( const char *pchSection, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
};

class proxy_IVRSettings_002 : public clone_IVRSettings_002
{
public:
	WOVR_ENTRY const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		return fns_IVRSettings::GetSettingsErrorNameFromEnum(eError);
	}

	WOVR_ENTRY bool Sync( bool bForce, EVRSettingsError *peError )
	{
		return fns_IVRSettings::Sync(bForce, peError);
	}

	WOVR_ENTRY void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		fns_IVRSettings::SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

	WOVR_ENTRY void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		fns_IVRSettings::SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

	WOVR_ENTRY void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		fns_IVRSettings::SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

	WOVR_ENTRY void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		fns_IVRSettings::SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

	WOVR_ENTRY bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return fns_IVRSettings::GetBool(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return fns_IVRSettings::GetInt32(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return fns_IVRSettings::GetFloat(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		fns_IVRSettings::GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}

	WOVR_ENTRY void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		fns_IVRSettings::RemoveSection(pchSection, peError);
		return;
	}

	WOVR_ENTRY void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		fns_IVRSettings::RemoveKeyInSection(pchSection, pchSettingsKey, peError);
		return;
	}
};

// Declared in proxy_getters.h
IVRSettings* getIVRSettingsProxy_002()
{
	return (IVRSettings*) new proxy_IVRSettings_002();
}
