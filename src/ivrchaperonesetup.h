#include "common.h"

namespace fns_IVRChaperoneSetup
{
	inline bool CommitWorkingCopy( EChaperoneConfigFile configFile )
	{
		return VRChaperoneSetup()->CommitWorkingCopy(configFile);
	}

	inline void RevertWorkingCopy()
	{
		VRChaperoneSetup()->RevertWorkingCopy();
		return;
	}

	inline bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return VRChaperoneSetup()->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
	}

	inline bool GetWorkingPlayAreaRect( HmdQuad_t *rect )
	{
		return VRChaperoneSetup()->GetWorkingPlayAreaRect(rect);
	}

	inline bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	inline bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	inline bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	inline bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
	}

	inline void SetWorkingPlayAreaSize( float sizeX, float sizeZ )
	{
		VRChaperoneSetup()->SetWorkingPlayAreaSize(sizeX, sizeZ);
		return;
	}

	inline void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		VRChaperoneSetup()->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
		return;
	}

	inline void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose )
	{
		VRChaperoneSetup()->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
		return;
	}

	inline void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose )
	{
		VRChaperoneSetup()->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
		return;
	}

	inline void ReloadFromDisk( EChaperoneConfigFile configFile )
	{
		VRChaperoneSetup()->ReloadFromDisk(configFile);
		return;
	}

	inline bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return VRChaperoneSetup()->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	inline void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount )
	{
		VRChaperoneSetup()->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
		return;
	}

	inline bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount )
	{
		return VRChaperoneSetup()->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
	}

	inline bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		return VRChaperoneSetup()->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
	}

	inline bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return VRChaperoneSetup()->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	inline bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength )
	{
		return VRChaperoneSetup()->ExportLiveToBuffer(pBuffer, pnBufferLength);
	}

	inline bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags )
	{
		return VRChaperoneSetup()->ImportFromBufferToWorking(pBuffer, nImportFlags);
	}
}
