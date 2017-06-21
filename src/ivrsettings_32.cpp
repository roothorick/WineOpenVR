#include <cstdio>

// HACK: No idea where this should actually be defined
#define nullptr 0x0
#include "openvr.h"
using namespace vr;

#define THISCALL __attribute__((thiscall))

// XXX: IVRSettings contains const static char arrays (i.e. C strings).
// I expect them to not be stored in the class object itself but instead treated as a constant, but this hasn't been
// verified.

class clone_IVRSettings
{
public:
	THISCALL virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;
	THISCALL virtual bool Sync( bool bForce, EVRSettingsError *peError ) = 0;
	THISCALL virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError ) = 0;
	THISCALL virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError ) = 0;
	THISCALL virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError ) = 0;
	THISCALL virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError ) = 0;
	THISCALL virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	THISCALL virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	THISCALL virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	THISCALL virtual void RemoveSection( const char *pchSection, EVRSettingsError *peError ) = 0;
	THISCALL virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError ) = 0;
	THISCALL virtual void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
};

class proxy_IVRSettings : public clone_IVRSettings
{
public:
	proxy_IVRSettings(IVRSettings* real) { realImpl = real; }

	THISCALL const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		return realImpl->GetSettingsErrorNameFromEnum(eError);
	}

	THISCALL bool Sync( bool bForce, EVRSettingsError *peError )
	{
		return realImpl->Sync(bForce, peError);
	}

	THISCALL void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		realImpl->SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

	THISCALL void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		realImpl->SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

	THISCALL void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		realImpl->SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

	THISCALL void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		realImpl->SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

	THISCALL bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetBool(pchSection, pchSettingsKey, peError);
	}

	THISCALL int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetInt32(pchSection, pchSettingsKey, peError);
	}

	THISCALL float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return realImpl->GetFloat(pchSection, pchSettingsKey, peError);
	}

	THISCALL void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		realImpl->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}

	THISCALL void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		realImpl->RemoveSection(pchSection, peError);
		return;
	}

	THISCALL void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
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
