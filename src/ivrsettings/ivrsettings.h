#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRSettings_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRSettings_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRSettingsProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

// XXX: IVRSettings contains const static char arrays (i.e. C strings).
// I expect them to not be stored in the class object itself but instead treated as a constant, but this hasn't been
// verified.

class CLONECLASS
{
public:
	WOVR_ENTRY virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;
	WOVR_ENTRY virtual bool Sync( bool bForce, EVRSettingsError *peError ) = 0;
#if ABIVER < 2
	WOVR_ENTRY virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
#endif
	WOVR_ENTRY virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError ) = 0;
#if ABIVER < 2
	WOVR_ENTRY virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
#endif
	WOVR_ENTRY virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError ) = 0;
#if ABIVER < 2
	WOVR_ENTRY virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
#endif
	WOVR_ENTRY virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError ) = 0;
#if ABIVER < 2
	WOVR_ENTRY virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
#endif
	WOVR_ENTRY virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError ) = 0;
#if ABIVER >= 2
	WOVR_ENTRY virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError ) = 0;
#endif
	WOVR_ENTRY virtual void RemoveSection( const char *pchSection, EVRSettingsError *peError ) = 0;
	WOVR_ENTRY virtual void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
	{
		TRACE("");
		return VRSettings()->GetSettingsErrorNameFromEnum(eError);
	}

	WOVR_ENTRY bool Sync( bool bForce, EVRSettingsError *peError )
	{
		TRACE("");
		return VRSettings()->Sync(bForce, peError);
	}

#if ABIVER < 2
	WOVR_ENTRY bool GetBool( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError = nullptr )
	{
		TRACE("");
		return VRSettings()->GetBool(pchSection, pchSettingsKey, peError);
	}
#endif

	WOVR_ENTRY void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->SetBool(pchSection, pchSettingsKey, bValue, peError);
		return;
	}

#if ABIVER < 2
	WOVR_ENTRY int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError = nullptr )
	{
		TRACE("");
		return VRSettings()->GetInt32(pchSection, pchSettingsKey, peError);
	}
#endif

	WOVR_ENTRY void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->SetInt32(pchSection, pchSettingsKey, nValue, peError);
		return;
	}

#if ABIVER < 2
	WOVR_ENTRY float GetFloat( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError = nullptr )
	{
		TRACE("");
		return VRSettings()->GetFloat(pchSection, pchSettingsKey, peError);
	}
#endif

	WOVR_ENTRY void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->SetFloat(pchSection, pchSettingsKey, flValue, peError);
		return;
	}

#if ABIVER < 2
	WOVR_ENTRY void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}
#endif

	WOVR_ENTRY void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->SetString(pchSection, pchSettingsKey, pchValue, peError);
		return;
	}

#if ABIVER >= 2
	WOVR_ENTRY bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		TRACE("");
		return VRSettings()->GetBool(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		TRACE("");
		return VRSettings()->GetInt32(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		TRACE("");
		return VRSettings()->GetFloat(pchSection, pchSettingsKey, peError);
	}

	WOVR_ENTRY void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
		return;
	}
#endif

	WOVR_ENTRY void RemoveSection( const char *pchSection, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->RemoveSection(pchSection, peError);
		return;
	}

	WOVR_ENTRY void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError )
	{
		TRACE("");
		VRSettings()->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
		return;
	}
};

// Declared in proxy_getters.h
IVRSettings* GETTER ()
{
	return (IVRSettings*) new PROXYCLASS ();
}
