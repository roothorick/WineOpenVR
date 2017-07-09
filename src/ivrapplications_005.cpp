#include "ivrapplications.h"

class clone_IVRApplications_005
{
public:
	WOVR_ENTRY virtual EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary ) = 0;
	WOVR_ENTRY virtual EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) = 0;
	WOVR_ENTRY virtual bool IsApplicationInstalled( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationCount() = 0;
	WOVR_ENTRY virtual EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchApplication( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys ) = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual bool CancelApplicationLaunch( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationProcessId( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	WOVR_ENTRY virtual EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) = 0;
	WOVR_ENTRY virtual bool GetApplicationAutoLaunch( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationTransitionState GetTransitionState() = 0;
	WOVR_ENTRY virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;
	WOVR_ENTRY virtual bool IsQuitUserPromptRequested() = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory ) = 0;
	WOVR_ENTRY virtual uint32_t GetCurrentSceneProcessId() = 0;
};

class proxy_IVRApplications_005 : public clone_IVRApplications_005
{
public:
	WOVR_ENTRY EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary )
	{
		return fns_IVRApplications::AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
	}

	WOVR_ENTRY EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath )
	{
		return fns_IVRApplications::RemoveApplicationManifest(pchApplicationManifestFullPath);
	}

	WOVR_ENTRY bool IsApplicationInstalled( const char *pchAppKey )
	{
		return fns_IVRApplications::IsApplicationInstalled(pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationCount()
	{
		return fns_IVRApplications::GetApplicationCount();
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return fns_IVRApplications::GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return fns_IVRApplications::GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError LaunchApplication( const char *pchAppKey )
	{
		return fns_IVRApplications::LaunchApplication(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys )
	{
		return fns_IVRApplications::LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
	}

	WOVR_ENTRY EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey )
	{
		return fns_IVRApplications::LaunchDashboardOverlay(pchAppKey);
	}

	WOVR_ENTRY bool CancelApplicationLaunch( const char *pchAppKey )
	{
		return fns_IVRApplications::CancelApplicationLaunch(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey )
	{
		return fns_IVRApplications::IdentifyApplication(unProcessId, pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationProcessId( const char *pchAppKey )
	{
		return fns_IVRApplications::GetApplicationProcessId(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error )
	{
		return fns_IVRApplications::GetApplicationsErrorNameFromEnum(error);
	}

	WOVR_ENTRY uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError )
	{
		return fns_IVRApplications::GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
	}

	WOVR_ENTRY bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return fns_IVRApplications::GetApplicationPropertyBool(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return fns_IVRApplications::GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch )
	{
		return fns_IVRApplications::SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
	}

	WOVR_ENTRY bool GetApplicationAutoLaunch( const char *pchAppKey )
	{
		return fns_IVRApplications::GetApplicationAutoLaunch(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return fns_IVRApplications::GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationTransitionState GetTransitionState()
	{
		return fns_IVRApplications::GetTransitionState();
	}

	WOVR_ENTRY EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey )
	{
		return fns_IVRApplications::PerformApplicationPrelaunchCheck(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state )
	{
		return fns_IVRApplications::GetApplicationsTransitionStateNameFromEnum(state);
	}

	WOVR_ENTRY bool IsQuitUserPromptRequested()
	{
		return fns_IVRApplications::IsQuitUserPromptRequested();
	}

	WOVR_ENTRY EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory )
	{
		return fns_IVRApplications::LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
	}

	WOVR_ENTRY uint32_t GetCurrentSceneProcessId()
	{
		return fns_IVRApplications::GetCurrentSceneProcessId();
	}
};

// Declared in proxy_getters.h
IVRApplications* getIVRApplicationsProxy_005()
{
	return (IVRApplications*) new proxy_IVRApplications_005();
}
