#include "common.h"

// The wrappers for individual IVRApplications functions. The various ivrapplications_xxx.cpp arrange these into a
// proxy class matching their corresponding ABI version.

// TODO: This probably should be wrapped a little more intelligently, to give SteamVR wine-based shortcuts instead of
// the values given directly by the app itself.

namespace fns_IVRApplications
{
	inline EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary )
	{
		return VRApplications()->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
	}

	inline EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath )
	{
		return VRApplications()->RemoveApplicationManifest(pchApplicationManifestFullPath);
	}

	inline bool IsApplicationInstalled( const char *pchAppKey )
	{
		return VRApplications()->IsApplicationInstalled(pchAppKey);
	}

	inline uint32_t GetApplicationCount()
	{
		return VRApplications()->GetApplicationCount();
	}

	inline EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	inline EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	inline EVRApplicationError LaunchApplication( const char *pchAppKey )
	{
		return VRApplications()->LaunchApplication(pchAppKey);
	}

	inline EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys )
	{
		return VRApplications()->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
	}

	inline vr::EVRApplicationError LaunchApplicationFromMimeType( const char *pchMimeType, const char *pchArgs )
	{
		return VRApplications()->LaunchApplicationFromMimeType(pchMimeType, pchArgs);
	}

	inline EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey )
	{
		return VRApplications()->LaunchDashboardOverlay(pchAppKey);
	}

	inline bool CancelApplicationLaunch( const char *pchAppKey )
	{
		return VRApplications()->CancelApplicationLaunch(pchAppKey);
	}

	inline EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey )
	{
		return VRApplications()->IdentifyApplication(unProcessId, pchAppKey);
	}

	inline uint32_t GetApplicationProcessId( const char *pchAppKey )
	{
		return VRApplications()->GetApplicationProcessId(pchAppKey);
	}

	inline const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error )
	{
		return VRApplications()->GetApplicationsErrorNameFromEnum(error);
	}

	inline uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
	}

	inline bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
	}

	inline uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError )
	{
		return VRApplications()->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
	}

	inline EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch )
	{
		return VRApplications()->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
	}

	inline bool GetApplicationAutoLaunch( const char *pchAppKey )
	{
		return VRApplications()->GetApplicationAutoLaunch(pchAppKey);
	}

	inline EVRApplicationError SetDefaultApplicationForMimeType( const char *pchAppKey, const char *pchMimeType )
	{
		return VRApplications()->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType);
	}

	inline bool GetDefaultApplicationForMimeType( const char *pchMimeType, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen);
	}

	inline bool GetApplicationSupportedMimeTypes( const char *pchAppKey, char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer )
	{
		return VRApplications()->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer);
	}

	inline uint32_t GetApplicationsThatSupportMimeType( const char *pchMimeType, char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer )
	{
		return VRApplications()->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer);
	}

	inline uint32_t GetApplicationLaunchArguments( uint32_t unHandle, char *pchArgs, uint32_t unArgs )
	{
		return VRApplications()->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs);
	}

	inline EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen )
	{
		return VRApplications()->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
	}

	inline EVRApplicationTransitionState GetTransitionState()
	{
		return VRApplications()->GetTransitionState();
	}

	inline EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey )
	{
		return VRApplications()->PerformApplicationPrelaunchCheck(pchAppKey);
	}

	inline const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state )
	{
		return VRApplications()->GetApplicationsTransitionStateNameFromEnum(state);
	}

	inline bool IsQuitUserPromptRequested()
	{
		return VRApplications()->IsQuitUserPromptRequested();
	}

	inline EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory )
	{
		return VRApplications()->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
	}

	inline uint32_t GetCurrentSceneProcessId()
	{
		return VRApplications()->GetCurrentSceneProcessId();
	}
}
