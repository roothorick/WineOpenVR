#include "common.h"

// TODO: This probably should be wrapped a little more intelligently, to give SteamVR wine-based shortcuts instead of
// the values given directly by the app itself.

class clone_IVRApplications
{
public:
	THISCALL virtual EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary ) = 0;
	THISCALL virtual EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) = 0;
	THISCALL virtual bool IsApplicationInstalled( const char *pchAppKey ) = 0;
	THISCALL virtual uint32_t GetApplicationCount() = 0;
	THISCALL virtual EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	THISCALL virtual EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	THISCALL virtual EVRApplicationError LaunchApplication( const char *pchAppKey ) = 0;
	THISCALL virtual EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys ) = 0;
	THISCALL virtual vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs ) = 0;
	THISCALL virtual EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) = 0;
	THISCALL virtual bool CancelApplicationLaunch( const char *pchAppKey ) = 0;
	THISCALL virtual EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) = 0;
	THISCALL virtual uint32_t GetApplicationProcessId( const char *pchAppKey ) = 0;
	THISCALL virtual const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) = 0;
	THISCALL virtual uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError ) = 0;
	THISCALL virtual bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	THISCALL virtual uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError ) = 0;
	THISCALL virtual EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) = 0;
	THISCALL virtual bool GetApplicationAutoLaunch( const char *pchAppKey ) = 0;
	THISCALL virtual EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType ) = 0;
	THISCALL virtual bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	THISCALL virtual bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer ) = 0;
	THISCALL virtual uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer ) = 0;
	THISCALL virtual uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs ) = 0;
	THISCALL virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;
	THISCALL virtual EVRApplicationTransitionState GetTransitionState() = 0;
	THISCALL virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;
	THISCALL virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;
	THISCALL virtual bool IsQuitUserPromptRequested() = 0;
	THISCALL virtual EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory ) = 0;
	THISCALL virtual uint32_t GetCurrentSceneProcessId() = 0;
};

class proxy_IVRApplications : public clone_IVRApplications
{
public:
	proxy_IVRApplications(IVRApplications* real) { realImpl = real; }

	THISCALL EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary )
	{
		return realImpl->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
	}

	THISCALL EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath )
	{
		return realImpl->RemoveApplicationManifest(pchApplicationManifestFullPath);
	}

	THISCALL bool IsApplicationInstalled( const char *pchAppKey )
	{
		return realImpl->IsApplicationInstalled(pchAppKey);
	}

	THISCALL uint32_t GetApplicationCount()
	{
		return realImpl->GetApplicationCount();
	}

	THISCALL EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	THISCALL EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	THISCALL EVRApplicationError LaunchApplication( const char *pchAppKey )
	{
		return realImpl->LaunchApplication(pchAppKey);
	}

	THISCALL EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys )
	{
		return realImpl->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
	}

	THISCALL vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs )
	{
		return realImpl->LaunchApplicationFromMimeType(pchMimeType, pchArgs);
	}

	THISCALL EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey )
	{
		return realImpl->LaunchDashboardOverlay(pchAppKey);
	}

	THISCALL bool CancelApplicationLaunch( const char *pchAppKey )
	{
		return realImpl->CancelApplicationLaunch(pchAppKey);
	}

	THISCALL EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey )
	{
		return realImpl->IdentifyApplication(unProcessId, pchAppKey);
	}

	THISCALL uint32_t GetApplicationProcessId( const char *pchAppKey )
	{
		return realImpl->GetApplicationProcessId(pchAppKey);
	}

	THISCALL const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error )
	{
		return realImpl->GetApplicationsErrorNameFromEnum(error);
	}

	THISCALL uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
	}

	THISCALL bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
	}

	THISCALL uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return realImpl->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
	}

	THISCALL EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch )
	{
		return realImpl->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
	}

	THISCALL bool GetApplicationAutoLaunch( const char *pchAppKey )
	{
		return realImpl->GetApplicationAutoLaunch(pchAppKey);
	}

	THISCALL EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType )
	{
		return realImpl->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType);
	}

	THISCALL bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	THISCALL bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer )
	{
		return realImpl->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer);
	}

	THISCALL uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer )
	{
		return realImpl->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer);
	}

	THISCALL uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs )
	{
		return realImpl->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs);
	}

	THISCALL EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return realImpl->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
	}

	THISCALL EVRApplicationTransitionState GetTransitionState()
	{
		return realImpl->GetTransitionState();
	}

	THISCALL EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey )
	{
		return realImpl->PerformApplicationPrelaunchCheck(pchAppKey);
	}

	THISCALL const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state )
	{
		return realImpl->GetApplicationsTransitionStateNameFromEnum(state);
	}

	THISCALL bool IsQuitUserPromptRequested()
	{
		return realImpl->IsQuitUserPromptRequested();
	}

	THISCALL EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory )
	{
		return realImpl->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
	}

	THISCALL uint32_t GetCurrentSceneProcessId()
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
