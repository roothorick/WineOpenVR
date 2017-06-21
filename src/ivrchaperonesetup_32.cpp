#include "common.h"

class clone_IVRChaperoneSetup
{
public:
	THISCALL virtual bool CommitWorkingCopy( EChaperoneConfigFile configFile ) = 0;
	THISCALL virtual void RevertWorkingCopy() = 0;
	THISCALL virtual bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ ) = 0;
	THISCALL virtual bool GetWorkingPlayAreaRect( HmdQuad_t *rect ) = 0;
	THISCALL virtual bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	THISCALL virtual bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	THISCALL virtual bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;
	THISCALL virtual bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose ) = 0;
	THISCALL virtual void SetWorkingPlayAreaSize( float sizeX, float sizeZ ) = 0;
	THISCALL virtual void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) = 0;
	THISCALL virtual void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose ) = 0;
	THISCALL virtual void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose ) = 0;
	THISCALL virtual void ReloadFromDisk( EChaperoneConfigFile configFile ) = 0;
	THISCALL virtual bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) = 0;
	THISCALL virtual void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount ) = 0;
	THISCALL virtual bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount ) = 0;
	THISCALL virtual bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) = 0;
	THISCALL virtual bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;
	THISCALL virtual bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength ) = 0;
	THISCALL virtual bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags ) = 0;
};

class proxy_IVRChaperoneSetup : public clone_IVRChaperoneSetup
{
public:
	proxy_IVRChaperoneSetup(IVRChaperoneSetup* real) { realImpl = real; }

	THISCALL bool CommitWorkingCopy( EChaperoneConfigFile configFile )
	{
		return realImpl->CommitWorkingCopy(configFile);
	}

	THISCALL void RevertWorkingCopy()
	{
		realImpl->RevertWorkingCopy();
		return;
	}

	THISCALL bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return realImpl->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
	}

	THISCALL bool GetWorkingPlayAreaRect( HmdQuad_t *rect )
	{
		return realImpl->GetWorkingPlayAreaRect(rect);
	}

	THISCALL bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	THISCALL bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	THISCALL bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return realImpl->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	THISCALL bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose )
	{
		return realImpl->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
	}

	THISCALL void SetWorkingPlayAreaSize( float sizeX, float sizeZ )
	{
		realImpl->SetWorkingPlayAreaSize(sizeX, sizeZ);
		return;
	}

	THISCALL void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		realImpl->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
		return;
	}

	THISCALL void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose )
	{
		realImpl->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
		return;
	}

	THISCALL void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose )
	{
		realImpl->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
		return;
	}

	THISCALL void ReloadFromDisk( EChaperoneConfigFile configFile )
	{
		realImpl->ReloadFromDisk(configFile);
		return;
	}

	THISCALL bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return realImpl->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	THISCALL void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount )
	{
		realImpl->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
		return;
	}

	THISCALL bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount )
	{
		return realImpl->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
	}

	THISCALL bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		return realImpl->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
	}

	THISCALL bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	THISCALL bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength )
	{
		return realImpl->ExportLiveToBuffer(pBuffer, pnBufferLength);
	}

	THISCALL bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags )
	{
		return realImpl->ImportFromBufferToWorking(pBuffer, nImportFlags);
	}

private:
	IVRChaperoneSetup* realImpl;
};

IVRChaperoneSetup* getIVRChaperoneSetupProxy(IVRChaperoneSetup* real)
{
	return (IVRChaperoneSetup*) new proxy_IVRChaperoneSetup(real);
}
