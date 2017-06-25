#include "common.h"

// XXX: IVRSettings contains const static char arrays (i.e. C strings).
// I expect them to not be stored in the class object itself but instead treated as a constant, but this hasn't been
// verified.

class clone_IVRSettings
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

class proxy_IVRSettings : public clone_IVRSettings
{
public:
	proxy_IVRSettings(IVRSettings* real) { realImpl = real; }

	WOVR_ENTRY const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		return realImpl->GetSettingsErrorNameFromEnum(eError);
	}

	WOVR_ENTRY bool Sync( bool bForce, EVRSettingsError *peError )
	{
		return realImpl->Sync(bForce, peError);
	}

	WOVR_ENTRY void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		realImpl->SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

	WOVR_ENTRY void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		realImpl->SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

	WOVR_ENTRY void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		realImpl->SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

	WOVR_ENTRY void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		realImpl->SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

	WOVR_ENTRY bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetBool(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetInt32(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetFloat(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		realImpl->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}

	WOVR_ENTRY void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		realImpl->RemoveSection(pchSection, peError);
		return;
	}

	WOVR_ENTRY void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		realImpl->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
		return;
	}

private:
	IVRSettings* realImpl;
};

// Declared in proxy_getters.h
IVRSettings* getIVRSettingsProxy(IVRSettings* real)
{
	return (IVRSettings*) new proxy_IVRSettings(real);
}
