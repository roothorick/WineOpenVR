#include "common.h"

// TODO: This probably should be wrapped a little more intelligently, to give SteamVR wine-based shortcuts instead of
// the values given directly by the app itself.

class clone_IVRApplications
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
	WOVR_ENTRY virtual vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs ) = 0;
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
	WOVR_ENTRY virtual EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType ) = 0;
	WOVR_ENTRY virtual bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer ) = 0;
	WOVR_ENTRY virtual uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs ) = 0;
	WOVR_ENTRY virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	WOVR_ENTRY virtual EVRApplicationTransitionState GetTransitionState() = 0;
	WOVR_ENTRY virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;
	WOVR_ENTRY virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;
	WOVR_ENTRY virtual bool IsQuitUserPromptRequested() = 0;
	WOVR_ENTRY virtual EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory ) = 0;
	WOVR_ENTRY virtual uint32_t GetCurrentSceneProcessId() = 0;
};

class proxy_IVRApplications : public clone_IVRApplications
{
public:
	proxy_IVRApplications(IVRApplications* real) { realImpl = real; }

	WOVR_ENTRY EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary )
	{
		return realImpl->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
	}

	WOVR_ENTRY EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath )
	{
		return realImpl->RemoveApplicationManifest(pchApplicationManifestFullPath);
	}

	WOVR_ENTRY bool IsApplicationInstalled( const char *pchAppKey )
	{
		return realImpl->IsApplicationInstalled(pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationCount()
	{
		return realImpl->GetApplicationCount();
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationError LaunchApplication( const char *pchAppKey )
	{
		return realImpl->LaunchApplication(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys )
	{
		return realImpl->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
	}

	WOVR_ENTRY vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs )
	{
		return realImpl->LaunchApplicationFromMimeType(pchMimeType, pchArgs);
	}

	WOVR_ENTRY EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey )
	{
		return realImpl->LaunchDashboardOverlay(pchAppKey);
	}

	WOVR_ENTRY bool CancelApplicationLaunch( const char *pchAppKey )
	{
		return realImpl->CancelApplicationLaunch(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey )
	{
		return realImpl->IdentifyApplication(unProcessId, pchAppKey);
	}

	WOVR_ENTRY uint32_t GetApplicationProcessId( const char *pchAppKey )
	{
		return realImpl->GetApplicationProcessId(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error )
	{
		return realImpl->GetApplicationsErrorNameFromEnum(error);
	}

	WOVR_ENTRY uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
	}

	WOVR_ENTRY bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
	}

	WOVR_ENTRY EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch )
	{
		return realImpl->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
	}

	WOVR_ENTRY bool GetApplicationAutoLaunch( const char *pchAppKey )
	{
		return realImpl->GetApplicationAutoLaunch(pchAppKey);
	}

	WOVR_ENTRY EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType )
	{
		return realImpl->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType);
	}

	WOVR_ENTRY bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer )
	{
		return realImpl->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer);
	}

	WOVR_ENTRY uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer )
	{
		return realImpl->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer);
	}

	WOVR_ENTRY uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs )
	{
		return realImpl->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs);
	}

	WOVR_ENTRY EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
	}

	WOVR_ENTRY EVRApplicationTransitionState GetTransitionState()
	{
		return realImpl->GetTransitionState();
	}

	WOVR_ENTRY EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey )
	{
		return realImpl->PerformApplicationPrelaunchCheck(pchAppKey);
	}

	WOVR_ENTRY const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state )
	{
		return realImpl->GetApplicationsTransitionStateNameFromEnum(state);
	}

	WOVR_ENTRY bool IsQuitUserPromptRequested()
	{
		return realImpl->IsQuitUserPromptRequested();
	}

	WOVR_ENTRY EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory )
	{
		return realImpl->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
	}

	WOVR_ENTRY uint32_t GetCurrentSceneProcessId()
	{
		return realImpl->GetCurrentSceneProcessId();
	}

private:
	IVRApplications* realImpl;
};

// Declared in proxy_getters.h
IVRApplications* getIVRApplicationsProxy (IVRApplications* real)
{
	return (IVRApplications*) new proxy_IVRApplications(real);
}
