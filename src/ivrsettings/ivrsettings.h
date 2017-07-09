#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRSettings_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRSettings_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRSettingsProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

// XXX: IVRSettings contains const static char arrays (i.e. C strings).
// I expect them to not be stored in the class object itself but instead treated as a constant, but this hasn't been
// verified.

class CLONECLASS
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

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		return VRSettings()->GetSettingsErrorNameFromEnum(eError);
	}

	WOVR_ENTRY bool Sync( bool bForce, EVRSettingsError *peError )
	{
		return VRSettings()->Sync(bForce, peError);
	}

	WOVR_ENTRY void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		VRSettings()->SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

	WOVR_ENTRY void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		VRSettings()->SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

	WOVR_ENTRY void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		VRSettings()->SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

	WOVR_ENTRY void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		VRSettings()->SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

	WOVR_ENTRY bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetBool(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetInt32(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		return VRSettings()->GetFloat(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		VRSettings()->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}

	WOVR_ENTRY void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		VRSettings()->RemoveSection(pchSection, peError);
		return;
	}

	WOVR_ENTRY void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		VRSettings()->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
		return;
	}
};

// Declared in proxy_getters.h
IVRSettings* GETTER ()
{
	return (IVRSettings*) new PROXYCLASS ();
}
