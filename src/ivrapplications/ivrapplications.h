#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRApplications_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRApplications_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRApplicationsProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

// TODO: This probably should be wrapped a little more intelligently, to give SteamVR wine-based shortcuts instead of
// the values given directly by the app itself.

class CLONECLASS
{
public:
	WOVR_ENTRY virtual EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary ) = 0;
	WOVR_ENTRY virtual EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) = 0;
	WOVR_ENTRY virtual bool IsApplicationInstalled( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationCount() = 0;
	WOVR_ENTRY virtual EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchApplication( const char *pchAppKey ) = 0;
#if ABIVER >= 5
	WOVR_ENTRY virtual EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys ) = 0;
#endif
#if ABIVER >= 6
	WOVR_ENTRY virtual vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs ) = 0;
#endif
	WOVR_ENTRY virtual EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) = 0;
#if ABIVER >= 4
	WOVR_ENTRY virtual bool CancelApplicationLaunch( const char *pchAppKey ) = 0;
#endif
	WOVR_ENTRY virtual EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationProcessId( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) = 0;
	WOVR_ENTRY virtual bool GetApplicationAutoLaunch( const char *pchAppKey ) = 0;
#if ABIVER >= 6
	WOVR_ENTRY virtual EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType ) = 0;
	WOVR_ENTRY virtual bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs ) = 0;
#endif
	WOVR_ENTRY virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationTransitionState GetTransitionState() = 0;
	WOVR_ENTRY virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;
	WOVR_ENTRY virtual bool IsQuitUserPromptRequested() = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory ) = 0;
	WOVR_ENTRY virtual uint32_t GetCurrentSceneProcessId() = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
	WOVR_ENTRY EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary )
	{
		return VRApplications()->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
	}

	WOVR_ENTRY EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath )
	{
		return VRApplications()->RemoveApplicationManifest(pchApplicationManifestFullPath);
	}

	WOVR_ENTRY bool IsApplicationInstalled( const char *pchAppKey )
	{
		return VRApplications()->IsApplicationInstalled(pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationCount()
	{
		return VRApplications()->GetApplicationCount();
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError LaunchApplication( const char *pchAppKey )
	{
		return VRApplications()->LaunchApplication(pchAppKey);
	}

#if ABIVER >= 5
	WOVR_ENTRY EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys )
	{
		return VRApplications()->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
	}
#endif

#if ABIVER >= 6
	WOVR_ENTRY vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs )
	{
		return VRApplications()->LaunchApplicationFromMimeType(pchMimeType, pchArgs);
	}
#endif

	WOVR_ENTRY EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey )
	{
		return VRApplications()->LaunchDashboardOverlay(pchAppKey);
	}

#if ABIVER >= 4
	WOVR_ENTRY bool CancelApplicationLaunch( const char *pchAppKey )
	{
		return VRApplications()->CancelApplicationLaunch(pchAppKey);
	}
#endif

	WOVR_ENTRY EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey )
	{
		return VRApplications()->IdentifyApplication(unProcessId, pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationProcessId( const char *pchAppKey )
	{
		return VRApplications()->GetApplicationProcessId(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error )
	{
		return VRApplications()->GetApplicationsErrorNameFromEnum(error);
	}

	WOVR_ENTRY uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
	}

	WOVR_ENTRY bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch )
	{
		return VRApplications()->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
	}

	WOVR_ENTRY bool GetApplicationAutoLaunch( const char *pchAppKey )
	{
		return VRApplications()->GetApplicationAutoLaunch(pchAppKey);
	}

#if ABIVER >= 6
	WOVR_ENTRY EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType )
	{
		return VRApplications()->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType);
	}

	WOVR_ENTRY bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer )
	{
		return VRApplications()->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer);
	}

	WOVR_ENTRY uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer )
	{
		return VRApplications()->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer);
	}

	WOVR_ENTRY uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs )
	{
		return VRApplications()->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs);
	}
#endif

	WOVR_ENTRY EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationTransitionState GetTransitionState()
	{
		return VRApplications()->GetTransitionState();
	}

	WOVR_ENTRY EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey )
	{
		return VRApplications()->PerformApplicationPrelaunchCheck(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state )
	{
		return VRApplications()->GetApplicationsTransitionStateNameFromEnum(state);
	}

	WOVR_ENTRY bool IsQuitUserPromptRequested()
	{
		return VRApplications()->IsQuitUserPromptRequested();
	}

	WOVR_ENTRY EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory )
	{
		return VRApplications()->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
	}

	// DANGER: This method was added in 1.0.6 but ABI version was not increased!
	WOVR_ENTRY uint32_t GetCurrentSceneProcessId()
	{
		return VRApplications()->GetCurrentSceneProcessId();
	}
};

// Declared in proxy_getters.h
IVRApplications* GETTER ()
{
	return (IVRApplications*) new PROXYCLASS ();
}
