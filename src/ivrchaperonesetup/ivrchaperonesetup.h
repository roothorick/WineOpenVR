#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRChaperoneSetup_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRChaperoneSetup_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRChaperoneSetupProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

class CLONECLASS
{
public:
	WOVR_ENTRY virtual bool CommitWorkingCopy( EChaperoneConfigFile configFile ) = 0;
	WOVR_ENTRY virtual void RevertWorkingCopy() = 0;
	WOVR_ENTRY virtual bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ ) = 0;
	WOVR_ENTRY virtual bool GetWorkingPlayAreaRect( HmdQuad_t *rect ) = 0;
	WOVR_ENTRY virtual bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	WOVR_ENTRY virtual bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	WOVR_ENTRY virtual bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;
	WOVR_ENTRY virtual bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose ) = 0;
	WOVR_ENTRY virtual void SetWorkingPlayAreaSize( float sizeX, float sizeZ ) = 0;
	WOVR_ENTRY virtual void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) = 0;
	WOVR_ENTRY virtual void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose ) = 0;
	WOVR_ENTRY virtual void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose ) = 0;
	WOVR_ENTRY virtual void ReloadFromDisk( EChaperoneConfigFile configFile ) = 0;
	WOVR_ENTRY virtual bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;
	WOVR_ENTRY virtual void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount ) = 0;
	WOVR_ENTRY virtual bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount ) = 0;
	WOVR_ENTRY virtual bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) = 0;
	WOVR_ENTRY virtual bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	WOVR_ENTRY virtual bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength ) = 0;
	WOVR_ENTRY virtual bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
    WOVR_ENTRY bool CommitWorkingCopy( EChaperoneConfigFile configFile )
	{
		return VRChaperoneSetup()->CommitWorkingCopy(configFile);
	}

	WOVR_ENTRY void RevertWorkingCopy()
	{
		VRChaperoneSetup()->RevertWorkingCopy();
		return;
	}

	WOVR_ENTRY bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return VRChaperoneSetup()->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetWorkingPlayAreaRect( HmdQuad_t *rect )
	{
		return VRChaperoneSetup()->GetWorkingPlayAreaRect(rect);
	}

	WOVR_ENTRY bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY void SetWorkingPlayAreaSize( float sizeX, float sizeZ )
	{
		VRChaperoneSetup()->SetWorkingPlayAreaSize(sizeX, sizeZ);
		return;
	}

	WOVR_ENTRY void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		VRChaperoneSetup()->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
		return;
	}

	WOVR_ENTRY void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose )
	{
		VRChaperoneSetup()->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
		return;
	}

	WOVR_ENTRY void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose )
	{
		VRChaperoneSetup()->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
		return;
	}

	WOVR_ENTRY void ReloadFromDisk( EChaperoneConfigFile configFile )
	{
		VRChaperoneSetup()->ReloadFromDisk(configFile);
		return;
	}

	WOVR_ENTRY bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount )
	{
		VRChaperoneSetup()->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
		return;
	}

	WOVR_ENTRY bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount )
	{
		return VRChaperoneSetup()->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
	}

	WOVR_ENTRY bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		return VRChaperoneSetup()->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
	}

	WOVR_ENTRY bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength )
	{
		return VRChaperoneSetup()->ExportLiveToBuffer(pBuffer, pnBufferLength);
	}

	WOVR_ENTRY bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags )
	{
		return VRChaperoneSetup()->ImportFromBufferToWorking(pBuffer, nImportFlags);
	}
};

IVRChaperoneSetup* GETTER ()
{
	return (IVRChaperoneSetup*) new PROXYCLASS ();
}
