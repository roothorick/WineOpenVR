#include "common.h"

class clone_IVRChaperoneSetup
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

class proxy_IVRChaperoneSetup : public clone_IVRChaperoneSetup
{
public:
	proxy_IVRChaperoneSetup(IVRChaperoneSetup* real) { realImpl = real; }

	WOVR_ENTRY bool CommitWorkingCopy( EChaperoneConfigFile configFile )
	{
		return realImpl->CommitWorkingCopy(configFile);
	}

	WOVR_ENTRY void RevertWorkingCopy()
	{
		realImpl->RevertWorkingCopy();
		return;
	}

	WOVR_ENTRY bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ )
	{
		return realImpl->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
	}

	WOVR_ENTRY bool GetWorkingPlayAreaRect( HmdQuad_t *rect )
	{
		return realImpl->GetWorkingPlayAreaRect(rect);
	}

	WOVR_ENTRY bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return realImpl->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose )
	{
		return realImpl->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY void SetWorkingPlayAreaSize( float sizeX, float sizeZ )
	{
		realImpl->SetWorkingPlayAreaSize(sizeX, sizeZ);
		return;
	}

	WOVR_ENTRY void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		realImpl->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
		return;
	}

	WOVR_ENTRY void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose )
	{
		realImpl->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
		return;
	}

	WOVR_ENTRY void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose )
	{
		realImpl->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
		return;
	}

	WOVR_ENTRY void ReloadFromDisk( EChaperoneConfigFile configFile )
	{
		realImpl->ReloadFromDisk(configFile);
		return;
	}

	WOVR_ENTRY bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose )
	{
		return realImpl->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
	}

	WOVR_ENTRY void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount )
	{
		realImpl->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
		return;
	}

	WOVR_ENTRY bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount )
	{
		return realImpl->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
	}

	WOVR_ENTRY bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount )
	{
		return realImpl->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
	}

	WOVR_ENTRY bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount )
	{
		return realImpl->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
	}

	WOVR_ENTRY bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength )
	{
		return realImpl->ExportLiveToBuffer(pBuffer, pnBufferLength);
	}

	WOVR_ENTRY bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags )
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
